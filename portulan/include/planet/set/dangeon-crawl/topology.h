#pragma once

#include "structure.h"
#include "component.h"
#include "living.h"


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
typedef struct {
    //aboutPlanet_t       aboutPlanet;

    dungeoncrawl::component::aboutComponent_t    aboutComponent;
    //dungeoncrawl::component::component_t         component;

    dungeoncrawl::living::aboutLiving_t          aboutLiving;
    //dungeoncrawl::living::living_t            living;

    //pressure_t          pressure;
    //temperature_t       temperature;
    //precipitations_t    precipitations;

    //aboutSurfaceVoid_t  aboutSurfaceVoid;

} topology_t;

        } // set
    } // planet
} // portulan
