#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Наборы биомов для моделирования планеты на основе
* мира игры Dungeon Crawl.
*
* # Биомы определяются на основе местности планеты.
*
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
* Перечисление кодов биомов из группы элементов
* GROUP_ELEMENT::GE_BIOME.
* Сами являясь элементами мира, биомы используются для группировок
* других элементов мира.
*
* @prototype http://dfwk.ru/Biome
* @prototype http://dwarffortresswiki.org/index.php/DF2012:Biome
* @prototype WWF System > http://en.wikipedia.org/wiki/Biome#WWF_system
* @see Карта биомов для Земли > http://wolfweb.unr.edu/~ldyer/classes/396/olsonetal.pdf
*/
#undef CB_NONE
enum CODE_BIOME {
    // код отсутствует или не определён
    CB_NONE = 0,

    // любой код
    CB_ANY = CB_NONE,

    // плодородная земля
    CB_FERTILE = 1,

    // пустыня (песок)
    CB_DESERT,

    // пустошь (камни)
    CB_WASTELAND,

    // бесплодная земля
    CB_BADLAND,


#if 0
// - @todo ? Сложные биомы - позже?
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
#endif

    
    // последний
    CB_last
};





/**
* Информация о биоме.
*/

typedef struct {
    cl_float min;
    cl_float max;
} diapasonCharacterBiome_t;


typedef struct {
    enum CODE_ELEMENT_LANDSCAPE  code;

    /* - @todo В каком кол-ве должны содержатся элементы ландшафта в
    *  этом биоме.
    diapasonCharacterBiome_t     count;
    */

} landscapeBiome_t;


typedef struct {
    diapasonCharacterBiome_t  temperature;
    diapasonCharacterBiome_t  rainfall;
    diapasonCharacterBiome_t  drainage;

    /**
    * Какие элементы ландшафта может содержать этот биом.
    * @todo extend Добавить хар-ки каждому элементу ландшафта.
    */
    landscapeBiome_t  landscape[ LANDSCAPE_BIOME_COUNT ];

} aboutOneBiome_t;





/**
* Информация о биомах.
*   #! В этом списке индекс соотв. коду биома.
*/
typedef aboutOneBiome_t  aboutBiome_t[ BIOME_COUNT ];





/**
* Присутствие биома.
*
* @see biomeCell_t
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_BIOME code;
} presentBiome_t;




/**
* Ячейка портулана с информацией, что в ней содержится биом.
* Т.к. территория планеты - большая, одна ячейка простирается на сотни км,
* поэтому ячейка может содержать несколько близких по параметрам биомов.
*   # Система выберет BIOME_CELL наиболее близких заданной
*     области планеты биомов из списка CODE_BIOME.
*/
typedef presentBiome_t  biomeCell_t[ BIOME_CELL ];




/**
* Биомы планеты.
*/
typedef biomeCell_t*  biomeContent_t;
typedef struct __attribute__ ((packed)) {
    biomeContent_t content;
} biome_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
