#pragma once

#include <CL/cl_platform.h>


/**
*   # ��������� ��������� ���, ����� �� ����������� �� ��� ���������
*     � ��� OpenCL.
*/

namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {

/**
* ��������, �������� ������������, ��������, ������ �����, ��
* ����������� �������� �����������.
* ��������, ����� ������� ����� �� ��������� ��� ����������� �� ��
* ����� "������ �����".
*/
static const cl_float IMMUNE = CL_FLT_MAX;



/**
* ������� ���������.
* �������� �����, ����� ���� ���� ��� ���� ��������� ��� ��� OpenCL.
* �� ����������� �������, ����� ������ �� C++ ����� ��������� �����������
* � OpenCL.
*
* @todo extend ��������� ������������ ������ ���������� �����.
*//* - ���������� ��-�� �����. ��. ����.
static const size_t GRID_SX = 81;
static const size_t GRID_SY = GRID_SX;
static const size_t GRID_SZ = GRID_SX;
*/


/**
* ������� ������� ������� �� ������.
* ������������ ��� ������������ ������ "�������" ����������, �������������
* ������� ������� � � ����� (�������, �������� ������� � "porte"). ��. ����.
*/
static const size_t GRID = 81;




/**
* ������ ����� ����������� � ������� ������� (� ���������).
*/
static const size_t COMPONENT_GRID = GRID;



/**
* ����. ���-�� *������* �����������, ������� ����� ��������������
* � ������� ������� (� ���������).
*/
static const size_t COMPONENT_COUNT = 100;



/**
* ����. ���-�� ����������� � ��������� ������ �� ������, ������� �����
* *������������* ��������� � 1-� ������ ���������.
*/
static const size_t COMPONENT_CELL = COMPONENT_COUNT / 10;



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
static const size_t LIFE_CYCLE = 6;



/**
* ������ ����� ������� �������� ����� ���������� � ������� �������.
*/
static const size_t LIVING_GRID = GRID / 3;



/**
* ������������ ���-�� *������* ������ (�������), �� ������� �����
* �������� �����.
*/
static const size_t PART_LIVING_COUNT = 20;



/**
* ������������ ���-�� *������* ����, ��������� ������ �����.
*/
static const size_t ATTACK_PART_LIVING_COUNT = 30;



/**
* ������������ ���-�� *������* �����, ��������� ������ �����.
*/
static const size_t RESIST_PART_LIVING_COUNT = ATTACK_PART_LIVING_COUNT;



/**
* ������������ ���-�� ������� ���� ��������, � ������� �����
* ���� �����.
*/
static const size_t HABITAT_LIVING_COUNT = 5;



/**
* ������������ ���-�� *������* ���. �����������, �� ������� �����
* �������� ����� �����.
*/
static const size_t COMPONENT_COMPOSITION_LIVING = 5;



/**
* ������������ ���-�� *������* ���. �����������, ������� �����
* ����� ��� ����������� �����.
*/
static const size_t COMPONENT_NEED_LIVING = 10;



/**
* ������������ ���-�� *������* ���. �����������, ������� ��������
* ����� ��� �����������������.
*/
static const size_t COMPONENT_WASTE_LIVING = COMPONENT_NEED_LIVING;



/**
* ������������ ���-�� *������* ����� �������, ������� ����������
* ����� ��� ����������� �����.
*
* @see CODE_ENERGY
*/
static const size_t ENERGY_NEED_LIVING = 5;



/**
* ������������ ���-�� *������* ����� �������, ������ ��������
* ����� ��� �����������������.
*
* @see CODE_ENERGY
*/
static const size_t ENERGY_WASTE_LIVING = ENERGY_NEED_LIVING;



/**
* ������������ ���������� ����, ��� ����� ������� �����.
*/
static const size_t ENVIRONMENT_SURVIVOR_LIVING = 5;



/**
* ����������� ��������� ���-�� *������* ������ � ������� �������.
*/
static const size_t LIVING_COUNT = 100;



/**
* ����. ���-�� ������, ������� ����� *������������* ������� � 1-� ������
* ������� �������.
*/
static const size_t LIVING_CELL = LIVING_COUNT / 4;



/**
* ������ ����� �������� �� �������.
* ����������� ��� ���� �������.
* ��������� ������� �������� � ��������� ��������� �����, �������.
*/
static const size_t PRESSURE_GRID = GRID;



/**
* ����� ������������� ����������� � ������� �������.
*/
static const size_t TEMPERATURE_GRID = GRID;



/**
* ����� ������������� ������� � ������� �������.
*/
static const size_t PRECIPITATIONS_GRID = GRID;



/**
* ����� ��� ��������� ����������� / ������ � ������� �������.
*/
static const size_t SURFACE_VOID_GRID = GRID;



/**
* ���������� ��������� ��� ��������� ����������� / ������ �
* ������� �������.
*/
static const size_t SURFACE_VOID_REGISTRY = 5;






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
    GE_count
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
* *������* ����� � ������� �������.
*/
//typedef aboutOneLiving_t aboutLiving_t[ LIVING_COUNT ];
typedef struct {
    aboutOneLiving_t about[ LIVING_COUNT ];
} aboutLiving_t;





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
* ����������� ������� �������.
*/
typedef struct {
    /**
    * ������� �������� �����������, �.
    */
    typedef cl_float average_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    average_t average;

    /**
    * ���������� ����������� �� �������� ��������, % / 100.
    */
    typedef cl_float dispersion_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    dispersion_t dispersion;

    /**
    * ������� ���������� ����������� �� �������� ��������, ��� / �����.
    */
    typedef cl_float rate_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    rate_t rate;

} temperature_t;






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


            } // dungeoncrawl
        } // set
    } // planet
} // portulan
