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
    __structLivingAll_t space;
    __structLivingAll_t atmosphere;
    __structLivingAll_t crust;
    __structLivingAll_t mantle;
    __structLivingAll_t core;
} livingPlanet_t;

typedef struct __attribute__ ((packed)) {
    __structTemperatureAll_t space;
    __structTemperatureAll_t atmosphere;
    __structTemperatureAll_t crust;
    __structTemperatureAll_t mantle;
    __structTemperatureAll_t core;
} temperaturePlanet_t;

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
    * Жизнь на планете, перечисление всех особей и их кол-во в области планеты.
    *   # Список должен заканчиваться на код CL_NONE, если содержит
    *     менее LIVING_CELL элементов.
    */
    livingPlanet_t living;

    /**
    * Температура на планете.
    *   # Чтобы отсутствовала резкая граница температур между зонами, граничные
    *     значения температур зон должны совпадать.
    */
    temperaturePlanet_t temperature;

} aboutPlanet_t;


#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
