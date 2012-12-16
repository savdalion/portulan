#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

/* - ?
#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    #pragma error( "Double precision floating point not supported by OpenCL implementation." )
#endif
*/

#include <CL/cl_platform.h>


/**
* # ��� ������� ������� ������� ���������� ����� � double: float ���
*   �������� �����������.
* # ���������� (~0, ~0, ~0) - ����� ������� �������.
* # ��������� ������������ �. �., ����� �� ����������� �� ��� ���������
*   � ��� OpenCL.
*/
#define __constant const

// ������������ ��� VC++ �� ���������
#define __attribute__(x) /*nothing*/

namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

// ���, �� ��� ���������� ������������ 'double' ��� OpenCL.
// #! ���� ������ ������ ���� ����������� � OpenCL GPU.
// # double4 �������������� �� ����� ������������ OpenCL. �� ����������.
#if defined( PERMIT_DOUBLE_ENGINE_PORTE )
typedef cl_double  real_t;
#else
typedef cl_float   real_t;
#endif

#endif




/**
* ������ ��������� ������� �������.
*/
enum GROUP_ELEMENT {
    // ������ ������ ��� �����������
    GE_NONE = 0,

    // ��������
    // @see asteroid_t
    GE_ASTEROID,

    // �������
    // @see planet_t
    GE_PLANET,

    // ������
    // @see star_t
    GE_STAR,

    // ���������
    GE_last
};




/**
* �������, ������� ����� ��������� ��� ��������� ������� �������.
*/
enum EVENT {
    // ������ ������� ��� �����������
    E_NONE = 0,

    // ������������ ��������� ������� �������
    E_COLLISION,

    // ���������
    E_last
};





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # � OpenCL ������� ��������� ��� define: OpenCL �� ������������
//   ��������� ������� �������.


/**
* ����. ���-�� ���������, ������� ����� ������������ (�����������������)
* � ������� ������� ������� (� ���������).
*/
static __constant size_t ASTEROID_COUNT = 1000;
static __constant size_t PLANET_COUNT = 100;
static __constant size_t STAR_COUNT = 10;



/**
* ����. ���-�� �������, ������� �������� ������� �������.
*
* @see event_t
*/
static __constant size_t ASTEROID_EVENT_COUNT = 10;
static __constant size_t PLANET_EVENT_COUNT = 10;
static __constant size_t STAR_EVENT_COUNT = 10;


#endif





/**
* ������������� ��������, ���������� � �������� ������.
* ������������� ������ UID ��������, �.�. �������� ������� �� ��������
* �� ���� ����� (������ �������).
*/
typedef cl_int  uid_t;




/**
* ��������� �� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT ge;

    /**
    * ������ � ������ ���������.
    */
    cl_uint ii;

    /**
    * ����. �����. � ������ ���������.
    * �����, �.�. �� ������ ������������� �������� ����� ������ ���
    * ��������� UID ��������.
    */
    uid_t uu;

} pointerElement_t;





/**
* ������� ��� ��������� ������� �������.
*
* ���������� ��� *MemoryEvent_t
*   # ������ ������� ������� ������� ������ � *_EVENT_COUNT ��������,
*     ������� ���-�� �������������� �� ���� - ��. *ImpactIn().
*   # ������� ������������ ��������������� �� ������� ��������� � �������.
*   # ������ ��� ������ �������� ������� ������ ����� � ���������
*     [0; *_EVENT_COUNT - 1]
*   # ������ ������� ������������ �� ������� 0.
*   # ������ ������ ������� ����������� ������ �� 1.
*   # ��� ���������� ������� *_EVENT_COUNT, ������ ��������� �� 1-� �������.
*
* @todo extend �������� � �������� ���������: ��� �������� "��������������"
*       ���������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    EVENT uid;

    /**
    * ������ �������-�������� �������.
    * ��������, ��� ������������ � ��������, ����� ���������
    * ��������� �� ������� � ������ ��������� ���������.
    */
    pointerElement_t pi;

} event_t;



/**
* ��������� ��� ����������������� ����������� �� �������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    pointerElement_t pi;

    /**
    * ������ ������� � ������ ��������.
    */
    cl_uint kk;

} pointerEvent_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
