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
    __structTemperatureAll_t space;
    __structTemperatureAll_t atmosphere;
    __structTemperatureAll_t crust;
    __structTemperatureAll_t mantle;
    __structTemperatureAll_t core;
} temperaturePlanet_t;

typedef struct __attribute__ ((packed)) {
    __structLivingAll_t space;
    __structLivingAll_t atmosphere;
    __structLivingAll_t crust;
    __structLivingAll_t mantle;
    __structLivingAll_t core;
} livingPlanet_t;

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
    * ����� �� �������, ������������ ���� ������ � �� ���-�� � ������� �������.
    *   # ������ ������ ������������� �� ��� CL_NONE, ���� ��������
    *     ����� LIVING_CELL ���������.
    */
    livingPlanet_t living;

    /**
    * ����������� ������ �� �������.
    */
    //rainfallPlanet_t rainfall;

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
