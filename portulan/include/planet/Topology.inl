namespace portulan {
    namespace planet {


template< size_t SX, size_t SY, size_t SZ >
inline Topology< SX, SY, SZ >::Topology() {
    static_assert( ((SX == SY) && (SY == SZ)),
        "@todo extend Работаем только с равными сторонами (с сеткой в виде куба)." );
    static_assert( ((SX % 3) == 0), "Размер стороны по X должен быть кратен 3." );
    static_assert( ((SY % 3) == 0), "Размер стороны по Y должен быть кратен 3." );
    static_assert( ((SZ % 3) == 0), "Размер стороны по Z должен быть кратен 3." );
}



template< size_t SX, size_t SY, size_t SZ >
inline Topology< SX, SY, SZ >::~Topology() {    
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::atmosphere_t const& Topology< SX, SY, SZ >::atmosphere() const {
    return mAtmosphere;
}



template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::atmosphere_t& Topology< SX, SY, SZ >::atmosphere() {
    return mAtmosphere;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::crust_t const& Topology< SX, SY, SZ >::crust() const {
    return mCrust;
}



template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::crust_t& Topology< SX, SY, SZ >::crust() {
    return mCrust;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::living_t const& Topology< SX, SY, SZ >::living() const {
    return mLiving;
}



template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::living_t& Topology< SX, SY, SZ >::living() {
    return mLiving;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::component_t const& Topology< SX, SY, SZ >::component() const {
    return mComponent;
}



template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::component_t& Topology< SX, SY, SZ >::component() {
    return mComponent;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::temperature_t const& Topology< SX, SY, SZ >::temperature() const {
    return mTemperature;
}



template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::temperature_t& Topology< SX, SY, SZ >::temperature() {
    return mTemperature;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::precipitations_t const& Topology< SX, SY, SZ >::precipitations() const {
    return mPrecipitations;
}



template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::precipitations_t& Topology< SX, SY, SZ >::precipitations() {
    return mPrecipitations;
}



    } // planet
} // portulan









namespace std {


template< size_t SX, size_t SY, size_t SZ >
inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::Topology< SX, SY, SZ >& tp ) {
    const auto atmosphere = tp.atmosphere();
    const auto crust = tp.crust();
    const auto living = tp.living();
    const auto component = tp.component();

    auto temperature = tp.temperature();
    static const size_t TG =
        portulan::planet::Topology< SX, SY, SZ >::TEMPERATURE_GRID;
    const std::pair< float*, float* > tminmax = std::minmax_element(
        temperature.content,
        temperature.content + TG * TG * TG
    );

    auto precipitations = tp.precipitations();
    static const size_t PG =
        portulan::planet::Topology< SX, SY, SZ >::PRECIPITATIONS_GRID;
    const std::pair< float*, float* > pminmax = std::minmax_element(
        precipitations.content,
        precipitations.content + PG * PG * PG
    );

    static const size_t AG =
        portulan::planet::Topology< SX, SY, SZ >::ATMOSPHERE_GRID;
    out <<
        "Память, занимаемая топологией планеты\n" <<
            "\ttopology " << sizeof( tp ) / 1024 / 1024 << " Мб\n" <<
                "\t\tatmosphere " << sizeof( atmosphere ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tcontent " <<
                        portulan::planet::Topology< SX, SY, SZ >::ATMOSPHERE_GRID << "x " <<
                        sizeof( atmosphere.content ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tpressure " <<
                        portulan::planet::Topology< SX, SY, SZ >::PRESSURE_ATMOSPHERE_GRID << "x " <<
                        sizeof( atmosphere.pressure ) / 1024 << " Кб\n" <<
                    "\t\t\twind " <<
                        portulan::planet::Topology< SX, SY, SZ >::WIND_ATMOSPHERE_GRID << "x " <<
                        sizeof( atmosphere.wind ) / 1024 << " Кб\n" <<
                "\t\tcrust " <<
                    portulan::planet::Topology< SX, SY, SZ >::CRUST_GRID << "x " <<
                    sizeof( crust ) / 1024 / 1024 << " Мб\n" <<
                "\t\tliving " << sizeof( living ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tcontent " <<
                        portulan::planet::Topology< SX, SY, SZ >::LIVING_GRID << "x " <<
                        sizeof( living.content ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tspecimen " <<
                        portulan::planet::Topology< SX, SY, SZ >::SPECIMEN_COUNT << "u " <<
                        sizeof( living.specimen ) / 1024 << " Кб\n" <<
                "\t\tcomponent " << sizeof( component ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\tcontent " <<
                        portulan::planet::Topology< SX, SY, SZ >::COMPONENT_GRID << "x " <<
                        sizeof( component.content ) / 1024 / 1024 << " Мб\n" <<
                    "\t\t\ttype " <<
                        portulan::planet::Topology< SX, SY, SZ >::TYPE_COMPONENT_COUNT << "u " <<
                        sizeof( component.type ) / 1024 << " Кб\n" <<
                "\t\ttemperature " <<
                    portulan::planet::Topology< SX, SY, SZ >::TEMPERATURE_GRID << "x " <<
                    sizeof( temperature ) / 1024 << " Кб" <<
                    "  [ " << *tminmax.first << "; " << *tminmax.second << " ]\n" <<
                "\t\tprecipitations " <<
                    portulan::planet::Topology< SX, SY, SZ >::PRECIPITATIONS_GRID << "x " <<
                    sizeof( precipitations ) / 1024 << " Кб" <<
                    "  [ " << *pminmax.first << "; " << *pminmax.second << " ]\n" <<
    std::endl;

    return out;
}





inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::euid_t& uid ) {
    out << static_cast< unsigned int >( uid.group ) <<
        "." << static_cast< unsigned int >( uid.code );
    return out;
}





inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::eportion_t& ep ) {
    out << ep.uid << ":" << ep.count;
    return out;
}




inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t& sp ) {
    typedef portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t  specimen_t;
    typedef portulan::planet::eportion_t  eportion_t;

    out <<
        "lifetime " << sp.lifetime <<
        "\nmass ";
    static const size_t LC = portulan::planet::Topology< 81, 81, 81 >::LIFE_CYCLE;
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



} // std
