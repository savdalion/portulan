namespace portulan {
    namespace planet {


inline Topology::Topology() {
    /* - @todo fine ...
    static_assert( ((GRID_SX == GRID_SY) && (GRID_SY == GRID_SZ)),
        "@todo extend Работаем только с равными сторонами (с сеткой в виде куба)." );
    static_assert( ((GRID_SX % 3) == 0), "Размер стороны по X должен быть кратен 3." );
    static_assert( ((GRID_SY % 3) == 0), "Размер стороны по Y должен быть кратен 3." );
    static_assert( ((GRID_SZ % 3) == 0), "Размер стороны по Z должен быть кратен 3." );
    */

    namespace pd = set::dungeoncrawl;

    mTopology.component.content =
        new pd::componentCell_t[ pd::COMPONENT_GRID * pd::COMPONENT_GRID * pd::COMPONENT_GRID ];

    mTopology.temperature.content =
        new pd::temperatureCell_t[ pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID ];

    mTopology.surfaceTemperature.content =
        new pd::surfaceTemperatureCell_t[ pd::SURFACE_TEMPERATURE_GRID * pd::SURFACE_TEMPERATURE_GRID * pd::SURFACE_TEMPERATURE_GRID ];

    mTopology.rainfall.content =
        new pd::rainfallCell_t[ pd::RAINFALL_GRID * pd::RAINFALL_GRID * pd::RAINFALL_GRID ];

    mTopology.drainage.content =
        new pd::drainageCell_t[ pd::DRAINAGE_GRID * pd::DRAINAGE_GRID * pd::DRAINAGE_GRID ];

    mTopology.landscape.content =
        new pd::landscapeCell_t[ pd::LANDSCAPE_GRID * pd::LANDSCAPE_GRID * pd::LANDSCAPE_GRID ];

    mTopology.biome.content =
        new pd::biomeCell_t[ pd::BIOME_GRID * pd::BIOME_GRID * pd::BIOME_GRID ];

    mTopology.living.content =
        new pd::livingCell_t[ pd::LIVING_GRID * pd::LIVING_GRID * pd::LIVING_GRID ];
}



inline Topology::~Topology() {
    delete[] mTopology.component.content;
    delete[] mTopology.temperature.content;
    delete[] mTopology.surfaceTemperature.content;
    delete[] mTopology.rainfall.content;
    delete[] mTopology.drainage.content;
    delete[] mTopology.landscape.content;
    delete[] mTopology.biome.content;
    delete[] mTopology.living.content;
}





inline set::topology_t const& Topology::topology() const {
    return mTopology;
}



inline set::topology_t& Topology::topology() {
    return mTopology;
}



    } // planet
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
