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
inline void excludeAsteroid( __global aboutAsteroid_t* e ) {
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
inline void excludePlanet( __global aboutPlanet_t* e ) {
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
* @return Указанный элемент присутствует в звёздной системе.
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
* @return Координата, обёрнутая в структуру coordOne_t.
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
* @return Координата, извлечённая из структуры coordOne_t.
*/
inline real_t coord1( __global const coordOne_t* coord ) {
    return
        coord->a * (real_t)COORD_ONE_BASE * (real_t)COORD_ONE_BASE +
        coord->b * (real_t)COORD_ONE_BASE +
        coord->c;
}




/**
* Сложение координаты со структурой coordOne_t.
*/
inline void addCoord1(
    __global coordOne_t* coord,
    const real_t delta
) {
    // # Максимум скорости. Просто меняем значение младшего разряда.
    coord->c += delta;
}




/**
* @return Масса элемента звёздной системы.
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
* Сложение массы со структурой mass_t.
*/
inline void addMass(
    __global mass_t* mass,
    const real_t delta
) {
    /* - @todo Переписать по аналогии с coordOne_t.
    const real_t P = (real_t)( 1e15 );
    ( (delta > P) || (delta < -P) )
        ? (mass->base  += delta)
        : (mass->knoll += delta);
    */
    mass->knoll += delta;
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
* @see Коммент. к lastIndexOfPresentAsteroid().
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
* @see Коммент. к nextUIDAsteroid().
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
* @see Коммент. к nextUIDAsteroid().
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
* @return Указанный список элементов звёздной системы - пустой.
*/
inline bool emptyAsteroid( __global const aboutAsteroid_t* ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* Оптимизирует список элементов звёздной системы.
* Меняется размещение элементов в списке.
*/
inline void optimizeCountAsteroid( __global aboutAsteroid_t* ec ) {
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
* @return Ссылка на информацию о планете в звёздной системе или nullptr,
*         если планета с заданным 'uid' не обнаружена.
*
* @param optimized Когда список оптимизирован, установка этого признака
*        ускорит подсчёт элементов.
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
* Забывает событие.
*
* @see absentEvent(), presentEvent()
*/
inline void forgetEvent( __global eventTwo_t* event ) {
    event->uid = E_NONE;
    // # Достаточно сбросить только UID события.
}




/**
* @return Событие отсутствует.
*
* @see forgetEvent()
*/
inline bool absentEvent( __global eventTwo_t* event ) {
    return (event->uid == E_NONE);
}




/**
* @return Событие существует.
*
* @see forgetEvent()
*/
inline bool presentEvent( __global eventTwo_t* event ) {
    return (event->uid != E_NONE);
}




/**
* @return Указатель на след. не пустое событие, начиная с конца.
*         -1 если список не содержит событий.
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
* Оптимизирует размещение событий в памяти.
* Указатель перемещается на посл. событие.
*
* #! Порядок событий не сохраняется.
*/
inline void optimizeEmitterEvent(
    __global eventTwo_t*  contentEvent,
    __global cl_int*   waldo,
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
* @return Указатель на элемент соотв. заданным параметрам.
*/
inline bool accordancePointerElement(
    const enum GROUP_ELEMENT ge,  const cl_uint ii,  const uid_t uu,
    __global const pointerElement_t*  b
) {
    return (ge == b->ge) && (ii == b->ii ) && (uu == b->uu);
}




/**
* @return Указатели на элементы одинаковы.
*/
inline bool equalPointerElement(
    __global const pointerElement_t*  a,
    __global const pointerElement_t*  b
) {
    return (a->ge == b->ge) && (a->ii == b->ii ) && (a->uu == b->uu);
}




/**
* @return События одинаковы.
*/
inline bool equalEvent(
    __global const eventTwo_t*  a,
    __global const eventTwo_t*  b
) {
    return (a->uid == b->uid) && equalPointerElement( &a->pi, &b->pi );
}




/**
* Удаляет дубликаты событий из памяти.
* 
* @see Методы *UniqueEvent() ниже.
*/
inline void uniqueEmitterEvent(
    __global eventTwo_t*  contentEvent,
    __global cl_int*   waldo,
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
