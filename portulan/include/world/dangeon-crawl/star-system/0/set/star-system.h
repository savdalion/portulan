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
    real_t size[ 3 ];

    // # Часть информации о звёздной системе декларирована в structure.h.

} aboutStarSystem_t;




/**
* Список взаимодействующих тел.
* Упаковываем в объединение, чтобы эффективно обрабатывать
* данные с помощью OpenCL.
*
* # Любые характеристики тела, включая группу элемента, могут меняться движком.
*/
typedef union __attribute__ ((packed)) {
    aboutPlanet_t  planet;
    aboutStar_t    star;
} aboutBodyWithoutGroup_t;

typedef struct {
    enum GROUP_ELEMENT       group;
    aboutBodyWithoutGroup_t  content;
} aboutBody_t;





/**
* Перечисление всех планет в звёздной системе.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
*/
typedef aboutBody_t  bodyContent_t[ BODY_COUNT ];




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
