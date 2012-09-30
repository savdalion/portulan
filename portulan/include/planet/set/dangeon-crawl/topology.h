#pragma once

#include "structure.h"
#include "component.h"
#include "component-set.h"
#include "temperature.h"
#include "surface-temperature.h"
#include "rainfall.h"
#include "drainage.h"
#include "biome.h"
#include "biome-set.h"
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
typedef struct __attribute__ ((packed)) {
    dungeoncrawl::aboutPlanet_t     aboutPlanet;
    dungeoncrawl::aboutComponent_t  aboutComponent;
    dungeoncrawl::aboutLiving_t     aboutLiving;

    dungeoncrawl::component_t           component;
    dungeoncrawl::temperature_t         temperature;
    dungeoncrawl::surfaceTemperature_t  surfaceTemperature;
    dungeoncrawl::rainfall_t            rainfall;
    dungeoncrawl::drainage_t            drainage;
    dungeoncrawl::landscape_t           landscape;
    dungeoncrawl::biome_t               biome;
    dungeoncrawl::living_t              living;

    // @todo extend Ветры.
    // @todo extend Облака.
    // @todo extend Карта пожаров > http://gis-lab.info/blog/2012-09/fires-wfa/

} topology_t;

        } // set
    } // planet
} // portulan
