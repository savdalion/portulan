#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include <CL/cl_platform.h>
#include "structure.h"
#include "asteroid.h"
#include "planet.h"
#include "star.h"


/**
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
* Исключает элемент из звёздной системы.
* Размещение элементов в списке не меняется.
*
* # Не можем, например, обнулять массу, т.к. элемент участвует в событиях,
*   порядок наступления которых не определён.
*/
static inline void excludeAsteroid( aboutAsteroid_t* e ) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "Элемент уже исключён." );
#endif
    e->live = false;
}



/**
* @see Коммент. к excludeAsteroid().
*/
static inline void excludePlanet( aboutPlanet_t* e ) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "Элемент уже исключён." );
#endif
    e->live = false;
}



/**
* @see Коммент. к excludeAsteroid().
*/
static inline void excludeStar( aboutStar_t* e ) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "Элемент уже исключён." );
#endif
    e->live = false;
}




/**
* @return Указанный элемент отсутствует в звёздной системе.
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
* @return Указанный элемент присутствует в звёздной системе.
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
* @return Масса элемента звёздной системы.
*/
static inline real_t massAsteroid( const aboutAsteroid_t& e ) {
    return (e.mass.base + e.mass.knoll);
}

static inline real_t massPlanet( const aboutPlanet_t& e ) {
    return (e.mass.base + e.mass.knoll);
}

static inline real_t massStar( const aboutStar_t& e ) {
    return (e.mass.base + e.mass.knoll);
}




/**
* @return Результат сравнения масс.
*/
static inline bool equalMass( const mass_t& a,  const mass_t& b ) {
    return
        ( typelib::equal( a.base, b.base ) && typelib::equal( a.knoll, b.knoll ) )
     || typelib::equal( a.base + a.knoll,  b.base + b.knoll );
}

static inline bool gtMass( const mass_t& a,  const mass_t& b ) {
    return
        ( typelib::equal( a.base, b.base ) && (a.knoll > b.knoll) )
     || ( (a.base + a.knoll) > (b.base + b.knoll) );
}

static inline bool ltMass( const mass_t& a,  const mass_t& b ) {
    return
        ( typelib::equal( a.base, b.base ) && (a.knoll < b.knoll) )
     || ( (a.base + a.knoll) < (b.base + b.knoll) );
}




/**
* @return Указатель на след. не пустой элемент в списке, начиная с конца.
*         -1 если список пустой.
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
* @see Коммент. к lastIndexOfPresentAsteroid().
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
* @see Коммент. к lastIndexOfPresentAsteroid().
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
* @return Следующий свободный UID для астероида.
*
* # UID элементов звёздной системы только увеличиваются.
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
* @see Коммент. к nextUIDAsteroid().
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
* @see Коммент. к nextUIDAsteroid().
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
* @return Указанный список элементов звёздной системы - пустой.
*/
static inline bool emptyAsteroid( const aboutAsteroid_t* ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* Оптимизирует список элементов звёздной системы.
* Меняется размещение элементов в списке.
*/
static inline void optimizeCountAsteroid( aboutAsteroid_t* ec ) {
    // удалим из списка все элементы, которые были исключены
    // с помощью exclude*()
    cl_int tail = lastIndexOfPresentAsteroid( ec );
    if ( (tail == 0) || (tail == -1) ) {
        // список содержит один элемент или пуст
        // нечего оптимизировать
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentAsteroid( ec[ i ] ) ) {
            // перемещаем элемент из хвоста на место пустого элемента
            ec[ i ] = ec[ tail ];
            excludeAsteroid( &ec[ tail ] );
            tail = lastIndexOfPresentAsteroid( ec, tail - 1 );
        }
    }
}




/**
* @see Коммент. к optimizeCountAsteroid().
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
* @see Коммент. к optimizeCountAsteroid().
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
* @return Количество элементов звёздной системы в списке.
*
* @param optimized Когда список оптимизирован, установка этого признака
*        ускорит подсчёт элементов.
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
* @return Ссылка на информацию о планете в звёздной системе или nullptr,
*         если планета с заданным 'uid' не обнаружена.
*
* @param optimized Когда список оптимизирован, установка этого признака
*        ускорит подсчёт элементов.
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
* Запоминает событие с двумя участниками в первой свободной ячейке памяти
* наблюдателя.
* Устанавливает индекс на только что заполненный элемент.
* Если новое значение счётчика превышает *_EVENT_*_COUNT, индекс обнуляется.
*/
static inline void observerMemorizeEventTwo(
    observerMemoryEventTwo_t* me,
    const eventTwo_t& eventTwo
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
#endif

    me->content[ me->waldo ] = eventTwo;

    ++me->waldo;
    if (me->waldo >= OBSERVER_EVENT_TWO_COUNT) {
        me->waldo = 0;
    }
}




/**
* Запоминает событие в первой свободной ячейке памяти астероида.
* Устанавливает индекс на только что заполненный элемент.
* Если новое значение счётчика превышает *_EVENT_COUNT, индекс обнуляется.
*/
static inline void asteroidMemorizeEvent(
    asteroidMemoryEvent_t* me,
    const event_t& event
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
#endif

    me->content[ me->waldo ] = event;

    ++me->waldo;
    if (me->waldo >= ASTEROID_EVENT_COUNT) {
        me->waldo = 0;
    }
}




/**
* @see Коммент. для asteroidMemorizeEvent().
*/
static inline void planetMemorizeEvent(
    planetMemoryEvent_t* me,
    const event_t& event
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
#endif

    me->content[ me->waldo ] = event;

    ++me->waldo;
    if (me->waldo >= PLANET_EVENT_COUNT) {
        me->waldo = 0;
    }
}




/**
* @see Коммент. для asteroidMemorizeEvent().
*/
static inline void starMemorizeEvent(
    starMemoryEvent_t* me,
    const event_t& event
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
#endif

    me->content[ me->waldo ] = event;

    ++me->waldo;
    if (me->waldo >= STAR_EVENT_COUNT) {
        me->waldo = 0;
    }
}




/**
* Забывает событие.
*/
static inline void forgetEvent( event_t* event ) {
    event->uid = E_NONE;
    // # Достаточно сбросить только UID события.
}




/**
* @see Коммент. для forgetEvent().
*/
static inline void forgetEventTwo( eventTwo_t* eventTwo ) {
    eventTwo->uid = E_NONE;
}




/**
* @return Указатель на след. не пустое событие, начиная с конца.
*         -1 если список не содержит событий.
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
* Оптимизирует размещение событий в памяти.
* Указатель перемещается на посл. событие.
*
* #! Порядок событий не сохраняется.
*/
static inline void optimizeMemoryEvent(
    event_t*  contentEvent,
    cl_int*   waldo,
    cl_int    size
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( contentEvent
        && "Содержание памяти событий не указано." );
    assert( waldo
        && "Ссылка на индекс для записи текущего события не указана." );
    assert( (size > 1)
        && "Память должа уметь хранить больше одного события." );
#endif

    cl_int tail = lastIndexOfPresentEvent( contentEvent, size - 1 );
    if ( (tail == 0) || (tail == -1) ) {
        // список содержит один элемент или пуст
        // оптимизировать нечего, переместим указатель на первый свободный слот
        *waldo = (tail == 0) ? 1 : 0;
        return;
    }

    // заполняем дырки 
    for (cl_int i = 0; i < tail; ++i) {
        event_t& event = contentEvent[ i ];
        if (event.uid == E_NONE) {
            contentEvent[ i ] = contentEvent[ tail ];
            forgetEvent( &contentEvent[ tail ] );
            tail = lastIndexOfPresentEvent( contentEvent, tail - 1 );
        }
    }

    // перемещаем указатель
    tail = lastIndexOfPresentEvent( contentEvent, size - 1 );
    *waldo = (tail == (size - 1)) ? 0 : (tail + 1);

#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( (*waldo >= 0)
        && "Валдо для запоминания событий разрушен." );
#endif
}




/**
* @return Указатели на элементы одинаковы.
*/
static inline bool equalPointerElement(
    const pointerElement_t&  a,
    const pointerElement_t&  b
) {
    return (a.ge == b.ge) && (a.ii == b.ii ) && (a.uu == b.uu);
}




/**
* @return События одинаковы.
*/
static inline bool equalEvent( const event_t&  a,  const event_t&  b ) {
    return (a.uid == b.uid) && equalPointerElement( a.pi, b.pi );
}




/**
* Удаляет дубликаты событий из памяти.
* 
* @see Методы *UniqueEvent() ниже.
*/
static inline void uniqueEvent(
    event_t*  contentEvent,
    cl_int*   waldo,
    cl_int    size
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( contentEvent
        && "Содержание памяти событий не указано." );
    assert( waldo
        && "Ссылка на индекс для записи текущего события не указана." );
    assert( (size > 1)
        && "Память должа уметь хранить больше одного события." );
#endif

    // отмечаем дубликаты как пустые события
    for (cl_int i = 0; i < size - 1; ++i) {
        const event_t& event = contentEvent[ i ];
        if (event.uid == E_NONE) {
            // пустые события пропускаем
            continue;
        }
        for (cl_int j = i + 1; j < size; ++j) {
            event_t& itEvent = contentEvent[ j ];
            if (itEvent.uid == E_NONE) {
                continue;
            }
            if ( equalEvent( event, itEvent ) ) {
                // дубликат, удаляем
                // в памяти останется только первое событие
                forgetEvent( &itEvent );
            }
        }
    }

    // выбрасываем пустые события
    // указатель перемещается на посл. событие
    optimizeMemoryEvent( contentEvent, waldo, size );
}




/**
* Удаляет дубликаты событий из памяти астероида.
* Устанавливает индекс на последний заполненный элемент
* (см. asteroidMemorizeEvent()).
*/
static inline void asteroidUniqueEvent(
    asteroidMemoryEvent_t* me
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
#endif
    uniqueEvent( me->content,  &me->waldo,  ASTEROID_EVENT_COUNT );
}




/**
* @see Коммент. к asteroidUniqueEvent().
*/
static inline void planetUniqueEvent(
    planetMemoryEvent_t* me
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
#endif
    uniqueEvent( me->content,  &me->waldo,  PLANET_EVENT_COUNT );
}




/**
* @see Коммент. к asteroidUniqueEvent().
*/
static inline void starUniqueEvent(
    starMemoryEvent_t* me
) {
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( me && "Память не указана." );
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
            (g == GE_ASTEROID) ? massAsteroid( topology->asteroid.content[ i ] ) :
            (g == GE_PLANET)   ? massPlanet( topology->planet.content[ i ] ) :
            (g == GE_STAR)     ? massStar( topology->star.content[ i ] ) :
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
* Выводит в поток информацию о событии.
* Мысль в коде, пример: "астероид[a] столкнулся[+] с планетой[p]".
*
* @param detail Будет отображаться больше инфо о событии. Например,
*        рядом с названием участника, напишем уникальный код участника
*        в звёздной системе.
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
        // участники: ge, ii, uu
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
