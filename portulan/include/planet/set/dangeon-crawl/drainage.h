#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о дренаже на поверхностях планеты.
*
*   # Используется только внешний слой планетарной коры. Но @todo можно
*     задействовать эту же структуру для задания дренажа в полостях планеты.
*   # Сохраняем похожесть структуры на "rainfall".
*
* @see rainfall_t
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* Поведение дренажа в 1-й ячейке на поверхности планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Среднее значение дренажа, мм / день.
    */
    cl_float average;

} behaviourDrainage_t;




/**
* Ячейка портулана с информацией о температуре на поверхности.
*/
typedef behaviourDrainage_t  drainageCell_t[ 1 ];





/**
* Температура на поверхности планеты.
*/
typedef drainageCell_t*  drainageContent_t;
typedef struct __attribute__ ((packed)) {
    drainageContent_t content;
} drainage_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
