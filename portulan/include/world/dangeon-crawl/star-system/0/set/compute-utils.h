#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>
#include "structure.h"


/**
* ������� ��� ���������� �������� �� ��������.
* ������ �. ����������� ����� �� typelib::compute � ���������� �.�., �����
* ����� �������������� ������ OpenCL.
*
* # ��������, � ������� �� 'utils.h', ������ � ���������� �����������.
* # ��� ������� ������� ������� ���������� ����� � double: float ���
*   �������� �����������.
* # ������ ������������ �. �., ����� �� ����������� �� ��� ���������
*   � ��� OpenCL.
*/
#define __constant const

// ������������ ��� VC++ �� ���������
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
    return
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
        v.s0 * v.s0 +
        v.s1 * v.s1 +
        v.s2 * v.s2;
#else
        v.s[ 0 ] * v.s[ 0 ] +
        v.s[ 1 ] * v.s[ 1 ] +
        v.s[ 2 ] * v.s[ 2 ];
#endif
}




/**
* @copy VectorT<>::length()
*/
inline real_t lengthVector( const real4_t v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return sqrt( squareLengthVector( v ) );
#else
    return std::sqrt( squareLengthVector( v ) );
#endif
}




/**
* @return ���� �����������.
*/
inline bool collision(
    const real4_t coordA,
    const real4_t coordB,
    const real_t  collisionDistance
) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    // ����������
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
        "�� �����������." );
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
