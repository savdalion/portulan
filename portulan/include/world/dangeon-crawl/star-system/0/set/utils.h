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
* # ��������� ������� ���� ��������� ����� == 0.
*/
static inline void excludeAsteroid( aboutAsteroid_t* aa ) {
    aa->mass = 0.0;
}




/**
* @return ��������� ������� ����������� � ������� �������.
*/
static inline bool absentAsteroid( const aboutAsteroid_t& e ) {
    return (e.mass <= 0);
}

static inline bool absentPlanet( const aboutPlanet_t& e ) {
    return (e.mass <= 0);
}

static inline bool absentStar( const aboutStar_t& e ) {
    return (e.mass <= 0);
}




/**
* @return ��������� ������� ������������ � ������� �������.
*/
static inline bool presentAsteroid( const aboutAsteroid_t& e ) {
    return (e.mass > 0);
}

static inline bool presentPlanet( const aboutPlanet_t& e ) {
    return (e.mass > 0);
}

static inline bool presentStar( const aboutStar_t& e ) {
    return (e.mass > 0);
}




/**
* @return ��������� �� ����. �� ������ ������� � ������, ������� � �����.
*         -1 ���� ������ ������.
*/
static inline cl_int lastIndexOfPresentAsteroid(
    const asteroidContent_t ec,
    cl_int startI = ASTEROID_COUNT - 1
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if ( presentAsteroid( ec[ tail ] ) ) {
            return tail;
        }
    }
    return -1;
}




/**
* @return ��������� ������ ��������� ������� ������� - ������.
*/
static inline bool emptyAsteroid( const asteroidContent_t ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* ������������ ������ ��������� ������� �������.
* �������� ���������� ��������� � ������.
*/
static inline void optimizeAsteroid( asteroidContent_t ec ) {
    // ������ �� ������ ��� ��������, ������� ���� ���������
    // � ������� exclude*()
    // # ������ �������� ���� �� 1 ������� (��������� ����).
    cl_int tail = lastIndexOfPresentAsteroid( ec );
    if (tail == -1) {
        // ������ ����
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentAsteroid( ec[ i ] ) ) {
            // ���������� ������� �� ������ �� ����� ������� ��������
            ec[ i ] = ec[ tail ];
            excludeAsteroid( &ec[ tail ] );
            tail = lastIndexOfPresentAsteroid( ec, tail - 1 );
        }
    }
}




/**
* @return ���������� ��������� ������� ������� � ������.
*
* @param optimized ����� ������ �������������, ��������� ����� ��������
*        ������� ������� ���������.
*/
static inline cl_uint countAsteroid(
    const asteroidContent_t ec,
    bool optimized = false
) {
    cl_uint n = 0;
    for (cl_uint i = 0; i < ASTEROID_COUNT; ++i) {
        if ( presentAsteroid( ec[ i ] ) ) {
            ++n;
        } else if ( optimized ) {
            return n;
        }
    }
    return n;
}





#ifdef _DEBUG
/**
* ������� � ����� ���������� � �������.
* ����� � ����, ������: "��������[a] ����������[+] � ��������[p]".
*
* @param detail ����� ������������ ������ ���� � �������. ��������,
*        ����� � ��������� ���������, ������� ���������� ��� ���������
*        � ������� �������.
*/
static inline void printEvent(
    enum GROUP_ELEMENT ge1, uid_t uid1,
    const event_t& event,
    bool detail
) {
    static const auto fnWho = []( enum GROUP_ELEMENT g ) -> std::string {
        return
            (g == GE_NONE)     ? "" :
            (g == GE_ASTEROID) ? "a" :
            (g == GE_PLANET)   ? "p" :
            (g == GE_STAR)     ? "s" :
            "?";
    };
    const std::string whoA = fnWho( ge1 );
    const std::string how =
        (event.uid == E_NONE) ? "!none" :
        (event.uid == E_COLLISION) ? "+" :
        "!?";
    const std::string whoB = fnWho( event.pi.ge );
    std::cout << whoA;
    if ( detail ) { std::cout << uid1; }
    std::cout << how;
    std::cout << whoB;
    if ( detail ) { std::cout << event.pi.uu; }
    std::cout << " ";
}
#endif




/**
* ���������� ������� � ������ ��������� ������ ������ ���������.
* ������������� ������ �� ������ ��� ����������� �������.
* ���� ����� �������� �������� ��������� *_EVENT_COUNT, ������
* ����������.
*/
static inline void asteroidMemorizeEvent(
    asteroidMemoryEvent_t* me,
    const event_t& event
) {
    assert( me && "������ �� �������." );

    me->content[ me->ck ] = event;

    ++me->ck;
    if (me->ck >= ASTEROID_EVENT_COUNT) {
        me->ck = 0;
    }
}




/**
* �������� �������.
*/
static inline void forgetEvent( event_t* event ) {
    event->uid = E_NONE;
    // # ���������� �������� ������ UID �������.
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
