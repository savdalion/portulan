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
    * ����� ������, ��.
    */
    cl_double mass;

    /**
    * ������ ������, �.
    */
    cl_double radius;

    /**
    * ������� �����������, �.
    */
    cl_double temperature;

    /**
    * ���������� ������ � ������� �������, XYZ, �.
    */
    cl_double coord[ 3 ];

    /**
    * �������� �������� ������ � ������� �������, XYZ, �/�.
    */
    cl_double velocity[ 3 ];

    /**
    * ������ �������������� ���, ����������� �� ������, �.
    */
    cl_double force[ 3 ];

} aboutStar_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
