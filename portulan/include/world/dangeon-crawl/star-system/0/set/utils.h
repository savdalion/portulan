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
static inline void excludeAsteroid( aboutAsteroid_t* e ) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "������� ��� ��������." );
#endif
    e->live = false;
}



/**
* @see �������. � excludeAsteroid().
*/
static inline void excludePlanet( aboutPlanet_t* e ) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "������� ��� ��������." );
#endif
    e->live = false;
}



/**
* @see �������. � excludeAsteroid().
*/
static inline void excludeStar( aboutStar_t* e ) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "������� ��� ��������." );
#endif
    e->live = false;
}




/**
* @return ��������� ������� ����������� � ������� �������.
*/
static inline bool absentAsteroid( const aboutAsteroid_t& e ) {
    return !e.live;
}

static inline bool absentPlanet( const aboutPlanet_t& e ) {
    return !e.live;
}

static inline bool absentStar( const aboutStar_t& e ) {
    return !e.live;
}




/**
* @return ��������� ������� ������������ � ������� �������.
*/
static inline bool presentAsteroid( const aboutAsteroid_t& e ) {
    return e.live;
}

static inline bool presentPlanet( const aboutPlanet_t& e ) {
    return e.live;
}

static inline bool presentStar( const aboutStar_t& e ) {
    return e.live;
}




/**
* @return ��������� �� ����. �� ������ ������� � ������, ������� � �����.
*         -1 ���� ������ ������.
*/
static inline cl_int lastIndexOfPresentAsteroid(
    const aboutAsteroid_t* ec,
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
* @see �������. � lastIndexOfPresentAsteroid().
*/
static inline cl_int lastIndexOfPresentPlanet(
    const aboutPlanet_t* ec,
    cl_int startI = PLANET_COUNT - 1
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if ( presentPlanet( ec[ tail ] ) ) {
            return tail;
        }
    }
    return -1;
}




/**
* @see �������. � lastIndexOfPresentAsteroid().
*/
static inline cl_int lastIndexOfPresentStar(
    const aboutStar_t* ec,
    cl_int startI = STAR_COUNT - 1
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        if ( presentStar( ec[ tail ] ) ) {
            return tail;
        }
    }
    return -1;
}




/**
* @return ��������� ��������� UID ��� ���������.
*
* # UID ��������� ������� ������� ������ �������������.
*/
static inline cl_int nextUIDAsteroid(
    const aboutAsteroid_t* ec
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
static inline cl_int nextUIDPlanet(
    const aboutPlanet_t* ec
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
static inline cl_int nextUIDStar(
    const aboutStar_t* ec
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
static inline bool emptyAsteroid( const aboutAsteroid_t* ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* ������������ ������ ��������� ������� �������.
* �������� ���������� ��������� � ������.
*/
static inline void optimizeCountAsteroid( aboutAsteroid_t* ec ) {
    // ������ �� ������ ��� ��������, ������� ���� ���������
    // � ������� exclude*()
    cl_int tail = lastIndexOfPresentAsteroid( ec );
    if ( (tail == 0) || (tail == -1) ) {
        // ������ �������� ���� ������� ��� ����
        // ������ ��������������
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
* @see �������. � optimizeCountAsteroid().
*/
static inline void optimizeCountPlanet( aboutPlanet_t* ec ) {
    cl_int tail = lastIndexOfPresentPlanet( ec );
    if ( (tail == 0) || (tail == -1) ) {
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentPlanet( ec[ i ] ) ) {
            ec[ i ] = ec[ tail ];
            excludePlanet( &ec[ tail ] );
            tail = lastIndexOfPresentPlanet( ec, tail - 1 );
        }
    }
}




/**
* @see �������. � optimizeCountAsteroid().
*/
static inline void optimizeCountStar( aboutStar_t* ec ) {
    cl_int tail = lastIndexOfPresentStar( ec );
    if ( (tail == 0) || (tail == -1) ) {
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentStar( ec[ i ] ) ) {
            ec[ i ] = ec[ tail ];
            excludeStar( &ec[ tail ] );
            tail = lastIndexOfPresentStar( ec, tail - 1 );
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
    const aboutAsteroid_t* ec,
    bool optimized
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




static inline cl_uint countPlanet(
    const aboutPlanet_t* ec,
    bool optimized
) {
    cl_uint n = 0;
    for (cl_uint i = 0; i < PLANET_COUNT; ++i) {
        if ( presentPlanet( ec[ i ] ) ) {
            ++n;
        } else if ( optimized ) {
            return n;
        }
    }
    return n;
}




static inline cl_uint countStar(
    const aboutStar_t* ec,
    bool optimized
) {
    cl_uint n = 0;
    for (cl_uint i = 0; i < STAR_COUNT; ++i) {
        if ( presentStar( ec[ i ] ) ) {
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
static inline const aboutPlanet_t* findPlanet(
    uid_t uid,
    const aboutPlanet_t* ec,
    bool optimized
) {
    for (cl_uint i = 0; i < PLANET_COUNT; ++i) {
        if ( presentPlanet( ec[ i ] ) ) {
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
* ���������� ������� � ����� ����������� � ������ ��������� ������ ������
* �����������.
* ������������� ������ �� ������ ��� ����������� �������.
* ���� ����� �������� �������� ��������� *_EVENT_*_COUNT, ������ ����������.
*/
static inline void observerMemorizeEventTwo(
    observerMemoryEventTwo_t* me,
    const eventTwo_t& eventTwo
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif

    me->content[ me->waldo ] = eventTwo;

    ++me->waldo;
    if (me->waldo >= OBSERVER_EVENT_TWO_COUNT) {
        me->waldo = 0;
    }
}




/**
* ���������� ������� � ������ ��������� ������ ������ ���������.
* ������������� ������ �� ������ ��� ����������� �������.
* ���� ����� �������� �������� ��������� *_EVENT_COUNT, ������ ����������.
*/
static inline void asteroidMemorizeEvent(
    asteroidMemoryEvent_t* me,
    const event_t& event
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif

    me->content[ me->waldo ] = event;

    ++me->waldo;
    if (me->waldo >= ASTEROID_EVENT_COUNT) {
        me->waldo = 0;
    }
}




/**
* @see �������. ��� asteroidMemorizeEvent().
*/
static inline void planetMemorizeEvent(
    planetMemoryEvent_t* me,
    const event_t& event
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif

    me->content[ me->waldo ] = event;

    ++me->waldo;
    if (me->waldo >= PLANET_EVENT_COUNT) {
        me->waldo = 0;
    }
}




/**
* @see �������. ��� asteroidMemorizeEvent().
*/
static inline void starMemorizeEvent(
    starMemoryEvent_t* me,
    const event_t& event
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif

    me->content[ me->waldo ] = event;

    ++me->waldo;
    if (me->waldo >= STAR_EVENT_COUNT) {
        me->waldo = 0;
    }
}




/**
* �������� �������.
*/
static inline void forgetEvent( event_t* event ) {
    event->uid = E_NONE;
    // # ���������� �������� ������ UID �������.
}




/**
* @see �������. ��� forgetEvent().
*/
static inline void forgetEventTwo( eventTwo_t* eventTwo ) {
    eventTwo->uid = E_NONE;
}




/**
* @return ��������� �� ����. �� ������ �������, ������� � �����.
*         -1 ���� ������ �� �������� �������.
*/
static inline cl_int lastIndexOfPresentEvent(
    event_t*  contentEvent,
    cl_int startI
) {
    cl_int tail = startI;
    for ( ; tail >= 0; --tail) {
        const event_t& event = contentEvent[ tail ];
        if (event.uid != E_NONE) {
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
static inline void optimizeMemoryEvent(
    event_t*  contentEvent,
    cl_int*   waldo,
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
        event_t& event = contentEvent[ i ];
        if (event.uid == E_NONE) {
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
* @return ��������� �� �������� ���������.
*/
static inline bool equalPointerElement(
    const pointerElement_t&  a,
    const pointerElement_t&  b
) {
    return (a.ge == b.ge) && (a.ii == b.ii ) && (a.uu == b.uu);
}




/**
* @return ������� ���������.
*/
static inline bool equalEvent(
    const event_t&  a,
    const event_t&  b
) {
    return (a.uid == b.uid) && equalPointerElement( a.pi, b.pi );
}




/**
* ������� ��������� ������� �� ������.
* 
* @see ������ *UniqueEvent() ����.
*/
static inline void uniqueEvent(
    event_t*  contentEvent,
    cl_int*   waldo,
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
        const event_t& event = contentEvent[ i ];
        if (event.uid == E_NONE) {
            // ������ ������� ����������
            continue;
        }
        for (cl_int j = i + 1; j < size; ++j) {
            event_t& itEvent = contentEvent[ j ];
            if (itEvent.uid == E_NONE) {
                continue;
            }
            if ( equalEvent( event, itEvent ) ) {
                // ��������, �������
                // � ������ ��������� ������ ������ �������
                forgetEvent( &itEvent );
            }
        }
    }

    // ����������� ������ �������
    // ��������� ������������ �� ����. �������
    optimizeMemoryEvent( contentEvent, waldo, size );
}




/**
* ������� ��������� ������� �� ������ ���������.
* ������������� ������ �� ��������� ����������� �������
* (��. asteroidMemorizeEvent()).
*/
static inline void asteroidUniqueEvent(
    asteroidMemoryEvent_t* me
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif
    uniqueEvent( me->content,  &me->waldo,  ASTEROID_EVENT_COUNT );
}




/**
* @see �������. � asteroidUniqueEvent().
*/
static inline void planetUniqueEvent(
    planetMemoryEvent_t* me
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif
    uniqueEvent( me->content,  &me->waldo,  PLANET_EVENT_COUNT );
}




/**
* @see �������. � asteroidUniqueEvent().
*/
static inline void starUniqueEvent(
    starMemoryEvent_t* me
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "������ �� �������." );
#endif
    uniqueEvent( me->content,  &me->waldo,  STAR_EVENT_COUNT );
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT


static inline void printEventTwo(
    const eventTwo_t& eventTwo,
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
            (g == GE_ASTEROID) ? topology->asteroid.content[ i ].mass :
            (g == GE_PLANET)   ? topology->planet.content[ i ].mass :
            (g == GE_STAR)     ? topology->star.content[ i ].mass :
            0.0;
    };

    const std::string whoA = fnWho( eventTwo.piA.ge );
    const std::string how =
        (eventTwo.uid == E_NONE) ? "!none" :
        (eventTwo.uid == E_COLLISION) ? "+" :
        "!?";
    const std::string whoB = fnWho( eventTwo.piB.ge );

    std::cout << whoA;
    if ( topology ) {
        std::cout << eventTwo.piA.uu <<
            " (" << fnMass( eventTwo.piA.ge, eventTwo.piA.ii ) << ")";
    }

    std::cout << " " << how << " ";

    std::cout << whoB;
    if ( topology ) {
        std::cout << eventTwo.piB.uu <<
            " (" << fnMass( eventTwo.piB.ge, eventTwo.piB.ii ) << ")";
    }

    std::cout << std::endl;
}




/**
* ������� � ����� ���������� � �������.
* ����� � ����, ������: "��������[a] ����������[+] � ��������[p]".
*
* @param detail ����� ������������ ������ ���� � �������. ��������,
*        ����� � ��������� ���������, ������� ���������� ��� ���������
*        � ������� �������.
*/
static inline void printEvent(
    enum GROUP_ELEMENT ge1,
    uid_t uid1,
    const event_t& event,
    topology_t* topology
) {
    const eventTwo_t eventTwo = {
        // uid event
        event.uid,
        // ���������: ge, ii, uu
        { ge1, 0, uid1 },
        event.pi
    };
    printEventTwo( eventTwo, topology );
}


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
