#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "temperature.h"
#include "living.h"


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


/**
* ��������� ���� �������� ����� ���������� � ����������� ��� ������������
* ��� ���������, ����������� ����, ���� � ��..
*/

typedef struct __attribute__ ((packed)) {

    enum CODE_COMPONENT code;

    /**
    * �������� ���� ���������� � ���������� ����.
    */
    cl_float count;

    /**
    * ���������� �������������, ������������ ���������� ��������� �����
    * ����������. ���������� �� ������� �� ���������� ������, ������
    * ��� ������ "�����������" ("����������") �� ������� ����� � ���� ����.
    *//* - ���. ��������� ��������� ������� �� ������ ���������� ��
           �����������. ����������� ���� �������, ����� ����� ����������.
    cl_uint minefield;
    */
} zoneComponent_t;

// # ������ COMPONENT_CELL ������ COMPONENT_COUNT, �.�. ��� ���������
//   ������������ ���� ��� �������������, � ���-�� ����������� � 1-� ������
//   � ����� ������ �� ����� ��������� COMPONENT_CELL �����������.
typedef zoneComponent_t  componentAll_t[ COMPONENT_CELL ];




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
    cl_float center;
    cl_float surface;

    // # ���������� �����������, ������� - ��� ��� �������� �������� �����:
    //   ���� ������� ������� ��� ����.

} zoneTemperature_t;

typedef zoneTemperature_t  temperatureAll_t;




/**
* ��������� ���-�� ������ � ������� ������� (� ���������) � ���������
* �������� �����. ��� ������ ������������ ��� ������������
* ������� �������� � ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING code;
    // *���������* ���-�� ������ � ������ ������� �������
    cl_float count;
    // # ������ ������ ������������ � aboutOneLiving_t::maxGroupSize.
} zoneLiving_t;

// # ������ LIVING_CELL ������ LIVING_COUNT, �.�. ��� ���������
//   ������������ ���� ��� �������������, � ���-�� ������ � 1-� ������
//   � ����� ������ �� ����� ��������� LIVING_CELL ������.
typedef zoneLiving_t  livingAll_t[ LIVING_CELL ];




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
    componentAll_t space;
    componentAll_t atmosphere;
    componentAll_t crust;
    componentAll_t mantle;
    componentAll_t core;
} componentPlanet_t;

typedef struct __attribute__ ((packed)) {
    temperatureAll_t space;
    temperatureAll_t atmosphere;
    temperatureAll_t crust;
    temperatureAll_t mantle;
    temperatureAll_t core;
} temperaturePlanet_t;

/*
typedef struct __attribute__ ((packed)) {
    __structRainfallAll_t space;
    __structRainfallAll_t atmosphere;
    __structRainfallAll_t crust;
    __structRainfallAll_t mantle;
    __structRainfallAll_t core;
} rainfallPlanet_t;
*/

typedef struct __attribute__ ((packed)) {
    livingAll_t space;
    livingAll_t atmosphere;
    livingAll_t crust;
    livingAll_t mantle;
    livingAll_t core;
} livingPlanet_t;

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
    * ����������� �� �������.
    *   # ����� ������������� ������ ������� ���������� ����� ������, ���������
    *     �������� ���������� ��� ������ ���������.
    */
    temperaturePlanet_t temperature;

    /**
    * ����������� ������ �� �������.
    *//*
    rainfallPlanet_t rainfall;
    */

    /**
    * ����� �� �������, ������������ ���� ������ � �� ���-�� � ������� �������.
    *   # ������ ������ ������������� �� ��� CL_NONE, ���� ��������
    *     ����� LIVING_CELL ���������.
    */
    livingPlanet_t living;

} aboutPlanet_t;




/**
* ��������� ��� �������� ���������� ������ ����� ������ � ������������
* �� LIFE_CYCLE � �� ����� ������� �������.
*
* #! ��������� ���� ��������� ������ ���� ����������� � �����
*    � DungeonCrawl::initLiving().
*/
typedef struct __attribute__ ((packed)) {
    float space;
    float atmosphere;
    float crust;
    float mantle;
    float core;
    // # ������ ����� ���� ���������������� ���.
    float all;
} zoneOneLivingCount_t;

typedef zoneOneLivingCount_t  zoneLCOneLivingCount_t[ LIFE_CYCLE_COUNT ];

// ������ �����. ���� �����
typedef zoneLCOneLivingCount_t  zoneLivingCount_t[ LIVING_COUNT ];




/**
* ��������� ��� �������� ��������� ������ ����� ������ � ������������
* �� LIFE_CYCLE � �� ����� ������� �������.
* ������������ ������ � zoneOneLivingCount_t.
*
* #! ��������� ���� ��������� ������ ���� ����������� � �����
*    � DungeonCrawl::initLiving().
*/
typedef struct __attribute__ ((packed)) {
    bool space;
    bool atmosphere;
    bool crust;
    bool mantle;
    bool core;
    // # ���� "�" �� ���� ���������������� �����.
    bool all;
} zoneOneLivingCountComplete_t;

typedef zoneOneLivingCountComplete_t  zoneLCOneLivingCountComplete_t[ LIFE_CYCLE_COUNT ];

// ������ �����. ���� �����
typedef zoneLCOneLivingCountComplete_t  zoneLivingCountComplete_t[ LIVING_COUNT ];





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
