#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>
#include "structure.h"


/**
* Функции для вычисления значений по формулам.
* Многие ф. скопированы взяты из typelib::compute и переписаны т.о., чтобы
* могли использоваться ядрами OpenCL.
*
* # Работают, в отличие от 'utils.h', только с локальными параметрами.
* # Для звёздной системы расчёты желательно вести в double: float даёт
*   ощутимую погрешность.
* # Методы организованы т. о., чтобы не дублировать их при включении
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

#endif


/**
* Вычисляет длину 3D-вектора. Записывает рез-т в последнюю ячейку вектора.
*/
inline void lengthVector( __global real4_t* v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    *v = (real4_t)(
        //v->x, v->y, v->z,
        0, 0, 0,
        length( (real4_t)( v->x, v->y, v->z, 0 ) )
    );
#else
    v->s[ 3 ] = std::sqrt(
        v->s[ 0 ] * v->s[ 0 ] +
        v->s[ 1 ] * v->s[ 1 ] +
        v->s[ 2 ] * v->s[ 2 ]
    );
#endif
}




#ifdef PORTULAN_AS_OPEN_CL_STRUCT
inline void lengthVectorL( real4_t* v ) {
    v->w = length( (real4_t)( v->x, v->y, v->z, 0 ) );
}
#endif




/**
* @return Тела столкнулись.
*
* В 'coordA.w' появится расстояние между телами.
*/
inline bool collision(
    real4_t* coordA,
    const real4_t coordB,
    const real_t  collisionDistance
) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    // расстояние
    coordA->s3 = length( (real4_t)(
        coordA->x - coordB.x,
        coordA->y - coordB.y,
        coordA->z - coordB.z,
        0
    ) );

    return (coordA->w < collisionDistance);

#else
    assert( false &&
        "Не реализовано." );
#endif
}




/**
* @copy typelib::compute::physics::speedCollision()
*/
inline void speedCollision(
    real_t* rsA,         real_t* rsB,
    const real_t massA,  const real_t speedA,
    const real_t massB,  const real_t speedB,
    const real_t COR
) {
    const real_t allMass = massA + massB;
    const real_t mvab = massA * speedA + massB * speedB;
    *rsA = (mvab + massB * COR * (speedB - speedA)) / allMass;
    *rsB = (mvab + massA * COR * (speedA - speedB)) / allMass;
}




inline void speedCollisionVector(
    real4_t* rsA,        real4_t* rsB,
    const real_t massA,  const real4_t  speedA,
    const real_t massB,  const real4_t  speedB,
    const real_t COR
) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    const real_t allMass = massA + massB;
    const real4_t mvab = massA * speedA + massB * speedB;
    *rsA = (mvab + massB * COR * (speedB - speedA)) / allMass;
    *rsB = (mvab + massA * COR * (speedA - speedB)) / allMass;

#else
    speedCollision( &rsA->s[ 0 ], &rsB->s[ 0 ],  massA, speedA.s[ 0 ],  massB, speedB.s[ 0 ],  COR );
    speedCollision( &rsA->s[ 1 ], &rsB->s[ 1 ],  massA, speedA.s[ 1 ],  massB, speedB.s[ 1 ],  COR );
    speedCollision( &rsA->s[ 2 ], &rsB->s[ 2 ],  massA, speedA.s[ 2 ],  massB, speedB.s[ 2 ],  COR );

#endif
}




/**
* @copy typelib::compute::physics::luminosity()
*/
inline void luminosity(
    __global real_t*        r,
    __global const real_t*  radius,
    __global const real_t*  temperature
) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    *r =
        4.0f * PI * ( *radius ) * ( *radius ) * STEFAN_BOLTZMANN *
        ( *temperature ) * ( *temperature ) * ( *temperature ) * ( *temperature );

#else
    *r = typelib::compute::physics::luminosity( *radius, *temperature );
#endif
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT

                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
