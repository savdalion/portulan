#pragma once

#include "structure.h"
#include "component.h"
#include "component-set.h"
#include "living.h"
#include "living-set.h"
#include "planet.h"
#include "temperature.h"


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
    dungeoncrawl::aboutPlanet_t                aboutPlanet;

    dungeoncrawl::component::aboutComponent_t  aboutComponent;
    dungeoncrawl::component::component_t       component;

    dungeoncrawl::living::aboutLiving_t        aboutLiving;
    dungeoncrawl::living::living_t             living;

    dungeoncrawl::temperature::temperature_t   temperature;
    //pressure_t          pressure;
    //precipitations_t    precipitations;

    //aboutSurfaceVoid_t  aboutSurfaceVoid;

} topology_t;

        } // set
    } // planet
} // portulan
