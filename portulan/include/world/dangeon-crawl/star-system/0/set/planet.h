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
* ���������� � ������� � ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������� ��������������� � ������� ���������� ������� �������.
    */
    bool live;

    /**
    * ����� �������, ��.
    *
    * @see pns::massPlanet()
    */
    real4_t mass;

    /**
    * ������ �������, �.
    */
    real_t radius;

    /**
    * ���������� ������� � ������� �������, XYZ, �.
    */
    real_t coord[ 3 ];

    /**
    * ������ ��� �������, �������.
    *
    * @see http://en.wikipedia.org/wiki/Axial_tilt
    */
    real_t axialTilt;

    /**
    * ������ �������� �������, �.
    */
    real_t rotationPeriod;

    /**
    * ������ �������������� ���, ����������� �� �������, �.
    * ����� ������ ����� �������.
    */
    real_t force[ 3 ];
    real_t absForce;

    /**
    * �������� �������� ������� � ������� �������, XYZ, �/�.
    */
    real_t velocity[ 3 ];

} characteristicPlanet_t;




typedef struct __attribute__ ((packed)) {
    /**
    * ������������� �������.
    */
    uid_t uid;

    /**
    * �������������� �������: ������ � ��� ����. ������.
    */
    characteristicPlanet_t today;
    characteristicPlanet_t future;

    /**
    * �������, ���������� �������� �� 1 �����.
    */
    emitterEvent_t emitterEvent;

} aboutPlanet_t;




/**
* ������� � ������� ������� �������.
*/
typedef aboutPlanet_t*   planetContent_t;
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
