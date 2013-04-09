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
                    
// # Звёздной системе требуется большая точность.
//   Пробы обойтись float-векторами для представления "больших чисел",
//   принесли больше проблем, чем решили. В любом случае, пока получится
//   что-то стоящее, современные компьютеры будут поддерживать OpenCL 1.2.
typedef cl_double   real_t;
typedef cl_double2  real2_t;
typedef cl_double3  real3_t;
typedef cl_double4  real4_t;

// суффикс для корректного восприятия чисел компилятором OpenCL
//   "f" - для float
//   ""  - для double
static const std::string NS = "";

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
    // # Включает в себя их уменьшение и увеличения.
    E_CHANGE_COORD,
    E_CHANGE_MASS,
    E_CHANGE_SIZE,
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




#if 0
// - ?
/**
* Модели поведения, которые могут быть усвоены *конкретными* элементами
* звёздной системы.
*
* # Декларированы как перечисление, чтобы модели можно было использовать
*   в ядрах OpenCL.
*/
enum MODEL {
    // пустая модель или отсутствует
    M_NONE = 0,

    /**
    * Расти, питаясь светом от звезды.
    */
    M_GROW_UP_EAT_SUN_LIGHT,

    // последняя
    M_last
};
#endif





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # В OpenCL передаём константы как define: OpenCL не воспринимает
//   константы должным образом.


/**
* Макс. кол-во элементов, которые могут существовать (взаимодействовать)
* в области звёздной системы (в портулане).
*
* # Резервируем на 1 элемент больше, чтобы в коде не заморачиваться с
*   условиями добавления признака окончания списка. Т.е. последний
*   элемент всегда пустой.
* # Т.к. структуры будут передаваться OpenCL, их оптимальный размер должен
*   быть кратен максимально возможному кол-ву рабочих групп на устройстве -
*   CL_DEVICE_MAX_WORK_GROUP_SIZE. Но если кол-во э. заведомо меньшего кол-ва
*   групп, надо придерживаться кратности устройства (multiple of the
*   wavefront / warp size).
*/
static __constant size_t WAVEFRONT_OPENCL_DEVICE = 64;
static __constant size_t HALF_WAVEFRONT_OPENCL_DEVICE =
    WAVEFRONT_OPENCL_DEVICE / 2;

static __constant size_t ASTEROID_COUNT = WAVEFRONT_OPENCL_DEVICE * 30;
static __constant size_t PLANET_COUNT =   WAVEFRONT_OPENCL_DEVICE * 2;
static __constant size_t STAR_COUNT =     WAVEFRONT_OPENCL_DEVICE * 1;




/**
* Какое макс. кол-во событий может выдать элемент за 1 пульс.
*
* @see Комм. к WAVEFRONT_OPENCL_DEVICE.
*/
static __constant size_t EMIT_EVENT_ASTEROID_COUNT = HALF_WAVEFRONT_OPENCL_DEVICE;
static __constant size_t EMIT_EVENT_PLANET_COUNT   = HALF_WAVEFRONT_OPENCL_DEVICE;
static __constant size_t EMIT_EVENT_STAR_COUNT     = HALF_WAVEFRONT_OPENCL_DEVICE;




/**
* Какое макс. кол-во уникальных моделей поведения способен запомнить элемент.
*
* @todo Индивидуальная память для каждой группы элементов.
* @todo extend Индивидуальная память для каждого конкретного элемента.
*/
static __constant size_t MEMORY_MODEL_COUNT = 7;




/**
* Сколько уникальных моделей поведения этот элемент может запомнить для
* выполнения через определённые промежутки времени.
*
* @todo Индивидуальная память для каждой группы элементов.
* @todo extend Индивидуальная память для каждого конкретного элемента.
*/
static __constant size_t FREQUENCY_MEMORY_MODEL_COUNT = 5;




/**
* Макс. длина UID для модели поведения.
*
* @todo optimize bad Можно не держать последний символ - всегда '\0'.
*
* @see real_t
*/
static __constant size_t UID_MODEL_LENGTH = 10 + 1;




/**
* Максимальное значение вещественного числа.
*
* @see real_t
*/
static __constant real_t REAL_MAX = std::numeric_limits< real_t >().max();


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
* Структура для обмена характеристиками событий.
*/
typedef struct __attribute__ ((packed)) {
    real_t   a;
    real_t   b;
    real_t   c;
    real_t   d;
    real3_t  a3;
    real3_t  b3;
} cell_t;




/**
* События для элементов звёздной системы.
*
* Соглашения для emitterEvent_t
*   # Каждый элемент звёздной системы помнит о EMITTER_EVENT_COUNT событиях,
*     которые как-то воздействовали на него - см. *ImpactIn().
*   # События записываются последовательно от меньшей адресации к большей.
*   # Индекс для записи текущего события всегда лежит в диапазоне
*     [0; EMITTER_EVENT_COUNT - 1]
*   # Первое событие записывается по индексу 0.
*   # Каждая запись нового события увеличивает индекс на 1.
*   # При достижения границы EMITTER_EVENT_COUNT, индекс вновь указывает
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
    */
    cell_t cell;

} eventTwo_t;




/**
* Указатель для прохождения по всем событиям элемента.
*/
typedef cl_uint  pointerEvent_t;




/**
* UID для моделей поведения.
* 
* # Хранятся названия моделей, т.к. модели оформлены в виде ядер OpenCL.
*
* @see model_t
*/
typedef cl_char  uidModel_t[ UID_MODEL_LENGTH ];




/**
* Модели поведения для элементов звёздной системы.
* Эти модели делают элемент *уникальным*.
*
* Соглашения для memoryModel_t
*   # Те же соглашения, что для emitterEvent_t.
*/
typedef struct __attribute__ ((packed)) {
    uidModel_t uid;

    // @todo Модель должна уметь распозновать может ли её усвоить
    //       конкретный элемент.

} model_t;




/**
* Все усвоенные элементом модели поведения.
*/
typedef struct __attribute__ ((packed)) {
    cl_int waldo;
    model_t content[ MEMORY_MODEL_COUNT ];
} memoryModel_t;




/**
* Структура для 'frequencyMemoryModel_t'.
*/
typedef struct __attribute__ ((packed)) {
    uidModel_t uid;

    /**
    * Сколько пульсов движка должна пропустить модель до своего выполнения
    * на элементе.
    *
    * # Промежуток простаивания модели задаётся в пульсах, т.к. это проще
    *   для реализации и быстрее, чем задавать в секундах.
    */
    cl_int skipPulse;

} frequencyModel_t;




/**
* Модели поведения, которые будут выполняться элементом через
* определённые промежутки времени.
*
* # Все перечисленные в этой памяти модели есть в 'memoryModel'.
*/
typedef struct __attribute__ ((packed)) {
    cl_int waldo;
    frequencyModel_t content[ FREQUENCY_MEMORY_MODEL_COUNT ];
} frequencyMemoryModel_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
