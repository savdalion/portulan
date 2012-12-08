#pragma once

#include "structure.h"
#include "star-system.h"


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

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
    aboutStarSystem_t  aboutStarSystem;

    body_t  body;

} topology_t;


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
