#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� � ������ � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ���������� � ������ � ������� �������.
* ������� ����� �� �����������: ����� MapContent3D - ������� ��������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������� ������.
    */
    uid_t uid;

    /**
    * ����� ������, ��.
    */
    real_t mass;

    /**
    * ������ ������, �.
    */
    real_t radius;

    /**
    * ������� �����������, �.
    */
    real_t temperature;

    /**
    * ���������� ������ � ������� �������, XYZ, �.
    */
    real_t coord[ 3 ];

    /**
    * ������ ������ �� XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * ������ �������������� ���, ����������� �� ������, �.
    */
    real_t force[ 3 ];

    /**
    * �������� �������� ������ � ������� �������, XYZ, �/�.
    */
    real_t velocity[ 3 ];


    /**
    * �������, ������� ��������� �� ������� � � ������� ��� ������.
    */
    //event_t event[ STAR_EVENT_COUNT ];


    /**
    * ���������� ������������ ���������� ��������, ����� ��������������
    * ������ � ���������.
    *
    * @example EngineND
    *
    * # ���������� ���� ����������� �������.
    * # ��� ��������� ���������� ���������� � ���������� ����, ������
    *   ���� ������ ����� Engine::sync().
    */
    real_t tm[ 16 ];


    /**
    * �������� �����.
    */
    real_t test[ 5 ];

} aboutStar_t;




/**
* ������������ ���� ���� � ������� �������.
*
* # ���� ���� ����������� - ���������, ����� �� ������� ������� �������
*   � �.�. - ��� ����� = 0.
* # ������������� ������ - ������ ����� ������.
*/
typedef aboutStar_t starContent_t[ STAR_COUNT ];




/**
* ����� � ������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    starContent_t content;
} star_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
