#pragma once

#include "structure.h"
#include "component.h"
#include "component-set.h"
#include "temperature.h"
#include "surface-temperature.h"
#include "rainfall.h"
#include "drainage.h"
#include "landscape.h"
#include "illuminance.h"
#include "biome.h"
#include "biome-set.h"
#include "living.h"
#include "living-set.h"
#include "planet.h"


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
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
    aboutPlanet_t     aboutPlanet;
    aboutComponent_t  aboutComponent;
    aboutLiving_t     aboutLiving;

    component_t           component;
    temperature_t         temperature;
    surfaceTemperature_t  surfaceTemperature;
    rainfall_t            rainfall;
    drainage_t            drainage;
    landscape_t           landscape;
    illuminance_t         illuminance;
    biome_t               biome;
    living_t              living;

    // @todo extend Ветры.
    // @todo extend Облака.
    // @todo extend Карта пожаров > http://gis-lab.info/blog/2012-09/fires-wfa/

} topology_t;


                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
