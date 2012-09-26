#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "living.h"
#include "temperature.h"


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
    __structComponentAll_t space;
    __structComponentAll_t atmosphere;
    __structComponentAll_t crust;
    __structComponentAll_t mantle;
    __structComponentAll_t core;
} componentPlanet_t;

typedef struct __attribute__ ((packed)) {
    __structTemperatureAll_t space;
    __structTemperatureAll_t atmosphere;
    __structTemperatureAll_t crust;
    __structTemperatureAll_t mantle;
    __structTemperatureAll_t core;
} temperaturePlanet_t;

typedef struct __attribute__ ((packed)) {
    __structLivingAll_t space;
    __structLivingAll_t atmosphere;
    __structLivingAll_t crust;
    __structLivingAll_t mantle;
    __structLivingAll_t core;
} livingPlanet_t;

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
    * Жизнь на планете, перечисление всех особей и их кол-во в области планеты.
    *   # Список должен заканчиваться на код CL_NONE, если содержит
    *     менее LIVING_CELL элементов.
    */
    livingPlanet_t living;

    /**
    * Атмосферные осадки на планете.
    */
    //rainfallPlanet_t rainfall;

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
