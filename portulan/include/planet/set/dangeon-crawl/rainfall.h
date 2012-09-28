#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� �� ����������� ������� �� ������������ �������.
*
*   # ������������ ������ ������� ���� ����������� ����. �� @todo �����
*     ������������� ��� �� ��������� ��� ������� ������� � �������� �������.
*   # ��������� ��������� ��������� �� "temperature".
*
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* ��������� ���. ������� � 1-� ������ �� ����������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������� �������� ���. �������, �� / ����.
    */
    cl_float average;

} behaviourRainfall_t;




/**
* ������ ��������� � ����������� �� ���. ������� �� �����������.
*/
typedef behaviourRainfall_t  rainfallCell_t[ 1 ];





/**
* ���. ������ �� ����������� �������.
*/
typedef rainfallCell_t*  rainfallContent_t;
typedef struct __attribute__ ((packed)) {
    rainfallContent_t content;
} rainfall_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
