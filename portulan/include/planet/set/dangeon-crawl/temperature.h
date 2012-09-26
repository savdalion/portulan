#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о температуре в области планеты.
*
*   # Сохраняем похожесть структуры на "component" и "living".
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace temperature {
#endif


/**
* Поведение температуры в 1-й ячейке области планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Среднее значение температуры, К.
    */
    cl_float average;

    /**
    * Отклонение температуры от среднего значения, % / 100.
    */
    cl_float dispersion;

    /**
    * Частота отклонения температуры от среднего значения, раз / день.
    * Значение < 1 декларирует частоту отклонения "раз в несколько дней":
    * = 1 / rate
    */
    cl_float rate;

} temperatureCell_t;




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
    cl_float map[2];

    // # Отклонение температуры, частота - все эти прелести появятся потом:
    //   силы природы сделают своё дело.

} zoneTemperature_t;

typedef zoneTemperature_t  temperatureAll_t;




/**
* Ячейка портулана с информацией о температуре.
*/
//typedef behaviourTemperature_t  temperatureCell_t;




/**
* Температура в области планеты.
*/
typedef temperatureCell_t*  temperatureContent_t;
typedef struct __attribute__ ((packed)) {
    temperatureContent_t content;
} temperature_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // temperature
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
