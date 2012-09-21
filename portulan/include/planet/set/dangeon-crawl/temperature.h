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
                namespace temperature {
#endif


/**
* ����������� � 1-� ������ ������� �������.
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

} temperatureCell_t;




/**
* ���������� � ����������� � ������� ������� (� ���������).
* ��� ������ ������������ ��� ��������� ������������ �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ����� ����������, �.
    *   # ����������� �������� �������.
    *   # �������� ���������� ������������� �� ������ (0.0, ����� �������� ����)
    *     � ����������� (1.0, ����� ������� ����).
    */
    cl_float map[2];

    // # ���������� �����������, ������� - ��� ��� �������� �������� �����:
    //   ���� ������� ������� ��� ����.

} zoneTemperature_t;

typedef zoneTemperature_t  temperatureAll_t;




/**
* ����������� � ������� �������.
*/
typedef temperatureCell_t*  temperatureContent_t;
typedef struct __attribute__ ((packed)) {
    temperatureContent_t content;
} temperature_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // temperature
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
