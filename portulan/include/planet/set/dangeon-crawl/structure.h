#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>


/**
*   # ��������� ������������ �. �., ����� �� ����������� �� ��� ���������
*     � ��� OpenCL.
*/
#define __constant const

// ������������ ��� VC++ �� ���������
#define __attribute__(x) /*nothing*/


namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
/**
* �������� ������ � ������� �������.
*    # 1 ����� = 1 ��� = 400 ����
*    # 1 ���� = 25 �����
*/
static __constant cl_float SECOND_IN_MINUTE = 60.0f;
static __constant cl_float MINUTE_IN_HOUR   = 60.0f;
static __constant cl_float HOUR_IN_DAY      = 25.0f;
static __constant cl_float DAY_IN_YEAR      = 400.0f;
static __constant cl_float HOUR_IN_YEAR     = DAY_IN_YEAR    * HOUR_IN_DAY;
static __constant cl_float MINUTE_IN_YEAR   = HOUR_IN_YEAR   * MINUTE_IN_HOUR;
static __constant cl_float SECOND_IN_YEAR   = MINUTE_IN_YEAR * SECOND_IN_MINUTE;
#endif





/**
* �������� ��� ������.
*/
enum CRITERIA {
    // ��������� �� ����� / ������ ��� / �� ����������
    CRITERIA_A = 0,
    // ���� �������� / ����
    CRITERIA_B,
    // ������� �������� / �����
    CRITERIA_C,
    // ���� �������� / ����� �����
    CRITERIA_D,
    // ��������� ������������� / �������������
    CRITERIA_E,

    // ��������� = ���-�� ���������
    CRITERIA_last,
    CRITERIA_count = CRITERIA_last
};





/**
* ���������.
*
* @prototype http://dfwk.ru/Biome
* @prototype http://dwarffortresswiki.org/index.php/DF2012:Biome
* @prototype WWF System > http://en.wikipedia.org/wiki/Biome#WWF_system
* @see ����� ������ ��� ����� > http://wolfweb.unr.edu/~ldyer/classes/396/olsonetal.pdf
*//*
enum TERRAIN {
    // ����������� ��� �� ����������
    TERRAIN_NONE = 0,

    TERRAIN_FOREST,
    TERRAIN_GRASSLAND,
    TERRAIN_HILL,
    TERRAIN_MARSH,

    TERRAIN_LOW_MOUNTAIN,
    TERRAIN_MOUNTAIN,
    TERRAIN_HIGHT_MOUNTAIN,

    TERRAIN_BADLAND_DESERT,
    TERRAIN_ROCK_DESERT,
    TERRAIN_SAND_DESERT,

    TERRAIN_SAVANNA,
    TERRAIN_SHRUBLAND,
    TERRAIN_SWAMP,
    TERRAIN_TAIGA,
    TERRAIN_TUNDRA,

    // ��������� = ���-�� ����������
    TERRAIN_last,
    TERRAIN_count = TERRAIN_last
};
*/





/**
* ��������� ���� ����� �� ������� (���������, ��������).
*
* @see LIFE_CYCLE_COUNT
*/
enum LIFE_CYCLE {
    // �������� ������, ������
    LC_EMBRYO   = 0,
    // ����, ������
    LC_CHILD    = 1,
    // ��������
    LC_ADULT    = 2,
    // �������
    LC_OLD      = 3,
    // ̸����� ����� - ����, �������
    LC_DEAD     = 4,
    // ����������� �����
    LC_IMMORTAL = 5,

    // ��������� = ���-�� ������
    LC_last,
    LC_count = LC_last
};





/**
* ������� ���������.
* �������� �����, ����� ���� ���� ��� ���� ��������� ��� ��� OpenCL.
* �� ����������� �������, ����� ������ �� C++ ����� ��������� �����������
* � OpenCL.
*
*   # ������� ������� ������� �� ������ ������������ ������������� ���
*     ������� �������� ����.
*
* @todo extend ��������� ������������ ������ ���������� �����.
*//* - ���������� ��-�� �����. ��. ����.
static __constant size_t GRID_SX = 81;
static __constant size_t GRID_SY = GRID_SX;
static __constant size_t GRID_SZ = GRID_SX;
*/


#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # � OpenCL ������� ��������� ��� define: OpenCL �� ������������
//   ��������� ������� �������.

/**
* ��������, �������� ������������, ��������, ������ �����, ��
* ����������� �������� �����������.
* ��������, ����� ������� ����� �� ��������� ��� ����������� �� ��
* ����� "������ �����".
*/
// #? ��� �������� � OpenCL � ��������� "-D" ����� �������� ��������.
static __constant cl_float IMMUNE = CL_FLT_MAX;
//#define IMMUNE  CL_FLT_MAX


/**
* ���������� ������� ��������.
*/
static __constant cl_float INFINITYf = CL_FLT_MAX;
//#define INFINITYf  CL_FLT_MAX



/**
* ����� �������� (��� ����� � ��������� ������).
*/
static __constant cl_float ANYf = -CL_FLT_MAX;
//#define ANYf  -CL_FLT_MAX




/**
* ������ ����� ����������� � ������� ������� (� ���������).
*/
static __constant size_t COMPONENT_GRID = 81;



/**
* ����. ���-�� *������* �����������, ������� ����� ��������������
* � ������� ������� (� ���������).
* >= CC_last
*
* @see CODE_COMPONENT
*/
static __constant size_t COMPONENT_COUNT = 100;



/**
* ����. ���-�� ����������� � ��������� ������ �� ������, ������� �����
* *������������* ��������� � 1-� ������ ���������.
*/
static __constant size_t COMPONENT_CELL = 20;



/**
* ����� ������������� ����������� � ������� �������.
*/
static __constant size_t TEMPERATURE_GRID = 81;



/**
* ����� ������������� ����������� �� ����������� �������.
*/
static __constant size_t SURFACE_TEMPERATURE_GRID = 81;



/**
* ����� ����������� ������� �� ����������� �������.
*/
static __constant size_t RAINFALL_GRID = 81;



/**
* ����� ������� �� ����������� �������.
*/
static __constant size_t DRAINAGE_GRID = 81;





/**
* ����� ������������� ������ � ������� �������.
*/
static __constant size_t BIOME_GRID = 81;



/**
* ����������� ��������� ���-�� *������* ������ � ������� �������.
* >= CB_last
*
* @see CODE_BIOME
*/
static __constant size_t BIOME_COUNT = 50;



/**
* ����. ���-�� ������, ������� ����� *������������* ���������
* � 1-� ������ ���������.
*/
static __constant size_t BIOME_CELL = 3;





/**
* ����. ���-�� ��������� ������ �����.
*
* @see LIFE_CYCLE
*/
static __constant size_t LIFE_CYCLE_COUNT = LC_last;





/**
* ������ ����� ������� �������� ����� ���������� � ������� �������.
*/
static __constant size_t LIVING_GRID = 81 / 3;



/**
* ������������ ���-�� *������* ������ (�������), �� ������� �����
* �������� �����.
*/
static __constant size_t PART_LIVING = 20;



/**
* ������������ ���-�� *������* ����, ��������� ������ �����.
*
* @see RESIST_PART_LIVING
*/
static __constant size_t ATTACK_PART_LIVING = 30;



/**
* ������������ ���-�� *������* �����, ��������� ������ �����.
*
* @see ATTACK_PART_LIVING
*/
static __constant size_t RESIST_PART_LIVING = 30;



/**
* ������������ ���-�� *������* ���. �����������, �� ������� �����
* �������� ����� �����.
*/
static __constant size_t COMPONENT_COMPOSITION_LIVING = 5;



/**
* ������������ ���-�� *������* ���. �����������, ������� �����
* ����� ��� ����������� �����.
*
* @see COMPONENT_WASTE_LIVING
*/
static __constant size_t COMPONENT_NEED_LIVING = 10;



/**
* ������������ ���-�� *������* ���. �����������, ������� ��������
* ����� ��� �����������������.
*
* @see COMPONENT_NEED_LIVING
*/
static __constant size_t COMPONENT_WASTE_LIVING = 10;



/**
* ������������ ���-�� *������* ����� �������, ������� ����������
* ����� ��� ����������� �����.
*
* @see ENERGY_WASTE_LIVING
* @see CODE_ENERGY
*/
static __constant size_t ENERGY_NEED_LIVING = 5;



/**
* ������������ ���-�� *������* ����� �������, ������ ��������
* ����� ��� �����������������.
*
* @see ENERGY_NEED_LIVING
* @see CODE_ENERGY
*/
static __constant size_t ENERGY_WASTE_LIVING = 5;



/**
* ������������ ���-�� ���� ��������, � ������� ����� ���� �����.
*/
static __constant size_t HABITAT_SURVIVOR_LIVING = 5;



/**
* ������������ ���-�� *������* ������, ��� ����� ��������� ���� ���������.
*/
static __constant size_t BIOME_COMFORT_SURVIVOR_LIVING = BIOME_COUNT;



/**
* ����������� ��������� ���-�� *������* ������ � ������� �������.
* >= CC_last
*
* @see CODE_LIVING
*/
static __constant size_t LIVING_COUNT = 100;



/**
* ����. ���-�� ������, ������� ����� *������������* ������� � 1-� ������
* ������� �������.
*/
static __constant size_t LIVING_CELL = 20;





#if 0
// @todo ...
/**
* ������ ����� �������� �� �������.
* ����������� ��� ���� �������.
* ��������� ������� �������� � ��������� ��������� �����, �������.
*/
static __constant size_t PRESSURE_GRID = 81;



/**
* ����� ������������� ������� � ������� �������.
*/
static __constant size_t PRECIPITATIONS_GRID = 81;



/**
* ����� ��� ��������� ����������� / ������ � ������� �������.
*/
static __constant size_t SURFACE_VOID_GRID = 81;



/**
* ���������� ��������� ��� ��������� ����������� / ������ �
* ������� �������.
*/
static __constant size_t SURFACE_VOID_REGISTRY = 5;
#endif

#endif





/**
* ������ ���������.
*
*   # ������������ �� ����� �������� NONE, ���� �� ��������������
*     ������������ � �������� ������� ��������.
*/
enum GROUP_ELEMENT {
    // ������ ������ ��� �����������
    GE_NONE = 0,

    /* - �� ����������. ������ ��� - ��������� (TERRAIN).
    // �����
    GE_BIOME,
    */

    // ���������� (������, ����������� �����, ������ � �.�.)
    // @see component_t
    GE_COMPONENT,

    // @see temperature_t
    GE_TEMPERATURE,

    // @see surfaceTemperature_t
    GE_SURFACE_TEMPERATURE,

    // @see rainfall_t
    GE_RAINFALL,

    // @see drainage_t
    GE_DRAINAGE,

    // @see TERRAIN
    GE_TERRAIN,

    // �������
    GE_ENERGY,

    // ����� ����� �����
    // @see aboutOneLiving_t
    GE_LIVING,

    // ����� ����� �������, ��������
    // @see aboutOnePartLiving_t
    GE_PART_LIVING,

    // ���������
    GE_last

    // @todo fine ����������� ����� ��� �������� ����.
};




/**
* ��� �������� (����������, �����).
* ����� �������� � CODE_*.
*
* @see set::Component, set::Living
*/
typedef cl_ushort code_t;






#if 0
// - @todo ...

/**
* ����� �������� ��������� � ����� � ������� �������.
* ��� ����������� � ��������� "������ ����" ������ �� �����.
*/
typedef struct {
    /**
    * ��������, ��.
    */
    typedef cl_float average_t[ PRESSURE_GRID * PRESSURE_GRID * PRESSURE_GRID ];
    average_t average;

} pressure_t;







/**
* ����������� ������ � ������� �������.
*
* @todo extend ������ ����� ���� �������: ����, �����, �������, ���������, ...
*/
typedef struct {
    /**
    * ���������� �������, � / �����.
    */
    typedef cl_float rainfall_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    rainfall_t rainfall;

    /**
    * ������� ��������� �������, ��� / �����.
    */
    typedef cl_float rate_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    rate_t rate;

    /**
    * ������� ������������ �������, ������� �����.
    */
    typedef cl_float averageDuration_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    averageDuration_t averageDuration;

    /**
    * ������� ������������ ������� (�� ������� % / 100 ������������
    * ����������� �� ������� ������������).
    */
    typedef cl_float dispersionDuration_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    dispersionDuration_t dispersionDuration;

} precipitations_t;






/**
* ����������� / ������� � ������� �������.
* �������� ������������ ��� ����������� ��������� ������������ �
* ������ (�����, ��������) ������ ������ ����������� �������.
*/
typedef struct {
    /**
    * ������������ ����� ���������, �������� ������� ����������������
    * � ��������� ����������� ������� ������� � �� ������� ���������.
    *
    * ���������, ������
    *   - �� ������������
    *
    * ����������� �������
    *   0, 1  ������� ���������� �� ����� ������� � ���� ������ (������� � ������)
    *   2     ���������� ���������
    *   3, 4  �������� ���������: (3) ���������� � (4) ������ ��������
    *
    * ������ ����������� ������� � ������ ���������
    *   - �� ������������
    *
    * ������ ����������� ������� � ������������ ���������
    *   - �� ������������
    *
    * ������ ����������� ������� � ������ ���������
    *   - 0, ... @todo �������������� ������
    */
    typedef cl_float r_t[ SURFACE_VOID_REGISTRY ];
    r_t r;

} aboutOneSurfaceVoid_t;

//typedef aboutOneSurfaceVoid_t aboutSurfaceVoid_t[ SURFACE_VOID_GRID * SURFACE_VOID_GRID * SURFACE_VOID_GRID ];
typedef struct {
    aboutOneSurfaceVoid_t about[ SURFACE_VOID_GRID * SURFACE_VOID_GRID * SURFACE_VOID_GRID ];
} aboutSurfaceVoid_t;
#endif




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
