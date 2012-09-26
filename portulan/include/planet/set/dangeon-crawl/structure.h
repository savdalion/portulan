#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>


/**
*   # Структуры построены так, чтобы не дублировать их при включении
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




// Декларируем структуры, используемые с пространством имён (OpenCL 1.0
// не поддерживает NS)
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
#define __structComponentAll_t      component::componentAll_t
#define __structPortionComponent_t  component::portionComponent_t
#define __structPortionEnergy_t     component::portionEnergy_t
#define __enumCodeComponent         component::CODE_COMPONENT
#define __enumCodeEnergy            component::CODE_ENERGY

#define __structLivingAll_t         living::livingAll_t

#define __structTemperatureAll_t    temperature::temperatureAll_t
//#define __structTemperatureCell_t   temperature::temperatureCell_t

#else
#define __structComponentAll_t      componentAll_t
#define __structPortionComponent_t  portionComponent_t
#define __structPortionEnergy_t     portionEnergy_t
#define __enumCodeComponent         enum CODE_COMPONENT
#define __enumCodeEnergy            enum CODE_ENERGY

#define __structLivingAll_t         livingAll_t

#define __structTemperatureAll_t    temperatureAll_t
//#define __structTemperatureCell_t   temperatureCell_t

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
* Значение, задающее неуязвимость, например, органа особи, от
* конкретного внешнего воздействия.
* Например, лапка муравья никак не реагирует при воздействии на неё
* магии "святое слово".
*/
static __constant cl_float IMMUNE = CL_FLT_MAX;





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
// В OpenCL передаём константы как define: OpenCL не воспринимает
// константы должным образом.

/**
* Размер сетки компонентов в области планеты (в портулане).
*/
static __constant size_t COMPONENT_GRID = 81;



/**
* Макс. кол-во *разных* компонентов, которые могут использоваться
* в области планеты (в портулане).
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



#if 0
// - Не будем использовать биомы. В основном они нужны, чтобы связать
//   живой мир с областью планеты. Сделаем это, определив подходящие
//   условия для жизни особей и расселяя их в комфортных зонах.
/**
* Сетка распределения биомов в области планеты.
*/
static __constant size_t BIOME_GRID = 81;



/**
* Макс. кол-во *разных* компонентов, которые могут использоваться
* в области планеты (в портулане).
*/
static __constant size_t BIOME_COUNT = 100;



/**
* Макс. кол-во биомов, которые могут *одновременно* храниться
* в 1-й ячейке портулана.
*/
static __constant size_t BIOME_CELL = 3;
#endif




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
static __constant size_t PART_LIVING_COUNT = 20;



/**
* Максимальное кол-во *разных* атак, известных органу особи.
*
* @see RESIST_PART_LIVING_COUNT
*/
static __constant size_t ATTACK_PART_LIVING_COUNT = 30;



/**
* Максимальное кол-во *разных* защит, известных органу особи.
*
* @see ATTACK_PART_LIVING_COUNT
*/
static __constant size_t RESIST_PART_LIVING_COUNT = 30;



/**
* Максимальное кол-во наборов сред обитания, в которых может
* жить особь.
*/
static __constant size_t HABITAT_LIVING_COUNT = 5;



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
* Максимальное количество сред, где может обитать особь.
*/
static __constant size_t ENVIRONMENT_SURVIVOR_LIVING = 5;



/**
* Максимально возможное кол-во *разных* особей в области планеты.
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
*   # Перечисления не имеют элемента UNDEFINED, т.к. планируется использовать
*     перечисления в качестве индекса массивов.
*/
enum GROUP_ELEMENT {
    // биомы
    GE_BIOME = 1,
    // компоненты (воздух, плодородная почва, камень и т.п.)
    GE_COMPONENT,
    // энергии
    GE_ENERGY,
    // живые существа, растения
    GE_LIVING,
    // части живых существ, растений
    GE_PART_LIVING,
    // @todo осадки, см. precipitations_t
    // GE_PRECIPITATIONS,

    // последняя
    GE_last
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
