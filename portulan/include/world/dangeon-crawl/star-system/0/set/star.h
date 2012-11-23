#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о звёздах в звёздной системе.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* Информация о звезде в звёздной системе.
* Хранить будем по координатам: сетка MapContent3D - слишком накладно.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Масса звезды, кг.
    */
    cl_double mass;

    /**
    * Радиус звезды, м.
    */
    cl_double radius;

    /**
    * Средняя температура, К.
    */
    cl_double temperature;

    /**
    * Координаты звезды в звёздной системе, XYZ, м.
    */
    cl_double coord[ 3 ];

    /**
    * Скорость движения звезды в звёздной системе, XYZ, м/с.
    */
    cl_double velocity[ 3 ];

    /**
    * Вектор гравитационных сил, действующих на звезду, Н.
    */
    cl_double force[ 3 ];

} aboutStar_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
