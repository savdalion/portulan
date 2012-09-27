#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "temperature.h"
#include "living.h"


/**
* Структура планеты.
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* Общая информация о планете.
*/


/**
* Структуры ниже содержат общую информацию о компонентах для формирования
* зон атмосферы, планетарной коры, ядра и пр..
*/

typedef struct __attribute__ ((packed)) {

    enum CODE_COMPONENT code;

    /**
    * Массовая доля компонента в задаваемой зоне.
    */
    cl_float count;

    /**
    * Количество месторождений, определяющих наибольшие скопления этого
    * компонента. Компонента на планете не становится больше, просто
    * его запасы "стягиваются" ("намываются") из планеты ближе к этой зоне.
    *//* - Нет. Начальное состояние планеты не должно отличаться от
           однородного. Задействуем силы природы, чтобы скуку равновесия.
    cl_uint minefield;
    */
} zoneComponent_t;

// # Берётся COMPONENT_CELL вместо COMPONENT_COUNT, т.к. эта структура
//   используется лишь при инициализации, а кол-во компонентов в 1-й ячейке
//   в любом случае не будет превышать COMPONENT_CELL компонентов.
typedef zoneComponent_t  componentAll_t[ COMPONENT_CELL ];




/**
* Информация о температуре в области планеты (в портулане).
* Эти данные используются при начальном формировании планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Карта температур, К.
    *   # Температура меняется линейно.
    *   # Значения температур перечисляются от центра (0.0, самый глубокий слой)
    *     к поверхности (1.0, самый верхний слой).
    */
    cl_float center;
    cl_float surface;

    // # Отклонение температуры, частота - все эти прелести появятся потом:
    //   силы природы сделают своё дело.

} zoneTemperature_t;

typedef zoneTemperature_t  temperatureAll_t;




/**
* Примерное кол-во особей в области планеты (в портулане) с указанием
* размеров групп. Эти данные используются для формирования
* ареалов обитания в области планеты.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING code;
    // *примерное* кол-во особей в ячейке области планеты
    cl_float count;
    // # Размер группы декларирован в aboutOneLiving_t::maxGroupSize.
} zoneLiving_t;

// # Берётся LIVING_CELL вместо LIVING_COUNT, т.к. эта структура
//   используется лишь при инициализации, а кол-во особей в 1-й ячейке
//   в любом случае не будет превышать LIVING_CELL особей.
typedef zoneLiving_t  livingAll_t[ LIVING_CELL ];




typedef struct __attribute__ ((packed)) {
    cl_float atmosphere;
    cl_float crust;
    cl_float mantle;
    cl_float core;
} radiusPlanet_t;

typedef struct __attribute__ ((packed)) {
    cl_float atmosphere;
    cl_float crust;
    cl_float mantle;
    cl_float core;
} massPlanet_t;

typedef struct __attribute__ ((packed)) {
    componentAll_t space;
    componentAll_t atmosphere;
    componentAll_t crust;
    componentAll_t mantle;
    componentAll_t core;
} componentPlanet_t;

typedef struct __attribute__ ((packed)) {
    temperatureAll_t space;
    temperatureAll_t atmosphere;
    temperatureAll_t crust;
    temperatureAll_t mantle;
    temperatureAll_t core;
} temperaturePlanet_t;

/*
typedef struct __attribute__ ((packed)) {
    __structRainfallAll_t space;
    __structRainfallAll_t atmosphere;
    __structRainfallAll_t crust;
    __structRainfallAll_t mantle;
    __structRainfallAll_t core;
} rainfallPlanet_t;
*/

typedef struct __attribute__ ((packed)) {
    livingAll_t space;
    livingAll_t atmosphere;
    livingAll_t crust;
    livingAll_t mantle;
    livingAll_t core;
} livingPlanet_t;

typedef struct __attribute__ ((packed)) {
    /**
    * Размер области планеты, м.
    *   # Размер области планеты = Радиус атмосферы * 2
    *   # Толщина атмосферы = Радиус атмосферы - Радиус коры планеты
    */
    cl_float size;

    /**
    * Внешние радиусы области планеты, части от размера области планеты.
    *   # Радиус атмосферы = 1.0.
    */
    radiusPlanet_t radius;

    /**
    * Массы скоплений в области планеты, кг.
    */
    massPlanet_t mass;

    /**
    * Состав планеты, перечисление всех компонентов по группам и
    * массовой части компонентов в целом.
    *   # Список должен заканчиваться на код CC_NONE, если содержит
    *     менее COMPONENT_CELL элементов.
    */
    componentPlanet_t component;

    /**
    * Температура на планете.
    *   # Чтобы отсутствовала резкая граница температур между зонами, граничные
    *     значения температур зон должны совпадать.
    */
    temperaturePlanet_t temperature;

    /**
    * Атмосферные осадки на планете.
    *//*
    rainfallPlanet_t rainfall;
    */

    /**
    * Жизнь на планете, перечисление всех особей и их кол-во в области планеты.
    *   # Список должен заканчиваться на код CL_NONE, если содержит
    *     менее LIVING_CELL элементов.
    */
    livingPlanet_t living;

} aboutPlanet_t;




/**
* Структура для хранения количества разных видов особей с группировкой
* по LIFE_CYCLE и по зонам области планеты.
*
* #! Изменения этой структуры должны быть согласованы с кодом
*    в DungeonCrawl::initLiving().
*/
typedef struct __attribute__ ((packed)) {
    float space;
    float atmosphere;
    float crust;
    float mantle;
    float core;
    // # Всегда сумма всех вышеобозначенных зон.
    float all;
} zoneOneLivingCount_t;

typedef zoneOneLivingCount_t  zoneLCOneLivingCount_t[ LIFE_CYCLE_COUNT ];

// индекс соотв. коду особи
typedef zoneLCOneLivingCount_t  zoneLivingCount_t[ LIVING_COUNT ];




/**
* Структура для хранения признаков разных видов особей с группировкой
* по LIFE_CYCLE и по зонам области планеты.
* Используется вместе с zoneOneLivingCount_t.
*
* #! Изменения этой структуры должны быть согласованы с кодом
*    в DungeonCrawl::initLiving().
*/
typedef struct __attribute__ ((packed)) {
    bool space;
    bool atmosphere;
    bool crust;
    bool mantle;
    bool core;
    // # Итог "И" по всем вышеобозначенным зонам.
    bool all;
} zoneOneLivingCountComplete_t;

typedef zoneOneLivingCountComplete_t  zoneLCOneLivingCountComplete_t[ LIFE_CYCLE_COUNT ];

// индекс соотв. коду особи
typedef zoneLCOneLivingCountComplete_t  zoneLivingCountComplete_t[ LIVING_COUNT ];





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
