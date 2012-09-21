namespace portulan {
    namespace io {
        namespace planet {
            namespace set {
                namespace dungeoncrawl {

        
inline TextVisual::TextVisual(
    std::ostream&  out,
    const option_t&  json
) :
    mOption( json ),
    out( &out )
{
}




inline TextVisual::~TextVisual() {
}






inline TextVisual& TextVisual::operator<<(
    const portulan::planet::Portulan&  portulan
) {
    const auto& topology = portulan.topology().topology();

    // �������, ��� ����� ��������
    const std::string only = mOption[ "only" ];

    // �������� �� ��������� ���������
    const bool showTopology = only.empty() || (only == ".topology");
    if ( showTopology ) {
        drawTopologySizeInMemory( topology );
    }

    /* - @todo �������� ����� ����������
    const bool showTopologyTemperature = (only == ".temperature");
    if ( showTopologyTemperature ) {
        ...
    }
    */

    return *this;
}






inline TextVisual& TextVisual::operator<<( const option_t& json ) {
    mOption = json;
    return *this;
}





inline void TextVisual::wait() {
    std::cin.ignore();
}










inline void TextVisual::drawTopologySizeInMemory(
    const portulan::planet::set::topology_t&  tp
) {
    namespace pd = portulan::planet::set::dungeoncrawl;
    namespace pc = portulan::planet::set::dungeoncrawl::component;
    namespace pl = portulan::planet::set::dungeoncrawl::living;
    namespace pt = portulan::planet::set::dungeoncrawl::temperature;

    static const size_t CG = pd::COMPONENT_GRID * pd::COMPONENT_GRID * pd::COMPONENT_GRID;
    const size_t memsizeComponent = sizeof( pc::componentCell_t ) * CG;
    static const size_t LG = pd::LIVING_GRID * pd::LIVING_GRID * pd::LIVING_GRID;
    const size_t memsizeLiving = sizeof( pl::livingCell_t ) * LG;
    static const size_t TG = pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID;
    const size_t memsizeTemperature = sizeof( pt::temperatureCell_t ) * TG;

    const auto tsumAverage = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pt::temperatureCell_t& a ) -> float {
            return sum + a.average;
        }
    );
    const auto tminmaxAverage = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pt::temperatureCell_t& a, const pt::temperatureCell_t& b ) -> bool {
            return (a.average < b.average);
        }
    );

    const auto tsumDispersion = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pt::temperatureCell_t& a ) -> float {
            return sum + a.dispersion;
        }
    );
    const auto tminmaxDispersion = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pt::temperatureCell_t& a, const pt::temperatureCell_t& b ) -> bool {
            return (a.dispersion < b.dispersion);
        }
    );

    const auto tsumRate = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pt::temperatureCell_t& a ) -> float {
            return sum + a.rate;
        }
    );
    const auto tminmaxRate = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pt::temperatureCell_t& a, const pt::temperatureCell_t& b ) -> bool {
            return (a.rate < b.rate);
        }
    );

    *out <<
        "������, ���������� ���������� �������\n" <<
            "\ttopology\n" <<
                "\t\taboutPlanet " <<
                    sizeof( tp.aboutPlanet ) / 1024 << "��\n" <<
                "\t\taboutComponent " <<
                    pd::COMPONENT_COUNT << "u " <<
                    sizeof( tp.aboutComponent ) / 1024 << "��\n" <<
                "\t\tcomponent\n" <<
                    "\t\t\tcontent " <<
                        pd::COMPONENT_GRID << "x " <<
                        pd::COMPONENT_CELL << "u " <<
                        memsizeComponent / 1024 / 1024 << "��\n" <<
                "\t\taboutLiving " <<
                    pd::LIVING_COUNT << "u " <<
                    sizeof( tp.aboutLiving ) / 1024 / 1024 << "��\n" <<
                "\t\tliving\n" <<
                    "\t\t\tcontent " <<
                        pd::LIVING_GRID << "x " <<
                        pd::LIVING_CELL << "u " <<
                        memsizeLiving / 1024 / 1024 << "��\n" <<
                "\t\ttemperature " <<
                    pd::TEMPERATURE_GRID << "x " <<
                    memsizeTemperature / 1024 / 1024 << "��\n" <<
                    "\t\t\taverage    [ " << tminmaxAverage.first->average       << "; " << tminmaxAverage.second->average       << " ]" <<
                        "\t~ " << (tsumAverage / static_cast< float >( TG )) <<
                    "\n" <<
                    "\t\t\tdispersion [ " << tminmaxDispersion.first->dispersion << "; " << tminmaxDispersion.second->dispersion << " ]" <<
                        "\t~ " << (tsumDispersion / static_cast< float >( TG )) <<
                    "\n" <<
                    "\t\t\trate       [ " << tminmaxRate.first->rate             << "; " << tminmaxRate.second->rate             << " ]" <<
                        "\t~ " << (tsumRate / static_cast< float >( TG )) <<
                    "\n" <<
                /*
                "\t\tpressure " <<
                    portulan::planet::structure::PRESSURE_GRID << "x " <<
                    sizeof( pressure ) / 1024 / 1024 << " ��\n" <<
                    "\t\t\taverage [ " << *pminmax.first << "; " << *pminmax.second << " ]\n" <<
                "\t\tprecipitations " <<
                    portulan::planet::structure::PRECIPITATIONS_GRID << "x " <<
                    sizeof( precipitations ) / 1024 / 1024 << " ��\n" <<
                    "\t\t\trainfall [ " << *rminmax.first << "; " << *rminmax.second << " ]\n" <<
                "\t\tsurfaceVoid " <<
                    portulan::planet::structure::SURFACE_VOID_GRID << "x " <<
                    sizeof( aboutSurfaceVoid ) / 1024 /1024 << " ��\n" <<
                */
    std::endl;
}



                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan
