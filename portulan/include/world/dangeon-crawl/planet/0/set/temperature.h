#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о температуре в области планеты.
*
*   # Сохраняем похожесть структуры на "component" и "living".
*
* @see surfaceTemperature_t
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
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
    * @todo Отклонение температуры от среднего значения, % / 100.
    */
    //cl_float dispersion;

    /**
    * @todo Частота отклонения температуры от среднего значения, раз / день.
    * Значение < 1 декларирует частоту отклонения "раз в несколько дней":
    * = 1 / rate
    */
    //cl_float rate;

} behaviourTemperature_t;




/**
* Ячейка портулана с информацией о температуре.
*/
typedef behaviourTemperature_t  temperatureCell_t[ 1 ];





/**
* Температура в области планеты.
*/
typedef temperatureCell_t*  temperatureContent_t;
typedef struct __attribute__ ((packed)) {
    temperatureContent_t content;
} temperature_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
