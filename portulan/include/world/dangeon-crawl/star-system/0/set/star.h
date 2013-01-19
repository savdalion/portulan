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
* Минимум событий, испускаемых звездой каждый пульс.
*/
const enum EVENT STAR_EVENT[] = {
    E_GRAVITY,
    // излучение всегда приводит к потере массы
    E_LUMINOSITY, /* E_CHANGE_MASS, - меняем в 'future' */
    E_NONE
};




/**
* Информация о звезде в звёздной системе.
*
* # Хранить будем по координатам: сетка MapContent3D - слишком накладно.
* # Характеристика, которая может быть изменена, имеет близнеца с именем
*   'future'. Этот близнец служит как память для событий об изменении
*   характеристик элемента.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Звезда взаимодействует с другими элементами звёздной системы.
    */
    bool live;

    /**
    * Масса звезды, кг.
    *
    * @see pns::massStar()
    */
    mass_t mass;

    /**
    * Радиус звезды, м.
    */
    real_t radius;

    /**
    * Температура ядра звезды, К.
    */
    real_t kernelTemperature;

    /**
    * Температура поверхности звезды, К.
    * Введена для расчёта светимости звезды.
    */
    real_t surfaceTemperature;

    /**
    * Координаты звезды в звёздной системе, XYZ, м.
    */
    real_t coord[ 3 ];

    /**
    * Наклон звезды по XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * Вектор гравитационных сил, действующих на звезду, Н.
    * Также храним длину вектора.
    */
    real_t force[ 3 ];
    real_t absForce;

    /**
    * Скорость движения звезды в звёздной системе, XYZ, м/с.
    */
    real_t velocity[ 3 ];

    /**
    * Светимость звезды.
    */
    real_t luminosity;

} characteristicStar_t;




typedef struct __attribute__ ((packed)) {
    /**
    * Идентификатор звезды.
    */
    uid_t uid;

    /**
    * Характеристика звезды: сейчас и для след. пульса.
    */
    characteristicStar_t today;
    characteristicStar_t future;

    /**
    * События, выпущенные звездой за 1 пульс.
    */
    emitterEvent_t emitterEvent;

} aboutStar_t;




/**
* Звёзды в области звёздной системы.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
* # Отсутствующая звезда - сигнал конца списка.
*/
typedef aboutStar_t*  starContent_t;
typedef struct __attribute__ ((packed)) {
    starContent_t content;
} star_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
