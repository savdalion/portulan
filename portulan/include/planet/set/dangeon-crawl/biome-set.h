#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "biome.h"


/**
* Наборы биомов для моделирования планеты на основе
* мира игры Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


static __constant aboutBiome_t aboutBiome = {
    // CB_NONE
    {
    },

    // CB_DESERT
    {
        // temperature
        { ANYf, ANYf },
        // rainfall
        { 0.0f, 1000.0f },
        // drainage
        { 0.0f, 3300.0f },
    },

    // CB_WASTELAND
    {
        // temperature
        { ANYf, ANYf },
        // rainfall
        { 0.0f, 1000.0f },
        // drainage
        { 3300.0f, 5000.0f },
    },

    // CB_BADLAND
    {
        // temperature
        { ANYf, ANYf },
        // rainfall
        { 0.0f, 1000.0f },
        // drainage
        { 5000.0f, INFINITYf },
    },

};






#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
