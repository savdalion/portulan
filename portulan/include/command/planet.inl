namespace portulan {
    namespace command {
        namespace planet {

template< size_t SX, size_t SY, size_t SZ >
inline void atmosphere(
    typename portulan::planet::Topology< SX, SY, SZ >::atmosphere_t&  map,
    double mass,
    double innerRadius,
    double depth,
    const std::vector< double >& chemicalSubstance
) {
    assert( (mass >= 0.0f)
        && "Масса атмосферы должна быть положительной." );
    assert( (innerRadius > 0.0f)
        && "Внутренний радиус атмосферы должен быть указан." );
    assert( (depth > 0.0f)
        && "Глубина атмосферы должна быть указана." );

    const size_t CS = portulan::planet::Topology< SX, SY, SZ >::CHEMICAL_SUBSTANCE;

    assert( (CS >= chemicalSubstance.size())
        && "Кол-во хим. веществ для атмосферы превышает допустимое." );
    const cl_float verifySum =
        std::accumulate( chemicalSubstance.cbegin(), chemicalSubstance.cend(), 0.0f );
    assert( ( typelib::equal( verifySum, 1.0f ) || typelib::equal( verifySum, 0.0f ) )
        && "Сумма частей хим. веществ атмосферы должна быть 1.0 или отсутствовать." );

    // Для создания сферического обруча атмосферы воспользуемся проектом Silhouette

    // 1. Построим биткарту "наличия атмосферы".

    // радиус области планеты, включая атмосферу, км
    const double allRadius = innerRadius + depth;

    const siu::shape::Sphere< SX, SY, SZ >  is( innerRadius, true, innerRadius / allRadius );
    const siu::Shaper< SX, SY, SZ >  innerSphere( is );
    const auto bmInnerSphere = innerSphere.draw();

    const siu::shape::Sphere< SX, SY, SZ >  os( allRadius, true, 1.0 );
    const siu::Shaper< SX, SY, SZ >  outerSphere( os );
    const auto bmOuterSphere = outerSphere.draw();

    // атмосфера заполняет собой всю область
    const auto bm = bmOuterSphere ^ bmInnerSphere;

    // @test
    const size_t n = bm.count();


    // 2. По созданной биткарте сформируем "область атмосферы" согласно
    //    заданной структуре.
    map.mass = static_cast< cl_float >( mass );
    map.innerRadius = static_cast< cl_float >( innerRadius * 1000.0 );
    map.depth = static_cast< cl_float >( depth * 1000.0 );

    /* - Не оставляем мусор в ячейках без атмосферы. Заменено. См. ниже.
    size_t i = bm.first();
    do {
        // наличие атмосферы в ячейке == наличие всего набора хим. элементов
        // в этой ячейке
        // @todo extend Распределять хим. элементы в зависимости от высоты.
        map.content[ i ] = chemicalSubstance;

        i = bm.next( i );

    } while (i != 0);
    */

    static const size_t AG = portulan::planet::Topology< SX, SY, SZ >::ATMOSPHERE_GRID;
    for (size_t i = 0; i < AG * AG * AG; ++i) {
        const bool present = bm.test( i );
        if ( present ) {
            //std::copy( chemicalSubstance.cbegin(),  chemicalSubstance.cend(),  map.content[i] );
            copyFill( map.content[i], CS, chemicalSubstance );

        } else {
            // заполняем нулями
            std::fill_n( map.content[i], CS, 0.0f );
        }

    } // for (size_t i = 0; i < AG * AG * AG; ++i)


    // @todo Давление и направление ветров.
    static const size_t PAG = portulan::planet::Topology< SX, SY, SZ >::PRESSURE_ATMOSPHERE_GRID;
    std::fill_n( map.pressure,  PAG * PAG * PAG,  0.0f );

    static const size_t WAG = portulan::planet::Topology< SX, SY, SZ >::WIND_ATMOSPHERE_GRID;
    std::fill_n( map.wind,  WAG * WAG * WAG,  0.0f );

}






template< size_t SX, size_t SY, size_t SZ >
inline void crust(
    typename portulan::planet::Topology< SX, SY, SZ >::crust_t&  map,
    double mass,
    double innerRadius,
    double depth,
    const std::vector< double >& chemicalSubstance
) {
    assert( (mass >= 0.0f)
        && "Масса планетарной коры должна быть положительной." );
    assert( (innerRadius > 0.0f)
        && "Внутренний радиус планетарной коры должен быть указан." );
    assert( (depth > 0.0f)
        && "Глубина планетарной коры должна быть указана." );

    const size_t CS = portulan::planet::Topology< SX, SY, SZ >::CHEMICAL_SUBSTANCE;

    assert( (CS >= chemicalSubstance.size())
        && "Кол-во хим. веществ для планетарной коры превышает допустимое." );
    const cl_float verifySum =
        std::accumulate( chemicalSubstance.cbegin(), chemicalSubstance.cend(), 0.0f );
    assert( ( typelib::equal( verifySum, 1.0f ) || typelib::equal( verifySum, 0.0f ) )
        && "Сумма частей хим. веществ планетарной коры должна быть 1.0 или отсутствовать." );

    // Для создания сферического обруча планетарной коры воспользуемся
    // проектом Silhouette

    // 1. Построим биткарту "наличия планетарной коры".

    // радиус области планеты, включая кору, км
    const double allRadius = innerRadius + depth;

    const siu::shape::Sphere< SX, SY, SZ >  is( innerRadius, true, innerRadius / allRadius );
    const siu::Shaper< SX, SY, SZ >  innerSphere( is );
    const auto bmInnerSphere = innerSphere.draw();

    const siu::shape::Sphere< SX, SY, SZ >  os( allRadius, true, 1.0 );
    const siu::Shaper< SX, SY, SZ >  outerSphere( os );
    const auto bmOuterSphere = outerSphere.draw();

    // планетарная кора заполняет собой всю область
    const auto bm = bmOuterSphere ^ bmInnerSphere;

    // @test
    const size_t n = bm.count();


    // 2. По созданной биткарте сформируем "область планетарной коры"
    //    согласно заданной структуре.
    map.mass = static_cast< cl_float >( mass );
    map.innerRadius = static_cast< cl_float >( innerRadius * 1000.0 );
    map.depth = static_cast< cl_float >( depth * 1000.0 );

    static const size_t CG = portulan::planet::Topology< SX, SY, SZ >::CRUST_GRID;
    for (size_t i = 0; i < CG * CG * CG; ++i) {
        const bool present = bm.test( i );
        if ( present ) {
            copyFill( map.content[i], CS, chemicalSubstance );

        } else {
            // заполняем нулями
            std::fill_n( map.content[i], CS, 0.0f );
        }

    } // for (size_t i = 0; i < CG * CG * CG; ++i)


    // @todo Поверхность.

}






template< size_t SX, size_t SY, size_t SZ >
inline void metabolism(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::metabolism_t  metabolism[],
    const std::vector< double >&  chemicalNeed,
    const std::vector< double >&  chemicalWaste,
    const std::vector< double >&  energyNeed,
    const std::vector< double >&  energyWaste,
    double lifetime,
    double massBurn,
    double massDie
) {
    const size_t CN = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::CHEMICAL_NEED;
    assert( (CN >= chemicalNeed.size())
        && "Кол-во хим. веществ превышает допустимое." );

    const size_t CW = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::CHEMICAL_WASTE;
    assert( (CW >= chemicalWaste.size())
        && "Кол-во хим. веществ превышает допустимое." );

    const size_t EN = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::ENERGY_NEED;
    assert( (EN >= energyNeed.size())
        && "Кол-во хим. веществ превышает допустимое." );

    const size_t EW = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::ENERGY_WASTE;
    assert( (EW >= energyWaste.size())
        && "Кол-во хим. веществ превышает допустимое." );

    const size_t LIFETIME = static_cast< size_t >( boost::math::round( lifetime ) );
    assert( (LIFETIME >= 0)
        && "Время жизни особи должно быть не менее 1/2 пульса." );

    assert( (massBurn >= 0.0f)
        && "Масса новорожденной особи должна быть положительной." );
    assert( (massDie >= 0.0f)
        && "Масса старой особи должна быть положительной." );

    const double deltaMass = (massDie - massBurn) / static_cast< double >( LIFETIME );
    for (size_t pulse = 0; pulse <= LIFETIME; ++pulse) {
        const double mass = massBurn + static_cast< double >( pulse ) * deltaMass;
        copyFill( metabolism[ pulse ].chemical.need,   CN,  chemicalNeed,   mass );
        copyFill( metabolism[ pulse ].chemical.waste,  CW,  chemicalWaste,  mass );
        copyFill( metabolism[ pulse ].energy.need,     EN,  energyNeed,     mass );
        copyFill( metabolism[ pulse ].energy.waste,    EW,  energyWaste,    mass );
    }

    // неиспользуемые пульсы заполняем нулями
    // @todo optimize bad Можно нулями не заполнять.
    static const std::vector< double >  EMPTY;
    for (size_t pulse = LIFETIME + 1; pulse < portulan::planet::Topology< SX, SY, SZ >::LIFE_CYCLE; ++pulse) {
        copyFill( metabolism[ pulse ].chemical.need,   CN,  EMPTY );
        copyFill( metabolism[ pulse ].chemical.waste,  CW,  EMPTY );
        copyFill( metabolism[ pulse ].energy.need,     EN,  EMPTY );
        copyFill( metabolism[ pulse ].energy.waste,    EW,  EMPTY );
    }
}





template< size_t SX, size_t SY, size_t SZ >
inline void survivor(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t&  survivor,
    const std::vector< size_t >&  environment,
    const std::pair< double, double >&  comfortTemperature,
    const std::pair< double, double >&  limitTemperature
) {
    // @todo fine Проверка 'environment'.

    assert( (comfortTemperature.first <= comfortTemperature.second)
        && "Температура комфорта должна декларироваться диапазоном вида \"меньше:больше\"." );
    assert( (limitTemperature.first <= limitTemperature.second)
        && "Предельная температура выживания должна декларироваться диапазоном вида \"меньше:больше\"." );
    assert( ( (comfortTemperature.first >= limitTemperature.first) && (comfortTemperature.second <= limitTemperature.second) )
        && "Температура комфорта должна лежать внутри предельной температуры выживания." );

    // температуры комфорта / выживания одинаковы для всех возрастов особи
    static const size_t LC = portulan::planet::Topology< SX, SY, SZ >::LIFE_CYCLE;
    for (size_t pulse = 0; pulse < LC; ++pulse) {
        survivor.temperatureRange[ pulse ].comfort.min = comfortTemperature.first;
        survivor.temperatureRange[ pulse ].comfort.max = comfortTemperature.second;
        survivor.temperatureRange[ pulse ].limit.min = limitTemperature.first;
        survivor.temperatureRange[ pulse ].limit.max = limitTemperature.second;
    }
}





template< size_t SX, size_t SY, size_t SZ >
inline void specimen(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&  specimen,
    double lifetime,
    double massBurn,
    double massDie,
    const std::vector< double >&  chemicalComposition,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::metabolism_t  metabolism[],
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t&  survivor
) {
    const size_t LIFETIME = static_cast< size_t >( boost::math::round( lifetime ) );
    assert( (LIFETIME >= 0)
        && "Время жизни особи должно быть не менее 1/2 пульса." );

    assert( (massBurn >= 0.0f)
        && "Масса новорожденной особи должна быть положительной." );
    assert( (massDie >= 0.0f)
        && "Масса старой особи должна быть положительной." );

    const size_t CC = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::CHEMICAL_COMPOSITION;
    assert( (CC >= chemicalComposition.size())
        && "Кол-во составляющих особь хим. веществ превышает допустимое." );

    specimen.lifetime = static_cast< cl_float >( lifetime );

    const double deltaMass = (massDie - massBurn) / static_cast< double >( LIFETIME );
    for (size_t pulse = 0; pulse <= LIFETIME; ++pulse) {
        specimen.mass[ pulse ] = deltaMass * static_cast< double >( pulse );
    }

    // неиспользуемые пульсы заполняем нулями
    // @todo optimize bad Можно нулями не заполнять.
    static const size_t LC = portulan::planet::Topology< SX, SY, SZ >::LIFE_CYCLE;
    for (size_t pulse = LIFETIME + 1; pulse < LC; ++pulse) {
        specimen.mass[ pulse ] = 0.0f;
    }

    copyFill( specimen.chemicalComposition,  CC,  chemicalComposition );

    std::copy( metabolism,  metabolism + LC,  specimen.metabolism );

    specimen.survivor = survivor;
}





template< size_t SX, size_t SY, size_t SZ >
inline void living(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t&  living,
    size_t uid,
    const boost::function< std::tuple< double, double >(
        size_t pulse,
        const typelib::coord_t&,
        const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&
    ) >&  fnLiving,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&  specimen
) {
    // 1. Добавляем информацию об особи.
    living.specimen[ uid ] = specimen;

    // 2. Проходим по всем ареалам живых организмов в области планеты и
    //    заполняем их кол-вом из 'fnLiving'.
    static const size_t LG =
        portulan::planet::Topology< SX, SY, SZ >::LIVING_GRID;
    typedef typelib::StaticMapContent3D< LG, LG, LG >  sm_t;
    for (int z = sm_t::minCoord().z; z <= sm_t::maxCoord().z; ++z) {
        for (int y = sm_t::minCoord().y; y <= sm_t::maxCoord().y; ++y) {
            for (int x = sm_t::minCoord().x; x <= sm_t::maxCoord().x; ++x) {
                const typelib::coordInt_t c( x, y, z );
                const size_t i = sm_t::ic( x, y, z );
                for (size_t pulse = 0; pulse < portulan::planet::Topology< SX, SY, SZ >::LIFE_CYCLE; ++pulse) {
                    const auto count = fnLiving( pulse, c, specimen );
                    living.content[ i ][ uid ].healthy[ pulse ] =
                        static_cast< cl_float >( std::get< 0 >( count ) );
                    living.content[ i ][ uid ].sick[ pulse ] =
                        static_cast< cl_float >( std::get< 1 >( count ) );
                }

            } // for (int x
        } // for (int y
    } // for (int z
}





template< size_t SX, size_t SY, size_t SZ >
inline void temperature(
    typename portulan::planet::Topology< SX, SY, SZ >::temperature_t&  temperature,
    const boost::function< double(
        const typelib::coord_t&,
        double radiusPlanet,
        double radiusAtmosphere
    ) >&  fnTemperature,
    double radiusPlanet,
    double radiusAtmosphere
) {
    // Проходим по всем ячейкам температуры в области планеты и
    // заполняем их градусами из 'fnTemperature'.
    static const size_t TG =
        portulan::planet::Topology< SX, SY, SZ >::TEMPERATURE_GRID;
    typedef typelib::StaticMapContent3D< TG, TG, TG >  sm_t;
    for (int z = sm_t::minCoord().z; z <= sm_t::maxCoord().z; ++z) {
        for (int y = sm_t::minCoord().y; y <= sm_t::maxCoord().y; ++y) {
            for (int x = sm_t::minCoord().x; x <= sm_t::maxCoord().x; ++x) {
                const typelib::coordInt_t c( x, y, z );
                const auto t = fnTemperature( c, radiusPlanet, radiusAtmosphere );
                const size_t i = sm_t::ic( x, y, z );
                temperature.content[ i ] = static_cast< cl_float >( t );

            } // for (int x
        } // for (int y
    } // for (int z
}







template< size_t SX, size_t SY, size_t SZ >
inline void planet(
    typename portulan::planet::Topology< SX, SY, SZ >&  map,
    const typename portulan::planet::Topology< SX, SY, SZ >::atmosphere_t&  atmosphere,
    const typename portulan::planet::Topology< SX, SY, SZ >::crust_t&  crust,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t&  living
) {
    map.atmosphere() = atmosphere;
    map.crust() = crust;
    map.living() = living;
}








template < typename D, typename S >
inline void copyFill(
    D dst[],
    size_t N,
    const std::vector< S >&  src,
    S k
) {
    auto itrSrc = src.cbegin();
    auto itrDst = dst;
	for ( ; itrSrc != src.cend(); ++itrSrc, ++itrDst) {
		*itrDst = static_cast< D >( (*itrSrc) * k );
    }
    const size_t filled = src.size();
    // дозаполняем хвост нулями
    std::fill_n( dst + filled,  N - filled,  0.0f );
}


        } // planet
    } // command
} // portulan
