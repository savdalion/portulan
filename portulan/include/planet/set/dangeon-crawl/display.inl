#pragma once

inline std::ostream& operator<<( std::ostream& out,  const portulan::planet::set::topology_t&  tp ) {
    using namespace portulan::planet::set::dungeoncrawl;

    out <<
        "Ïאלÿעü, חאםטלאולאÿ עמןמכמדטוי ןכאםועû\n" <<
            "\ttopology " << sizeof( tp ) / 1024 / 1024 << " Ìב\n" <<
                "\t\taboutPlanet " <<
                    sizeof( tp.aboutPlanet ) / 1024 << " Êב\n" <<
                "\t\taboutComponent " <<
                    COMPONENT_COUNT << "u " <<
                    sizeof( tp.aboutComponent ) / 1024 << " Êב\n" <<
                "\t\tcomponent " << sizeof( tp.component ) / 1024 / 1024 << " Ìב\n" <<
                    "\t\t\tcontent " <<
                        COMPONENT_GRID << "x " <<
                        COMPONENT_CELL << "u " <<
                        sizeof( tp.component.content ) / 1024 / 1024 << " Ìב\n" <<
                "\t\taboutLiving " <<
                    LIVING_COUNT << "u " <<
                    sizeof( tp.aboutLiving ) / 1024 << " Êב\n" <<
                "\t\tliving " << sizeof( tp.living ) / 1024 / 1024 << " Ìב\n" <<
                    "\t\t\tcontent " <<
                        LIVING_GRID << "x " <<
                        LIVING_CELL << "u " <<
                        sizeof( tp.living.content ) / 1024 / 1024 << " Ìב\n" <<
                /*
                "\t\tpressure " <<
                    portulan::planet::structure::PRESSURE_GRID << "x " <<
                    sizeof( pressure ) / 1024 / 1024 << " Ìב\n" <<
                    "\t\t\taverage [ " << *pminmax.first << "; " << *pminmax.second << " ]\n" <<
                "\t\ttemperature " <<
                    portulan::planet::structure::TEMPERATURE_GRID << "x " <<
                    sizeof( temperature ) / 1024 / 1024 << " Ìב\n" <<
                    "\t\t\taverage [ " << *tminmax.first << "; " << *tminmax.second << " ]\n" <<
                "\t\tprecipitations " <<
                    portulan::planet::structure::PRECIPITATIONS_GRID << "x " <<
                    sizeof( precipitations ) / 1024 / 1024 << " Ìב\n" <<
                    "\t\t\trainfall [ " << *rminmax.first << "; " << *rminmax.second << " ]\n" <<
                "\t\tsurfaceVoid " <<
                    portulan::planet::structure::SURFACE_VOID_GRID << "x " <<
                    sizeof( aboutSurfaceVoid ) / 1024 /1024 << " Ìב\n" <<
                */
    std::endl;

    return out;
}
