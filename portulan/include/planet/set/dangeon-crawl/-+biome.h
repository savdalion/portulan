#if 0

#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Наборы биомов для моделирования планеты на основе
* мира игры Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace biome {
#endif


/**
* Перечисление кодов в группе биомов
* GROUP_ELEMENT::GE_BIOME.
*
*   #! Нумерация компонентов должна соотв. индексу в списке aboutBiome_t.
*/





/**
* Перечисление кодов биомов из группы элементов
* GROUP_ELEMENT::GE_BIOME.
* Сами являясь элементами мира, биомы используются для группировок
* других элементов мира.
*
* @prototype WWF System > http://en.wikipedia.org/wiki/Biome#WWF_system
* @see Карта биомов для Земли > http://wolfweb.unr.edu/~ldyer/classes/396/olsonetal.pdf
*/
#undef CB_NONE
enum CODE_BIOME {
    // код отсутствует или не определён
    CB_NONE = 0,

    // 01 Tropical and subtropical moist broadleaf forests
    // (tropical and subtropical, humid)
    // тропический дождевой широколиственный лес
    CB_TROPICAL_MOIST_BROADLEAF_FOREST,

    // 02 Tropical and subtropical dry broadleaf forests
    // (tropical and subtropical, semihumid)
    // тропический сухой широколиственный лес
    CB_TROPICAL_DRY_BROADLEAF_FOREST,

    // 03 Tropical and subtropical coniferous forests
    // (tropical and subtropical, semihumid)
    // тропический хвойный лес
    CB_TROPICAL_CONIFEROUS_FOREST,

    // 04 Temperate broadleaf and mixed forests
    // (temperate, humid)
    // умеренный широколиственный и смешанный лес
    CB_TEMPERATE_DRY_BROADLEAF_MIXED_FOREST,

    // 05 Temperate coniferous forests
    // (temperate, humid to semihumid)
    // умеренный хвойный лес
    CB_TEMPERATE_CONIFEROUS_FOREST,

    // 06 Boreal forests / taiga
    // (subarctic, humid)
    CB_TAIGA,

    // 07 Tropical and subtropical grasslands, savannas, and shrublands
    // (tropical and subtropical, semiarid)
    // тропические луг, саванна и мелколесье
    CB_TROPICAL_GRASSLAND,
    CB_TROPICAL_SAVANNA,
    CB_TROPICAL_SHRUBLAND,

    // 08 Temperate grasslands, savannas, and shrublands
    // (temperate, semiarid)
    // умеренные луг, саванна и мелколесье
    CB_TEMPERATE_GRASSLAND,
    CB_TEMPERATE_SAVANNA,
    CB_TEMPERATE_SHRUBLAND,

    // 09 Flooded grasslands and savannas
    // (temperate to tropical, fresh or brackish water inundated)
    // затопленные луг и саванна
    CB_FLOODED_GRASSLAND,
    CB_FLOODED_SAVANNA,

    // 10 Montane grasslands and shrublands
    // (alpine or montane climate)
    // горные луга и мелколесье
    CB_MONTANE_GRASSLAND,
    CB_MONTANE_SHRUBLAND,

    // 11 Tundra
    // (Arctic)
    CB_TUNDRA,

    // 12 Mediterranean forests, woodlands, and scrub or sclerophyll forests
    // (temperate warm, semihumid to semiarid with winter rainfall)
    // средиземноморские лес, лесистая местность, низкорослый лес
    CB_MEDITERRANEAN_FOREST,

    // 13 Deserts and xeric shrublands
    // (temperate to tropical, arid)
    // пустынное засушливое мелколесье
    CB_DESERT_SHRUBLAND,
    
    // 14 Mangrove
    // (subtropical and tropical, salt water inundated)
    // мангры
    CB_MANGROVE,

    // последний
    CB_last
};





/**
* Код биома и на сколько близко местность соотв. этому биому.
*   "+"    максимальное соответствие
*   "-"    не соответствует
*   "0.0"  ни рыба, ни мясо
* Чем больше разница, тем больше несоответствие.
* Подход "-0+" принят, чтобы не тратить силы на бессмысленную
* нормализацию. В то же время, нормализованные значения также
* не исказят картину.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_BIOME code;
    cl_float count;
} fidelityBiom_t;






/**
* Информация о биоме.
*
* @source Прим. к CODE_BIOME.
*/
typedef __structTemperatureCell_t  behaviourTemperature_t;

typedef __structTemperatureCell_t  behaviourPrecipitations_t;

typedef struct __attribute__ ((packed)) {
    /**
    * Код биома.
    */
    enum CODE_BIOME code;

    /**
    * Поведение температуры в биоме.
    */
    behaviourTemperature_t temperature;

    /**
    * Поведение осадков в биоме.
    */
    behaviourPrecipitations_t precipitations;

} aboutOneBiome_t;



/**
* Информация о биомах.
*   #! В этом списке индекс биома соотв. коду биома.
*/
typedef aboutOneBiome_t  aboutBiome_t[ BIOME_COUNT ];




/**
* Ячейка портулана с информацией о биоме.
*   # Системой будет выбрано BIOME_CELL наиболее близких заданной
*     области планеты биомов из списка CODE_BIOME.
*/
typedef fidelityBiom_t  biomCell_t[ BIOME_CELL ];



/**
* Биомы планеты. На сколько окружение соотв. ожиданиям.
*/
typedef biomeCell_t*  biomeContent_t;
typedef struct __attribute__ ((packed)) {
    /**
    * Содержание в ячейке.
    */
    biomeContent_t content;

} biome_t;



#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // biome
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif

#endif
