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
* Память звезды о событиях в звёздной системе.
*
* @see Комментарии в 'asteroid.h'.
*/
typedef struct __attribute__ ((packed)) {
    cl_int   waldo;
    event_t  content[ STAR_EVENT_COUNT ];
} starMemoryEvent_t;




/**
* Информация о звезде в звёздной системе.
* Хранить будем по координатам: сетка MapContent3D - слишком накладно.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Идентификатор звезды.
    */
    uid_t uid;

    /**
    * Звезда взаимодействует с другими элементами звёздной системы.
    */
    bool live;

    /**
    * Масса звезды, кг.
    */
    real_t mass;

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
    */
    real_t force[ 3 ];

    /**
    * Скорость движения звезды в звёздной системе, XYZ, м/с.
    */
    real_t velocity[ 3 ];


    /**
    * События, которые произошли со звездой.
    * @see #Соглашения в 'event_t'.
    */
    starMemoryEvent_t memoryEvent;


    /**
    * Переменные используются некоторыми движками, чтобы оптимизировать
    * работу с элементом.
    *
    * @example EngineND
    *
    * # Переменные ниже заполняются движком.
    * # Для получения актуальной информации в переменные выше, должен
    *   быть вызван метод Engine::sync().
    */
    real_t tm[ 16 ];

    /**
    * Светимость звезды.
    */
    real_t luminosity;

    /**
    * Тестовый набор.
    */
    real_t test[ 5 ];

} aboutStar_t;




/**
* Перечисление всех звёзд в звёздной системе.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
* # Отсутствующая звезда - сигнал конца списка.
*/
typedef aboutStar_t starContent_t[ STAR_COUNT ];




/**
* Звёзды в области звёздной системы.
*/
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
