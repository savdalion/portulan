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




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
