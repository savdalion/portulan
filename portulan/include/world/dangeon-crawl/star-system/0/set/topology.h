#pragma once

#include "structure.h"
#include "star-system.h"


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

/**
* Структуры для работы с топологией звёздной системы.
* (см. starsystem::Portulan).
*
* Соглашения
*   # Физические величины указываются в системе измерения СИ.
*   # Типы данных топологии сразу готовы к передаче OpenCL: это позволит
*     избежать создания booster-структуры (см. porte::Booster).
*   # Любые характеристики тела, включая группу элемента, могут меняться движком.
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
