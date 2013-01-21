#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

// #! Структуры OpenCL и C++ должны быть одинакового размера.
//    Особое внимание стоит обратить на структуры, которые содержат
//    вложенные структуры и атрибут "упаковать".
#pragma pack( 1 )


/* - ?
#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    #pragma error( "Double precision floating point not supported by OpenCL implementation." )
#endif
*/

#include "../../../../../../configure.h"
#include <CL/cl_platform.h>
#include <string>
#include <ostream>


/**
* # Для звёздной системы расчёты желательно вести с большей точностью:
*   чистый float даёт ощутимую погрешность.
* # Координаты (~0, ~0, ~0) - центр звёздной системы.
* # Структуры организованы т. о., чтобы не дублировать их при включении
*   в код OpenCL.
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
            namespace starsystem {
                namespace l0 {
                    
// # Т.к. не все видеокарты поддерживают 'double' для OpenCL и не все CPU
//   на сегодня корректно отрабатывают двойную точность (на CPU Intel i5 под
//   Windows мне не удалось подключить расширение cl_khr_fp64), я отказался
//   от работы с типом 'double' в пользу составных чисел, где требуется
//   большая точность.
typedef cl_float   real_t;
typedef cl_float2  real2_t;
typedef cl_float4  real4_t;

#endif




/**
* Группы элементов звёздной системы.
*/
enum GROUP_ELEMENT {
    // пустая группа или отсутствует
    GE_NONE = 0,

    // астероид
    // @see asteroid_t
    GE_ASTEROID,

    // планета
    // @see planet_t
    GE_PLANET,

    // звезда
    // @see star_t
    GE_STAR,

    // последняя
    GE_last
};




/**
* События, которые могут случиться для элементов звёздной системы.
*/
enum EVENT {
    // пустое событие или отсутствует
    E_NONE = 0,

    // столкновение элементов звёздной системы
    E_COLLISION,

    // изменение характеристик
    E_CHANGE_COORD,
    E_CHANGE_MASS,
    E_CHANGE_TEMPERATURE,
    E_CHANGE_VELOCITY,

    // раскалывание на N частей
    E_CRUSH_N,

    // уничтожение элемента
    E_DESTROY,

    // притягивание / отталкивание гравитацией других объектов
    E_GRAVITY,

    // тело ускоряется
    E_IMPACT_ACCELERATION,

    // воздействие силы
    E_IMPACT_FORCE,

    // излучение энергии (например, свет звезды)
    E_RADIATION,

    // последнее
    E_last
};





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # В OpenCL передаём константы как define: OpenCL не воспринимает
//   константы должным образом.


/**
* Макс. кол-во элементов, которые могут существовать (взаимодействовать)
* в области звёздной системы (в портулане).
*
* # Резервируем на 1 элемент больше, чтобы в коде не заморачиваться с
*   условиями добавления признака окончания списка.
*/
static __constant size_t ASTEROID_COUNT = 1000 + 1;
static __constant size_t PLANET_COUNT = 100 + 1;
static __constant size_t STAR_COUNT = 10 + 1;



/**
* Макс. кол-во характеристик, которое может содержать событие.
*
* @see eventTwo_t
*/
static __constant size_t MAX_FEATURE_EVENT = 5;




/**
* Какое макс. кол-во событий может выдать элемент за 1 пульс.
*/
static __constant size_t EMITTER_EVENT_COUNT = 10;




/**
* Базы по которым вычисляются "большие числа".
*
* # "Большие числа" храним в структуре real4_t.
* # Задача структуры - обеспечить достаточную точность вычисления
*   1D-координаты с максимально высокой скоростью.
* # Числа одинарной точности обеспечивают относит. точность
*   7-8 десятичных цифр в диапазоне ( 1e-38; 1e38 ).
*
* @see utils.h / convertToBigValue() для отражения float-значения в real4_t.
* @see utils.h / convertFromBigValue() для получения real4_t как float или double.
* @see Коммент. к typedef real*_t.
*
* @see utils.h / convertBigValue()
*/
static __constant real_t BIG_VALUE_BASE_0 = static_cast< real_t >( 1e10 );
static __constant real_t BIG_VALUE_BASE_1 = static_cast< real_t >( 1e20 );
static __constant real_t BIG_VALUE_BASE_2 = static_cast< real_t >( 1e30 );
// # Четвёртое число записывается в float уменьшенное в 1e38 раз.
static __constant real_t BIG_VALUE_BASE_3 = static_cast< real_t >( 1e38 );


#endif





/**
* Идентификатор элемента, уникальный в пределах списка.
* Необходимость ввести UID возникла, т.к. элементы списков не остаются
* на своём месте (меняют индексы).
*/
typedef cl_int  uid_t;




/**
* Идентификатор элемента в звёздной системе.
*/
typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT ge;
    uid_t uid;
} uidElement_t;




/**
* Указатель на элемент системы.
*/
typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT ge;

    /**
    * Индекс в списке элементов.
    */
    cl_uint ii;

    /**
    * Уник. идент. в списке элементов.
    * Введён, т.к. не всегда целесообразно отдавать целый список для
    * получения UID элемента.
    */
    uid_t uu;

} pointerElement_t;




/**
* Координаты элемента в звёздной системе.
*
* @see utils.h / convert*BigValue() для работы с "большими числами".
*/
typedef struct __attribute__ ((packed)) {
    real4_t x;
    real4_t y;
    real4_t z;
} coord_t;




/**
* События для элементов звёздной системы.
*
* Соглашения для *MemoryEvent_t
*   # Каждый элемент звёздной системы помнит о *_EVENT_COUNT событиях,
*     которые как-то воздействовали на него - см. *ImpactIn().
*   # События записываются последовательно от меньшей адресации к большей.
*   # Индекс для записи текущего события всегда лежит в диапазоне
*     [0; *_EVENT_COUNT - 1]
*   # Первое событие записывается по индексу 0.
*   # Каждая запись нового события увеличивает индекс на 1.
*   # При достижения границы *_EVENT_COUNT, индекс вновь указывает
*     на первую ячейку памяти для события.
*/
typedef struct __attribute__ ((packed)) {
    enum EVENT uid;

    /**
    * Второй элемент-участник события.
    * Например, при столкновении элемента с планетой, будет содержать
    * указатель на планету в списке топологии портулана.
    */
    pointerElement_t pi;

    /**
    * Характеристики события.
    *
    * #i Удобно было бы оформить характеристик в виде union-структур, но
    *    OpenCL 1.0 не дружит с обменом подобных структур.
    */
    real_t fReal[ MAX_FEATURE_EVENT ];

} eventTwo_t;




/**
* Все выпущенные элементом за 1 пульс события.
*/
typedef struct __attribute__ ((packed)) {
    cl_int waldo;
    eventTwo_t content[ EMITTER_EVENT_COUNT ];
} emitterEvent_t;




/**
* Указатель для прохождения по всем событиям элемента.
*/
typedef cl_uint  pointerEvent_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
