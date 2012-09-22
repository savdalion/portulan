#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "living.h"
#include "temperature.h"


/**
* ��������� �������.
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* ����� ���������� � �������.
*/

typedef struct __attribute__ ((packed)) {
    cl_float atmosphere;
    cl_float crust;
    cl_float mantle;
    cl_float core;
} radiusPlanet_t;

typedef struct __attribute__ ((packed)) {
    cl_float atmosphere;
    cl_float crust;
    cl_float mantle;
    cl_float core;
} massPlanet_t;

typedef struct __attribute__ ((packed)) {
    __structComponentAll_t space;
    __structComponentAll_t atmosphere;
    __structComponentAll_t crust;
    __structComponentAll_t mantle;
    __structComponentAll_t core;
} componentPlanet_t;

typedef struct __attribute__ ((packed)) {
    __structLivingAll_t space;
    __structLivingAll_t atmosphere;
    __structLivingAll_t crust;
    __structLivingAll_t mantle;
    __structLivingAll_t core;
} livingPlanet_t;

typedef struct __attribute__ ((packed)) {
    __structTemperatureAll_t space;
    __structTemperatureAll_t atmosphere;
    __structTemperatureAll_t crust;
    __structTemperatureAll_t mantle;
    __structTemperatureAll_t core;
} temperaturePlanet_t;

typedef struct __attribute__ ((packed)) {
    /**
    * ������ ������� �������, �.
    *   # ������ ������� ������� = ������ ��������� * 2
    *   # ������� ��������� = ������ ��������� - ������ ���� �������
    */
    cl_float size;

    /**
    * ������� ������� ������� �������, ����� �� ������� ������� �������.
    *   # ������ ��������� = 1.0.
    */
    radiusPlanet_t radius;

    /**
    * ����� ��������� � ������� �������, ��.
    */
    massPlanet_t mass;

    /**
    * ������ �������, ������������ ���� ����������� �� ������� �
    * �������� ����� ����������� � �����.
    *   # ������ ������ ������������� �� ��� CC_NONE, ���� ��������
    *     ����� COMPONENT_CELL ���������.
    */
    componentPlanet_t component;

    /**
    * ����� �� �������, ������������ ���� ������ � �� ���-�� � ������� �������.
    *   # ������ ������ ������������� �� ��� CL_NONE, ���� ��������
    *     ����� LIVING_CELL ���������.
    */
    livingPlanet_t living;

    /**
    * ����������� �� �������.
    *   # ����� ������������� ������ ������� ���������� ����� ������, ���������
    *     �������� ���������� ��� ������ ���������.
    */
    temperaturePlanet_t temperature;

} aboutPlanet_t;


#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
