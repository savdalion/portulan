namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

namespace pnp = portulan::world::dungeoncrawl::planet::l0;


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
    const pnp::Portulan&  portulan
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






inline TextVisual& TextVisual::operator<<( const std::string& s ) {
    *out << s;
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
    const pnp::topology_t&  tp
) {
    namespace pns = portulan::world::dungeoncrawl::planet::l0;

    static const size_t CG = pns::COMPONENT_GRID * pns::COMPONENT_GRID * pns::COMPONENT_GRID;
    const size_t memsizeComponent = sizeof( pns::componentCell_t ) * CG;

    static const size_t TG = pns::TEMPERATURE_GRID * pns::TEMPERATURE_GRID * pns::TEMPERATURE_GRID;
    const size_t memsizeTemperature = sizeof( pns::temperatureCell_t ) * TG;

    static const size_t STG = pns::SURFACE_TEMPERATURE_GRID * pns::SURFACE_TEMPERATURE_GRID * pns::SURFACE_TEMPERATURE_GRID;
    const size_t memsizeSurfaceTemperature = sizeof( pns::surfaceTemperatureCell_t ) * STG;

    static const size_t RG = pns::RAINFALL_GRID * pns::RAINFALL_GRID * pns::RAINFALL_GRID;
    const size_t memsizeRainfall = sizeof( pns::rainfallCell_t ) * RG;

    static const size_t DG = pns::DRAINAGE_GRID * pns::DRAINAGE_GRID * pns::DRAINAGE_GRID;
    const size_t memsizeDrainage = sizeof( pns::temperatureCell_t ) * DG;

    static const size_t ELG = pns::LANDSCAPE_GRID * pns::LANDSCAPE_GRID * pns::LANDSCAPE_GRID;
    const size_t memsizeLandscape = sizeof( pns::landscapeCell_t ) * ELG;

    static const size_t IG = pns::ILLUMINANCE_GRID * pns::ILLUMINANCE_GRID * pns::ILLUMINANCE_GRID;
    const size_t memsizeIlluminance = sizeof( pns::illuminanceCell_t ) * IG;

    static const size_t BG = pns::BIOME_GRID * pns::BIOME_GRID * pns::BIOME_GRID;
    const size_t memsizeBiome = sizeof( pns::biomeCell_t ) * BG;

    static const size_t LG = pns::LIVING_GRID * pns::LIVING_GRID * pns::LIVING_GRID;
    const size_t memsizeLiving = sizeof( pns::livingCell_t ) * LG;

    const auto tsumAverage = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pns::temperatureCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto tminmaxAverage = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pns::temperatureCell_t& a, const pns::temperatureCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    /* - @todo
    const auto tsumDispersion = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pns::temperatureCell_t& a ) -> float {
            return sum + a[0].dispersion;
        }
    );
    const auto tminmaxDispersion = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pns::temperatureCell_t& a, const pns::temperatureCell_t& b ) -> bool {
            return (a[0].dispersion < b[0].dispersion);
        }
    );

    const auto tsumRate = std::accumulate(
        tp.temperature.content,
        tp.temperature.content + TG,
        0.0f,
        [] ( float sum, const pns::temperatureCell_t& a ) -> float {
            return sum + a[0].rate;
        }
    );
    const auto tminmaxRate = std::minmax_element(
        tp.temperature.content,
        tp.temperature.content + TG,
        [] ( const pns::temperatureCell_t& a, const pns::temperatureCell_t& b ) -> bool {
            return (a[0].rate < b[0].rate);
        }
    );
    */

    const auto stsumAverage = std::accumulate(
        tp.surfaceTemperature.content,
        tp.surfaceTemperature.content + STG,
        0.0f,
        [] ( float sum, const pns::surfaceTemperatureCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto stminmaxAverage = std::minmax_element(
        tp.surfaceTemperature.content,
        tp.surfaceTemperature.content + STG,
        [] ( const pns::surfaceTemperatureCell_t& a, const pns::surfaceTemperatureCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    const auto rsumAverage = std::accumulate(
        tp.rainfall.content,
        tp.rainfall.content + RG,
        0.0f,
        [] ( float sum, const pns::rainfallCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto rminmaxAverage = std::minmax_element(
        tp.rainfall.content,
        tp.rainfall.content + RG,
        [] ( const pns::rainfallCell_t& a, const pns::rainfallCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    const auto dsumAverage = std::accumulate(
        tp.drainage.content,
        tp.drainage.content + DG,
        0.0f,
        [] ( float sum, const pns::drainageCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto dminmaxAverage = std::minmax_element(
        tp.drainage.content,
        tp.drainage.content + DG,
        [] ( const pns::drainageCell_t& a, const pns::drainageCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    const auto iSsumAverage = std::accumulate(
        tp.illuminance.content,
        tp.illuminance.content + IG,
        0.0f,
        [] ( float sum, const pns::illuminanceCell_t& a ) -> float {
            return sum + a[0].star;
        }
    );
    const auto iSminmaxAverage = std::minmax_element(
        tp.illuminance.content,
        tp.illuminance.content + IG,
        [] ( const pns::illuminanceCell_t& a, const pns::illuminanceCell_t& b ) -> bool {
            return (a[0].star < b[0].star);
        }
    );

    *out <<
        "ѕам€ть, занимаема€ топологией планеты\n" <<
            "    topology\n" <<
                "        aboutPlanet " <<
                    sizeof( tp.aboutPlanet ) / 1024 << " б" <<
                    "\n" <<
                "        aboutComponent " <<
                    pns::COMPONENT_COUNT << "u " <<
                    sizeof( tp.aboutComponent ) / 1024 << " б" <<
                    "\n" <<
                "        aboutLiving " <<
                    pns::LIVING_COUNT << "u " <<
                    sizeof( tp.aboutLiving ) / 1024 / 1024 << "ћб" <<
                    "\n" <<
                "        component " <<
                    pns::COMPONENT_GRID << "x " <<
                    pns::COMPONENT_CELL << "u " <<
                    memsizeComponent / 1024 / 1024 << "ћб" <<
                    "\n" <<
                "        temperature " <<
                    pns::TEMPERATURE_GRID << "x " <<
                    memsizeTemperature / 1024 / 1024 << "ћб\n" <<
                    "            average  [ " << tminmaxAverage.first[0]->average       <<
                        "; " << tminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (tsumAverage / static_cast< float >( TG )) <<
                    "\n" <<
                    /* - @todo
                    "            dispersion [ " << tminmaxDispersion.first[0]->dispersion <<
                        "; " << tminmaxDispersion.second[0]->dispersion << " ]" <<
                        "    ~ " << (tsumDispersion / static_cast< float >( TG )) <<
                    "\n" <<
                    "            rate       [ " << tminmaxRate.first[0]->rate             <<
                        "; " << tminmaxRate.second[0]->rate             << " ]" <<
                        "    ~ " << (tsumRate / static_cast< float >( TG )) <<
                    "\n" <<
                    */
                "        surfaceTemperature " <<
                    pns::SURFACE_TEMPERATURE_GRID << "x " <<
                    memsizeSurfaceTemperature / 1024 / 1024 << "ћб\n" <<
                    "            average  [ " << stminmaxAverage.first[0]->average       <<
                        "; " << stminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (stsumAverage / static_cast< float >( STG )) <<
                    "\n" <<
                "        rainfall " <<
                    pns::RAINFALL_GRID << "x " <<
                    memsizeRainfall / 1024 / 1024 << "ћб\n" <<
                    "            average  [ " << rminmaxAverage.first[0]->average       <<
                        "; " << rminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (rsumAverage / static_cast< float >( RG )) <<
                    "\n" <<
                "        drainage " <<
                    pns::DRAINAGE_GRID << "x " <<
                    memsizeDrainage / 1024 / 1024 << "ћб\n" <<
                    "            average  [ " << dminmaxAverage.first[0]->average       <<
                        "; " << dminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (dsumAverage / static_cast< float >( DG )) <<
                    "\n" <<
                "        landscape " <<
                    pns::LANDSCAPE_GRID << "x " <<
                    pns::LANDSCAPE_CELL << "u " <<
                    memsizeLandscape / 1024 / 1024 << "ћб" <<
                    "\n" <<
                "        illuminance from star" <<
                    pns::ILLUMINANCE_GRID << "x " <<
                    memsizeIlluminance / 1024 / 1024 << "ћб\n" <<
                    "            average  [ " << iSminmaxAverage.first[0]->star       <<
                        "; " << iSminmaxAverage.second[0]->star       << " ]" <<
                        "  ~ " << (iSsumAverage / static_cast< float >( IG )) <<
                    "\n" <<
                "        biome " <<
                    pns::BIOME_GRID << "x " <<
                    memsizeBiome / 1024 / 1024 << "ћб" <<
                    "\n" <<
                "        living " <<
                    pns::LIVING_GRID << "x " <<
                    pns::LIVING_CELL << "u " <<
                    memsizeLiving / 1024 / 1024 << "ћб" <<
                    "\n" <<
    std::endl;
}



                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan
