#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "planet.h"
#include "star.h"


/**
* ���������� � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ���������� � ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������ ������� �������, XYZ, �.
    */
    cl_double size[ 3 ];

    // # ����� ���������� � ������� ������� ������������� � structure.h.

} aboutStarSystem_t;




/**
* ������ ����������������� ���.
* ����������� � �����������, ����� ���������� ������������
* ������ � ������� OpenCL.
*
* # ������ ���� ����� �����: �����[0] � ������[1]. �.�. ������ �������
*   ������������ ������� � ������ OpenCL.
*   ��. - NVidia / OpenCL / ������ NBody.
* # ����� �������������� ���� ����� �������� �������.
*/
typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT  group;
    aboutPlanet_t       content[ 2 ];
} planet_t;

typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT  group;
    aboutStar_t         content[ 2 ];
} star_t;

typedef union __attribute__ ((packed)) {
    planet_t  planet;
    star_t    star;
} aboutBody_t;




/**
* ������������ ���� ������ � ������� �������.
*
* # ���� ���� ����������� - ���������, ����� �� ������� ������� �������
*   � �.�. - ��� ����� = 0.
*/
typedef aboutBody_t*  bodyContent_t;




/**
* ������� � ������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    bodyContent_t content;
} body_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
