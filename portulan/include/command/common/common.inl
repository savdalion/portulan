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
    typename Portulan3D< SX, SY, SZ, Number >& map
) const {

    std::cout << "ok! " << this->sign << std::endl;


    auto& topology = map.topology();
    // @todo ...

}

#endif





template< size_t SX, size_t SY, size_t SZ, typename Number >
inline void elevationMap(
    typename Portulan3D< SX, SY, SZ, Number >& map, 
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
    const auto sl = typelib::SignBitMap< SX, SY, SZ >::signLayerRaw_t( sign, bm.raw );
    topology.present = sl;
}






template< size_t SX, size_t SY, size_t SZ, typename Number >
void flood(
    typename Portulan3D< SX, SY, SZ, Number >& map,
    const std::string& sign,
    const std::string& source,
    size_t gridHMin,
    size_t gridHMax
) {
#if 0
// - @todo

    // �������� ��������, ����������� ��������� ���������.
    // �������� ����������� ������ � �� ������, � ������� ���
    // ������ �������.

    auto& topology = map.topology();
    const auto pm = topology.present.presence();
    if ( pm.full() ) {
        // ����� ��������� ��������? ������ ����������� � ��� ������ �������� ������.
        return;
    }

    // �������� �������� �����������
    @todo ...

    // ��� ���������� ������ ����� - ����������� "����� �����������"
    const typelib::InverseFilterMapContent  inverse;
    inverse( pm );

    typedef BitMap< SX, SY, SZ >  bm_t;
    bm_t r;
    size_t i = ipm.get_first();
    do {
        // ���������, ��� ��� ������ ��� ��������� ���������
        const typelib::coordInt_t c =
            Portulan3D< SX, SY, SZ, Number >::bitLayer_t::ci( i );

        // �������� �� �����������
        if ( typelib::between( c.z, gridHMin, gridHMax ) ) {
            // �������� �� 
            if ( 
            r.set( c );
        }

        i = ipm.get_next( i );

    } while (i != 0);

    const auto sl = typelib::SignBitMap< SX, SY, SZ >::signLayerRaw_t( sign, r.raw );
    topology.present = sl;

#endif
}




    } // command
} // portulan
