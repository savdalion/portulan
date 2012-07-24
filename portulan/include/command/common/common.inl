namespace portulan {
    namespace command {


#if 0
// - �������� �� ����� ������� ������. ��. ����.
template< size_t SX, size_t SY, size_t SZ, typename Number >
inline elevationMap< SX, SY, SZ, Number >::elevationMap(
    const std::string& sign,
    const std::string& source,
    double scaleXY, double hMin, double hMax
) :
    sign( sign ),
    source( source),
    scaleXY( scaleXY ),
    hMin( hMin ),
    hMax( hMax )
{
}




template< size_t SX, size_t SY, size_t SZ, typename Number >
inline void elevationMap< SX, SY, SZ, Number >::operator()(
    typename Portulan< SX, SY, SZ, Number >& map
) const {

    std::cout << "ok! " << this->sign << std::endl;


    auto& topology = map.topology();
    // @todo ...

}

#endif





template< size_t SX, size_t SY, size_t SZ >
inline void elevationMap(
    typename Portulan< SX, SY, SZ >& map,
    const std::string& sign,
    const std::string& source,
    double scaleXY,
    double hMin,
    double hMax,
    const typelib::coordInt_t& shiftArea,
    const typelib::psizeInt_t& sizeArea
) {
    // ��� �������� ����� ����� ������������� �������� Silhouette
    const siu::shape::ElevationMap< SX, SY, SZ >  elm( source, scaleXY, hMin, hMax, true, shiftArea, sizeArea );
    const siu::Shaper< SX, SY, SZ >  shaper( elm );

    auto& topology = map.topology();
    const auto bm = shaper.draw();
    const auto sl = typelib::SignBitMap< SX, SY, SZ >::signLayerRaw_t( sign, bm.raw() );
    topology.presence() = sl;
}






template< size_t SX, size_t SY, size_t SZ >
inline void flood(
    typename Portulan< SX, SY, SZ >& map,
    const std::string& sign,
    const std::string& source,
    int gridHMin,
    int gridHMax
) {
    assert( (gridHMin <= gridHMax)
        && "������� ���������� ������ ���� ������ � ������� �������-�������." );

    // �������� ��������, ����������� ��������� ���������.
    // �������� ����������� ������ � �� ������, � ������� ���
    // ������ �������.

    auto& topology = map.topology();
    const auto pm = topology.presence();

    typedef typelib::BitMap< SX, SY, SZ >  bm_t;
    bm_t filledMap;
    for (auto str = pm.raw().cbegin(); str != pm.raw().cend(); ++str) {
        filledMap |= bm_t( str->second );
    }

    if ( filledMap.full() ) {
        // ����� ��������� ��������? ������ ����������� � ��� ������ �������� ������.
        return;
    }


    // ��������� �������� ��� ���������� ��������� "sign"

    // @use http://graphicsmagick.org/Magick++/Image.html

    Magick::InitializeMagick( nullptr );

    // ������ ����������� �����, �������� �������� � ������� ����� � ������
    // ���������� ������� � ��������, ������ ������� �� ������� �����

    // ������� @todo ���������� �� Warning C4252, ����������.
    // @source http://www.windows-api.com/microsoft/VC-Language/30952961/a-solution-to-warning-c4251--class-needs-to-have-dllinterface.aspx
    struct Wrapper {
        Magick::Image image;
        Magick::Color color;
    };
    Wrapper wrapper;

    size_t imageSizeWidth = 0;
    size_t imageSizeHeight = 0;
    try {
        wrapper.image.read( source.c_str() );
        imageSizeWidth  = wrapper.image.size().width();
        imageSizeHeight = wrapper.image.size().height();

    } catch( const Magick::Exception& ex ) {
        const auto exWhat = ex.what();
        //std::cout << "Caught exception: " << ex.what() << std::endl;
        assert( false && "�� ������� ��������� ����� ��� ���������� ������." );
        return;
    }
    


    // ����������� (��� ��� �����) ������ ���������� � ������� �����
    const Magick::Geometry zoomGeometry( SX, SY );
    
    try {
        wrapper.image.zoom( zoomGeometry );

        // ��������� � ����������� ���������
        // @source http://imagemagick.org/Magick++/Image.html
        wrapper.image.quantizeColorSpace( Magick::GRAYColorspace );
        wrapper.image.quantizeColors( 1 );
        wrapper.image.quantize();

#ifdef _DEBUG
        // @test
        const std::string file = "!flood-bitmask.png";
        wrapper.image.write( file );
#endif

    } catch( const Magick::Exception& ex ) {
        const auto exWhat = ex.what();
        assert( false && "�� ������� ��������� ����� ��� ���������� ������." );
        return;
    }

    // ������ ����������� (� ����� ������) ������
    imageSizeWidth  = wrapper.image.size().width();
    imageSizeHeight = wrapper.image.size().height();



    // �������� �� ����������� ����������� � � ����������� �� �����
    // ��������� �����
    bm_t floodMap;
    for (size_t j = 0; j < imageSizeHeight; ++j) {
        for (size_t i = 0; i < imageSizeWidth; ++i) {
            // ����� ������������ �����-����� ������� ���������: R == G == B
            wrapper.color = wrapper.image.pixelColor( i, j );
            const bool v = (wrapper.color.redQuantum() != 0);
            if ( v ) {
                const int x = static_cast< int >( i ) - bm_t::maxCoord().x;
                const int y = static_cast< int >( j ) - bm_t::maxCoord().y;
                for (int z = gridHMin; z <= gridHMax; ++z) {
                    floodMap.set( x, y, z );
                }
            }

        } // for (int i

    } // for (int j

#ifdef _DEBUG
        // @test
        const size_t nFloodBefore = floodMap.count();
#endif


    // ��������� �������� ������ ���������� ���� ��������� ��� �����
    // ��������� �����, ������������� � "map" � �������������� � "floodMap"
    const typelib::InverseFilterMap inverse;
    inverse( filledMap );
    floodMap &= filledMap;

#ifdef _DEBUG
        // @test
        const size_t nFloodAfter = floodMap.count();
        const size_t nFilled = filledMap.count();
#endif


    // ��������� / ��������� ���� "sign"
    const auto sl = typelib::SignBitMap< SX, SY, SZ >::signLayerRaw_t( sign, floodMap.raw() );
    topology.presence() = sl;
}






template< size_t SX, size_t SY, size_t SZ >
inline void temperature(
    typename Portulan< SX, SY, SZ >& map,
    const fnTemperature_t& fn
) {
    typedef typename Portulan< SX, SY, SZ >::topology_t::numberLayer_t  nl_t;

    auto& topology = map.topology();

    topology.temperature() = 0.0f;

    for (int z = nl_t::minCoord().z; z <= nl_t::maxCoord().z; ++z) {
        for (int y = nl_t::minCoord().y; y <= nl_t::maxCoord().y; ++y) {
            for (int x = nl_t::minCoord().x; x <= nl_t::maxCoord().x; ++x) {
                const typelib::coordInt_t c( x, y, z );
                const float t = fn( c );
                topology.temperature().set( c, t );
            }
        }
    }
}



    } // command
} // portulan
