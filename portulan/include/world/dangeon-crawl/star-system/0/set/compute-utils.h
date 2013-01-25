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
* @copy VectorT<>::squareLength()
*/
inline real_t squareLengthVector( const real4_t v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return
        v.s0 * v.s0 +
        v.s1 * v.s1 +
        v.s2 * v.s2;

#else
    return
        v.s[ 0 ] * v.s[ 0 ] +
        v.s[ 1 ] * v.s[ 1 ] +
        v.s[ 2 ] * v.s[ 2 ];

#endif
}


inline real_t squareLengthVectorK( const real4_t v,  const real_t K ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    // # Уменьшаем число в К раз, чтобы избежать переполнения. Лучше
    //   задавать экспонентой. Например, 1e15.
    const real4_t pv = v / K;
    return
        pv.s0 * pv.s0 +
        pv.s1 * pv.s1 +
        pv.s2 * pv.s2;

#else
    assert( false
        && "Не реализовано." );
    return 0;

#endif
}




/**
* @copy VectorT<>::length()
*/
inline real_t lengthVector( const real4_t v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return length( (real4_t)( v.x, v.y, v.z, 0 ) );
#else
    return std::sqrt( squareLengthVector( v ) );
#endif
}


inline real_t lengthVectorAccurate( const real4_t v ) {
    // # @todo bad Уменьшаем экспоненту, чтобы избежать переполнения.
    // @todo Переписать через природную length() OpenCL.
    const real_t K = 1e15f;
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    //return K * sqrt( squareLengthVectorK( v, K ) );
    return length( (real4_t)( v.x, v.y, v.z, 0 ) );
#else
    return std::sqrt( squareLengthVectorK( v, K ) );
#endif
}




/**
* @return Тела столкнулись.
*/
inline bool collision(
    const real4_t coordA,
    const real4_t coordB,
    const real_t  collisionDistance
) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    // расстояние
    const real4_t r = (real4_t)(
        coordA.s0 - coordB.s0,
        coordA.s1 - coordB.s1,
        coordA.s2 - coordB.s2,
        0
    );
    const real_t squareDistance = squareLengthVector( r );

    return (squareDistance < (collisionDistance * collisionDistance));

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
    real_t vxA, vxB;
    speedCollision( &vxA, &vxB,  massA, speedA.s0,  massB, speedB.s0,  COR );
    real_t vyA, vyB;
    speedCollision( &vyA, &vyB,  massA, speedA.s1,  massB, speedB.s1,  COR );
    real_t vzA, vzB;
    speedCollision( &vzA, &vzB,  massA, speedA.s2,  massB, speedB.s2,  COR );
    *rsA = (real4_t)( vxA, vyA, vzA, 0 );
    *rsB = (real4_t)( vxB, vyB, vzB, 0 );
#else
    speedCollision( &rsA->s[ 0 ], &rsB->s[ 0 ],  massA, speedA.s[ 0 ],  massB, speedB.s[ 0 ],  COR );
    speedCollision( &rsA->s[ 1 ], &rsB->s[ 1 ],  massA, speedA.s[ 1 ],  massB, speedB.s[ 1 ],  COR );
    speedCollision( &rsA->s[ 2 ], &rsB->s[ 2 ],  massA, speedA.s[ 2 ],  massB, speedB.s[ 2 ],  COR );
#endif
}




/**
* @copy typelib::compute::physics::luminosity()
*/
inline real_t luminosity(
    const real_t radius,  const real_t temperature
) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return
        4.0f * PI * radius * radius * STEFAN_BOLTZMANN *
        temperature * temperature * temperature * temperature;

#else
    return typelib::compute::physics::luminosity( radius, temperature );
#endif
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT

                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
