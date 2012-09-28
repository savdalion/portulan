#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о температуре на поверхностях планеты.
*
*   # Используется только внешний слой планетарной коры. Но @todo можно
*     задействовать эту же структуру для задания температуры полостей планеты.
*   # Сохраняем похожесть структуры на "temperature".
*
* @see temperature_t
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* Поведение температуры в 1-й ячейке на поверхности планеты.
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

} behaviourSurfaceTemperature_t;




/**
* Ячейка портулана с информацией о температуре на поверхности.
*/
typedef behaviourSurfaceTemperature_t  surfaceTemperatureCell_t[ 1 ];





/**
* Температура на поверхности планеты.
*/
typedef surfaceTemperatureCell_t*  surfaceTemperatureContent_t;
typedef struct __attribute__ ((packed)) {
    surfaceTemperatureContent_t content;
} surfaceTemperature_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
