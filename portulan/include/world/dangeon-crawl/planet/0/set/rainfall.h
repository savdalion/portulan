#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация об атмосферных осадках на поверхностях планеты.
*
*   # Используется только внешний слой планетарной коры. Но @todo можно
*     задействовать эту же структуру для задания осадков в полостях планеты.
*   # Сохраняем похожесть структуры на "temperature".
*
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif


/**
* Поведение атм. осадков в 1-й ячейке на поверхности планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Среднее значение атм. осадков, мм / день.
    */
    cl_float average;

} behaviourRainfall_t;




/**
* Ячейка портулана с информацией об атм. осадках на поверхности.
*/
typedef behaviourRainfall_t  rainfallCell_t[ 1 ];





/**
* Атм. осадки на поверхности планеты.
*/
typedef rainfallCell_t*  rainfallContent_t;
typedef struct __attribute__ ((packed)) {
    rainfallContent_t content;
} rainfall_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
