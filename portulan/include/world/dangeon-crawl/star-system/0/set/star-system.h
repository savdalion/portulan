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
    real_t size[ 3 ];

    // # ����� ���������� � ������� ������� ������������� � structure.h.

} aboutStarSystem_t;




/**
* ������ ����������������� ���.
* ����������� � �����������, ����� ���������� ������������
* ������ � ������� OpenCL.
*
* # ����� �������������� ����, ������� ������ ��������, ����� �������� �������.
*/
typedef union __attribute__ ((packed)) {
    aboutPlanet_t  planet;
    aboutStar_t    star;
} aboutBodyWithoutGroup_t;

typedef struct {
    enum GROUP_ELEMENT       group;
    aboutBodyWithoutGroup_t  content;
} aboutBody_t;





/**
* ������������ ���� ������ � ������� �������.
*
* # ���� ���� ����������� - ���������, ����� �� ������� ������� �������
*   � �.�. - ��� ����� = 0.
*/
typedef aboutBody_t  bodyContent_t[ BODY_COUNT ];




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
