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
* ������ ������ � �������� � ������� �������.
*
* @see ����������� � 'asteroid.h'.
*/
typedef struct __attribute__ ((packed)) {
    cl_int   waldo;
    event_t  content[ STAR_EVENT_COUNT ];
} starMemoryEvent_t;




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
    * ������ ��������������� � ������� ���������� ������� �������.
    */
    bool live;

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
    * ���� �����, ��.
    *
    * @source http://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D0%BB%D0%B0_%D1%81%D0%B2%D0%B5%D1%82%D0%B0
    */
    real_t luminousIntensity;

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
    * �������, ������� ��������� �� �������.
    * @see #���������� � 'event_t'.
    */
    starMemoryEvent_t memoryEvent;


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
