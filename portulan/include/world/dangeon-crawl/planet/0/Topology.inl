namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {


inline Topology::Topology() {
    /* - @todo fine ...
    static_assert( ((GRID_SX == GRID_SY) && (GRID_SY == GRID_SZ)),
        "@todo extend Работаем только с равными сторонами (с сеткой в виде куба)." );
    static_assert( ((GRID_SX % 3) == 0), "Размер стороны по X должен быть кратен 3." );
    static_assert( ((GRID_SY % 3) == 0), "Размер стороны по Y должен быть кратен 3." );
    static_assert( ((GRID_SZ % 3) == 0), "Размер стороны по Z должен быть кратен 3." );
    */

    // # Все структуры инициализируем нулями. Удобно для отладки.

    std::memset( &mTopology.aboutPlanet, 0, sizeof( mTopology.aboutPlanet ) );
    std::memset( &mTopology.aboutComponent, 0, sizeof( mTopology.aboutComponent ) );
    std::memset( &mTopology.aboutLiving, 0, sizeof( mTopology.aboutLiving ) );
    std::memset( &mTopology.aboutIlluminanceSource, 0, sizeof( mTopology.aboutIlluminanceSource ) );

    mTopology.component.content =
        new componentCell_t[ COMPONENT_GRID * COMPONENT_GRID * COMPONENT_GRID ];
    std::memset( mTopology.component.content, 0, sizeof( *mTopology.component.content ) );

    mTopology.temperature.content =
        new temperatureCell_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    std::memset( mTopology.temperature.content, 0, sizeof( *mTopology.temperature.content ) );

    mTopology.surfaceTemperature.content =
        new surfaceTemperatureCell_t[ SURFACE_TEMPERATURE_GRID * SURFACE_TEMPERATURE_GRID * SURFACE_TEMPERATURE_GRID ];
    std::memset( mTopology.surfaceTemperature.content, 0, sizeof( *mTopology.surfaceTemperature.content ) );

    mTopology.rainfall.content =
        new rainfallCell_t[ RAINFALL_GRID * RAINFALL_GRID * RAINFALL_GRID ];
    std::memset( mTopology.rainfall.content, 0, sizeof( *mTopology.rainfall.content ) );

    mTopology.drainage.content =
        new drainageCell_t[ DRAINAGE_GRID * DRAINAGE_GRID * DRAINAGE_GRID ];
    std::memset( mTopology.drainage.content, 0, sizeof( *mTopology.drainage.content ) );

    mTopology.landscape.content =
        new landscapeCell_t[ LANDSCAPE_GRID * LANDSCAPE_GRID * LANDSCAPE_GRID ];
    std::memset( mTopology.landscape.content, 0, sizeof( *mTopology.landscape.content ) );

    mTopology.illuminance.content =
        new illuminanceCell_t[ ILLUMINANCE_GRID * ILLUMINANCE_GRID * ILLUMINANCE_GRID ];
    std::memset( mTopology.illuminance.content, 0, sizeof( *mTopology.illuminance.content ) );

    mTopology.biome.content =
        new biomeCell_t[ BIOME_GRID * BIOME_GRID * BIOME_GRID ];
    std::memset( mTopology.biome.content, 0, sizeof( *mTopology.biome.content ) );

    mTopology.living.content =
        new livingCell_t[ LIVING_GRID * LIVING_GRID * LIVING_GRID ];
    std::memset( mTopology.living.content, 0, sizeof( *mTopology.living.content ) );
}



inline Topology::~Topology() {
    delete[] mTopology.component.content;
    delete[] mTopology.temperature.content;
    delete[] mTopology.surfaceTemperature.content;
    delete[] mTopology.rainfall.content;
    delete[] mTopology.drainage.content;
    delete[] mTopology.landscape.content;
    delete[] mTopology.illuminance.content;
    delete[] mTopology.biome.content;
    delete[] mTopology.living.content;
}





inline topology_t const& Topology::topology() const {
    return mTopology;
}



inline topology_t& Topology::topology() {
    return mTopology;
}


                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan









namespace std {

#if 0

inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::Topology& tp ) {
    const auto aboutPlanet = tp.aboutPlanet();

    const auto component = tp.component();
    const auto aboutComponent = tp.aboutComponent();

    auto pressure = tp.pressure();
    static const size_t PG = portulan::planet::structure::PRESSURE_GRID;
    const std::pair< float*, float* > pminmax = std::minmax_element(
        pressure.average,
        pressure.average + PG * PG * PG
    );

    auto temperature = tp.temperature();
    static const size_t TG = portulan::planet::structure::TEMPERATURE_GRID;
    const std::pair< float*, float* > tminmax = std::minmax_element(
        temperature.average,
        temperature.average + TG * TG * TG
    );

    auto precipitations = tp.precipitations();
    static const size_t RG = portulan::planet::structure::PRECIPITATIONS_GRID;
    const std::pair< float*, float* > rminmax = std::minmax_element(
        precipitations.rainfall,
        precipitations.rainfall + RG * RG * RG
    );

    const auto aboutSurfaceVoid = tp.aboutSurfaceVoid();

    const auto living = tp.living();
    const auto aboutLiving = tp.aboutLiving();

    out <<
        "Память, занимаемая топологией планеты\n" <<
            "\ttopology " << sizeof( tp ) / 1024 / 1024 << " Мб\n" <<
                "\t\taboutPlanet " <<
                    sizeof( aboutPlanet ) / 1024 << " Кб\n" <<
                "\t\tcomponent " << sizeof( component ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tcontent " <<
                        portulan::planet::structure::COMPONENT_GRID << "x " <<
                        portulan::planet::structure::COMPONENT_CELL << "u " <<
                        sizeof( component.content ) / 1024 / 1024 << " Мб\n" <<
                "\t\taboutComponent " <<
                    portulan::planet::structure::COMPONENT_COUNT << "u " <<
                    sizeof( aboutComponent ) / 1024 << " Кб\n" <<
                "\t\tliving " << sizeof( living ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tcontent " <<
                        portulan::planet::structure::LIVING_GRID << "x " <<
                        portulan::planet::structure::LIVING_CELL << "u " <<
                        sizeof( living.content ) / 1024 / 1024 << " Мб\n" <<
                "\t\taboutLiving " <<
                    portulan::planet::structure::LIVING_COUNT << "u " <<
                    sizeof( aboutLiving ) / 1024 << " Кб\n" <<
                "\t\tpressure " <<
                    portulan::planet::structure::PRESSURE_GRID << "x " <<
                    sizeof( pressure ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\taverage [ " << *pminmax.first << "; " << *pminmax.second << " ]\n" <<
                "\t\ttemperature " <<
                    portulan::planet::structure::TEMPERATURE_GRID << "x " <<
                    sizeof( temperature ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\taverage [ " << *tminmax.first << "; " << *tminmax.second << " ]\n" <<
                "\t\tprecipitations " <<
                    portulan::planet::structure::PRECIPITATIONS_GRID << "x " <<
                    sizeof( precipitations ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\trainfall [ " << *rminmax.first << "; " << *rminmax.second << " ]\n" <<
                "\t\tsurfaceVoid " <<
                    portulan::planet::structure::SURFACE_VOID_GRID << "x " <<
                    sizeof( aboutSurfaceVoid ) / 1024 /1024 << " Мб\n" <<
    std::endl;

    return out;
}





inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::structure::euid_t& uid ) {
    out << static_cast< unsigned int >( uid.group ) <<
        "." << static_cast< unsigned int >( uid.code );
    return out;
}





inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::structure::eportion_t& ep ) {
    out << ep.code << ":" << ep.count;
    return out;
}





inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t& sp ) {
    typedef portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t  specimen_t;
    typedef portulan::planet::eportion_t  eportion_t;

    out <<
        "lifetime " << sp.lifetime <<
        "\nmass ";
    static const size_t LC = portulan::planet::Topology< 81, 81, 81 >::LC_count;
    typelib::print< cl_float, LC >( std::cout, sp.mass );

    out <<
        "\nimmunity " << sp.immunity <<
        "\nchemicalComposition ";
    typelib::print< eportion_t, specimen_t::CHEMICAL_COMPOSITION >( std::cout, sp.chemicalComposition );

    out << "\nmetabolism";
    //typelib::print< specimen_t::metabolism_t, LC >( std::cout, sp.metabolism );
    typedef portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t  specimen_t;
    typedef portulan::planet::eportion_t  eportion_t;
    for (size_t i = 0; i < LC; ++i) {
        out << "\n\tLife cycle " << i;
        const auto mt = sp.metabolism[ i ];

        out << "\n\tch.need ";
        typelib::print< eportion_t, specimen_t::CHEMICAL_NEED >( std::cout, mt.chemical.need );

        out << "\n\tch.waste ";
        typelib::print< eportion_t, specimen_t::CHEMICAL_WASTE >( std::cout, mt.chemical.waste );

        out << "\n\ten.need ";
        typelib::print< cl_float, specimen_t::ENERGY_NEED >( std::cout, mt.energy.need );

        out << "\n\ten.waste ";
        typelib::print< cl_float, specimen_t::ENERGY_WASTE >( std::cout, mt.energy.waste );
    }

    out << "\nsurvivor" <<
        "\n\tenvironment ";
    typelib::print< size_t, specimen_t::survivor_t::ENVIRONMENT_SURVIVOR >( std::cout, sp.survivor.environment );
    const auto& tr = sp.survivor.temperatureRange;
    out << "\n\ttemperatureRange.comfort [ " << tr.comfort.min << ", " << tr.comfort.max << " ]";
    out << "\n\ttemperatureRange.limit [ " << tr.limit.min << ", " << tr.limit.max << " ]";

    out << std::endl;

    return out;
}




inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t::metabolism_t& mt ) {
    typedef portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t  specimen_t;
    typedef portulan::planet::eportion_t  eportion_t;

    out << "chemical.need ";
    typelib::print< eportion_t, specimen_t::CHEMICAL_NEED >( std::cout, mt.chemical.need );

    out << "\nchemical.waste ";
    typelib::print< eportion_t, specimen_t::CHEMICAL_WASTE >( std::cout, mt.chemical.waste );

    out << "\nenergy.need ";
    typelib::print< cl_float, specimen_t::ENERGY_NEED >( std::cout, mt.energy.need );

    out << "\nenergy.waste ";
    typelib::print< cl_float, specimen_t::ENERGY_WASTE >( std::cout, mt.energy.waste );

    return out;
}

#endif


} // std
