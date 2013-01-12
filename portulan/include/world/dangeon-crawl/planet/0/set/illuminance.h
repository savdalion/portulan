#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация об освещённости в области планеты.
* Освещённость имеется ввиду от внешних источников (например, звезды, спутника).
*
*   # Нет прямой связи между освещённостью и теплом (см. "лучистый теплообмен").
*
*   # Сохраняем похожесть структуры на "component" и "living".
*
* @see http://ru.wikipedia.org/wiki/%D0%9E%D1%81%D0%B2%D0%B5%D1%89%D1%91%D0%BD%D0%BD%D0%BE%D1%81%D1%82%D1%8C
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif


/**
* Освещённость в 1-й ячейке области планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Освещённость от звёзд, лк.
    */
    cl_float star;

    /**
    * @todo Освещённость от спутников и др. планет, лк.
    */
    //cl_float planet;
    //cl_float satellite;

    /**
    * @todo Изменение освещённости из-за погодных условий, неппер.
    */
    //cl_float weather;

} sourceIlluminance_t;




/**
* Ячейка портулана с информацией об освещённости.
*/
typedef sourceIlluminance_t  illuminanceCell_t[ 1 ];




/**
* Освещённость в области планеты.
*/
typedef illuminanceCell_t*  illuminanceContent_t;
typedef struct __attribute__ ((packed)) {
    illuminanceContent_t content;
} illuminance_t;





/**
* Структуры для обмена инфо об освещённости.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Радиус звезды, м.
    */
    cl_float radius;

    /**
    * Средняя температура поверхности, К.
    */
    cl_float surfaceTemperature;

    /**
    * Светимость, Вт / м2.
    */
    cl_float luminosity;

    /**
    * Координаты звезды в звёздной системе, XYZ, м.
    */
    cl_float coord[ 3 ];

} aboutIlluminanceStar_t;




typedef struct __attribute__ ((packed)) {
    aboutIlluminanceStar_t  star[ ILLUMINANCE_STAR_COUNT ];
    // @todo sattelite, planet
} aboutIlluminanceSource_t;




typedef struct {
    // результат освещения
    illuminanceContent_t  result;
    // тело, которое освещают
    cl_float  radius;
    cl_float  coord[ 3 ];
    cl_float  omega[ 3 ];
    // источники освещения
    aboutIlluminanceSource_t  source;
} illuminanceBody_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
