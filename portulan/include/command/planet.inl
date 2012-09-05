namespace portulan {
    namespace command {
        namespace planet {

template< size_t SX, size_t SY, size_t SZ >
inline void atmosphere(
    typename portulan::planet::Topology< SX, SY, SZ >::atmosphere_t&  map,
    double mass,
    double innerRadius,
    double depth,
    const std::map< int, double >&  chemicalSubstance
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
    const double verifySum =
        std::accumulate( chemicalSubstance.cbegin(),  chemicalSubstance.cend(),  0.0,
            [] ( double currentSum,  const std::pair< int, double >& v ) -> double {
                return currentSum + v.second;
        } );
    assert( ( typelib::equal( verifySum, 1.0 ) || typelib::equal( verifySum, 0.0 ) )
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
    static const std::map< int, double > EMPTY = boost::assign::map_list_of( 0, 0.0 );
    for (size_t i = 0; i < AG * AG * AG; ++i) {
        const bool present = bm.test( i );
        if ( present ) {
            //std::copy( chemicalSubstance.cbegin(),  chemicalSubstance.cend(),  map.content[i] );
            copyFill( map.content[i],  CS,  portulan::planet::GE_COMPONENT,  chemicalSubstance,  1 );

        } else {
            // заполняем нулями
            copyFill( map.content[i],  CS,  portulan::planet::GE_COMPONENT,  EMPTY,  1 );
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
    const std::map< int, double >&  chemicalSubstance
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
    const double verifySum =
        std::accumulate( chemicalSubstance.cbegin(),  chemicalSubstance.cend(),  0.0,
            [] ( double currentSum,  const std::pair< int, double >& v ) -> double {
                return currentSum + v.second;
        } );
    assert( ( typelib::equal( verifySum, 1.0 ) || typelib::equal( verifySum, 0.0 ) )
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
    const std::map< int, double > EMPTY = boost::assign::map_list_of( 0, 0.0 );
    for (size_t i = 0; i < CG * CG * CG; ++i) {
        const bool present = bm.test( i );
        if ( present ) {
            copyFill( map.content[i],  CS,  portulan::planet::GE_COMPONENT,  chemicalSubstance,  1 );

        } else {
            // заполняем нулями
            //std::fill_n( map.content[i], CS, 0.0f );
            copyFill( map.content[i],  CS,  portulan::planet::GE_COMPONENT,  EMPTY,  1 );
        }

    } // for (size_t i = 0; i < CG * CG * CG; ++i)


    // @todo Поверхность.
    static const size_t SCG = portulan::planet::Topology< SX, SY, SZ >::SURFACE_CRUST_GRID;
    portulan::planet::Topology< SX, SY, SZ >::crust_t::structSurface_t  plane;
    plane.depth = 0.0f;
    plane.height = 0.0f;
    plane.jamb.drop = 0.0f;
    plane.jamb.distance = 0.0f;
    std::fill_n( map.surface,  SCG * SCG * SCG,  plane );

}






template< size_t SX, size_t SY, size_t SZ >
inline void metabolism(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::metabolism_t  metabolism[],
    const std::map< int, double >&  chemicalNeed,
    const std::map< int, double >&  chemicalWaste,
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
        && "Кол-во потребляемых энергий превышает допустимое." );

    const size_t EW = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::ENERGY_WASTE;
    assert( (EW >= energyWaste.size())
        && "Кол-во излучаемых энергий превышает допустимое." );

    const size_t LIFETIME = static_cast< size_t >( boost::math::round( lifetime ) );
    assert( (LIFETIME >= 0)
        && "Время жизни особи должно быть не менее 1/2 пульса." );

    assert( (massBurn >= 0.0f)
        && "Масса новорожденной особи должна быть положительной." );
    assert( (massDie >= 0.0f)
        && "Масса старой особи должна быть положительной." );

    static const auto GEC = portulan::planet::GE_COMPONENT;
    const double deltaMass = (massDie - massBurn) / static_cast< double >( LIFETIME );
    for (size_t pulse = 0; pulse <= LIFETIME; ++pulse) {
        const double mass = massBurn + static_cast< double >( pulse ) * deltaMass;
        copyFill( metabolism[ pulse ].chemical.need,   CN,  GEC,  chemicalNeed,   mass );
        copyFill( metabolism[ pulse ].chemical.waste,  CW,  GEC,  chemicalWaste,  mass );
        copyFill( metabolism[ pulse ].energy.need,     EN,  energyNeed,     mass );
        copyFill( metabolism[ pulse ].energy.waste,    EW,  energyWaste,    mass );
    }

    // неиспользуемые пульсы заполняем нулями
    // @todo optimize bad Можно нулями не заполнять.
    static const std::map< int, double >  CHEMICAL_EMPTY;
    static const std::vector< double >    ENERGY_EMPTY;
    for (size_t pulse = LIFETIME + 1; pulse < portulan::planet::Topology< SX, SY, SZ >::LIFE_CYCLE; ++pulse) {
        copyFill( metabolism[ pulse ].chemical.need,   CN,  GEC,  CHEMICAL_EMPTY,  1 );
        copyFill( metabolism[ pulse ].chemical.waste,  CW,  GEC,  CHEMICAL_EMPTY,  1 );
        copyFill( metabolism[ pulse ].energy.need,     EN,  ENERGY_EMPTY,  1 );
        copyFill( metabolism[ pulse ].energy.waste,    EW,  ENERGY_EMPTY,  1 );
    }
}





template< size_t SX, size_t SY, size_t SZ >
inline void survivor(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t&  survivor,
    const std::vector< size_t >&  environment,
    const std::pair< double, double >&  comfortTemperature,
    const std::pair< double, double >&  limitTemperature
) {
    assert( (comfortTemperature.first <= comfortTemperature.second)
        && "Температура комфорта должна декларироваться диапазоном вида \"меньше:больше\"." );
    assert( (limitTemperature.first <= limitTemperature.second)
        && "Предельная температура выживания должна декларироваться диапазоном вида \"меньше:больше\"." );
    assert( ( (comfortTemperature.first >= limitTemperature.first) && (comfortTemperature.second <= limitTemperature.second) )
        && "Температура комфорта должна лежать внутри предельной температуры выживания." );

    // @todo fine Проверка 'environment'.
    const size_t ES = portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t::ENVIRONMENT_SURVIVOR;
    copyFill( survivor.environment,  ES,  environment,  1 );

    // температуры комфорта / выживания одинаковы для всех возрастов особи
    survivor.temperatureRange.comfort.min = comfortTemperature.first;
    survivor.temperatureRange.comfort.max = comfortTemperature.second;
    survivor.temperatureRange.limit.min = limitTemperature.first;
    survivor.temperatureRange.limit.max = limitTemperature.second;
}





template< size_t SX, size_t SY, size_t SZ >
inline void specimen(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&  specimen,
    double lifetime,
    double massBurn,
    double massDie,
    double immunity,
    const std::map< int, double >&  chemicalComposition,
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
    specimen.immunity = static_cast< cl_float >( immunity );

    const double deltaMass = (massDie - massBurn) / static_cast< double >( LIFETIME );
    // @copy LIFE_CYCLE
    //     0    Эмбрионы особей, семена.
    //     1    Дети, ростки.
    //     2    Взрослые.
    //     3    Старики.
    //     4    Мёртвые особи - тела, скелеты.
    //     5    Бессмертные особи.
    for (size_t pulse = 0; pulse <= 3; ++pulse) {
        specimen.mass[ pulse ] = deltaMass * static_cast< double >( pulse + 1 );
    }
    specimen.mass[ 4 ] = specimen.mass[ 3 ] * 0.9;
    specimen.mass[ 5 ] = specimen.mass[ 3 ] * 1.1;

    copyFill( specimen.chemicalComposition,  CC,  portulan::planet::GE_LIVING,  chemicalComposition, 1 );

    static const size_t LC = portulan::planet::Topology< SX, SY, SZ >::LIFE_CYCLE;
    std::copy( metabolism,  metabolism + LC,  specimen.metabolism );

    specimen.survivor = survivor;
}





template< size_t SX, size_t SY, size_t SZ >
inline void living(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t&  living,
    const size_t uidCode,
    const boost::function< double(
        size_t pulse,
        const typelib::coord_t&,
        const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&
    ) >&  fnLiving,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&  specimen
) {
    portulan::planet::euid_t uid;
    uid.group = portulan::planet::GE_LIVING;
    uid.code = static_cast< cl_uchar >( uidCode );

    // Добавляем информацию об особи.
    living.specimen[ uid.code ] = specimen;

    // Проходим по всем ареалам живых организмов в области планеты и
    // заполняем их кол-вом из 'fnLiving'.
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
                    living.content[ i ][ uid.code ][ pulse ] = static_cast< cl_float >( count );
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
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t&  living,
    const typename portulan::planet::Topology< SX, SY, SZ >::temperature_t&  temperature,
    const typename portulan::planet::Topology< SX, SY, SZ >::precipitations_t&  precipitations
) {
    map.atmosphere() = atmosphere;
    map.crust() = crust;
    map.living() = living;
    map.temperature() = temperature;
    map.precipitations() = precipitations;
}








template < typename S >
inline void copyFill(
    portulan::planet::eportion_t  dst[],
    size_t n,
    portulan::planet::GROUP_ELEMENT  egroup,
    const std::map< int, S >&  src,
    double k
) {
    auto itrSrc = src.cbegin();
    auto itrDst = dst;
	for ( ; itrSrc != src.cend(); ++itrSrc, ++itrDst) {
        itrDst->uid.group = static_cast< cl_uchar >( egroup );
        itrDst->uid.code = static_cast< cl_uchar >( itrSrc->first );
		itrDst->count = static_cast< cl_float >( itrSrc->second * k );
    }

    // дозаполняем хвост неопределёнными элементами и нулями
	for (size_t i = 0; i < n; ++i, ++itrDst) {
        itrDst->uid.group = 0;
        itrDst->uid.code = 0;
		itrDst->count = 0.0;
    }

    /* @test
	for (size_t i = 0; i < n; ++i) {
        std::cout << static_cast< int >( dst[i].uid.group ) <<
            ":" << static_cast< int >( dst[i].uid.code ) <<
            " " << dst[i].count <<
        std::endl;
    }
    */
}




template < typename D, typename S >
inline void copyFill(
    D dst[],
    size_t n,
    const std::vector< S >&  src,
    double k
) {
    auto itrSrc = src.cbegin();
    auto itrDst = dst;
	for ( ; itrSrc != src.cend(); ++itrSrc, ++itrDst) {
        *itrDst = static_cast< D >( (*itrSrc) * k );
    }

    // дозаполняем хвост неопределёнными элементами и нулями
	for (size_t i = 0; i < n; ++i, ++itrDst) {
        *itrDst = static_cast< D >( 0 );
    }

    /* @test
	for (size_t i = 0; i < n; ++i) {
        std::cout << dst[i] << std::endl;
    }
    */
}


        } // planet
    } // command
} // portulan
