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
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Планета взаимодействует с другими элементами звёздной системы.
    */
    bool live;

    /**
    * Масса планеты, кг.
    *
    * @see pns::massPlanet()
    */
    real4_t mass;

    /**
    * Радиус планеты, м.
    */
    real_t radius;

    /**
    * Координаты планеты в звёздной системе, XYZ, м.
    */
    real_t coord[ 3 ];

    /**
    * Наклон оси планеты, градусы.
    *
    * @see http://en.wikipedia.org/wiki/Axial_tilt
    */
    real_t axialTilt;

    /**
    * Период вращения планеты, с.
    */
    real_t rotationPeriod;

    /**
    * Вектор гравитационных сил, действующих на планету, Н.
    * Также храним длину вектора.
    */
    real_t force[ 3 ];
    real_t absForce;

    /**
    * Скорость движения планеты в звёздной системе, XYZ, м/с.
    */
    real_t velocity[ 3 ];

} characteristicPlanet_t;




typedef struct __attribute__ ((packed)) {
    /**
    * Идентификатор планеты.
    */
    uid_t uid;

    /**
    * Характеристика планеты: сейчас и для след. пульса.
    */
    characteristicPlanet_t today;
    characteristicPlanet_t future;

    /**
    * События, выпущенные планетой за 1 пульс.
    */
    emitterEvent_t emitterEvent;

} aboutPlanet_t;




/**
* Планеты в области звёздной системы.
*/
typedef aboutPlanet_t*   planetContent_t;
typedef struct __attribute__ ((packed)) {
    planetContent_t content;
} planet_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
