namespace portulan {
    namespace command {


#if 0
// - «аменено на более простые методы. —м. ниже.
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





template< size_t SX, size_t SY, size_t SZ >
inline void elevationMap(
    typename Portulan3D< SX, SY, SZ >& map,
    const std::string& sign,
    const std::string& source,
    double scaleXY,
    double hMin,
    double hMax,
    const typelib::coordInt_t& shiftArea,
    const typelib::psizeInt_t& sizeArea
) {
    // ƒл€ создани€ карты высот воспользуемс€ проектом Silhouette
    const siu::shape::ElevationMap< SX, SY, SZ >  elm( source, scaleXY, hMin, hMax, true, shiftArea, sizeArea );
    const siu::Shaper< SX, SY, SZ >  shaper( elm );

    auto& topology = map.topology();
    const auto bm = shaper.draw();
    const auto sl = typelib::SignBitMap< SX, SY, SZ >::signLayerRaw_t( sign, bm.raw );
    topology.presence = sl;
}






template< size_t SX, size_t SY, size_t SZ >
inline void flood(
    typename Portulan3D< SX, SY, SZ >& map,
    const std::string& sign,
    const std::string& source,
    size_t gridHMin,
    size_t gridHMax
) {
#if 0
// - @todo

    // —оздадим биткарту, заполненную указанным веществом.
    // ¬ещество добавл€етс€ только в те €чейки, в которых нет
    // других веществ.

    auto& topology = map.topology();
    const auto pm = topology.presence.presence();
    if ( pm.full() ) {
        // объЄм полностью заполнен? нечего затапливать и нет смысла смотреть дальше.
        return;
    }

    // получаем биткарту поверхности
    @todo ...

    // нас интересуют пустые места - инвертируем "карту присутстви€"
    const typelib::InverseFilterMapContent  inverse;
    inverse( pm );

    typedef BitMap< SX, SY, SZ >  bm_t;
    bm_t r;
    size_t i = ipm.get_first();
    do {
        // провер€ем, что эту €чейку нас попросили заполнить
        const typelib::coordInt_t c =
            Portulan3D< SX, SY, SZ, Number >::signBitLayer_t::ci( i );

        // проверка по координатам
        if ( typelib::between( c.z, gridHMin, gridHMax ) ) {
            // проверка по 
            if ( 
            r.set( c );
        }

        i = ipm.get_next( i );

    } while (i != 0);

    const auto sl = typelib::SignBitMap< SX, SY, SZ >::signLayerRaw_t( sign, r.raw );
    topology.presence = sl;

#endif
}






template< size_t SX, size_t SY, size_t SZ >
inline void temperature(
    typename Portulan3D< SX, SY, SZ >& map,
    const fnTemperature_t& fn
) {
    typedef typename Portulan3D< SX, SY, SZ >::topology_t::numberLayer_t  nl_t;

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
