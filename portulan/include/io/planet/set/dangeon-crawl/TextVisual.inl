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

    // смотрим, что нужно показать
    const std::string only = mOption[ "only" ];

    // проходим по структуре топологии
    const bool showTopology = only.empty() || (only == ".topology");
    if ( showTopology ) {
        drawTopologySizeInMemory( topology );
    }

    /* - @todo собираем карту температур
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

    static const size_t CG = pd::COMPONENT_GRID * pd::COMPONENT_GRID * pd::COMPONENT_GRID;
    const size_t memsizeComponent = sizeof( pd::componentCell_t ) * CG;
    static const size_t LG = pd::LIVING_GRID * pd::LIVING_GRID * pd::LIVING_GRID;
    const size_t memsizeLiving = sizeof( pd::livingCell_t ) * LG;
    static const size_t TG = pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID;
    const size_t memsizeTemperature = sizeof( pd::temperatureCell_t ) * TG;

    const auto tsumAverage = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pd::temperatureCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto tminmaxAverage = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pd::temperatureCell_t& a, const pd::temperatureCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    /* - @todo
    const auto tsumDispersion = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pd::temperatureCell_t& a ) -> float {
            return sum + a[0].dispersion;
        }
    );
    const auto tminmaxDispersion = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pd::temperatureCell_t& a, const pd::temperatureCell_t& b ) -> bool {
            return (a[0].dispersion < b[0].dispersion);
        }
    );

    const auto tsumRate = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pd::temperatureCell_t& a ) -> float {
            return sum + a[0].rate;
        }
    );
    const auto tminmaxRate = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pd::temperatureCell_t& a, const pd::temperatureCell_t& b ) -> bool {
            return (a[0].rate < b[0].rate);
        }
    );
    */

    *out <<
        "ѕам€ть, занимаема€ топологией планеты\n" <<
            "\ttopology\n" <<
                "\t\taboutPlanet " <<
                    sizeof( tp.aboutPlanet ) / 1024 << " б\n" <<
                "\t\taboutComponent " <<
                    pd::COMPONENT_COUNT << "u " <<
                    sizeof( tp.aboutComponent ) / 1024 << " б\n" <<
                "\t\tcomponent\n" <<
                    "\t\t\tcontent " <<
                        pd::COMPONENT_GRID << "x " <<
                        pd::COMPONENT_CELL << "u " <<
                        memsizeComponent / 1024 / 1024 << "ћб\n" <<
                "\t\taboutLiving " <<
                    pd::LIVING_COUNT << "u " <<
                    sizeof( tp.aboutLiving ) / 1024 / 1024 << "ћб\n" <<
                "\t\tliving\n" <<
                    "\t\t\tcontent " <<
                        pd::LIVING_GRID << "x " <<
                        pd::LIVING_CELL << "u " <<
                        memsizeLiving / 1024 / 1024 << "ћб\n" <<
                "\t\ttemperature " <<
                    pd::TEMPERATURE_GRID << "x " <<
                    memsizeTemperature / 1024 / 1024 << "ћб\n" <<
                    "\t\t\taverage    [ " << tminmaxAverage.first[0]->average       <<
                        "; " << tminmaxAverage.second[0]->average       << " ]" <<
                        "\t~ " << (tsumAverage / static_cast< float >( TG )) <<
                    "\n" <<
                    /* - @todo
                    "\t\t\tdispersion [ " << tminmaxDispersion.first[0]->dispersion <<
                        "; " << tminmaxDispersion.second[0]->dispersion << " ]" <<
                        "\t~ " << (tsumDispersion / static_cast< float >( TG )) <<
                    "\n" <<
                    "\t\t\trate       [ " << tminmaxRate.first[0]->rate             <<
                        "; " << tminmaxRate.second[0]->rate             << " ]" <<
                        "\t~ " << (tsumRate / static_cast< float >( TG )) <<
                    "\n" <<
                    */
    std::endl;
}



                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan
