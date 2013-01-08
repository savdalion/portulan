#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация о наблюдателе в звёздной системе.
*
* # Наблюдатель в мире всегда один.
* # Наблюдатель не взаимодействует с элементами мира.
* # Задача наблюдателя - фиксировать события между двумя и более участниками,
*   чтобы позже движок проанализировал эти проишествия (события) и разбросал
*   нужные события конкретным участникам.
*
* #i Введение наблюдателя позволяет обрабатывать множество событий для
*    конкретного (одного) участника *независимо* от других участников. Сделано
*    для возможности включить распределённые вычисления (например, OpenCL).
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* Память наблюдателя о событиях с двумя участниками.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Индекс ("валдо" - см. игру 'SpaceChem') для записи текущего события.
    * [0; *_EVENT_TWO_COUNT - 1]
    *
    * # Позволяем быть отрицательным, чтобы ускорить работу с ним.
    */
    cl_int  waldo;

    eventTwo_t  content[ OBSERVER_EVENT_TWO_COUNT ];
    
} observerMemoryEventTwo_t;




/**
* Информация о наблюдателе звёздной системы.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * События с двумя участниками, запомненные наблюдателем.
    * @see #Соглашения в 'event_t'.
    */
    observerMemoryEventTwo_t memoryEventTwo;

} observer_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
