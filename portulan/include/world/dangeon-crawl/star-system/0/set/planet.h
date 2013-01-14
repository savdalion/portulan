#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� � �������� � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ������ ������� � �������� � ������� �������.
*
* @see ����������� � 'asteroid.h'.
*/
typedef struct __attribute__ ((packed)) {
    cl_int   waldo;
    event_t  content[ PLANET_EVENT_COUNT ];
} planetMemoryEvent_t;




/**
* ���������� � ������� � ������� �������.
* ������� ����� �� �����������: ����� MapContent3D - ������� ��������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������� �������.
    */
    uid_t uid;

    /**
    * ������� ��������������� � ������� ���������� ������� �������.
    */
    bool live;

    /**
    * ����� �������, ��.
    *
    * @see pns::massPlanet()
    */
    mass_t mass;

    /**
    * ������ �������, �.
    */
    real_t radius;

    /**
    * ���������� ������� � ������� �������, XYZ, �.
    */
    real_t coord[ 3 ];

    /**
    * ������ ������� �� XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * ������ �������������� ���, ����������� �� �������, �.
    */
    real_t force[ 3 ];

    /**
    * �������� �������� ������� � ������� �������, XYZ, �/�.
    */
    real_t velocity[ 3 ];

    /**
    * ������ ��� �������, �������.
    *
    * @see http://en.wikipedia.org/wiki/Axial_tilt
    */
    real_t axilTilt;

    /**
    * ������ �������� �������, �.
    */
    real_t rotationPeriod;


    /**
    * �������, ������� ��������� � ��������.
    * @see #���������� � 'event_t'.
    */
    planetMemoryEvent_t memoryEvent;


    /**
    * @see star.h
    */
    real_t tm[ 16 ];


    /**
    * �������� �����.
    */
    real_t test[ 5 ];

} aboutPlanet_t;




/**
* ������������ ���� ������ � ������� �������.
*
* # ���� ���� ����������� - ���������, ����� �� ������� ������� �������
*   � �.�. - ��� ����� = 0.
* # ������������� ������� - ������ ����� ������.
*/
typedef aboutPlanet_t  planetContent_t[ PLANET_COUNT ];




/**
* ������� � ������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    planetContent_t content;
} planet_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
