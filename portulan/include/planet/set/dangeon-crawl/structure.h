#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>


/**
*   # Структуры организованы т. о., чтобы не дублировать их при включении
*     в код OpenCL.
*/
#define __constant const

// Выравнивание для VC++ не требуется
#define __attribute__(x) /*nothing*/


namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
/**
* Величина пульса в области планеты.
*    # 1 пульс = 1 год = 400 дней
*    # 1 день = 25 часов
*/
static __constant cl_float SECOND_IN_MINUTE = 60.0f;
static __constant cl_float MINUTE_IN_HOUR   = 60.0f;
static __constant cl_float HOUR_IN_DAY      = 25.0f;
static __constant cl_float DAY_IN_YEAR      = 400.0f;
static __constant cl_float HOUR_IN_YEAR     = DAY_IN_YEAR    * HOUR_IN_DAY;
static __constant cl_float MINUTE_IN_YEAR   = HOUR_IN_YEAR   * MINUTE_IN_HOUR;
static __constant cl_float SECOND_IN_YEAR   = MINUTE_IN_YEAR * SECOND_IN_MINUTE;
#endif





/**
* Критерии для оценки.
*/
enum CRITERIA {
    // абсолютно не важно / ничего нет / не определено
    CRITERIA_A = 0,
    // ниже среднего / мало
    CRITERIA_B,
    // средняя важность / много
    CRITERIA_C,
    // выше среднего / очень много
    CRITERIA_D,
    // жизненная необходимость / предостаточно
    CRITERIA_E,

    // последний = кол-во критериев
    CRITERIA_last,
    CRITERIA_count = CRITERIA_last
};





/**
* Жизненный цикл особи на планете (животного, растения).
*
* @see LIFE_CYCLE_COUNT
*/
enum LIFE_CYCLE {
    // Эмбрионы особей, семена
    LC_EMBRYO   = 0,
    // Дети, ростки
    LC_CHILD    = 1,
    // Взрослые
    LC_ADULT    = 2,
    // Старики
    LC_OLD      = 3,
    // Мёртвые особи - тела, скелеты
    LC_DEAD     = 4,
    // Бессмертные особи
    LC_IMMORTAL = 5,

    // последний = кол-во циклов
    LC_last,
    LC_count = LC_last
};





/**
* Размеры портулана.
* Задаются здесь, чтобы этот файл мог быть подключен как код OpenCL.
* Не задействуем шаблоны, чтобы модель на C++ более органично вписывалась
* в OpenCL.
*
*   # Деление области планеты на ячейки производится индивидуально для
*     каждого элемента мира.
*
* @todo extend Допустимо использовать только кубическую сетку.
*//* - Используем мн-во сеток. См. ниже.
static __constant size_t GRID_SX = 81;
static __constant size_t GRID_SY = GRID_SX;
static __constant size_t GRID_SZ = GRID_SX;
*/


#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # В OpenCL передаём константы как define: OpenCL не воспринимает
//   константы должным образом.

/**
* Значение, задающее неуязвимость, например, органа особи, от
* конкретного внешнего воздействия.
* Например, лапка муравья никак не реагирует при воздействии на неё
* магии "святое слово".
*/
// #? При передаче в OpenCL в параметре "-D" можем потерять точность.
static __constant cl_float IMMUNE = CL_FLT_MAX;
//#define IMMUNE  CL_FLT_MAX


/**
* Бесконечно большое значение.
*/
static __constant cl_float INFINITYf = CL_FLT_MAX;
//#define INFINITYf  CL_FLT_MAX



/**
* Любое значение (для чисел с плавающей точкой).
*/
static __constant cl_float ANYf = -CL_FLT_MAX;
//#define ANYf  -CL_FLT_MAX




/**
* Размер сетки компонентов в области планеты (в портулане).
*/
static __constant size_t COMPONENT_GRID = 81;



/**
* Макс. кол-во *разных* компонентов, которые могут использоваться
* в области планеты (в портулане).
* >= CC_last
*
* @see CODE_COMPONENT
*/
static __constant size_t COMPONENT_COUNT = 100;



/**
* Макс. кол-во компонентов с указанием частей от целого, которые могут
* *одновременно* храниться в 1-й ячейке портулана.
*/
static __constant size_t COMPONENT_CELL = 20;



/**
* Сетка распределения температуры в области планеты.
*/
static __constant size_t TEMPERATURE_GRID = 81;



/**
* Сетка распределения температуры на поверхности планеты.
*/
static __constant size_t SURFACE_TEMPERATURE_GRID = 81;



/**
* Сетка атмосферных осадков на поверхности планеты.
*/
static __constant size_t RAINFALL_GRID = 81;



/**
* Сетка дренажа на поверхности планеты.
*/
static __constant size_t DRAINAGE_GRID = 81;





/**
* Сетка распределения биомов в области планеты.
*/
static __constant size_t BIOME_GRID = 81;



/**
* Максимально возможное кол-во *разных* биомов в области планеты.
* >= CB_last
*
* @see CODE_BIOME
*/
static __constant size_t BIOME_COUNT = 50;



/**
* Макс. кол-во биомов, которые могут *одновременно* храниться
* в 1-й ячейке портулана.
*/
static __constant size_t BIOME_CELL = 3;





/**
* Макс. кол-во жизненных циклов особи.
*
* @see LIFE_CYCLE
*/
static __constant size_t LIFE_CYCLE_COUNT = LC_last;





/**
* Размер сетки ареалов обитания живых организмов в области планеты.
*/
static __constant size_t LIVING_GRID = 81 / 3;



/**
* Максимальное кол-во *разных* частей (органов), из которых может
* состоять особь.
*/
static __constant size_t PART_LIVING = 20;



/**
* Максимальное кол-во *разных* атак, известных органу особи.
*
* @see RESIST_PART_LIVING
*/
static __constant size_t ATTACK_PART_LIVING = 30;



/**
* Максимальное кол-во *разных* защит, известных органу особи.
*
* @see ATTACK_PART_LIVING
*/
static __constant size_t RESIST_PART_LIVING = 30;



/**
* Максимальное кол-во *разных* хим. компонентов, из которых может
* состоять орган особи.
*/
static __constant size_t COMPONENT_COMPOSITION_LIVING = 5;



/**
* Макисмальное кол-во *разных* хим. компонентов, которые нужны
* особи для поддержания жизни.
*
* @see COMPONENT_WASTE_LIVING
*/
static __constant size_t COMPONENT_NEED_LIVING = 10;



/**
* Максимальное кол-во *разных* хим. компонентов, которые выделяет
* особь при жизнедеятельности.
*
* @see COMPONENT_NEED_LIVING
*/
static __constant size_t COMPONENT_WASTE_LIVING = 10;



/**
* Максимальное кол-во *разных* видов энергии, которая необходима
* особи для поддержания жизни.
*
* @see ENERGY_WASTE_LIVING
* @see CODE_ENERGY
*/
static __constant size_t ENERGY_NEED_LIVING = 5;



/**
* Максимальное кол-во *разных* видов энергии, которя излучает
* особь при жизнедеятельности.
*
* @see ENERGY_NEED_LIVING
* @see CODE_ENERGY
*/
static __constant size_t ENERGY_WASTE_LIVING = 5;



/**
* Максимальное кол-во сред обитания, в которых может жить особь.
*/
static __constant size_t HABITAT_SURVIVOR_LIVING = 5;



/**
* Максимальное кол-во *разных* биомов, где особь чувствует себя комфортно.
*/
static __constant size_t BIOME_COMFORT_SURVIVOR_LIVING = BIOME_COUNT;



/**
* Максимально возможное кол-во *разных* особей в области планеты.
* >= CC_last
*
* @see CODE_LIVING
*/
static __constant size_t LIVING_COUNT = 100;



/**
* Макс. кол-во особей, которые могут *одновременно* обитать в 1-й ячейке
* области планеты.
*/
static __constant size_t LIVING_CELL = 20;





#if 0
// @todo ...
/**
* Размер сетки давлений на планете.
* Указывается для всей планеты.
* Благодаря разнице давлений в атмосфере возникают ветры, тайфуны.
*/
static __constant size_t PRESSURE_GRID = 81;



/**
* Сетка распределения осадков в области планеты.
*/
static __constant size_t PRECIPITATIONS_GRID = 81;



/**
* Сетка для генерации поверхности / пустот в области планеты.
*/
static __constant size_t SURFACE_VOID_GRID = 81;



/**
* Количество регистров для генерации поверхности / пустот в
* области планеты.
*/
static __constant size_t SURFACE_VOID_REGISTRY = 5;
#endif

#endif





/**
* Группы элементов.
*
*   # Перечисления не имеют элемента NONE, если их предполагается
*     использовать в качестве индекса массивов.
*/
enum GROUP_ELEMENT {
    // пустая группа или отсутствует
    GE_NONE = 0,

    /* - Не используем. Вместо них - местность (TERRAIN).
    // биомы
    GE_BIOME,
    */

    // компоненты (воздух, плодородная почва, камень и т.п.)
    // @see component_t
    GE_COMPONENT,

    // @see temperature_t
    GE_TEMPERATURE,

    // @see surfaceTemperature_t
    GE_SURFACE_TEMPERATURE,

    // @see rainfall_t
    GE_RAINFALL,

    // @see drainage_t
    GE_DRAINAGE,

    // @see TERRAIN
    GE_TERRAIN,

    // энергии
    GE_ENERGY,

    // любые формы жизни
    // @see aboutOneLiving_t
    GE_LIVING,

    // части живых существ, растений
    // @see aboutOnePartLiving_t
    GE_PART_LIVING,

    // последняя
    GE_last

    // @todo fine Перечислить здесь все элементы мира.
};




/**
* Код элемента (компонента, особи).
* Номер элемента в CODE_*.
*
* @see set::Component, set::Living
*/
typedef cl_ushort code_t;






#if 0
// - @todo ...

/**
* Сетка давлений жидкостей и газов в области планеты.
* Для компонентов в состоянии "твёрдое тело" смысла не имеет.
*/
typedef struct {
    /**
    * Давление, Па.
    */
    typedef cl_float average_t[ PRESSURE_GRID * PRESSURE_GRID * PRESSURE_GRID ];
    average_t average;

} pressure_t;







/**
* Атмосферные осадки в области планеты.
*
* @todo extend Осадки могут быть разными: вода, пепел, кислота, метеориты, ...
*/
typedef struct {
    /**
    * Количество осадков, м / пульс.
    */
    typedef cl_float rainfall_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    rainfall_t rainfall;

    /**
    * Частота выпадения осадков, раз / пульс.
    */
    typedef cl_float rate_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    rate_t rate;

    /**
    * Средняя длительность осадков, дробный пульс.
    */
    typedef cl_float averageDuration_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    averageDuration_t averageDuration;

    /**
    * Разброс длительности осадков (на сколько % / 100 длительность
    * отклоняется от средней длительности).
    */
    typedef cl_float dispersionDuration_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
    dispersionDuration_t dispersionDuration;

} precipitations_t;






/**
* Поверхности / пустоты в области планеты.
* Значения используются для детализации ландшафта поверхностей и
* пустот (пещер, полостей) внутри твёрдых компонентов планеты.
*/
typedef struct {
    /**
    * Используется набор регистров, значения которых интерпретируются
    * в контексте компонентов области планеты и их фазовых состояний.
    *
    * Атмосфера, вакуум
    *   - Не используются
    *
    * Поверхность планеты
    *   0, 1  Крайние отклонения от сферы планеты в этой ячейке (глубины и высоты)
    *   2     Количество перепадов
    *   3, 4  Крутизна перепадов: (3) расстояние и (4) высота перепада
    *
    * Внутри компонентов планеты в жидком состоянии
    *   - Не используется
    *
    * Внутри компонентов планеты в газообразном состоянии
    *   - Не используется
    *
    * Внутри компонентов планеты в твёрдом состоянии
    *   - 0, ... @todo Характеристики пустот
    */
    typedef cl_float r_t[ SURFACE_VOID_REGISTRY ];
    r_t r;

} aboutOneSurfaceVoid_t;

//typedef aboutOneSurfaceVoid_t aboutSurfaceVoid_t[ SURFACE_VOID_GRID * SURFACE_VOID_GRID * SURFACE_VOID_GRID ];
typedef struct {
    aboutOneSurfaceVoid_t about[ SURFACE_VOID_GRID * SURFACE_VOID_GRID * SURFACE_VOID_GRID ];
} aboutSurfaceVoid_t;
#endif




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
