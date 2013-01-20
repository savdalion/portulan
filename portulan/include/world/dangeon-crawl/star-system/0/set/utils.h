#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>
#include "structure.h"
#include "asteroid.h"
#include "planet.h"
#include "star.h"


/**
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
* ��������� ������� �� ������� �������.
* ���������� ��������� � ������ �� ��������.
*
* # �� �����, ��������, �������� �����, �.�. ������� ��������� � ��������,
*   ������� ����������� ������� �� ��������.
*/
inline void excludeAsteroid( __global aboutAsteroid_t* e ) {
/* - ������: ������� ������ ������� �� ��������.
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "������� ��� ��������." );
#endif
*/
    e->future.live = false;
}



/**
* @see �������. � excludeAsteroid().
*/
inline void excludePlanet( __global aboutPlanet_t* e ) {
    e->future.live = false;
}




/**
* @see �������. � excludeAsteroid().
*/
inline void excludeStar( __global aboutStar_t* e ) {
    e->future.live = false;
}




/**
* @return ��������� ������� ����������� � ������� �������.
*/
inline bool absentAsteroid( __global const aboutAsteroid_t* e ) {
    return !e->today.live;
}

inline bool absentPlanet( __global const aboutPlanet_t* e ) {
    return !e->today.live;
}

inline bool absentStar( __global const aboutStar_t* e ) {
    return !e->today.live;
}




/**
* @return ��������� ������� ������������ � ������� �������.
*/
inline bool presentAsteroid( __global const aboutAsteroid_t* e ) {
    return e->today.live;
}

inline bool presentPlanet( __global const aboutPlanet_t* e ) {
    return e->today.live;
}

inline bool presentStar( __global const aboutStar_t* e ) {
    return e->today.live;
}




/**
* @return ����������, �������� � ��������� coordOne_t.
*/
inline coordOne_t convertCoord1( real_t v ) {
    coordOne_t coord = {};

    real_t K = (real_t)COORD_ONE_BASE * (real_t)COORD_ONE_BASE;
    coord.a = v / K;
    real_t vt = v - floor( coord.a ) * K;

    K = (real_t)COORD_ONE_BASE;
    coord.b = vt / K;
    vt -= floor( coord.b ) * K;

    coord.c = vt;
    
    return coord;
}




/**
* @return ����������, ����������� �� ��������� coordOne_t.
*/
inline real_t coord1( __global const coordOne_t* coord ) {
    return
        coord->a * (real_t)COORD_ONE_BASE * (real_t)COORD_ONE_BASE +
        coord->b * (real_t)COORD_ONE_BASE +
        coord->c;
}




/**
* �������� ���������� �� ���������� coordOne_t.
*/
inline void addCoord1(
    __global coordOne_t* coord,
    const real_t delta
) {
    // # �������� ��������. ������ ������ �������� �������� �������.
    coord->c += delta;
}




/**
* @return ����� �������� ������� �������.
*/
inline real_t massAsteroid( __global const aboutAsteroid_t* e ) {
    return (e->today.mass.base + e->today.mass.knoll);
}

inline real_t massPlanet( __global const aboutPlanet_t* e ) {
    return (e->today.mass.base + e->today.mass.knoll);
}

inline real_t massStar( __global const aboutStar_t* e ) {
    return (e->today.mass.base + e->today.mass.knoll);
}




/**
* �������� ����� �� ���������� mass_t.
*/
inline void addMass(
    __global mass_t* mass,
    const real_t delta
) {
    /* - @todo ���������� �� �������� � coordOne_t.
    const real_t P = (real_t)( 1e15 );
    ( (delta > P) || (delta < -P) )
        ? (mass->base  += delta)
        : (mass->knoll += delta);
    */
    mass->knoll += delta;
}




/**
* @return ��������� ��������� ����.
*/
inline bool equalMass( const mass_t* a,  const mass_t* b ) {
    // @todo optimize fine ���������� ����� abs_diff().
    const real_t abab = a->base - b->base;
    const real_t absABAB = (abab > 0) ? abab : -abab;
    const real_t akak = a->knoll - b->knoll;
    const real_t absAKAK = (akak > 0) ? akak : -akak;
    const real_t ab = (a->base + a->knoll) - (b->base + b->knoll);
    const real_t absAB = (ab > 0) ? ab : -ab;
    return
        ( (absABAB < 0.001) && (absAKAK < 0.001) )
     || (absAB < 0.001);
}

inline bool gtMass( const mass_t* a,  const mass_t* b ) {
    // @todo fine ��� ����� 'knoll' �� ����� ��������. ����������.
    return (a->base + a->knoll) > (b->base + b->knoll);
}

inline bool ltMass( const mass_t* a,  const mass_t* b ) {
    // @todo fine ��� ����� 'knoll' �� ����� ��������. ����������.
    return (a->base + a->knoll) < (b->base + b->knoll);
}




/**
* @return ��������� �� ����. �� ������ ������� � ������, ������� � �����.
*         -1 ���� ������ ������.
*/
inline cl_int lastIndexOfPresentAsteroidTail(
    __global const aboutAsteroid_t* ec,
    cl_int startI
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if ( presentAsteroid( &ec[ tail ] ) ) {
            return tail;
        }
    }
    return -1;
}


inline cl_int lastIndexOfPresentAsteroid( __global const aboutAsteroid_t* ec ) {
    return lastIndexOfPresentAsteroidTail( ec, ASTEROID_COUNT - 1 );
}




/**
* @see �������. � lastIndexOfPresentAsteroid().
*/
inline cl_int lastIndexOfPresentPlanetTail(
    __global const aboutPlanet_t* ec,
    cl_int startI
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if ( presentPlanet( &ec[ tail ] ) ) {
            return tail;
        }
    }
    return -1;
}


inline cl_int lastIndexOfPresentPlanet( __global const aboutPlanet_t* ec ) {
    return lastIndexOfPresentPlanetTail( ec, PLANET_COUNT - 1 );
}




/**
* @see �������. � lastIndexOfPresentAsteroid().
*/
inline cl_int lastIndexOfPresentStarTail(
    __global const aboutStar_t* ec,
    cl_int startI
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if ( presentStar( &ec[ tail ] ) ) {
            return tail;
        }
    }
    return -1;
}


inline cl_int lastIndexOfPresentStar( __global const aboutStar_t* ec ) {
    return lastIndexOfPresentStarTail( ec, STAR_COUNT - 1 );
}




/**
* @return ��������� ��������� UID ��� ���������.
*
* # UID ��������� ������� ������� ������ �������������.
*/
inline cl_int nextUIDAsteroid(
    __global const aboutAsteroid_t* ec
) {
    uid_t maxUID = ec[ 0 ].uid;
    for (size_t i = 1; i < ASTEROID_COUNT; ++i) {
        const uid_t uid = ec[ i ].uid;
        if (uid > maxUID) {
            maxUID = uid;
        }
    }
    return (maxUID + 1);
}




/**
* @see �������. � nextUIDAsteroid().
*/
inline cl_int nextUIDPlanet(
    __global const aboutPlanet_t* ec
) {
    uid_t maxUID = ec[ 0 ].uid;
    for (size_t i = 1; i < PLANET_COUNT; ++i) {
        const uid_t uid = ec[ i ].uid;
        if (uid > maxUID) {
            maxUID = uid;
        }
    }
    return (maxUID + 1);
}




/**
* @see �������. � nextUIDAsteroid().
*/
inline cl_int nextUIDStar(
    __global const aboutStar_t* ec
) {
    uid_t maxUID = ec[ 0 ].uid;
    for (size_t i = 1; i < STAR_COUNT; ++i) {
        const uid_t uid = ec[ i ].uid;
        if (uid > maxUID) {
            maxUID = uid;
        }
    }
    return (maxUID + 1);
}




/**
* @return ��������� ������ ��������� ������� ������� - ������.
*/
inline bool emptyAsteroid( __global const aboutAsteroid_t* ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* ������������ ������ ��������� ������� �������.
* �������� ���������� ��������� � ������.
*/
inline void optimizeCountAsteroid( __global aboutAsteroid_t* ec ) {
    // ������ �� ������ ��� ��������, ������� ���� ���������
    // � ������� exclude*()
    cl_int tail = lastIndexOfPresentAsteroid( ec );
    if ( (tail == 0) || (tail == -1) ) {
        // ������ �������� ���� ������� ��� ����
        // ������ ��������������
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentAsteroid( &ec[ i ] ) ) {
            // ���������� ������� �� ������ �� ����� ������� ��������
            ec[ i ] = ec[ tail ];
            excludeAsteroid( &ec[ tail ] );
            tail = lastIndexOfPresentAsteroidTail( ec, tail - 1 );
        }
    }
}




/**
* @see �������. � optimizeCountAsteroid().
*/
inline void optimizeCountPlanet( __global aboutPlanet_t* ec ) {
    cl_int tail = lastIndexOfPresentPlanet( ec );
    if ( (tail == 0) || (tail == -1) ) {
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentPlanet( &ec[ i ] ) ) {
            ec[ i ] = ec[ tail ];
            excludePlanet( &ec[ tail ] );
            tail = lastIndexOfPresentPlanetTail( ec, tail - 1 );
        }
    }
}




/**
* @see �������. � optimizeCountAsteroid().
*/
inline void optimizeCountStar( __global aboutStar_t* ec ) {
    cl_int tail = lastIndexOfPresentStar( ec );
    if ( (tail == 0) || (tail == -1) ) {
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentStar( &ec[ i ] ) ) {
            ec[ i ] = ec[ tail ];
            excludeStar( &ec[ tail ] );
            tail = lastIndexOfPresentStarTail( ec, tail - 1 );
        }
    }
}




/**
* @return ���������� ��������� ������� ������� � ������.
*
* @param optimized ����� ������ �������������, ��������� ����� ��������
*        ������� ������� ���������.
*/
inline cl_uint countAsteroid(
    __global const aboutAsteroid_t* ec,
    bool optimized
) {
    cl_uint n = 0;
    for (cl_uint i = 0; i < ASTEROID_COUNT; ++i) {
        if ( presentAsteroid( &ec[ i ] ) ) {
            ++n;
        } else if ( optimized ) {
            return n;
        }
    }
    return n;
}




inline cl_uint countPlanet(
    __global const aboutPlanet_t* ec,
    bool optimized
) {
    cl_uint n = 0;
    for (cl_uint i = 0; i < PLANET_COUNT; ++i) {
        if ( presentPlanet( &ec[ i ] ) ) {
            ++n;
        } else if ( optimized ) {
            return n;
        }
    }
    return n;
}




inline cl_uint countStar(
    __global const aboutStar_t* ec,
    bool optimized
) {
    cl_uint n = 0;
    for (cl_uint i = 0; i < STAR_COUNT; ++i) {
        if ( presentStar( &ec[ i ] ) ) {
            ++n;
        } else if ( optimized ) {
            return n;
        }
    }
    return n;
}




/**
* @return ������ �� ���������� � ������� � ������� ������� ��� nullptr,
*         ���� ������� � �������� 'uid' �� ����������.
*
* @param optimized ����� ������ �������������, ��������� ����� ��������
*        ������� ������� ���������.
*/
inline __global const aboutPlanet_t* findPlanet(
    uid_t uid,
    __global const aboutPlanet_t* ec,
    bool optimized
) {
    for (cl_uint i = 0; i < PLANET_COUNT; ++i) {
        if ( presentPlanet( &ec[ i ] ) ) {
            if (ec[ i ].uid == uid) {
                return &ec[ i ];
            }
        } else if ( optimized ) {
            return nullptr;
        }
    }
    return nullptr;
}




/**
* �������� �������.
*
* @see absentEvent(), presentEvent()
*/
inline void forgetEvent( __global eventTwo_t* event ) {
    event->uid = E_NONE;
    // # ���������� �������� ������ UID �������.
}




/**
* @return ������� �����������.
*
* @see forgetEvent()
*/
inline bool absentEvent( __global eventTwo_t* event ) {
    return (event->uid == E_NONE);
}




/**
* @return ������� ����������.
*
* @see forgetEvent()
*/
inline bool presentEvent( __global eventTwo_t* event ) {
    return (event->uid != E_NONE);
}




/**
* @return ��������� �� ����. �� ������ �������, ������� � �����.
*         -1 ���� ������ �� �������� �������.
*/
inline cl_int lastIndexOfPresentEvent(
    __global eventTwo_t*  contentEvent,
    cl_int startI
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if (contentEvent[ tail ].uid != E_NONE) {
            return tail;
        }
    }
    return -1;
}




/**
* ������������ ���������� ������� � ������.
* ��������� ������������ �� ����. �������.
*
* #! ������� ������� �� �����������.
*/
inline void optimizeEmitterEvent(
    __global eventTwo_t*  contentEvent,
    __global cl_int*   waldo,
    cl_int    size
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( contentEvent
        && "���������� ������ ������� �� �������." );
    assert( waldo
        && "������ �� ������ ��� ������ �������� ������� �� �������." );
    assert( (size > 1)
        && "������ ����� ����� ������� ������ ������ �������." );
#endif

    cl_int tail = lastIndexOfPresentEvent( contentEvent, size - 1 );
    if ( (tail == 0) || (tail == -1) ) {
        // ������ �������� ���� ������� ��� ����
        // �������������� ������, ���������� ��������� �� ������ ��������� ����
        *waldo = (tail == 0) ? 1 : 0;
        return;
    }

    // ��������� ����� 
    for (cl_int i = 0; i < tail; ++i) {
        if (contentEvent[ i ].uid == E_NONE) {
            contentEvent[ i ] = contentEvent[ tail ];
            forgetEvent( &contentEvent[ tail ] );
            tail = lastIndexOfPresentEvent( contentEvent, tail - 1 );
        }
    }

    // ���������� ���������
    tail = lastIndexOfPresentEvent( contentEvent, size - 1 );
    *waldo = (tail == (size - 1)) ? 0 : (tail + 1);

#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( (*waldo >= 0)
        && "����� ��� ����������� ������� ��������." );
#endif
}




/**
* @return ��������� �� ������� �����. �������� ����������.
*/
inline bool accordancePointerElement(
    const enum GROUP_ELEMENT ge,  const cl_uint ii,  const uid_t uu,
    __global const pointerElement_t*  b
) {
    return (ge == b->ge) && (ii == b->ii ) && (uu == b->uu);
}




/**
* @return ��������� �� �������� ���������.
*/
inline bool equalPointerElement(
    __global const pointerElement_t*  a,
    __global const pointerElement_t*  b
) {
    return (a->ge == b->ge) && (a->ii == b->ii ) && (a->uu == b->uu);
}




/**
* @return ������� ���������.
*/
inline bool equalEvent(
    __global const eventTwo_t*  a,
    __global const eventTwo_t*  b
) {
    return (a->uid == b->uid) && equalPointerElement( &a->pi, &b->pi );
}




/**
* ������� ��������� ������� �� ������.
* 
* @see ������ *UniqueEvent() ����.
*/
inline void uniqueEmitterEvent(
    __global eventTwo_t*  contentEvent,
    __global cl_int*   waldo,
    cl_int    size
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( contentEvent
        && "���������� ������ ������� �� �������." );
    assert( waldo
        && "������ �� ������ ��� ������ �������� ������� �� �������." );
    assert( (size > 1)
        && "������ ����� ����� ������� ������ ������ �������." );
#endif

    // �������� ��������� ��� ������ �������
    for (cl_int i = 0; i < size - 1; ++i) {
        if (contentEvent[ i ].uid == E_NONE) {
            // ������ ������� ����������
            continue;
        }
        for (cl_int j = i + 1; j < size; ++j) {
            if (contentEvent[ j ].uid == E_NONE) {
                continue;
            }
            if ( equalEvent( &contentEvent[ i ],  &contentEvent[ j ] ) ) {
                // ��������, �������
                // � ������ ��������� ������ ������ �������
                forgetEvent( &contentEvent[ j ] );
            }
        }
    }

    // ����������� ������ �������
    // ��������� ������������ �� ����. �������
    optimizeEmitterEvent( contentEvent, waldo, size );
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT


/**
* ������� � ����� ���������� � �������.
* ����� � ����, ������: "��������[a] ����������[+] �� �������[s]".
*/
inline void printEvent(
    const pointerElement_t& first,
    const eventTwo_t& event,
    topology_t* topology
) {
    static const auto fnWho = []( enum GROUP_ELEMENT g ) -> std::string {
        return
            (g == GE_NONE)     ? "" :
            (g == GE_ASTEROID) ? "a" :
            (g == GE_PLANET)   ? "p" :
            (g == GE_STAR)     ? "s" :
            "?";
    };

    static const auto fnMass = [ topology ]( enum GROUP_ELEMENT g,  cl_uint i ) -> real_t {
        return
            (g == GE_NONE)     ? 0.0 :
            (g == GE_ASTEROID) ? massAsteroid( &topology->asteroid.content[ i ] ) :
            (g == GE_PLANET)   ? massPlanet( &topology->planet.content[ i ] ) :
            (g == GE_STAR)     ? massStar( &topology->star.content[ i ] ) :
            0.0;
    };

    const std::string whoA = fnWho( first.ge );
    const std::string how =
        (event.uid == E_NONE) ? "!none" :
        (event.uid == E_COLLISION) ? "+" :
        "!?";
    const std::string whoB = fnWho( event.pi.ge );

    std::cout << whoA;
    if ( topology ) {
        std::cout << first.uu <<
            " (" << fnMass( first.ge, first.ii ) << ")";
    }

    std::cout << " " << how << " ";

    std::cout << whoB;
    if ( topology ) {
        std::cout << event.pi.uu <<
            " (" << fnMass( event.pi.ge, event.pi.ii ) << ")";
    }

    std::cout << std::endl;
}


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
