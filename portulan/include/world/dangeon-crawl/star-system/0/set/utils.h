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
    e->today.live = false;
}



/**
* @see Коммент. к excludeAsteroid().
*/
inline void excludePlanet( __global aboutPlanet_t* e ) {
    e->today.live = false;
}




/**
* @see Коммент. к excludeAsteroid().
*/
inline void excludeStar( __global aboutStar_t* e ) {
    e->today.live = false;
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
* @return "Большое число", обёрнутое в структуру real4_t.
*/
inline real4_t convertToBigValue( real_t v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    const real_t absV = (v < 0) ? -v : v;
    if (absV < BIG_VALUE_BASE_0) {
        return (real4_t)( v, 0, 0, 0 );
    } else if (absV < BIG_VALUE_BASE_1) {
        return (real4_t)( 0, v, 0, 0 );
    } else if (absV < BIG_VALUE_BASE_2) {
        return (real4_t)( 0, 0, v, 0 );
    }
    return (real4_t)( 0,  0,  0,  v / BIG_VALUE_BASE_3 );

#else
    real4_t bv = {};
    const real_t absV = (v < 0) ? -v : v;
    if (absV < BIG_VALUE_BASE_0) {
        bv.s[ 0 ] = v;
    } else if (absV < BIG_VALUE_BASE_1) {
        bv.s[ 1 ] = v;
    } else if (absV < BIG_VALUE_BASE_2) {
        bv.s[ 2 ] = v;
    } else {
        bv.s[ 3 ] = v / BIG_VALUE_BASE_3;
    }
    return bv;
#endif
}




/**
* @return "Большое число", собранное из структуры real4_t.
*
* #! Теряется точность.
* #! Возможно переполнение.
*
* @see convertFromBig3DValue()
*/
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
inline real_t convertFromBigValue( const real4_t bv ) {
    return
        bv.s0 + bv.s1 + bv.s2 +
        bv.s3 * BIG_VALUE_BASE_3;
}

#else
// # На стороне хоста можем обеспечить бОльшую точность.
template< typename T >
inline T convertFromBigValue( const real4_t bv ) {
    return
        static_cast< T >( bv.s[ 0 ] ) +
        static_cast< T >( bv.s[ 1 ] ) +
        static_cast< T >( bv.s[ 2 ] ) +
        static_cast< T >( bv.s[ 3 ] ) * static_cast< T >( BIG_VALUE_BASE_3 );
}
#endif




/**
* @return "Большое 3D-число", собранное из структуры real4_t.
*
* #! Теряется точность.
* #! Возможно переполнение.
*
* @see convertFromBigValue()
*/
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
inline small3d_t convertFromBig3DValue( const big3d_t b3v ) {
    return (small3d_t)(
        convertFromBigValue( b3v.x ),
        convertFromBigValue( b3v.y ),
        convertFromBigValue( b3v.z ),
        0
    );
}

#else
inline small3d_t convertFromBig3DValue( const big3d_t& b3v ) {
    small3d_t r;
    r.s[ 0 ] = convertFromBigValue< real_t >( b3v.x );
    r.s[ 1 ] = convertFromBigValue< real_t >( b3v.y );
    r.s[ 2 ] = convertFromBigValue< real_t >( b3v.z );
    r.s[ 3 ] = 0;
    return r;
}
#endif




/**
* Сложение "больших чисел".
*/
inline void addBigValueV( __global real4_t* bv,  const real_t v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    printf( "Use expression 'bv += convertToBigValue( v )'.\n" );

#else
    if (v < BIG_VALUE_BASE_0) {
        bv->s[ 0 ] += v;
    } else if (v < BIG_VALUE_BASE_1) {
        bv->s[ 1 ] += v;
    } else if (v < BIG_VALUE_BASE_2) {
        bv->s[ 2 ] += v;
    } else {
        bv->s[ 3 ] += (v / BIG_VALUE_BASE_3);
    }
#endif
}




/**
* @return Результат сравнения "больших чисел".
*/
inline bool equalBigValue( const real4_t a,  const real4_t b ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    {
        const real_t ab = (a.s3 > b.s3) ? (a.s3 - b.s3) : (b.s3 - a.s3);
        if (ab >= PRECISION) { return false; }
    }
    {
        const real_t ab = (a.s2 > b.s2) ? (a.s2 - b.s2) : (b.s2 - a.s2);
        if (ab >= PRECISION) { return false; }
    }
    {
        const real_t ab = (a.s1 > b.s1) ? (a.s1 - b.s1) : (b.s1 - a.s1);
        if (ab >= PRECISION) { return false; }
    }
    const real_t ab = (a.s0 > b.s0) ? (a.s0 - b.s0) : (b.s0 - a.s0);
    return (ab < PRECISION);

#else
    return typelib::equal(
        convertFromBigValue< double >( a ),
        convertFromBigValue< double >( b )
    );
#endif
}




inline bool gtBigValue( const real4_t a,  const real4_t b ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    printf( "gtBigValue() Не реализовано." );
    return false;

#else
    return (convertFromBigValue< double >( a ) > convertFromBigValue< double >( b ));
#endif
}




inline bool ltBigValue( const real4_t a,  const real4_t b ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    printf( "ltBigValue() Не реализовано." );
    return false;

#else
    return (convertFromBigValue< double >( a ) < convertFromBigValue< double >( b ));
#endif
}




/**
* Проверка вещественных чисел на корректность.
*/
inline bool testReal( const real_t v ) {
    // @source http://johndcook.com/IEEE_exceptions_in_cpp.html
    return ( (v <= REAL_MAX) && (v >= -REAL_MAX) );
}


#ifdef PORTULAN_AS_OPEN_CL_STRUCT
inline void assertReal(
    const real_t v,
    __constant const char* s
) {
    if ( !testReal( v ) ) {
        printf( s );
    }
}
#endif




inline bool testReal4( const real4_t v ) {
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return
        testReal( v.s0 )
        && testReal( v.s1 )
        && testReal( v.s2 )
        && testReal( v.s3 );

#else
    return
        testReal( v.s[ 0 ] )
        && testReal( v.s[ 1 ] )
        && testReal( v.s[ 2 ] )
        && testReal( v.s[ 3 ] );

#endif
}


#ifdef PORTULAN_AS_OPEN_CL_STRUCT
inline void assertReal4(
    const real4_t v,
    __constant const char* s
) {
    if ( !testReal4( v ) ) {
        printf( s );
    }
}
#endif




/**
* @return Масса элемента звёздной системы.
*/
inline real_t massAsteroid( __global const aboutAsteroid_t* e ) {
    const real4_t bv = e->today.mass;
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return convertFromBigValue( bv );
#else
    return convertFromBigValue< real_t >( bv );
#endif
}

inline real_t massPlanet( __global const aboutPlanet_t* e ) {
    const real4_t bv = e->today.mass;
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return convertFromBigValue( bv );
#else
    return convertFromBigValue< real_t >( bv );
#endif
}

inline real_t massStar( __global const aboutStar_t* e ) {
    const real4_t bv = e->today.mass;
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    return convertFromBigValue( bv );
#else
    return convertFromBigValue< real_t >( bv );
#endif
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
* Обучает модели поведения указанный элемент.
*/
#ifdef PORTULAN_AS_OPEN_CL_STRUCT

#else
// @todo inline void learnModel*()

inline void learnModelAsteroid(
    __global aboutAsteroid_t* e,
    const std::string& model
) {
    int w = e->memoryModel.waldo;
    model_t m = {};
    strcpy( reinterpret_cast< char* >( &m.uid[ 0 ] ),  model.c_str() );
    e->memoryModel.content[ w ] = m;
    ++w;
    e->memoryModel.waldo = w;
}

#endif




/**
* Элемент узнаёт, как часто должен отрабатывать на себе указанную модель.
*
* @param Сколько пульсов надо пропустить. При == 0, каждый пульс.
*/
#ifdef PORTULAN_AS_OPEN_CL_STRUCT

// @todo inline void frequenceModel*()
#else

inline void frequenceModelAsteroid(
    __global aboutAsteroid_t* e,
    const std::string& model,
    const cl_int skipPulse
) {
    int w = e->frequencyMemoryModel.waldo;
    frequencyModel_t m = {};
    strcpy( reinterpret_cast< char* >( &m.uid[ 0 ] ),  model.c_str() );
    m.skipPulse = skipPulse;
    e->frequencyMemoryModel.content[ w ] = m;
    ++w;
    e->frequencyMemoryModel.waldo = w;
}

#endif




/**
* @return Указанный элемент сейчас должен отработать эту модель.
*/
inline bool needPulseModelAsteroid(
    __global const aboutAsteroid_t* e,
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
    const uidModel_t model,
#else
    const std::string& model,
#endif
    const long pulselive
) {
    // проверим, есть ли заданная модель в списке для отработки
    __global const frequencyMemoryModel_t* fmm = &e->frequencyMemoryModel;
    __global const frequencyModel_t* present = nullptr;
    for (int w = fmm->waldo - 1; w >= 0; --w) {
        __global const frequencyModel_t* fm = &fmm->content[ w ];
        // # Модель с таким UID в списке может быть только одна.
        for (int q = 0; q < sizeof( model ); ++q) {
            const char c1 = model[ q ];
            const char c2 = fm->uid[ q ];
	        if (c1 != c2) {
                break;
            }
            if (c1 == '\0') {
                break;
            }
        }
        // uid совпадают
        present = fm;
    }

    // проверяем, должна ли модель выполняться на этом пульсе
    if ( present ) {
        const long sp = present->skipPulse + 1;
        const bool need = ((pulselive % sp) == 0);
        return need;
    }

    return false;
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
