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
    big3d_t coord;

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
    * �������� �������� ������� � ������� �������, XYZ, �/�.
    */
    real3_t velocity;

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
