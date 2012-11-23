#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "temperature.h"
#include "landscape.h"
#include "living.h"


/**
* Структура планеты.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif


/**
* Общая информация о планете.
*/


/**
* Структуры ниже содержат общую информацию о компонентах для формирования
* зон атмосферы, планетарной коры, ядра и пр..
*/

typedef struct __attribute__ ((packed)) {

    enum CODE_COMPONENT code;

    /**
    * Массовая доля компонента в задаваемой зоне.
    */
    cl_float count;

    /**
    * Количество месторождений, определяющих наибольшие скопления этого
    * компонента. Компонента на планете не становится больше, просто
    * его запасы "стягиваются" ("намываются") из планеты ближе к этой зоне.
    *//* - Нет. Начальное состояние планеты не должно отличаться от
           однородного. Задействуем силы природы, чтобы скуку равновесия.
    cl_uint minefield;
    */
} zoneComponent_t;

// # Берётся COMPONENT_CELL вместо COMPONENT_COUNT, т.к. эта структура
//   используется лишь при инициализации, а кол-во компонентов в 1-й ячейке
//   в любом случае не будет превышать COMPONENT_CELL компонентов.
typedef zoneComponent_t  componentAll_t[ COMPONENT_CELL ];




/**
* Информация о температуре в области планеты (в портулане).
* Эти данные используются при начальном формировании планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Карта температур, К.
    *   # Температура меняется линейно.
    *   # Значения температур перечисляются от центра (0.0, самый глубокий слой)
    *     к поверхности (1.0, самый верхний слой).
    *   # Чтобы отсутствовала резкая граница температур между зонами, граничные
    *     значения температур зон-соседей должны совпадать.
    */
    cl_float center;
    cl_float surface;

} zoneTemperature_t;

typedef zoneTemperature_t  temperatureAll_t;




/**
* Информация о температуре на *поверхности* планеты.
* Выделены в отдельную структуру, чтобы уточнить температуру
* из zoneTemperature_t.
* Эти данные используются при начальном формировании планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Карта температур, К.
    */
    // средняя годовая температура на полюсах и экваторе, К
    cl_float pole;
    cl_float equator;
    // @todo частота колебания температуры, раз / день
    //cl_float rate;

} zoneSurfaceTemperature_t;

typedef zoneSurfaceTemperature_t  surfaceTemperatureAll_t;




/**
* Информация об атмосферных осадках в области планеты (в портулане).
* Эти данные используются при начальном формировании планеты.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Карта атмосферных осадков.
    */
    // граничное средне дневное количество осадков, мм / день
    cl_float min;
    cl_float max;
    // @todo частота выпадения осадков, раз / день
    //cl_float rate;
    // @todo продолжительность выпадения осадков, день
    //cl_float duration;

} zoneRainfall_t;

typedef zoneRainfall_t  rainfallAll_t;




/**
* Информация о дренаже в области планеты (в портулане).
* Эти данные используются при начальном формировании планеты.
* Дренаж определяет, как быстро атм. осадки будут убраны после выпадения.
* Показатели атм. осадков и дренажа определяют состав и форму поверхности.
*
* @prototype http://dfwk.ru/Biome
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Карта дренажа.
    * @see zoneRainfall_t
    */
    // минимальный и максимальный дренаж на планете, мм / день
    cl_float min;
    cl_float max;

} zoneDrainage_t;

typedef zoneDrainage_t  drainageAll_t;




/**
* Примерное кол-во особей в области планеты (в портулане) с указанием
* размеров групп. Эти данные используются для формирования
* ареалов обитания в области планеты.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING code;
    // *примерное* кол-во особей в ячейке области планеты
    cl_float count;
    // # Размер группы декларирован в aboutOneLiving_t::maxGroupSize.
} zoneLiving_t;

// # Берётся LIVING_CELL вместо LIVING_COUNT, т.к. эта структура
//   используется лишь при инициализации, а кол-во особей в 1-й ячейке
//   в любом случае не будет превышать LIVING_CELL особей.
typedef zoneLiving_t  livingAll_t[ LIVING_CELL ];




typedef struct __attribute__ ((packed)) {
    cl_float atmosphere;
    cl_float crust;
    cl_float mantle;
    cl_float core;
} radiusPlanet_t;

typedef struct __attribute__ ((packed)) {
    cl_float atmosphere;
    cl_float crust;
    cl_float mantle;
    cl_float core;
} massPlanet_t;

typedef struct __attribute__ ((packed)) {
    componentAll_t space;
    componentAll_t atmosphere;
    componentAll_t crust;
    componentAll_t mantle;
    componentAll_t core;
} componentPlanet_t;


typedef struct __attribute__ ((packed)) {
    temperatureAll_t space;
    temperatureAll_t atmosphere;
    temperatureAll_t crust;
    temperatureAll_t mantle;
    temperatureAll_t core;
} temperaturePlanet_t;

typedef struct __attribute__ ((packed)) {
    // к поверхности планеты - особое внимание
    surfaceTemperatureAll_t crust;
} surfaceTemperaturePlanet_t;

typedef struct __attribute__ ((packed)) {
    rainfallAll_t crust;
    // # Осадки инициируем только на поверхности планетарной коры.
} rainfallPlanet_t;

typedef struct __attribute__ ((packed)) {
    drainageAll_t crust;
    // # Дренаж инициируем только на поверхности планетарной коры.
} drainagePlanet_t;


/* - Эта абстракция не делает работу с портуланом более простой.
     Более того, она вынуждает тянуть за собой довольно большую структуру,
     лишая нас и гибкости, и скорости.
typedef struct __attribute__ ((packed)) {
    temperaturePlanet_t      temperature;
    surfaceTemperatureAll_t  surfaceTemperature;
    rainfallPlanet_t         rainfall;
    drainagePlanet_t         drainage;
} climatePlanet_t;
*/


/**
* Для элементов ландшафта задаются средние значения и отклонение.
*/
typedef struct __attribute__ ((packed)) {
    mountainLandscape_t  mountain;
    cl_float             deviationMountain;

    basinLandscape_t     basin;
    cl_float             deviationBasin;

    rangeLandscape_t     range;
    cl_float             deviationRange;

    ravineLandscape_t    ravine;
    cl_float             deviationRavine;

    lakeLandscape_t      lake;
    cl_float             deviationLake;

    riverLandscape_t     river;
    cl_float             deviationRiver;

    // @todo ...

} landscapePlanet_t;


typedef struct __attribute__ ((packed)) {
    livingAll_t space;
    livingAll_t atmosphere;
    livingAll_t crust;
    livingAll_t mantle;
    livingAll_t core;
} livingPlanet_t;


typedef struct __attribute__ ((packed)) {
    /**
    * Размер области планеты, м.
    *   # Размер области планеты = Радиус атмосферы * 2
    *   # Толщина атмосферы = Радиус атмосферы - Радиус коры планеты
    */
    cl_float size;

    /**
    * Внешние радиусы области планеты, части от размера области планеты.
    *   # Радиус атмосферы = 1.0.
    */
    radiusPlanet_t radius;

    /**
    * Массы скоплений в области планеты, кг.
    */
    massPlanet_t mass;

    /**
    * Состав планеты, перечисление всех компонентов по группам и
    * массовой части компонентов в целом.
    *   # Список должен заканчиваться на код CC_NONE, если содержит
    *     менее COMPONENT_CELL элементов.
    */
    componentPlanet_t component;

    /**
    * Климат планеты.
    * Характеризуется параметрами
    *   - @todo атмосферное давление
    *   - @todo температура воздуха
    *   - @todo влажность воздуха
    *   - @todo скорость и направление ветра
    * 
    *   # @todo Климат определяем по всей области планеты. Т.о. сможем
    *     создавать полости с особой погодой.
    *   # Не оборачиваем в отдельную структуру, т.к. подобная абстракция
    *     не делает работу с портуланом более простой, но лишает нас гибкости
    *     в вопросе "Что влияет на климат планеты?"
    *
    * @todo Параметры выше позволяют проявляться атмосферным явлениям
    *   - атмосферные осадки (дождь, снег, град)
    *   - туман
    *   - метель
    *   - гроза
    *   - смерч
    *   - буря
    *   - ураган
    *   - метеоритный дождь
    *   - ...
    *
    * @see Климат > http://ru.wikipedia.org/wiki/%D0%9A%D0%BB%D0%B8%D0%BC%D0%B0%D1%82
    */
    temperaturePlanet_t         temperature;
    // температура на поверхности уточняет "temperature"
    surfaceTemperaturePlanet_t  surfaceTemperature;
    rainfallPlanet_t            rainfall;
    drainagePlanet_t            drainage;

    /**
    * Ландшафт планеты.
    */
    landscapePlanet_t landscape;

    /**
    * Жизнь на планете, перечисление всех особей и их кол-во в области планеты.
    *   # Список должен заканчиваться на код CL_NONE, если содержит
    *     менее LIVING_CELL элементов.
    */
    livingPlanet_t living;

} aboutPlanet_t;




/**
* Структура для хранения количества разных видов особей с группировкой
* по LIFE_CYCLE и по зонам области планеты.
*
* #! Изменения этой структуры должны быть согласованы с кодом
*    в DungeonCrawl::initLiving().
*/
typedef struct __attribute__ ((packed)) {
    float space;
    float atmosphere;
    float crust;
    float mantle;
    float core;
    // # Всегда сумма всех вышеобозначенных зон.
    float all;
} zoneOneLivingCount_t;

typedef zoneOneLivingCount_t  zoneLCOneLivingCount_t[ LIFE_CYCLE_COUNT ];

// индекс соотв. коду особи
typedef zoneLCOneLivingCount_t  zoneLivingCount_t[ LIVING_COUNT ];




/**
* Структура для хранения признаков разных видов особей с группировкой
* по LIFE_CYCLE и по зонам области планеты.
* Используется вместе с zoneOneLivingCount_t.
*
* #! Изменения этой структуры должны быть согласованы с кодом
*    в DungeonCrawl::initLiving().
*/
typedef struct __attribute__ ((packed)) {
    bool space;
    bool atmosphere;
    bool crust;
    bool mantle;
    bool core;
    // # Итог "И" по всем вышеобозначенным зонам.
    bool all;
} zoneOneLivingCountComplete_t;

typedef zoneOneLivingCountComplete_t  zoneLCOneLivingCountComplete_t[ LIFE_CYCLE_COUNT ];

// индекс соотв. коду особи
typedef zoneLCOneLivingCountComplete_t  zoneLivingCountComplete_t[ LIVING_COUNT ];





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
