#pragma once

#include "structure.h"
#include "component.h"


/**
* ��������� �������.
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {

/**
* ����� ���������� � �������.
*/
typedef struct {
    /**
    * ������ �������, �.
    */
    cl_float radiusPlanet;

    /**
    * ������ ������� �������, �.
    * ������ ��������� = ������ ������� ������� / 2
    * ������� ��������� = ������ ��������� - ������ �������
    */
    cl_float sizeArea;

    /**
    * ����� �������, ��.
    */
    cl_float massPlanet;

    /**
    * ������ �������, ������������ ���� ����������� � �� �������� ����� � �����.
    *
    *   # ��� �������� ��� ���������� �����. ��� ������� � componentAll_t.
    *   # �������������� ���������� ����������� ������.
    */
    component::componentAll_t componentPlanet;

    /**
    * ����� ���������, ��.
    */
    cl_float massAtmosphere;

    /**
    * ������ ���������, ������������ ���� ����������� � �� �������� ����� � �����.
    *
    * @see ���������� ��� componentPlanet.
    */
    component::componentAll_t componentAtmosphere;

    /**
    * ����� �� �������, ������������ ������ � �� ���-�� � ������� �������.
    */
    living::livingAll_t livingPlanet;

} aboutPlanet_t;


            } // dungeoncrawl
        } // set
    } // planet
} // portulan
