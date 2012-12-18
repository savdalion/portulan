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
    * Идентификатор планеты.
    */
    uid_t uid;

    /**
    * Масса планеты, кг.
    */
    real_t mass;

    /**
    * Радиус планеты, м.
    */
    real_t radius;

    /**
    * Координаты планеты в звёздной системе, XYZ, м.
    */
    real_t coord[ 3 ];

    /**
    * Наклон планеты по XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * Вектор гравитационных сил, действующих на планету, Н.
    */
    real_t force[ 3 ];

    /**
    * Скорость движения планеты в звёздной системе, XYZ, м/с.
    */
    real_t velocity[ 3 ];

    /**
    * Наклон оси планеты, градусы.
    *
    * @see http://en.wikipedia.org/wiki/Axial_tilt
    */
    real_t axilTilt;

    /**
    * Период вращения планеты, с.
    */
    real_t rotationPeriod;


    /**
    * События, которые произошли с планетой и о которых она помнит.
    */
    //event_t event[ PLANET_EVENT_COUNT ];


    /**
    * @see star.h
    */
    real_t tm[ 16 ];


    /**
    * Тестовый набор.
    */
    real_t test[ 5 ];

} aboutPlanet_t;




/**
* Перечисление всех планет в звёздной системе.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
* # Отсутствующая планета - сигнал конца списка.
*/
typedef aboutPlanet_t  planetContent_t[ PLANET_COUNT ];




/**
* Планеты в области звёздной системы.
*/
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
