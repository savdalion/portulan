#pragma once

#include "structure.h"
#include "component.h"
#include "component-set.h"
#include "living.h"
#include "living-set.h"
#include "planet.h"
#include "temperature.h"
#include "surface-temperature.h"


namespace portulan {
    namespace planet {
        namespace set {

/**
* ��������� ��� ������ � ���������� �������.
* ������ ��������, ��� ��������� ���������� ��������� ����������
* (��. planet::Portulan).
*
* ����������
*   # ���������� �������� ����������� � ������� ��������� ��.
*   # ������� ��������� ������� ������ 3.
*   # ������� ����� � ������������ ��������� � ������ ��������� �������
*     ������� �� 81 x 81 x 81 ������.
*   # ���� ������ ��������� ����� ������ � �������� OpenCL: ��� ��������
*     �������� �������� booster-��������� (��. porte::Booster).
*/
typedef struct __attribute__ ((packed)) {
    dungeoncrawl::aboutPlanet_t     aboutPlanet;
    dungeoncrawl::aboutComponent_t  aboutComponent;
    dungeoncrawl::aboutLiving_t     aboutLiving;

    dungeoncrawl::component_t           component;
    dungeoncrawl::temperature_t         temperature;
    dungeoncrawl::surfaceTemperature_t  surfaceTemperature;
    dungeoncrawl::living_t              living;

} topology_t;

        } // set
    } // planet
} // portulan
