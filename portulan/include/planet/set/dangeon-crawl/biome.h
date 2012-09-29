#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Ќаборы биомов дл€ моделировани€ планеты на основе
* мира игры Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* ѕеречисление кодов биомов из группы элементов
* GROUP_ELEMENT::GE_BIOME.
* —ами €вл€€сь элементами мира, биомы используютс€ дл€ группировок
* других элементов мира.
*
* @prototype http://dfwk.ru/Biome
* @prototype http://dwarffortresswiki.org/index.php/DF2012:Biome
* @prototype WWF System > http://en.wikipedia.org/wiki/Biome#WWF_system
* @see  арта биомов дл€ «емли > http://wolfweb.unr.edu/~ldyer/classes/396/olsonetal.pdf
*/
#undef CB_NONE
enum CODE_BIOME {
    // код отсутствует или не определЄн
    CB_NONE = 0,

    // любой код
    CB_ANY = CB_NONE,

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
    // средиземноморские лес, лесиста€ местность, низкорослый лес
    CB_MEDITERRANEAN_FOREST,

    // 13 Deserts and xeric shrublands
    // (temperate to tropical, arid)
    // пустынное засушливое мелколесье
    CB_DESERT_SHRUBLAND,
    
    // 14 Mangrove
    // (subtropical and tropical, salt water inundated)
    // мангры
    CB_MANGROVE,

    
    /* дополнительные биомы */

    // пустын€ (песок)
    CB_DESERT,

    // пустошь (камни)
    CB_WASTELAND,

    // бесплодна€ земл€
    CB_BADLAND,


    // последний
    CB_last
};





/**
* »нформаци€ о биоме.
*/
typedef struct {
    float min;
    float max;
} diapasonCharacterBiome_t;

typedef struct {
    diapasonCharacterBiome_t  temperature;
    diapasonCharacterBiome_t  rainfall;
    diapasonCharacterBiome_t  drainage;
} aboutOneBiome_t;





/**
* »нформаци€ о биомах.
*   #! ¬ этом списке индекс особи соотв. коду биома.
*/
typedef aboutOneBiome_t  aboutBiome_t[ BIOME_COUNT ];





/**
* ѕрисутствие биома.
*
* @see biomeCell_t
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_BIOME code;
} presentBiome_t;




/**
* ячейка портулана с информацией, что в ней содержитс€ биом.
* “.к. территори€ планеты - больша€, одна €чейка простираетс€ на сотни км,
* поэтому может содержать несколько близких по параметрам биомов.
*   # —истема выберет BIOME_CELL наиболее близких заданной
*     области планеты биомов из списка CODE_BIOME.
*/
typedef presentBiome_t  biomeCell_t[ BIOME_CELL ];




/**
* Ѕиомы планеты.
*/
typedef biomeCell_t*  biomeContent_t;
typedef struct __attribute__ ((packed)) {
    biomeContent_t content;
} biome_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
