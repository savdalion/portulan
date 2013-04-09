#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "asteroid.h"
#include "planet.h"
#include "star.h"


/**
* Информация о звёздной системе.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* Информация о физическом теле.
* Структура для обмена данными при рассчёте физ. взаимодействий.
*/
typedef struct __attribute__ ((packed)) {
    real_t mass;
    real_t coord[ 3 ];
    real_t rotation[ 3 ];
} aboutBody_t;




/**
* Информация о физ. теле, как материальной точке.
* Структура для обмена данными при рассчёте физ. взаимодействий.
*/
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
typedef struct __attribute__ ((packed)) {
    real_t  coord[ 3 ];
    real_t  velocity[ 3 ];
    real_t  lengthVelocity;
} point_t;

#else
typedef struct __attribute__ ((packed)) {
    typelib::CoordT< real_t >   coord;
    typelib::VectorT< real_t >  velocity;
    real_t                      lengthVelocity;
} point_t;


#endif




/**
* Информация об изменении характеристик элементов и их количества
* в списках. Структура для обмена данными.
* Повторяет структуру элементов для запоминания разницы между "было"
* и "стало" (дельты).
*/
typedef struct __attribute__ ((packed)) {
    aboutAsteroid_t about;
    int count;
} deltaAsteroid_t;

typedef struct __attribute__ ((packed)) {
    aboutPlanet_t about;
    int count;
} deltaPlanet_t;

typedef struct __attribute__ ((packed)) {
    aboutStar_t about;
    int count;
} deltaStar_t;

typedef struct __attribute__ ((packed)) {
    deltaAsteroid_t asteroid;
    deltaPlanet_t   planet;
    deltaStar_t     star;
} deltaElement_t;




/**
* Структура для сбора статистики о звёздной системе.
* Может использоваться движками для оптимизации расчётов.
*
* # Минимум и максимум хранятся в массивах размером 2:
*     0 минимум
*     1 максимум
*/
typedef struct __attribute__ ((packed)) {
    real_t  distance[ 2 ];
    real_t  velocity[ 2 ];

    /**
    * Ожидаемое время сближения двух тел.
    */
    real_t  estimateTimeApproaching[ 2 ];

} statistics_t;








#ifndef PORTULAN_AS_OPEN_CL_STRUCT

/**
* Класс для работы с общей информацией о звёздной системе.
*/
class AboutStarSystem :
    public Element
{
public:
    inline AboutStarSystem( const real3_t& size ) : mSize( size ) {
    }




private:
    /**
    * Протяжённость звёздной системы, XYZ, м.
    */
    const real3_t mSize;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
