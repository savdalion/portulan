#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>


/**
*   # ��������� ��������� ���, ����� �� ����������� �� ��� ���������
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






// ����������� ���������, ������������ � ������������� ��� (OpenCL 1.0
// �� ������������ NS)
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
#define __structComponentAll_t      component::componentAll_t
#define __structPortionComponent_t  component::portionComponent_t
#define __structPortionEnergy_t     component::portionEnergy_t
#define __enumCodeComponent         component::CODE_COMPONENT
#define __enumCodeEnergy            component::CODE_ENERGY

#define __structLivingAll_t         living::livingAll_t

#define __structTemperatureAll_t    temperature::temperatureAll_t

#else
#define __structComponentAll_t      componentAll_t
#define __structPortionComponent_t  portionComponent_t
#define __structPortionEnergy_t     portionEnergy_t
#define __enumCodeComponent         enum CODE_COMPONENT
#define __enumCodeEnergy            enum CODE_ENERGY

#define __structLivingAll_t         livingAll_t

#define __structTemperatureAll_t    temperatureAll_t

#endif





/**
* ��������, �������� ������������, ��������, ������ �����, ��
* ����������� �������� �����������.
* ��������, ����� ������� ����� �� ��������� ��� ����������� �� ��
* ����� "������ �����".
*/
static __constant cl_float IMMUNE = CL_FLT_MAX;



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
// � OpenCL ������� ��������� ��� define: OpenCL �� ������������
// ��������� ������� �������.

/**
* ������ ����� ����������� � ������� ������� (� ���������).
*/
static __constant size_t COMPONENT_GRID = 81;



/**
* ����. ���-�� *������* �����������, ������� ����� ��������������
* � ������� ������� (� ���������).
*/
static __constant size_t COMPONENT_COUNT = 100;



/**
* ����. ���-�� ����������� � ��������� ������ �� ������, ������� �����
* *������������* ��������� � 1-� ������ ���������.
*/
static __constant size_t COMPONENT_CELL = 20;



/**
* ��������� ���� ����� �� ������� (���������, ��������).
*
* # ���� ��������� ��������:
*     0    �������� ������, ������.
*     1    ����, ������.
*     2    ��������.
*     3    �������.
*     4    ̸����� ����� - ����, �������.
*     5    ����������� �����.
*/
static __constant size_t LIFE_CYCLE = 6;



/**
* ������ ����� ������� �������� ����� ���������� � ������� �������.
*/
static __constant size_t LIVING_GRID = 81 / 3;



/**
* ������������ ���-�� *������* ������ (�������), �� ������� �����
* �������� �����.
*/
static __constant size_t PART_LIVING_COUNT = 20;



/**
* ������������ ���-�� *������* ����, ��������� ������ �����.
*
* @see RESIST_PART_LIVING_COUNT
*/
static __constant size_t ATTACK_PART_LIVING_COUNT = 30;



/**
* ������������ ���-�� *������* �����, ��������� ������ �����.
*
* @see ATTACK_PART_LIVING_COUNT
*/
static __constant size_t RESIST_PART_LIVING_COUNT = 30;



/**
* ������������ ���-�� ������� ���� ��������, � ������� �����
* ���� �����.
*/
static __constant size_t HABITAT_LIVING_COUNT = 5;



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
* ������������ ���������� ����, ��� ����� ������� �����.
*/
static __constant size_t ENVIRONMENT_SURVIVOR_LIVING = 5;



/**
* ����������� ��������� ���-�� *������* ������ � ������� �������.
*/
static __constant size_t LIVING_COUNT = 100;



/**
* ����. ���-�� ������, ������� ����� *������������* ������� � 1-� ������
* ������� �������.
*/
static __constant size_t LIVING_CELL = 20;



/**
* ����� ������������� ����������� � ������� �������.
*/
static __constant size_t TEMPERATURE_GRID = 81;





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
*   # ������������ �� ����� �������� UNDEFINED, �.�. ����������� ������������
*     ������������ � �������� ������� ��������.
*/
enum GROUP_ELEMENT {
    // ���������� (������, ����������� �����, ������ � �.�.)
    GE_COMPONENT,
    // �������
    GE_ENERGY,
    // ����� ��������, ��������
    GE_LIVING,
    // ����� ����� �������, ��������
    GE_PART_LIVING,
    // @todo ������, ��. precipitations_t
    // GE_PRECIPITATIONS,

    // ���������
    GE_last
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




/*
typedef struct __attribute__ ((packed)) {
    float t[ 100 ];
} test_t;
*/




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif