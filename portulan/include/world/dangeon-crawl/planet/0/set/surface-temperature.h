#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� � ����������� �� ������������ �������.
*
*   # ������������ ������ ������� ���� ����������� ����. �� @todo �����
*     ������������� ��� �� ��������� ��� ������� ����������� �������� �������.
*   # ��������� ��������� ��������� �� "temperature".
*
* @see temperature_t
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif


/**
* ��������� ����������� � 1-� ������ �� ����������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������� �������� �����������, �.
    */
    cl_float average;

} behaviourSurfaceTemperature_t;




/**
* ������ ��������� � ����������� � ����������� �� �����������.
*/
typedef behaviourSurfaceTemperature_t  surfaceTemperatureCell_t[ 1 ];





/**
* ����������� �� ����������� �������.
*/
typedef surfaceTemperatureCell_t*  surfaceTemperatureContent_t;
typedef struct __attribute__ ((packed)) {
    surfaceTemperatureContent_t content;
} surfaceTemperature_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
