#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "biome.h"


/**
* Ќаборы биомов дл€ моделировани€ планеты на основе
* мира игры Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif


// # «десь не помешает хранение 'static', но CPU OpenCL не воспринимает его.
__constant aboutBiome_t aboutBiome[ BIOME_COUNT ] = {
    // CB_NONE
    {
    },

    // CB_FERTILE
    {
        // temperature
        { 10, 30 },
        // rainfall
        { 1000.0f, 3000.0f },
        // drainage
        { 1000.0f, 3000.0f },
        // landscape
        { CEL_FLAT },
    },

    // CB_DESERT
    {
        // temperature
        { ANYf, ANYf },
        // rainfall
        { 0.0f, 1000.0f },
        // drainage
        { 0.0f, 3300.0f },
        // landscape
        { CEL_FLAT },
    },

    // CB_WASTELAND
    {
        // temperature
        { ANYf, ANYf },
        // rainfall
        { 0.0f, 1000.0f },
        // drainage
        { 3300.0f, 5000.0f },
        // landscape
        { CEL_FLAT, CEL_BASIN, CEL_RAVINE },
    },

    // CB_BADLAND
    {
        // temperature
        { ANYf, ANYf },
        // rainfall
        { 0.0f, 1000.0f },
        // drainage
        { 5000.0f, INFINITYf },
        // landscape
        { CEL_FLAT, CEL_BASIN, CEL_RAVINE },
    },

    // # ѕризнак завершени€ списка.
    {
        // temperature
        { INFINITYf, INFINITYf },
        // rainfall
        { },
        // drainage
        { },
        // landscape
        { },
    },
};






#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
