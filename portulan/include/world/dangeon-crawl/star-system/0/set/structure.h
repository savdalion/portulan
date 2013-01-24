#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

// #! ��������� OpenCL � C++ ������ ���� ����������� �������.
//    ������ �������� ����� �������� �� ���������, ������� ��������
//    ��������� ��������� � ������� "���������".
#pragma pack( 1 )


/* - ?
#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    #pragma error( "Double precision floating point not supported by OpenCL implementation." )
#endif
*/

#include "../../../../../../configure.h"
#include <CL/cl_platform.h>
#include <string>
#include <ostream>


/**
* # ��� ������� ������� ������� ���������� ����� � ������� ���������:
*   ������ float ��� �������� �����������.
* # ���������� (~0, ~0, ~0) - ����� ������� �������.
* # ��������� ������������ �. �., ����� �� ����������� �� ��� ���������
*   � ��� OpenCL.
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
            namespace starsystem {
                namespace l0 {
                    
// # �.�. �� ��� ���������� ������������ 'double' ��� OpenCL � �� ��� CPU
//   �� ������� ��������� ������������ ������� �������� (�� CPU Intel i5 ���
//   Windows ��� �� ������� ���������� ���������� cl_khr_fp64), � ���������
//   �� ������ � ����� 'double' � ������ ��������� �����, ��� ���������
//   ������� ��������.
typedef cl_float   real_t;
typedef cl_float2  real2_t;
typedef cl_float4  real4_t;

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

    // ��������� �������������
    // # �������� � ���� �� ���������� � ����������.
    E_CHANGE_COORD,
    E_CHANGE_MASS,
    E_CHANGE_SIZE,
    E_CHANGE_TEMPERATURE,
    E_CHANGE_VELOCITY,

    // ���������� �������������
    E_DECREASE_MASS,
    E_DECREASE_SIZE,
    E_DECREASE_TEMPERATURE,
    E_DECREASE_VELOCITY,

    // ���������� �������������
    E_INCREASE_MASS,
    E_INCREASE_SIZE,
    E_INCREASE_TEMPERATURE,
    E_INCREASE_VELOCITY,

    // ������������ �� N ������
    E_CRUSH_N,

    // ����������� ��������
    E_DESTROY,

    // ������������ / ������������ ����������� ������ ��������
    E_GRAVITY,

    // ���� ����������
    E_IMPACT_ACCELERATION,

    // ����������� ����
    E_IMPACT_FORCE,

    // ��������� ������� (��������, ���� ������)
    E_RADIATION,

    // ���������
    E_last
};




#if 0
// - ?
/**
* ������ ���������, ������� ����� ���� ������� *�����������* ����������
* ������� �������.
*
* # ������������� ��� ������������, ����� ������ ����� ���� ������������
*   � ����� OpenCL.
*/
enum MODEL {
    // ������ ������ ��� �����������
    M_NONE = 0,

    /**
    * �����, ������� ������ �� ������.
    */
    M_GROW_UP_EAT_SUN_LIGHT,

    // ���������
    M_last
};
#endif





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # � OpenCL ������� ��������� ��� define: OpenCL �� ������������
//   ��������� ������� �������.


/**
* ����. ���-�� ���������, ������� ����� ������������ (�����������������)
* � ������� ������� ������� (� ���������).
*
* # ����������� �� 1 ������� ������, ����� � ���� �� �������������� �
*   ��������� ���������� �������� ��������� ������.
*/
static __constant size_t ASTEROID_COUNT = 500 + 1;
static __constant size_t PLANET_COUNT = 100 + 1;
static __constant size_t STAR_COUNT = 10 + 1;



/**
* ����. ���-�� �������������, ������� ����� ��������� �������.
*
* @see eventTwo_t
*/
static __constant size_t FEATURE_EVENT_COUNT = 6;




/**
* ����� ����. ���-�� ������� ����� ������ ������� �� 1 �����.
*/
static __constant size_t EMITTER_EVENT_COUNT = 10;




/**
* ����� ����. ���-�� ���������� ������� ��������� �������� ��������� �������.
*
* @todo �������������� ������ ��� ������ ������ ���������.
* @todo extend �������������� ������ ��� ������� ����������� ��������.
*/
static __constant size_t MEMORY_MODEL_COUNT = 7;




/**
* ������� ���������� ������� ��������� ���� ������� ����� ��������� ���
* ���������� ����� ����������� ���������� �������.
*
* @todo �������������� ������ ��� ������ ������ ���������.
* @todo extend �������������� ������ ��� ������� ����������� ��������.
*/
static __constant size_t FREQUENCY_MEMORY_MODEL_COUNT = 5;




/**
* ���� �� ������� �������������� "������� �����".
*
* # "������� �����" ������ � ��������� real4_t.
* # ������ ��������� - ���������� ����������� �������� ����������
*   1D-���������� � ����������� ������� ���������.
* # ����� ��������� �������� ������������ �������. ��������
*   7-8 ���������� ���� � ��������� ( 1e-38; 1e38 ).
*
* @see utils.h / convertToBigValue() ��� ��������� float-�������� � real4_t.
* @see utils.h / convertFromBigValue() ��� ��������� real4_t ��� float ��� double.
* @see �������. � typedef real*_t.
*
* @see utils.h / convertBigValue()
*/
static __constant real_t BIG_VALUE_BASE_0 = static_cast< real_t >( 1e10 );
static __constant real_t BIG_VALUE_BASE_1 = static_cast< real_t >( 1e20 );
static __constant real_t BIG_VALUE_BASE_2 = static_cast< real_t >( 1e30 );
// # �������� ����� ������������ � float ����������� � BIG_VALUE_BASE_3 ���.
static __constant real_t BIG_VALUE_BASE_3 = static_cast< real_t >( 1e37 );




/**
* ������������ �������� ������������� �����.
*
* @see real_t
*/
static __constant real_t REAL_MAX = std::numeric_limits< real_t >().max();


#endif





/**
* ������������� ��������, ���������� � �������� ������.
* ������������� ������ UID ��������, �.�. �������� ������� �� ��������
* �� ���� ����� (������ �������).
*/
typedef cl_int  uid_t;




/**
* ������������� �������� � ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT ge;
    uid_t uid;
} uidElement_t;




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
* 3D-��������� ��� �������������� �������� � ������� �������.
* ��������, ���������� ��������, ������ ��������.
*
* # ������ � real4_t ��� ����������� ������ � OpenCL.
* # �������� �������� �������� ����������������� � *�����* ��������������
*   �������. ��������, � �� ����� ��������� ����� XYZ-�������.
*
* @see utils.h / convert*BigValue() ��� ������ � "�������� �������".
*/
typedef real4_t  small3d_t;


typedef struct __attribute__ ((packed)) {
    real4_t x;
    real4_t y;
    real4_t z;
} big3d_t;




/**
* ������� ��� ��������� ������� �������.
*
* ���������� ��� emitterEvent_t
*   # ������ ������� ������� ������� ������ � EMITTER_EVENT_COUNT ��������,
*     ������� ���-�� �������������� �� ���� - ��. *ImpactIn().
*   # ������� ������������ ��������������� �� ������� ��������� � �������.
*   # ������ ��� ������ �������� ������� ������ ����� � ���������
*     [0; EMITTER_EVENT_COUNT - 1]
*   # ������ ������� ������������ �� ������� 0.
*   # ������ ������ ������ ������� ����������� ������ �� 1.
*   # ��� ���������� ������� EMITTER_EVENT_COUNT, ������ ����� ���������
*     �� ������ ������ ������ ��� �������.
*/
typedef struct __attribute__ ((packed)) {
    enum EVENT uid;

    /**
    * ������ �������-�������� �������.
    * ��������, ��� ������������ �������� � ��������, ����� ���������
    * ��������� �� ������� � ������ ��������� ���������.
    */
    pointerElement_t pi;

    /**
    * �������������� �������.
    *
    * #i ������ ���� �� �������� ������������� � ���� union-��������, ��
    *    OpenCL 1.0 �� ������ � ������� �������� ��������.
    */
    real_t fReal[ FEATURE_EVENT_COUNT ];

} eventTwo_t;




/**
* ��� ���������� ��������� �� 1 ����� �������.
*/
typedef struct __attribute__ ((packed)) {
    cl_int waldo;
    eventTwo_t content[ EMITTER_EVENT_COUNT ];
} emitterEvent_t;




/**
* ��������� ��� ����������� �� ���� �������� ��������.
*/
typedef cl_uint  pointerEvent_t;




/**
* UID ��� ������� ���������.
* 
* # �������� �������� �������, �.�. ������ ��������� � ���� ���� OpenCL.
*
* @todo optimize bad ����� �� ������� ��������� ������ - ������ '\0'.
*
* @see model_t
*/
typedef cl_char  uidModel_t[ 10 + 1 ];




/**
* ������ ��������� ��� ��������� ������� �������.
* ��� ������ ������ ������� *����������*.
*
* ���������� ��� memoryModel_t
*   # �� �� ����������, ��� ��� emitterEvent_t.
*/
typedef struct __attribute__ ((packed)) {
    uidModel_t uid;

    // @todo ������ ������ ����� ������������ ����� �� � �������
    //       ���������� �������.

} model_t;




/**
* ��� ��������� ��������� ������ ���������.
*/
typedef struct __attribute__ ((packed)) {
    cl_int waldo;
    model_t content[ MEMORY_MODEL_COUNT ];
} memoryModel_t;




/**
* ��������� ��� 'frequencyMemoryModel_t'.
*/
typedef struct __attribute__ ((packed)) {
    uidModel_t uid;

    /**
    * ������� ������� ������ ������ ���������� ������ �� ������ ����������
    * �� ��������.
    *
    * # ���������� ������������ ������ ������� � �������, �.�. ��� �����
    *   ��� ���������� � �������, ��� �������� � ��������.
    */
    cl_int skipPulse;

} frequencyModel_t;




/**
* ������ ���������, ������� ����� ����������� ��������� �����
* ����������� ���������� �������.
*
* # ��� ������������� � ���� ������ ������ ���� � 'memoryModel'.
*/
typedef struct __attribute__ ((packed)) {
    cl_int waldo;
    frequencyModel_t content[ FREQUENCY_MEMORY_MODEL_COUNT ];
} frequencyMemoryModel_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
