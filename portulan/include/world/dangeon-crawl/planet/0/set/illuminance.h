#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� �� ������������ � ������� �������.
* ������������ ������� ����� �� ������� ���������� (��������, ������, ��������).
*
*   # ��� ������ ����� ����� ������������� � ������ (��. "�������� ����������").
*
*   # ��������� ��������� ��������� �� "component" � "living".
*
* @see http://ru.wikipedia.org/wiki/%D0%9E%D1%81%D0%B2%D0%B5%D1%89%D1%91%D0%BD%D0%BD%D0%BE%D1%81%D1%82%D1%8C
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif


/**
* ������������ � 1-� ������ ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������ �� ����, ��.
    */
    cl_float star;

    /**
    * @todo ������������ �� ��������� � ��. ������, ��.
    */
    //cl_float planet;
    //cl_float satellite;

    /**
    * @todo ��������� ������������ ��-�� �������� �������, ������.
    */
    //cl_float weather;

} sourceIlluminance_t;




/**
* ������ ��������� � ����������� �� ������������.
*/
typedef sourceIlluminance_t  illuminanceCell_t[ 1 ];




/**
* ������������ � ������� �������.
*/
typedef illuminanceCell_t*  illuminanceContent_t;
typedef struct __attribute__ ((packed)) {
    illuminanceContent_t content;
} illuminance_t;





/**
* ��������� ��� ������ ���� �� ������������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������ ������, �.
    */
    cl_float radius;

    /**
    * ������� �����������, �.
    */
    cl_float temperature;

    /**
    * ���� �����, ��.
    *
    * @source http://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D0%BB%D0%B0_%D1%81%D0%B2%D0%B5%D1%82%D0%B0
    */
    cl_float luminousIntensity;

    /**
    * ���������� ������ � ������� �������, XYZ, �.
    */
    cl_float coord[ 3 ];

} aboutIlluminanceStar_t;




typedef struct __attribute__ ((packed)) {
    aboutIlluminanceStar_t  star[ ILLUMINANCE_STAR_COUNT ];
    // @todo sattelite, planet
} aboutIlluminanceSource_t;




typedef struct {
    // ��������� ���������
    illuminanceContent_t  result;
    // ����, ������� ��������
    cl_float  radius;
    cl_float  coord[ 3 ];
    cl_float  omega[ 3 ];
    // ��������� ���������
    aboutIlluminanceSource_t  source;
} illuminanceBody_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
