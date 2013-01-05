#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>


/**
*   # ��������� ������������ �. �., ����� �� ����������� �� ��� ���������
*     � ��� OpenCL.
*/
#ifndef __constant
#define __constant const
#endif

#ifndef __global
#define __global /*nothing*/
#endif

// ������������ ��� VC++ �� ���������
#define __attribute__(x) /*nothing*/


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {
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
    CRITERIA_NONE = 0,
    CRITERIA_EMPTY = CRITERIA_NONE,
    CRITERIA_A_WHITE = CRITERIA_NONE,
    // ���� �������� / ����
    CRITERIA_B_GREEN,
    // ������� �������� / ���������
    CRITERIA_C_BLUE,
    // ���� �������� / �����
    CRITERIA_D_YELLOW,
    // ��������� ������������� / �������������
    CRITERIA_E_RED,

    // ��������� = ���-�� ���������
    CRITERIA_last,
    CRITERIA_count = CRITERIA_last
};





/**
* ��������� ���� ����� (���������, ��������).
*
* @see LIFE_CYCLE_COUNT
*/
enum LIFE_CYCLE {
    // ������� �����, ����
    LC_EMBRYO   = 0,
    // ������, ������
    LC_CHILD    = 1,
    // ��������
    LC_ADULT    = 2,
    // ������
    LC_OLD      = 3,
    // ̸����� ����� - ����, ������
    LC_DEAD     = 4,
    // ����������� �����
    LC_IMMORTAL = 5,

    // ��������� = ���-�� ������
    LC_last,
    LC_count = LC_last
};





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
* ����������� ��������� ���-�� *������* ������.
* >= CC_last
*
* @see CODE_LIVING
*/
static __constant size_t LIVING_COUNT = 100;



#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
