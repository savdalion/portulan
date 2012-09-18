#pragma once

#include "structure.h"
#include "component.h"
#include "component-set.h"
#include "living.h"
#include "living-set.h"
#include "planet.h"


namespace portulan {
    namespace planet {
        namespace set {

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
typedef struct {
    dungeoncrawl::aboutPlanet_t                aboutPlanet;

    dungeoncrawl::component::aboutComponent_t  aboutComponent;
    dungeoncrawl::component::component_t       component;

    dungeoncrawl::living::aboutLiving_t        aboutLiving;
    dungeoncrawl::living::living_t             living;

    //pressure_t          pressure;
    //temperature_t       temperature;
    //precipitations_t    precipitations;

    //aboutSurfaceVoid_t  aboutSurfaceVoid;

} topology_t;

        } // set
    } // planet
} // portulan
