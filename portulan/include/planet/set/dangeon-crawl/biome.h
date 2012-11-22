#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ������ ������ ��� ������������� ������� �� ������
* ���� ���� Dungeon Crawl.
*
* # ����� ������������ �� ������ ��������� �������.
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
* ������������ ����� ������ �� ������ ���������
* GROUP_ELEMENT::GE_BIOME.
* ���� ������� ���������� ����, ����� ������������ ��� �����������
* ������ ��������� ����.
*
* @prototype http://dfwk.ru/Biome
* @prototype http://dwarffortresswiki.org/index.php/DF2012:Biome
* @prototype WWF System > http://en.wikipedia.org/wiki/Biome#WWF_system
* @see ����� ������ ��� ����� > http://wolfweb.unr.edu/~ldyer/classes/396/olsonetal.pdf
*/
#undef CB_NONE
enum CODE_BIOME {
    // ��� ����������� ��� �� ��������
    CB_NONE = 0,

    // ����� ���
    CB_ANY = CB_NONE,

    // ����������� �����
    CB_FERTILE = 1,

    // ������� (�����)
    CB_DESERT,

    // ������� (�����)
    CB_WASTELAND,

    // ���������� �����
    CB_BADLAND,


#if 0
// - @todo ? ������� ����� - �����?
    // 01 Tropical and subtropical moist broadleaf forests
    // (tropical and subtropical, humid)
    // ����������� �������� ���������������� ���
    CB_TROPICAL_MOIST_BROADLEAF_FOREST,

    // 02 Tropical and subtropical dry broadleaf forests
    // (tropical and subtropical, semihumid)
    // ����������� ����� ���������������� ���
    CB_TROPICAL_DRY_BROADLEAF_FOREST,

    // 03 Tropical and subtropical coniferous forests
    // (tropical and subtropical, semihumid)
    // ����������� ������� ���
    CB_TROPICAL_CONIFEROUS_FOREST,

    // 04 Temperate broadleaf and mixed forests
    // (temperate, humid)
    // ��������� ���������������� � ��������� ���
    CB_TEMPERATE_DRY_BROADLEAF_MIXED_FOREST,

    // 05 Temperate coniferous forests
    // (temperate, humid to semihumid)
    // ��������� ������� ���
    CB_TEMPERATE_CONIFEROUS_FOREST,

    // 06 Boreal forests / taiga
    // (subarctic, humid)
    CB_TAIGA,

    // 07 Tropical and subtropical grasslands, savannas, and shrublands
    // (tropical and subtropical, semiarid)
    // ����������� ���, ������� � ����������
    CB_TROPICAL_GRASSLAND,
    CB_TROPICAL_SAVANNA,
    CB_TROPICAL_SHRUBLAND,

    // 08 Temperate grasslands, savannas, and shrublands
    // (temperate, semiarid)
    // ��������� ���, ������� � ����������
    CB_TEMPERATE_GRASSLAND,
    CB_TEMPERATE_SAVANNA,
    CB_TEMPERATE_SHRUBLAND,

    // 09 Flooded grasslands and savannas
    // (temperate to tropical, fresh or brackish water inundated)
    // ����������� ��� � �������
    CB_FLOODED_GRASSLAND,
    CB_FLOODED_SAVANNA,

    // 10 Montane grasslands and shrublands
    // (alpine or montane climate)
    // ������ ���� � ����������
    CB_MONTANE_GRASSLAND,
    CB_MONTANE_SHRUBLAND,

    // 11 Tundra
    // (Arctic)
    CB_TUNDRA,

    // 12 Mediterranean forests, woodlands, and scrub or sclerophyll forests
    // (temperate warm, semihumid to semiarid with winter rainfall)
    // ����������������� ���, �������� ���������, ����������� ���
    CB_MEDITERRANEAN_FOREST,

    // 13 Deserts and xeric shrublands
    // (temperate to tropical, arid)
    // ��������� ���������� ����������
    CB_DESERT_SHRUBLAND,
    
    // 14 Mangrove
    // (subtropical and tropical, salt water inundated)
    // ������
    CB_MANGROVE,
#endif

    
    // ���������
    CB_last
};





/**
* ���������� � �����.
*/

typedef struct {
    cl_float min;
    cl_float max;
} diapasonCharacterBiome_t;


typedef struct {
    enum CODE_ELEMENT_LANDSCAPE  code;

    /* - @todo � ����� ���-�� ������ ���������� �������� ��������� �
    *  ���� �����.
    diapasonCharacterBiome_t     count;
    */

} landscapeBiome_t;


typedef struct {
    diapasonCharacterBiome_t  temperature;
    diapasonCharacterBiome_t  rainfall;
    diapasonCharacterBiome_t  drainage;

    /**
    * ����� �������� ��������� ����� ��������� ���� ����.
    * @todo extend �������� ���-�� ������� �������� ���������.
    */
    landscapeBiome_t  landscape[ LANDSCAPE_BIOME_COUNT ];

} aboutOneBiome_t;





/**
* ���������� � ������.
*   #! � ���� ������ ������ �����. ���� �����.
*/
typedef aboutOneBiome_t  aboutBiome_t[ BIOME_COUNT ];





/**
* ����������� �����.
*
* @see biomeCell_t
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_BIOME code;
} presentBiome_t;




/**
* ������ ��������� � �����������, ��� � ��� ���������� ����.
* �.�. ���������� ������� - �������, ���� ������ ������������ �� ����� ��,
* ������� ������ ����� ��������� ��������� ������� �� ���������� ������.
*   # ������� ������� BIOME_CELL �������� ������� ��������
*     ������� ������� ������ �� ������ CODE_BIOME.
*/
typedef presentBiome_t  biomeCell_t[ BIOME_CELL ];




/**
* ����� �������.
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
