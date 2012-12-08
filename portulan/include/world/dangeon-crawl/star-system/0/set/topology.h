#pragma once

#include "structure.h"
#include "star-system.h"


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

/**
* Структура для работы с топологией планеты.
* Помимо удобства, эта структура декларирут некоторые соглашения
* (см. planet::Portulan).
*
* Соглашения
*   # Физические величины указываются в системе измерения СИ.
*   # Размеры топологии планеты кратны 3.
*   # Размеры сеток в комментариях приведены с учётом разбиения области
*     планеты на 81 x 81 x 81 ячейку.
*   # Типы данных топологии сразу готовы к передаче OpenCL: это позволит
*     избежать создания booster-структуры (см. porte::Booster).
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
