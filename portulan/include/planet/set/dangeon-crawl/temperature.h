#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� � ����������� � ������� �������.
*
*   # ��������� ��������� ��������� �� "component" � "living".
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* ��������� ����������� � 1-� ������ ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������� �������� �����������, �.
    */
    cl_float average;

    /**
    * ���������� ����������� �� �������� ��������, % / 100.
    */
    cl_float dispersion;

    /**
    * ������� ���������� ����������� �� �������� ��������, ��� / ����.
    * �������� < 1 ����������� ������� ���������� "��� � ��������� ����":
    * = 1 / rate
    */
    cl_float rate;

} behaviourTemperature_t;




/**
* ������ ��������� � ����������� � �����������.
*/
typedef behaviourTemperature_t  temperatureCell_t[ 1 ];





/**
* ����������� � ������� �������.
*/
typedef temperatureCell_t*  temperatureContent_t;
typedef struct __attribute__ ((packed)) {
    temperatureContent_t content;
} temperature_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
