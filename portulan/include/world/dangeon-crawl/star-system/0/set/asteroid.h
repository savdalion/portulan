#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� �� ���������� � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ������ ��������� � �������� � ������� �������.
*
* @see #���������� � 'event_t'.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������ ("�����" - ��. ���� 'SpaceChem') ��� ������ �������� �������.
    * [0; *_EVENT_COUNT - 1]
    *
    * # ��������� ���� �������������, ����� �������� ������ � ���.
    */
    cl_int   waldo;

    event_t  content[ ASTEROID_EVENT_COUNT ];
    
} asteroidMemoryEvent_t;




/**
* ���������� �� ��������� � ������� �������.
* ������� ����� �� �����������: ����� MapContent3D - ������� ��������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������� ���������.
    */
    uid_t uid;

    /**
    * �������� ��������������� � ������� ���������� ������� �������.
    */
    bool live;

    /**
    * ����� ���������, ��.
    */
    real_t mass;

    /**
    * ������� ��������� �� XYZ, �.
    */
    real_t size[ 3 ];

    /**
    * ���������� ��������� � ������� �������, XYZ, �.
    */
    real_t coord[ 3 ];

    /**
    * ������ ��������� �� XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * ������ �������������� ���, ����������� �� ��������, �.
    */
    real_t force[ 3 ];

    /**
    * �������� �������� ��������� � ������� �������, XYZ, �/�.
    */
    real_t velocity[ 3 ];


    /**
    * �������, ������� ��������� � ����������.
    * @see #���������� � 'event_t'.
    */
    asteroidMemoryEvent_t memoryEvent;


    /**
    * @see star.h
    */
    real_t tm[ 16 ];


    /**
    * �������� �����.
    */
    real_t test[ 5 ];

} aboutAsteroid_t;




/**
* ������������ ���� ���������� � ������� �������.
*
* # ���� ���� ����������� - ���������, ����� �� ������� ������� �������
*   � �.�. - ��� ����� = 0.
* # ������������� �������� - ������ ����� ������.
*/
typedef aboutAsteroid_t asteroidContent_t[ ASTEROID_COUNT ];




/**
* ��������� � ������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    asteroidContent_t content;
} asteroid_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
