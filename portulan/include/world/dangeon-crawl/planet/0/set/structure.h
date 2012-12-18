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
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
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
* ����������� � 3D.
* ������������ �������� �������.
*   # ���������� ����, ��������������� ��������� ����� (��. ����).
*
* @copy typelib::StaticMapContent3D
* ������� ���������� ������ 3D-������ (��������), �������� 3-�� �����������.
* ������� �� ��� OY �� ��� 3x3x3. ��� Z ���������� �����.
* ������� ������� (�����������) 2D ���� - �������� ��� �������� isc2D().
* ������� ������� - �������� �����. ������� ������� ���� - ����������.
*
    ���������, ������������ ������:

    ������� 2D ����
    26   19   23
    22   18   20
    25   21   24

    ����������� 2D ����
    8   1   5
    4   0   2
    7   3   6

    ������� 2D ����
    17   10   14
    13    9   11
    16   12   15
*/
enum DIRECTION {
    // ����������� ����������� ��� �� ����������
    D_NONE = 1 << 0,

    // ����������� 2D ����
    D_00 = D_NONE,
    D_01 = 1 << 1,
    D_ZENITH = D_01,
    D_02 = 1 << 2,
    D_EAST = D_02,
    D_03 = 1 << 3,
    D_NADIR = D_03,
    D_04 = 1 << 4,
    D_WEST = D_04,
    D_05 = 1 << 5,
    D_06 = 1 << 6,
    D_07 = 1 << 7,
    D_08 = 1 << 8,

    // ������� 2D ����
    D_09 = 1 << 9,
    D_SOUTH = D_09,
    D_10 = 1 << 10,
    D_11 = 1 << 11,
    D_12 = 1 << 12,
    D_13 = 1 << 13,
    D_14 = 1 << 14,
    D_15 = 1 << 15,
    D_16 = 1 << 16,
    D_17 = 1 << 17,

    // ������� 2D ����
    D_18 = 1 << 18,
    D_NORTH = D_18,
    D_19 = 1 << 19,
    D_20 = 1 << 20,
    D_21 = 1 << 21,
    D_22 = 1 << 22,
    D_23 = 1 << 23,
    D_24 = 1 << 24,
    D_25 = 1 << 25,
    D_26 = 1 << 26,
};





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
* ����� ������������� ��������� ��������� � ������� �������.
*/
static __constant size_t LANDSCAPE_GRID = 27;



/**
* ����. ���-�� ��������� ���������, ������� ����� *������������* ���������
* � 1-� ������ ���������.
*/
static __constant size_t LANDSCAPE_CELL = 30;





/**
* ����� ������������� ������������ � ������� �������.
*/
static __constant size_t ILLUMINANCE_GRID = 27;



/**
* ����������� ��������� ���-�� ���� ��� �������� ������������.
*
* @see illuminance-utils.h
*/
static __constant size_t ILLUMINANCE_STAR_COUNT = 10;




/**
* ����� ������������� ������ � ������� �������.
*/
static __constant size_t BIOME_GRID = 81;



/**
* ����������� ��������� ���-�� *������* ������ � ������� �������.
* >= CB_last
*
* @see CODE_BIOME
*
* #! ��������� ���� ����� �� �������� � ���� ����������� �� ������ ���
*    ��� ������� BIOME_COUNT.
*/
static __constant size_t BIOME_COUNT = 20;



/**
* ����. ���-�� ������, ������� ����� *������������* ���������
* � 1-� ������ ���������.
*/
static __constant size_t BIOME_CELL = 3;



/**
* ���-�� ������ ��������� ���������, ������� ����� ���� ������ � ��������
* �������������� ��� �����.
*
* @see CEL_last
*/
static __constant size_t LANDSCAPE_BIOME_COUNT = 10;





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
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
