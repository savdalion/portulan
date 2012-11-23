namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

        
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
    const portulan::world::dungeoncrawl::planet::l0::Portulan&  portulan
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
    const portulan::world::dungeoncrawl::planet::l0::topology_t&  tp
) {
    namespace pd = portulan::world::dungeoncrawl::planet::l0;

    static const size_t CG = pd::COMPONENT_GRID * pd::COMPONENT_GRID * pd::COMPONENT_GRID;
    const size_t memsizeComponent = sizeof( pd::componentCell_t ) * CG;

    static const size_t TG = pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID;
    const size_t memsizeTemperature = sizeof( pd::temperatureCell_t ) * TG;

    static const size_t STG = pd::SURFACE_TEMPERATURE_GRID * pd::SURFACE_TEMPERATURE_GRID * pd::SURFACE_TEMPERATURE_GRID;
    const size_t memsizeSurfaceTemperature = sizeof( pd::surfaceTemperatureCell_t ) * STG;

    static const size_t RG = pd::RAINFALL_GRID * pd::RAINFALL_GRID * pd::RAINFALL_GRID;
    const size_t memsizeRainfall = sizeof( pd::rainfallCell_t ) * RG;

    static const size_t DG = pd::DRAINAGE_GRID * pd::DRAINAGE_GRID * pd::DRAINAGE_GRID;
    const size_t memsizeDrainage = sizeof( pd::temperatureCell_t ) * DG;

    static const size_t ELG = pd::LANDSCAPE_GRID * pd::LANDSCAPE_GRID * pd::LANDSCAPE_GRID;
    const size_t memsizeLandscape = sizeof( pd::landscapeCell_t ) * ELG;

    static const size_t BG = pd::BIOME_GRID * pd::BIOME_GRID * pd::BIOME_GRID;
    const size_t memsizeBiome = sizeof( pd::biomeCell_t ) * BG;

    static const size_t LG = pd::LIVING_GRID * pd::LIVING_GRID * pd::LIVING_GRID;
    const size_t memsizeLiving = sizeof( pd::livingCell_t ) * LG;

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

    const auto stsumAverage = std::accumulate(
        tp.surfaceTemperature.content,
        tp.surfaceTemperature.content + TG,
        0.0f,
        [] ( float sum, const pd::surfaceTemperatureCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto stminmaxAverage = std::minmax_element(
        tp.surfaceTemperature.content,
        tp.surfaceTemperature.content + TG,
        [] ( const pd::surfaceTemperatureCell_t& a, const pd::surfaceTemperatureCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    const auto rsumAverage = std::accumulate(
        tp.rainfall.content,
        tp.rainfall.content + TG,
        0.0f,
        [] ( float sum, const pd::rainfallCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto rminmaxAverage = std::minmax_element(
        tp.rainfall.content,
        tp.rainfall.content + TG,
        [] ( const pd::rainfallCell_t& a, const pd::rainfallCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    const auto dsumAverage = std::accumulate(
        tp.drainage.content,
        tp.drainage.content + TG,
        0.0f,
        [] ( float sum, const pd::drainageCell_t& a ) -> float {
            return sum + a[0].average;
        }
    );
    const auto dminmaxAverage = std::minmax_element(
        tp.drainage.content,
        tp.drainage.content + TG,
        [] ( const pd::drainageCell_t& a, const pd::drainageCell_t& b ) -> bool {
            return (a[0].average < b[0].average);
        }
    );

    *out <<
        "������, ���������� ���������� �������\n" <<
            "    topology\n" <<
                "        aboutPlanet " <<
                    sizeof( tp.aboutPlanet ) / 1024 << "��" <<
                    "\n" <<
                "        aboutComponent " <<
                    pd::COMPONENT_COUNT << "u " <<
                    sizeof( tp.aboutComponent ) / 1024 << "��" <<
                    "\n" <<
                "        aboutLiving " <<
                    pd::LIVING_COUNT << "u " <<
                    sizeof( tp.aboutLiving ) / 1024 / 1024 << "��" <<
                    "\n" <<
                "        component " <<
                    pd::COMPONENT_GRID << "x " <<
                    pd::COMPONENT_CELL << "u " <<
                    memsizeComponent / 1024 / 1024 << "��" <<
                    "\n" <<
                "        temperature " <<
                    pd::TEMPERATURE_GRID << "x " <<
                    memsizeTemperature / 1024 / 1024 << "��\n" <<
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
                    pd::SURFACE_TEMPERATURE_GRID << "x " <<
                    memsizeSurfaceTemperature / 1024 / 1024 << "��\n" <<
                    "            average  [ " << stminmaxAverage.first[0]->average       <<
                        "; " << stminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (stsumAverage / static_cast< float >( STG )) <<
                    "\n" <<
                "        rainfall " <<
                    pd::RAINFALL_GRID << "x " <<
                    memsizeRainfall / 1024 / 1024 << "��\n" <<
                    "            average  [ " << rminmaxAverage.first[0]->average       <<
                        "; " << rminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (rsumAverage / static_cast< float >( RG )) <<
                    "\n" <<
                "        drainage " <<
                    pd::DRAINAGE_GRID << "x " <<
                    memsizeDrainage / 1024 / 1024 << "��\n" <<
                    "            average  [ " << dminmaxAverage.first[0]->average       <<
                        "; " << dminmaxAverage.second[0]->average       << " ]" <<
                        "  ~ " << (dsumAverage / static_cast< float >( DG )) <<
                    "\n" <<
                "        landscape " <<
                    pd::LANDSCAPE_GRID << "x " <<
                    pd::LANDSCAPE_CELL << "u " <<
                    memsizeLandscape / 1024 / 1024 << "��" <<
                    "\n" <<
                "        biome " <<
                    pd::BIOME_GRID << "x " <<
                    memsizeBiome / 1024 / 1024 << "��" <<
                    "\n" <<
                "        living " <<
                    pd::LIVING_GRID << "x " <<
                    pd::LIVING_CELL << "u " <<
                    memsizeLiving / 1024 / 1024 << "��" <<
                    "\n" <<
    std::endl;
}



                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan
