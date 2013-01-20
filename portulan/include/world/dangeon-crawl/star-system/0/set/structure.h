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
// @see coordOne_t, mass_t
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
* База по которой вычисляются координаты для coordOne_t.
*
* @see utils.h / convertCoord()
*/
static __constant real_t COORD_ONE_BASE = 1000000000.0f;


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
* Координата элемента с увеличенной точностью.
*
* # Задача структуры - обеспечить достаточную точность вычисления
*   1D-координаты с максимально высокой скоростью.
*
* @see utils.h / convertCoord() для отражения float-значения в coordOne_t.
* @see utils.h / coord() для получения coordOne_t как float-значения.
* @see Коммент. к typedef real_t.
*/
typedef struct __attribute__ ((packed)) {
    real_t a;
    real_t b;
    real_t c;
} coordOne_t;





/**
* Масса элемента и прирост к массе (бугорок).
* Из-за огромных значений, вынуждены держать массу в двух переменных
* Для получения полной массы элемента следует вызывать pns::mass*().
*/
typedef struct __attribute__ ((packed)) {
    real_t base;
    real_t knoll;
} mass_t;




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
