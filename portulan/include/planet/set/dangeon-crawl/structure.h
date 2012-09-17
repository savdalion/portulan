#pragma once

#include <CL/cl_platform.h>


/**
*   # Структуры построены так, чтобы не дублировать их при включении
*     в код OpenCL.
*/

namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {

/**
* Значение, задающее неуязвимость, например, органа особи, от
* конкретного внешнего воздействия.
* Например, лапка муравья никак не реагирует при воздействии на неё
* магии "святое слово".
*/
static const cl_float IMMUNE = CL_FLT_MAX;



/**
* Размеры портулана.
* Задаются здесь, чтобы этот файл мог быть подключен как код OpenCL.
* Не задействуем шаблоны, чтобы модель на C++ более органично вписывалась
* в OpenCL.
*
* @todo extend Допустимо использовать только кубическую сетку.
*//* - Используем мн-во сеток. См. ниже.
static const size_t GRID_SX = 81;
static const size_t GRID_SY = GRID_SX;
static const size_t GRID_SZ = GRID_SX;
*/


/**
* Деление области планеты на ячейки.
* Используется для формирования разных "кратных" портуланов, декларирующих
* область планеты и её жизнь (статика, динамика задаётся в "porte"). См. ниже.
*/
static const size_t GRID = 81;




/**
* Размер сетки компонентов в области планеты (в портулане).
*/
static const size_t COMPONENT_GRID = GRID;



/**
* Макс. кол-во *разных* компонентов, которые могут использоваться
* в области планеты (в портулане).
*/
static const size_t COMPONENT_COUNT = 100;



/**
* Макс. кол-во компонентов с указанием частей от целого, которые могут
* *одновременно* храниться в 1-й ячейке портулана.
*/
static const size_t COMPONENT_CELL = COMPONENT_COUNT / 10;



/**
* Жизненный цикл особи на планете (животного, растения).
*
* # Цикл обрисован группами:
*     0    Эмбрионы особей, семена.
*     1    Дети, ростки.
*     2    Взрослые.
*     3    Старики.
*     4    Мёртвые особи - тела, скелеты.
*     5    Бессмертные особи.
*/
static const size_t LIFE_CYCLE = 6;



/**
* Размер сетки ареалов обитания живых организмов в области планеты.
*/
static const size_t LIVING_GRID = GRID / 3;



/**
* Максимальное кол-во *разных* частей (органов), из которых может
* состоять особь.
*/
static const size_t PART_LIVING_COUNT = 20;



/**
* Максимальное кол-во наборов сред обитания, в которых может
* жить особь.
*/
static const size_t HABITAT_LIVING_COUNT = 5;



/**
* Максимальное кол-во *разных* хим. компонентов, из которых может
* состоять орган особи.
*/
static const size_t COMPONENT_COMPOSITION_LIVING = 5;



/**
* Макисмальное кол-во *разных* хим. компонентов, которые нужны
* особи для поддержания жизни.
*/
static const size_t COMPONENT_NEED_LIVING = 10;



/**
* Максимальное кол-во *разных* хим. компонентов, которые выделяет
* особь при жизнедеятельности.
*/
static const size_t COMPONENT_WASTE_LIVING = COMPONENT_NEED_LIVING;



/**
* Максимальное кол-во *разных* видов энергии, которая необходима
* особи для поддержания жизни.
*
* @see CODE_ENERGY
*/
static const size_t ENERGY_NEED_LIVING = 5;



/**
* Максимальное кол-во *разных* видов энергии, которя излучает
* особь при жизнедеятельности.
*
* @see CODE_ENERGY
*/
static const size_t ENERGY_WASTE_LIVING = ENERGY_NEED_LIVING;



/**
* Максимальное количество сред, где может обитать особь.
*/
static const size_t ENVIRONMENT_SURVIVOR_LIVING = 5;



/**
* Максимально возможное кол-во *разных* особей в области планеты.
*/
static const size_t LIVING_COUNT = 100;



/**
* Макс. кол-во особей, которые могут *одновременно* обитать в 1-й ячейке
* области планеты.
*/
static const size_t LIVING_CELL = LIVING_COUNT / 4;



/**
* Размер сетки давлений на планете.
* Указывается для всей планеты.
* Благодаря разнице давлений в атмосфере возникают ветры, тайфуны.
*/
static const size_t PRESSURE_GRID = GRID;



/**
* Сетка распределения температуры в области планеты.
*/
static const size_t TEMPERATURE_GRID = GRID;



/**
* Сетка распределения осадков в области планеты.
*/
static const size_t PRECIPITATIONS_GRID = GRID;



/**
* Сетка для генерации поверхности / пустот в области планеты.
*/
static const size_t SURFACE_VOID_GRID = GRID;



/**
* Количество регистров для генерации поверхности / пустот в
* области планеты.
*/
static const size_t SURFACE_VOID_REGISTRY = 5;






/**
* Группы элементов.
*
*   # Перечисления не имеют элемента UNDEFINED, т.к. планируется использовать
*     перечисления в качестве индекса массивов.
*/
enum GROUP_ELEMENT {
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
    GE_count
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
* Общая информация о планете.
*/
typedef struct {
    /**
    * Радиус планеты, м.
    */
    cl_float radiusPlanet;

    /**
    * Размер области планеты, м.
    * Радиус атмосферы = Размер области планеты / 2
    * Толщина атмосферы = Радиус атмосферы - Радиус планеты
    */
    cl_float sizeArea;

    /**
    * Масса планеты, кг.
    */
    cl_float massPlanet;

    /**
    * Состав планеты, перечисление всех компонентов и их массовой части в целом.
    *
    * # Для удобства код компонента соотв. его индексу в componentAll_t.
    * # Неиспользуемые компоненты заполняются нулями.
    */
    componentAll_t componentPlanet;

    /**
    * Масса атмосферы, кг.
    */
    cl_float massAtmosphere;

    /**
    * Состав атмосферы, перечисление всех компонентов и их массовой части в целом.
    *
    * @see Соглашения для componentPlanet.
    */
    componentAll_t componentAtmosphere;

} aboutPlanet_t;




/**
* Компоненты планеты. Какую часть объёма занимают в 1-й ячейке портулана.
*
* Например: воздух 0.1, плодородная почва 0.7, вода 0.05, камень 0.15.
*/
typedef struct {
    /**
    * Содержание в ячейке (по объёму).
    * Реализовано в виде % / 100 концентрации компонентов.
    * Сумма всех = 1.0.
    */
    typedef componentCell_t content_t[ COMPONENT_GRID * COMPONENT_GRID * COMPONENT_GRID ];
    content_t content;

} component_t;







/**
* *Разные* особи в области планеты.
*/
//typedef aboutOneLiving_t aboutLiving_t[ LIVING_COUNT ];
typedef struct {
    aboutOneLiving_t about[ LIVING_COUNT ];
} aboutLiving_t;



/**
* Особи, которые *одновременно* обитают в 1-й ячейке области планеты.
*/
typedef eportion_t     livingCount_t[ LIFE_CYCLE ];
typedef livingCount_t  livingCell_t[ LIVING_CELL ];


/**
* Живой мир (растения, животные и пр.; далее - особи).
* Кол-во особей по ареалам обитания; область планеты разбивается на объём
* 27х27х27 и каждая полученная ячейка считается ареалом обитания групп
* особей; т.о. *каждой* группе живого мира сопоставляется 19683 ареалов
* обитания.
*/
typedef struct {
    /**
    * Кол-во особей в ячейке.
    * Кол-во больных особей определяется @todo очагами болезней и
    * иммунитетом особей.
    * Особи собраны по группам.
    */
    typedef livingCell_t content_t[ LIVING_GRID * LIVING_GRID * LIVING_GRID ];
    content_t content;

} living_t;




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
* Температура области планеты.
*/
typedef struct {
    /**
    * Среднее значение температуры, К.
    */
    typedef cl_float average_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    average_t average;

    /**
    * Отклонение температуры от среднего значения, % / 100.
    */
    typedef cl_float dispersion_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    dispersion_t dispersion;

    /**
    * Частота отклонения температуры от среднего значения, раз / пульс.
    */
    typedef cl_float rate_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
    rate_t rate;

} temperature_t;






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


            } // dungeoncrawl
        } // set
    } // planet
} // portulan
