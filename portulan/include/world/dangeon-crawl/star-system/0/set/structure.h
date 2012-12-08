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

#include <CL/cl_platform.h>


/**
* # Для звёздной системы расчёты желательно вести в double: float даёт
*   ощутимую погрешность.
* # Координаты (~0, ~0, ~0) - центр звёздной системы.
* # Структуры организованы т. о., чтобы не дублировать их при включении
*   в код OpenCL.
*/
#define __constant const

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
#if defined( PERMIT_DOUBLE_ENGINE_PORTE )
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




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
// # В OpenCL передаём константы как define: OpenCL не воспринимает
//   константы должным образом.


/**
* Макс. кол-во тел, которые могут существовать (взаимодействовать)
* в области звёздной системы (в портулане).
*/
static __constant size_t BODY_COUNT = 5000;


#endif




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
