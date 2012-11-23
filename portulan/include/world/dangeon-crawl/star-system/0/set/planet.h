#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о планетах в звёздной системе.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif



/**
* Информация о планете в звёздной системе.
* Хранить будем по координатам: сетка MapContent3D - слишком накладно.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Масса планеты, кг.
    */
    cl_double mass;

    /**
    * Радиус планеты, м.
    */
    cl_double radius;

    /**
    * Координаты планеты в звёздной системе, XYZ, м.
    */
    cl_double coord[ 3 ];

    /**
    * Скорость движения планеты в звёздной системе, XYZ, м/с.
    */
    cl_double velocity[ 3 ];

    /**
    * Вектор гравитационных сил, действующих на планету, Н.
    */
    cl_double force[ 3 ];

} aboutPlanet_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
