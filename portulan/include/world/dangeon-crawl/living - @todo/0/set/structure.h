#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>


/**
*   # Структуры организованы т. о., чтобы не дублировать их при включении
*     в код OpenCL.
*/
#ifndef __constant
#define __constant const
#endif

#ifndef __global
#define __global /*nothing*/
#endif

// Выравнивание для VC++ не требуется
#define __attribute__(x) /*nothing*/


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {
#endif



/**
* Направления в 3D.
* Представлено битовыми масками.
*   # Зажигаются биты, соответствующие нумерации ячеек (см. ниже).
*
* @copy typelib::StaticMapContent3D
* Принцип нумерациии частей 3D-ячейки (тринумов), разбитой 3-мя плоскостями.
* Смотрим по оси OY на куб 3x3x3. Ось Z направлена вверх.
* Снимаем средний (центральный) 2D слой - номеруем его согласно isc2D().
* Снимаем ближний - номеруем также. Снимаем дальний слой - аналогично.
*
    Нумерация, вертикальный разрез:

    дальний 2D слой
    26   19   23
    22   18   20
    25   21   24

    центральный 2D слой
    8   1   5
    4   0   2
    7   3   6

    ближний 2D слой
    17   10   14
    13    9   11
    16   12   15
*/
enum DIRECTION {
    // направление отсутствует или не определено
    D_NONE = 1 << 0,

    // центральный 2D слой
    D_00 = D_NONE,
    D_01 = 1 << 1,
    D_ZENITH = D_01,
    D_02 = 1 << 2,
    D_EAST = D_02,
    D_03 = 1 << 3,
    D_NADIR = D_03,
    D_04 = 1 << 4,
    D_WEST = D_04,
    D_05 = 1 << 5,
    D_06 = 1 << 6,
    D_07 = 1 << 7,
    D_08 = 1 << 8,

    // ближний 2D слой
    D_09 = 1 << 9,
    D_SOUTH = D_09,
    D_10 = 1 << 10,
    D_11 = 1 << 11,
    D_12 = 1 << 12,
    D_13 = 1 << 13,
    D_14 = 1 << 14,
    D_15 = 1 << 15,
    D_16 = 1 << 16,
    D_17 = 1 << 17,

    // дальний 2D слой
    D_18 = 1 << 18,
    D_NORTH = D_18,
    D_19 = 1 << 19,
    D_20 = 1 << 20,
    D_21 = 1 << 21,
    D_22 = 1 << 22,
    D_23 = 1 << 23,
    D_24 = 1 << 24,
    D_25 = 1 << 25,
    D_26 = 1 << 26,
};





/**
* Критерии для оценки.
* Цвета разданы по спектру > http://ru.wikipedia.org/wiki/%D0%A6%D0%B2%D0%B5%D1%82#.D0.A6.D0.B2.D0.B5.D1.82.D0.B0_.D1.81.D0.BF.D0.B5.D0.BA.D1.82.D1.80.D0.B0_.D0.B8_.D0.BE.D1.81.D0.BD.D0.BE.D0.B2.D0.BD.D1.8B.D0.B5_.D1.86.D0.B2.D0.B5.D1.82.D0.B0
*/
enum CRITERIA {
    // абсолютно не важно / ничего нет / не определено
    CRITERIA_NONE = 0,
    CRITERIA_EMPTY = CRITERIA_NONE,
    CRITERIA_A_WHITE = CRITERIA_NONE,
    // ниже среднего / мало
    CRITERIA_B_BLUE,
    // средняя важность / нормально
    CRITERIA_C_GREEN,
    // выше среднего / много
    CRITERIA_D_YELLOW,
    // жизненная необходимость / предостаточно
    CRITERIA_E_RED,

    // последний = кол-во критериев
    CRITERIA_last,
    CRITERIA_count = CRITERIA_last
};





/**
* Жизненный цикл особи (животного, растения).
*
* @see LIFE_CYCLE_COUNT
*/
enum LIFE_CYCLE {
    // Эмбрион особи, семя
    LC_EMBRYO   = 0,
    // Ребёнок, росток
    LC_CHILD    = 1,
    // Взрослый
    LC_ADULT    = 2,
    // Старик
    LC_OLD      = 3,
    // Мёртвая особь - тело, скелет
    LC_DEAD     = 4,
    // Бессмертная особь
    LC_IMMORTAL = 5,

    // последний = кол-во циклов
    LC_last,
    LC_count = LC_last
};





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
* Максимально возможное кол-во *разных* особей.
* >= CC_last
*
* @see CODE_LIVING
*/
static __constant size_t LIVING_COUNT = 100;



#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
