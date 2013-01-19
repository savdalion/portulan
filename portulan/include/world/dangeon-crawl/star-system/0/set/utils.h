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
inline void excludeAsteroid( aboutAsteroid_t* e ) {
/* - Нельзя: порядок вызова событий не определён.
#ifndef PORTULAN_AS_OPEN_CL_STRUCT
    assert( e->live && "Элемент уже исключён." );
#endif
*/
    e->future.live = false;
}



/**
* @see Коммент. к excludeAsteroid().
*/
inline void excludePlanet( aboutPlanet_t* e ) {
    e->future.live = false;
}




/**
* @see Коммент. к excludeAsteroid().
*/
inline void excludeStar( __global aboutStar_t* e ) {
    e->future.live = false;
}




/**
* @return Указанный элемент отсутствует в звёздной системе.
*/
inline bool absentAsteroid( const aboutAsteroid_t* e ) {
    return !e->today.live;
}

inline bool absentPlanet( const aboutPlanet_t* e ) {
    return !e->today.live;
}

inline bool absentStar( __global const aboutStar_t* e ) {
    return !e->today.live;
}




/**
* @return Указанный элемент присутствует в звёздной системе.
*/
inline bool presentAsteroid( const aboutAsteroid_t* e ) {
    return e->today.live;
}

inline bool presentPlanet( const aboutPlanet_t* e ) {
    return e->today.live;
}

inline bool presentStar( __global const aboutStar_t* e ) {
    return e->today.live;
}




/**
* @return Масса элемента звёздной системы.
*/
inline real_t massAsteroid( const aboutAsteroid_t* e ) {
    return (e->today.mass.base + e->today.mass.knoll);
}

inline real_t massPlanet( const aboutPlanet_t* e ) {
    return (e->today.mass.base + e->today.mass.knoll);
}

inline real_t massStar( const aboutStar_t* e ) {
    return (e->today.mass.base + e->today.mass.knoll);
}




/**
* @return Результат сравнения масс.
*/
inline bool equalMass( const mass_t* a,  const mass_t* b ) {
    // @todo optimize fine Переписать через abs_diff().
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
    // @todo fine Для малых 'knoll' не будет работать. Переписать.
    return (a->base + a->knoll) > (b->base + b->knoll);
}

inline bool ltMass( const mass_t* a,  const mass_t* b ) {
    // @todo fine Для малых 'knoll' не будет работать. Переписать.
    return (a->base + a->knoll) < (b->base + b->knoll);
}




/**
* @return Указатель на след. не пустой элемент в списке, начиная с конца.
*         -1 если список пустой.
*/
inline cl_int lastIndexOfPresentAsteroidTail(
    const aboutAsteroid_t* ec,
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


inline cl_int lastIndexOfPresentAsteroid( const aboutAsteroid_t* ec ) {
    return lastIndexOfPresentAsteroidTail( ec, ASTEROID_COUNT - 1 );
}




/**
* @see Коммент. к lastIndexOfPresentAsteroid().
*/
inline cl_int lastIndexOfPresentPlanetTail(
    const aboutPlanet_t* ec,
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


inline cl_int lastIndexOfPresentPlanet( const aboutPlanet_t* ec ) {
    return lastIndexOfPresentPlanetTail( ec, PLANET_COUNT - 1 );
}




/**
* @see Коммент. к lastIndexOfPresentAsteroid().
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
* @return Следующий свободный UID для астероида.
*
* # UID элементов звёздной системы только увеличиваются.
*/
inline cl_int nextUIDAsteroid(
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
inline cl_int nextUIDPlanet(
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
inline cl_int nextUIDStar(
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
inline bool emptyAsteroid( const aboutAsteroid_t* ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* Оптимизирует список элементов звёздной системы.
* Меняется размещение элементов в списке.
*/
inline void optimizeCountAsteroid( aboutAsteroid_t* ec ) {
    // удалим из списка все элементы, которые были исключены
    // с помощью exclude*()
    cl_int tail = lastIndexOfPresentAsteroid( ec );
    if ( (tail == 0) || (tail == -1) ) {
        // список содержит один элемент или пуст
        // нечего оптимизировать
        return;
    }

    for (cl_int i = 0; i < tail; ++i) {
        if ( absentAsteroid( &ec[ i ] ) ) {
            // перемещаем элемент из хвоста на место пустого элемента
            ec[ i ] = ec[ tail ];
            excludeAsteroid( &ec[ tail ] );
            tail = lastIndexOfPresentAsteroidTail( ec, tail - 1 );
        }
    }
}




/**
* @see Коммент. к optimizeCountAsteroid().
*/
inline void optimizeCountPlanet( aboutPlanet_t* ec ) {
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
* @see Коммент. к optimizeCountAsteroid().
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
* @return Количество элементов звёздной системы в списке.
*
* @param optimized Когда список оптимизирован, установка этого признака
*        ускорит подсчёт элементов.
*/
inline cl_uint countAsteroid(
    const aboutAsteroid_t* ec,
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
    const aboutPlanet_t* ec,
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
* @return Ссылка на информацию о планете в звёздной системе или nullptr,
*         если планета с заданным 'uid' не обнаружена.
*
* @param optimized Когда список оптимизирован, установка этого признака
*        ускорит подсчёт элементов.
*/
inline const aboutPlanet_t* findPlanet(
    uid_t uid,
    const aboutPlanet_t* ec,
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
* Забывает событие.
*/
inline void forgetEvent( eventTwo_t* event ) {
    event->uid = E_NONE;
    // # Достаточно сбросить только UID события.
}




/**
* @return Указатель на след. не пустое событие, начиная с конца.
*         -1 если список не содержит событий.
*/
inline cl_int lastIndexOfPresentEvent(
    eventTwo_t*  contentEvent,
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
* Оптимизирует размещение событий в памяти.
* Указатель перемещается на посл. событие.
*
* #! Порядок событий не сохраняется.
*/
inline void optimizeEmitterEvent(
    eventTwo_t*  contentEvent,
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
        if (contentEvent[ i ].uid == E_NONE) {
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
inline bool equalPointerElement(
    const pointerElement_t*  a,
    const pointerElement_t*  b
) {
    return (a->ge == b->ge) && (a->ii == b->ii ) && (a->uu == b->uu);
}




/**
* @return События одинаковы.
*/
inline bool equalEvent( const eventTwo_t*  a,  const eventTwo_t*  b ) {
    return (a->uid == b->uid) && equalPointerElement( &a->pi, &b->pi );
}




/**
* @return Тела столкнулись.
*/
inline bool collision(
    const real_t coordA[ 3 ],
    const real_t coordB[ 3 ],
    real_t collisionDistance
) {
    // расстояние
    const real_t r[ 3 ] = {
        coordA[ 0 ] - coordB[ 0 ],
        coordA[ 1 ] - coordB[ 1 ],
        coordA[ 2 ] - coordB[ 2 ],
    };
    const real_t distance2 = (
        r[ 0 ] * r[ 0 ] +
        r[ 1 ] * r[ 1 ] +
        r[ 2 ] * r[ 2 ]
    );

    return (distance2 < (collisionDistance * collisionDistance));
}




/**
* Удаляет дубликаты событий из памяти.
* 
* @see Методы *UniqueEvent() ниже.
*/
inline void uniqueEmitterEvent(
    eventTwo_t*  contentEvent,
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
        if (contentEvent[ i ].uid == E_NONE) {
            // пустые события пропускаем
            continue;
        }
        for (cl_int j = i + 1; j < size; ++j) {
            if (contentEvent[ j ].uid == E_NONE) {
                continue;
            }
            if ( equalEvent( &contentEvent[ i ],  &contentEvent[ j ] ) ) {
                // дубликат, удаляем
                // в памяти останется только первое событие
                forgetEvent( &contentEvent[ j ] );
            }
        }
    }

    // выбрасываем пустые события
    // указатель перемещается на посл. событие
    optimizeEmitterEvent( contentEvent, waldo, size );
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT


/**
* Выводит в поток информацию о событии.
* Мысль в коде, пример: "астероид[a] столкнулся[+] со звездой[s]".
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
