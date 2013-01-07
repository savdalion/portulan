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
* # Исключаем элемент путём установки массы == 0.
*/
static inline void excludeAsteroid( aboutAsteroid_t* aa ) {
    aa->mass = 0.0;
}




/**
* @return Указанный элемент отсутствует в звёздной системе.
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
* @return Указанный элемент присутствует в звёздной системе.
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
* @return Указанный список элементов звёздной системы - пустой.
*/
static inline bool emptyAsteroid( const aboutAsteroid_t* ec ) {
    return (lastIndexOfPresentAsteroid( ec ) == -1);
}




/**
* Оптимизирует список элементов звёздной системы.
* Меняется размещение элементов в списке.
*/
static inline void optimizeAsteroid( aboutAsteroid_t* ec ) {
    // удалим из списка все элементы, которые были исключены
    // с помощью exclude*()
    // # Список содержит хотя бы 1 элемент (проверили выше).
    cl_int tail = lastIndexOfPresentAsteroid( ec );
    if (tail == -1) {
        // список пуст
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





#ifdef _DEBUG
/**
* Выводит в поток информацию о событии.
* Мысль в коде, пример: "астероид[a] столкнулся[+] с планетой[p]".
*
* @param detail Будет отображаться больше инфо о событии. Например,
*        рядом с названием участника, напишем уникальный код участника
*        в звёздной системе.
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
* Запоминает событие в первой свободной ячейке памяти астероида.
* Устанавливает индекс на только что заполненный элемент.
* Если новое значение счётчика превышает *_EVENT_COUNT, индекс
* обнуляется.
*/
static inline void asteroidMemorizeEvent(
    asteroidMemoryEvent_t* me,
    const event_t& event
) {
    assert( me && "Память не указана." );

    me->content[ me->ck ] = event;

    ++me->ck;
    if (me->ck >= ASTEROID_EVENT_COUNT) {
        me->ck = 0;
    }
}




/**
* Забывает событие.
*/
static inline void forgetEvent( event_t* event ) {
    event->uid = E_NONE;
    // # Достаточно сбросить только UID события.
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
