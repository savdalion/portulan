#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "temperature.h"
#include "landscape.h"
#include "living.h"


/**
* ��������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
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
    *   # ����� ������������� ������ ������� ���������� ����� ������, ���������
    *     �������� ���������� ���-������� ������ ���������.
    */
    cl_float center;
    cl_float surface;

} zoneTemperature_t;

typedef zoneTemperature_t  temperatureAll_t;




/**
* ���������� � ����������� �� *�����������* �������.
* �������� � ��������� ���������, ����� �������� �����������
* �� zoneTemperature_t.
* ��� ������ ������������ ��� ��������� ������������ �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ����� ����������, �.
    */
    // ������� ������� ����������� �� ������� � ��������, �
    cl_float pole;
    cl_float equator;
    // @todo ������� ��������� �����������, ��� / ����
    //cl_float rate;

} zoneSurfaceTemperature_t;

typedef zoneSurfaceTemperature_t  surfaceTemperatureAll_t;




/**
* ���������� �� ����������� ������� � ������� ������� (� ���������).
* ��� ������ ������������ ��� ��������� ������������ �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ����� ����������� �������.
    */
    // ��������� ������ ������� ���������� �������, �� / ����
    cl_float min;
    cl_float max;
    // @todo ������� ��������� �������, ��� / ����
    //cl_float rate;
    // @todo ����������������� ��������� �������, ����
    //cl_float duration;

} zoneRainfall_t;

typedef zoneRainfall_t  rainfallAll_t;




/**
* ���������� � ������� � ������� ������� (� ���������).
* ��� ������ ������������ ��� ��������� ������������ �������.
* ������ ����������, ��� ������ ���. ������ ����� ������ ����� ���������.
* ���������� ���. ������� � ������� ���������� ������ � ����� �����������.
*
* @prototype http://dfwk.ru/Biome
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ����� �������.
    * @see zoneRainfall_t
    */
    // ����������� � ������������ ������ �� �������, �� / ����
    cl_float min;
    cl_float max;

} zoneDrainage_t;

typedef zoneDrainage_t  drainageAll_t;




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

typedef struct __attribute__ ((packed)) {
    // � ����������� ������� - ������ ��������
    surfaceTemperatureAll_t crust;
} surfaceTemperaturePlanet_t;

typedef struct __attribute__ ((packed)) {
    rainfallAll_t crust;
    // # ������ ���������� ������ �� ����������� ����������� ����.
} rainfallPlanet_t;

typedef struct __attribute__ ((packed)) {
    drainageAll_t crust;
    // # ������ ���������� ������ �� ����������� ����������� ����.
} drainagePlanet_t;


/* - ��� ���������� �� ������ ������ � ���������� ����� �������.
     ����� ����, ��� ��������� ������ �� ����� �������� ������� ���������,
     ����� ��� � ��������, � ��������.
typedef struct __attribute__ ((packed)) {
    temperaturePlanet_t      temperature;
    surfaceTemperatureAll_t  surfaceTemperature;
    rainfallPlanet_t         rainfall;
    drainagePlanet_t         drainage;
} climatePlanet_t;
*/


/**
* ��� ��������� ��������� �������� ������� �������� � ����������.
*/
typedef struct __attribute__ ((packed)) {
    mountainLandscape_t  mountain;
    cl_float             deviationMountain;

    basinLandscape_t     basin;
    cl_float             deviationBasin;

    rangeLandscape_t     range;
    cl_float             deviationRange;

    ravineLandscape_t    ravine;
    cl_float             deviationRavine;

    lakeLandscape_t      lake;
    cl_float             deviationLake;

    riverLandscape_t     river;
    cl_float             deviationRiver;

    // @todo ...

} landscapePlanet_t;


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
    * ������ �������.
    * ��������������� �����������
    *   - @todo ����������� ��������
    *   - @todo ����������� �������
    *   - @todo ��������� �������
    *   - @todo �������� � ����������� �����
    * 
    *   # @todo ������ ���������� �� ���� ������� �������. �.�. ������
    *     ��������� ������� � ������ �������.
    *   # �� ����������� � ��������� ���������, �.�. �������� ����������
    *     �� ������ ������ � ���������� ����� �������, �� ������ ��� ��������
    *     � ������� "��� ������ �� ������ �������?"
    *
    * @todo ��������� ���� ��������� ����������� ����������� ��������
    *   - ����������� ������ (�����, ����, ����)
    *   - �����
    *   - ������
    *   - �����
    *   - �����
    *   - ����
    *   - ������
    *   - ����������� �����
    *   - ...
    *
    * @see ������ > http://ru.wikipedia.org/wiki/%D0%9A%D0%BB%D0%B8%D0%BC%D0%B0%D1%82
    */
    temperaturePlanet_t         temperature;
    // ����������� �� ����������� �������� "temperature"
    surfaceTemperaturePlanet_t  surfaceTemperature;
    rainfallPlanet_t            rainfall;
    drainagePlanet_t            drainage;

    /**
    * �������� �������.
    */
    landscapePlanet_t landscape;

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
*    � Engine::initLiving().
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
*    � Engine::initLiving().
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
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
