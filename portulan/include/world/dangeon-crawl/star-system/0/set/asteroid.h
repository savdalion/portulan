#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация об астероидах в звёздной системе.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* Память астероида о событиях в звёздной системе.
*
* @see #Соглашения в 'event_t'.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Индекс ("валдо" - см. игру 'SpaceChem') для записи текущего события.
    * [0; *_EVENT_COUNT - 1]
    *
    * # Позволяем быть отрицательным, чтобы ускорить работу с ним.
    */
    cl_int   waldo;

    event_t  content[ ASTEROID_EVENT_COUNT ];
    
} asteroidMemoryEvent_t;




/**
* Информация об астероиде в звёздной системе.
* Хранить будем по координатам: сетка MapContent3D - слишком накладно.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Идентификатор астероида.
    */
    uid_t uid;

    /**
    * Астероид взаимодействует с другими элементами звёздной системы.
    */
    bool live;

    /**
    * Масса астероида, кг.
    */
    real_t mass;

    /**
    * Размеры астероида по XYZ, м.
    */
    real_t size[ 3 ];

    /**
    * Координаты астероида в звёздной системе, XYZ, м.
    */
    real_t coord[ 3 ];

    /**
    * Наклон астероида по XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * Вектор гравитационных сил, действующих на астероид, Н.
    */
    real_t force[ 3 ];

    /**
    * Скорость движения астероида в звёздной системе, XYZ, м/с.
    */
    real_t velocity[ 3 ];


    /**
    * События, которые произошли с астероидом.
    * @see #Соглашения в 'event_t'.
    */
    asteroidMemoryEvent_t memoryEvent;


    /**
    * @see star.h
    */
    real_t tm[ 16 ];


    /**
    * Тестовый набор.
    */
    real_t test[ 5 ];

} aboutAsteroid_t;




/**
* Перечисление всех астероидов в звёздной системе.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
* # Отсутствующий астероид - сигнал конца списка.
*/
typedef aboutAsteroid_t asteroidContent_t[ ASTEROID_COUNT ];




/**
* Астероиды в области звёздной системы.
*/
typedef struct __attribute__ ((packed)) {
    asteroidContent_t content;
} asteroid_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
