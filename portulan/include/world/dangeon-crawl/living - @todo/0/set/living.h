#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Наборы живых организмов - животные, растения - на основе мира
* игры Dungeon Crawl.
*
* # Живые организмы состоят из частей.
* # Не разделяем части на органы, ткани, кровь и т.п. - декларируем структуру,
*   способную закодировать в себе любые органы, хим. компоненты и
*   даже энергии, используемые организмом.
* # Организм - это совокупность частей.
*
* @see http://crawl.chaosforge.org
* @see living::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {
#endif



typedef cl_int  uid_t;



/**
* Функции, выполняемые частью тела.
*/
enum FUNCTION {
    // не указана или не определена
    F_NONE = 0,

    // хранит компонент (служит резервуаром)
    // @example Тело может откладывать сахарозу как доп. ист. питания.
    // Кровь насыщается кислородом, углекислым газом.
    F_STORE_COMPONENT,

    // хранит другую часть (скреплено, служит резервуаром)
    // @example Многие части содержат кровь, нервную систему, мышцы, кости.
    // Рука прикреплена к туловищу.
    // Глаза, уши, нос находятся снаружи головы.
    // Позвоночник, ноги прикреплены к тазу.
    F_STORE_PART,

    // хранит информацию
    // информация о местоположении элемента мира
    F_STORE_LOCATION_INFO,
    // информация об отношении к элементу: нравится / нет
    F_STORE_LIKE_INFO,
    // чужое присутствие (помним: это мир Dungeon Crawl)
    F_STORE_PRESENCE_INFO,
    // информация о запахе (обоняние)
    F_STORE_SMELL_INFO,
    // информация о звуке
    F_STORE_SOUND_INFO,
    // информация о тактильном ощущении (осязание)
    F_STORE_TACTIL_INFO,
    // информация о вкусе
    F_STORE_TASTE_INFO,
    // информация об образе
    F_STORE_VISION_INFO,

    // переносит другую часть или компонент в часть тела или внешнюю среду
    // @example Кровь переносит кислород, углек. газ, белки, жиры, воду.
    // Нервная система передаёт сигналы.
    // Лёгкие обогащают кровь кислородом.
    F_TRANSFER,

    // расщепляет компонент или другую часть на др. компоненты / части
    // @see Катаболизм > http://ru.wikipedia.org/wiki/%D0%9A%D0%B0%D1%82%D0%B0%D0%B1%D0%BE%D0%BB%D0%B8%D0%B7%D0%BC
    // @example Желудок подготавливает пищу для усваивания (разлагает на белки,
    // жиры, углеводы, аминокислоты).
    F_FISSION,
    F_CATABOLISM = F_FISSION,

    // собирает из компонентов или других частей др. компоненты / части
    // @see Анаболизм > http://ru.wikipedia.org/wiki/%D0%90%D0%BD%D0%B0%D0%B1%D0%BE%D0%BB%D0%B8%D0%B7%D0%BC
    // @example Растение синтезирует на свету органич. вещ. из углекислого
    // газа и воды.
    // Организм животного синтезирует белки из аминокислот.
    F_FUSSION,
    F_ANABOLISM = F_FUSSION,

    // последняя
    F_last
};



typedef struct {
    /**
    * Какой компонент может хранить.
    */
    uid_t   whose;

    /**
    * В каком количестве.
    * # Количество указывается как часть от целого.
    */
    cl_float  how;

} contentWhoseHow_t;


typedef struct {
    contentWhoseHow_t  content[ 10 ];
} storeComponentFunction_t;


typedef struct {
    contentWhoseHow_t  content[ 10 ];
} storePartFunction_t;



typedef struct {
    /**
    * Сколько едениц инфо может помнить.
    */
    cl_uint   size;

} storeInfoFunction_t;




typedef struct {
    uid_t     whose[ 10 ];

    /**
    * Мощность - показатель, какая часть 'whose' будет разом перенесена.
    * @example Кровь переносит весь свой состав сразу (мощность = 1.0).
    */
    cl_float  power;

} transferFunction_t;



typedef struct {
    storeComponentFunction_t  storeComponent;
    storePartFunction_t       storePart;

    storeInfoFunction_t  storeLocationInfo;
    storeInfoFunction_t  storeLikeInfo;
    storeInfoFunction_t  storePresenceInfo;
    storeInfoFunction_t  storeSmellInfo;
    storeInfoFunction_t  storeSoundInfo;
    storeInfoFunction_t  storeTactilInfo;
    storeInfoFunction_t  storeTasteInfo;
    storeInfoFunction_t  storeVisionInfo;

    transferFunction_t  transferComponent;
    transferFunction_t  transferPart;

} function_t;



/**
* Часть организма.
*/
typedef struct {
    /**
    * Уникальный ID части.
    * # UID введён, чтобы можно было однозначно обратиться к органу.
    * # Положительный UID соотв. enum CODE_ORGANISM.
    * # Отрицательный UID предназначен для декларации новых частей.
    */
    uid_t  uid;


    /**
    * Какие части требуются, чтобы функции выполнялись.
    *
    * @example Сердце не может ф. без крови.
    * Тело не может ф. без мозга.
    * Рука может хватать при отсутствии одного или несколько пальцев.
    * Щупальца могут сжимать при достаточной длине.
    */


    /**
    * Какие функции выполняет.
    *
    * @example Сердце переносит кровь в другие части тела.
    * Кровь переносит кислород.
    * Нервная система передаёт сигналы.
    */
    function_t function;

} part_t;




typedef part_t  organ_t;

typedef part_t  creature_t;







#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
