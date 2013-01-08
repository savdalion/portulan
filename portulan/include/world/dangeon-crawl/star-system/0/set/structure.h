#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

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
* # Для звёздной системы расчёты желательно вести в double: float даёт
*   ощутимую погрешность.
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
                    
// Увы, не все видеокарты поддерживают 'double' для OpenCL.
// #! Типы данных должны быть согласованы с OpenCL GPU.
// # double4 поддерживается не всеми устройствами OpenCL. Не используем.
#ifdef PERMIT_DOUBLE_ENGINE_PORTULAN
typedef cl_double  real_t;
#else
typedef cl_float   real_t;
#endif

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

    // последнее
    E_last
};





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # В OpenCL передаём константы как define: OpenCL не воспринимает
//   константы должным образом.


/**
* Макс. кол-во элементов, которые могут существовать (взаимодействовать)
* в области звёздной системы (в портулане).
*/
static __constant size_t ASTEROID_COUNT = 1000;
static __constant size_t PLANET_COUNT = 100;
static __constant size_t STAR_COUNT = 10;



/**
* Макс. кол-во событий, которые способен помнить элемент.
*
* # Элемент должен уметь помнить больше одного события.
*
* @see event_t
*/
static __constant size_t ASTEROID_EVENT_COUNT = 10;
static __constant size_t PLANET_EVENT_COUNT = 20;
static __constant size_t STAR_EVENT_COUNT = 40;



/**
* Макс. кол-во событий, которые способен помнить наблюдатель.
*
* # Объём памяти наблюдателя должен быть достаточен, чтобы охватить все
*   события с двумя (@todo extend и более) участниками, которые могут случиться
*   за один пульс.
*/
static __constant size_t OBSERVER_EVENT_TWO_COUNT = 200;


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
typedef struct {
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
* События для наблюдателя за элементами звёздной системы.
*
* Соглашения для *MemoryEventTwo_t
*   # Наблюдатель звёздной системы помнит о *_EVENT_*_COUNT событиях.
*   # События записываются последовательно от меньшей адресации к большей.
*   # Индекс для записи текущего события всегда лежит в диапазоне
*     [0; *_EVENT_*_COUNT - 1]
*   # Первое событие записывается по индексу 0.
*   # Каждая запись нового события увеличивает индекс на 1.
*   # При достижения границы *_EVENT_*_COUNT, индекс вновь указывает
*     на первую ячейку памяти для события.
*/
typedef struct __attribute__ ((packed)) {
    EVENT uid;

    /**
    * Элементы-участники события.
    * Например, при столкновении астероида со звездой, будет содержать
    * указатели на астероид и на звезду в списке топологии портулана.
    */
    pointerElement_t piA;
    pointerElement_t piB;

} eventTwo_t;




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
    EVENT uid;

    /**
    * Второй элемент-участник события.
    * Например, при столкновении элемента с планетой, будет содержать
    * указатель на планету в списке топологии портулана.
    */
    pointerElement_t pi;

} event_t;



/**
* Указатель для последовательного прохождения по событиям звёздной системы.
*/
typedef struct __attribute__ ((packed)) {
    pointerElement_t pi;

    /**
    * Индекс события в памяти элемента.
    */
    cl_uint kk;

} pointerEvent_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
