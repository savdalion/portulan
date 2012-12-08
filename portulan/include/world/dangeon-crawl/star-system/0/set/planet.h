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
* ������� ����� �� �����������: ����� MapContent3D - ������� ��������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ����� �������, ��.
    */
    real_t mass;

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
    * @see star.h
    */
    real_t tm[ 16 ];


    /**
    * �������� �����.
    */
    real_t test[ 5 ];

} aboutPlanet_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
