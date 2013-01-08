#pragma once

#include "structure.h"
#include "star-system.h"


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

/**
* ��������� ��� ������ � ���������� ������� �������.
* (��. starsystem::Portulan).
*
* ����������
*   # ���������� �������� ����������� � ������� ��������� ��.
*   # ���� ������ ��������� ����� ������ � �������� OpenCL: ��� ��������
*     �������� �������� booster-��������� (��. porte::Booster).
*   # ����� �������������� ����, ������� ������ ��������, ����� �������� �������.
*/
typedef struct __attribute__ ((packed)) {
    aboutStarSystem_t  aboutStarSystem;

    observer_t  observer;

    asteroid_t  asteroid;
    planet_t    planet;
    star_t      star;

} topology_t;


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
