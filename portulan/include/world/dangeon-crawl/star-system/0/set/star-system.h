#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
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
* Информация о звёздной системе.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Протяжённость звёздной системы, XYZ, м.
    */
    cl_double size[ 3 ];

    // # Часть информации о звёздной системе декларирована в structure.h.

} aboutStarSystem_t;




/**
* Список взаимодействующих тел.
* Упаковываем в объединение, чтобы эффективно обрабатывать
* данные с помощью OpenCL.
*
* # Храним тела парой копий: новое[0] и старое[1]. Т.о. сможем быстрее
*   обмениваться данными с ядрами OpenCL.
*   См. - NVidia / OpenCL / проект NBody.
* # Любые характеристики тела могут меняться движком.
*/
typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT  group;
    aboutPlanet_t       content[ 2 ];
} planet_t;

typedef struct __attribute__ ((packed)) {
    enum GROUP_ELEMENT  group;
    aboutStar_t         content[ 2 ];
} star_t;

typedef union __attribute__ ((packed)) {
    planet_t  planet;
    star_t    star;
} aboutBody_t;




/**
* Перечисление всех планет в звёздной системе.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
*/
typedef aboutBody_t*  bodyContent_t;




/**
* Планеты в области звёздной системы.
*/
typedef struct __attribute__ ((packed)) {
    bodyContent_t content;
} body_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
