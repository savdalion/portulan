#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    #pragma error( "Double precision floating point not supported by OpenCL implementation." )
#endif

#include <CL/cl_platform.h>


/**
* # ��� ������� ������� ������� ���� � double: float ��� ��������
*   �����������.
* # ���������� (0, 0, 0) - ����� ������� �������.
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
#endif




/**
* ������ ��������� ������� �������.
*/
enum GROUP_ELEMENT {
    // ������ ������ ��� �����������
    GE_NONE = 0,

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
* ����. ���-�� ���, ������� ����� ������������ (�����������������)
* � ������� ������� ������� (� ���������).
*/
static __constant size_t BODY_COUNT = 5000;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
