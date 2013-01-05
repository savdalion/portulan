#pragma once

#include "living.h"
#include <typelib/typelib.h>


/**
* Наборы живых организмов - животные, растения - для моделирования планеты
* на основе мира игры Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {

namespace tc = typelib::constant::physics;



/**
* Перечисление частей организма, хим. компонентов, излучений.
* Элементы этого перечисления служат как UID части организма.
*/
enum CODE_LIVING {
    // не определён или не используется
    CL_NONE,
    CL_EMPTY= CL_NONE,

    // кость
    CL_BONE,

    // кровь
    CL_BLOOD,

    // кровеносый сосуд
    CL_BLOOD_VESSEL,

    // лимфа
    CL_LYMPH,

    // лимфатический сосуд
    CL_LYMPHATIC_VESSEL,

    // кожа (эпителиальная ткань)
    CL_SKIN,

    // мышца (мышечная ткань)
    CL_MUSCLE,

    // нерв (нервная ткань)
    CL_NERVOUS,

    // @todo прочие виды соединительной ткани
    // связка
    // сухожилие
    // хрящ
    // сустав

    // кислород
    CL_OXYGEN,

    // углекислый газ
    CL_CO2,

    // азот
    CL_NITROGEN,

    // воздух
    // = азот + кислород + углекислый газ
    CL_AIR,


    // свет
    CL_LIGHT,

    // тепло
    CL_HEAT,


    // последний
    CL_last
};





static const aboutLiving_t aboutLiving[ LIVING_COUNT ] = {
/**
* Пустая особь.
* Используется для выравнивания индексов списка по CODE_LIVING.
*/
#if 1
{
},
#endif




/**
* Кровь теплокровного.
* @base Кровь человека.
* @source http://xumuk.ru/biologhim/257.html
* @source http://potomy.ru/human/800.html
* @source Теплоёмкость, терморегуляция > http://medicinskaya-biofizika.ru/teploemkost-krovi
*/
#if 1
{
    // uid
    CL_BLOOD,

    // функции
    // fasten / store
    {
        // whose, how %
        { CL_H2O,     0.75 },
        { CL_OXYGEN,  0.20 },
        { CL_CO2,     0.05 },
        { CL_HEAT },
    },

    // transfer
    // # Перенос тепла вычисляется движком из теплоёмкости составляющих
    //   кровь компонентов.
    {
        // whose
        { CL_H2O, CL_OXYGEN, CL_CO2, CL_HEAT },
        // power
        1.0
    },

    // из чего состоит

},
#endif




/**
* Кровь.
* @base Кровь человека.
* @source http://xumuk.ru/biologhim/257.html
* @source http://potomy.ru/human/800.html
* @source Теплоёмкость, терморегуляция > http://medicinskaya-biofizika.ru/teploemkost-krovi
*/
#if 1
{
    // uid
    CL_BLOOD,

    // функции

    // fasten / store
    {
        // whose, how %
        { CL_H2O,     0.75 },
        { CL_OXYGEN,  0.20 },
        { CL_CO2,     0.05 },
        { CL_HEAT },
    },

    // transfer
    // # Перенос тепла вычисляется движком из теплоёмкости составляющих
    //   кровь компонентов.
    {
        // whose
        { CL_H2O, CL_OXYGEN, CL_CO2, CL_HEAT },
        // power
        1.0
    },

    // из чего состоит

},
#endif




/**
* Рабочий муравей.
*
* @prototype http://crawl.chaosforge.org/index.php?title=Worker_ant
*
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html#MONS_WORKER_ANT
*/
#if 1

// рабочий муравей
#if 1
{
    // uid
    CL_WORKER_ANT,

    // из чего состоит, положение части
    // # Перечисляются части, максимально охватывающие др. части.
    // # Расположение - голова вверху, плоскость XY.
    {
        // голова
        { CL_HEAD_WORKER_ANT,   D_NONE, D_NORTH },
        // грудь (средняя часть тела)
        { CL_BREAST_WORKER_ANT, D_NONE, D_NONE  },
        // брюшко (задняя часть тела)
        { CL_BELLY_WORKER_ANT,  D_NONE, D_SOUTH },
    },

    // функции
    // fasten / store
    {},
    // transfer
    {},
},
#endif

// голова рабочего муравья
#if 1
{
    // uid
    CL_HEAD_WORKER_ANT,

    // из чего состоит, положение части
    // # Расположение: согласно положению муравья (см. ниже).
    {
        // правый глаз
        { CL_EYE_WORKER_ANT,      D_EAST, D_NONE },
        // левый глаз
        { CL_EYE_WORKER_ANT,      D_WEST, D_NONE },
        // правый усик
        { CL_FEELER_WORKER_ANT,   D_EAST, D_NORTH },
        // левый усик
        { CL_FEELER_WORKER_ANT,   D_WEST, D_NORTH },
        // жвалы
        { CL_MANDIBLE_WORKER_ANT, D_NONE, D_NORTH },
        // мозг
        { CL_BRAIN_WORKER_ANT,    D_NONE, D_SOURTH },
    },

    // функции
    // fasten / store
    {},
    // transfer
    {},
},
#endif

// мозг рабочего муравья
#if 1
{
    // uid
    CL_HEAD_WORKER_ANT,

    // из чего состоит, положение части
    {},

    // функции, function_t
    {
        // storeComponent
        // whose, how
        {
            { CL_BLOOD, 0.2 },
        },

        // storePart
        {},

        // storeLocationInfo
        // способен хранить инфо о положении:
        // # Может узнавать элементы только исходя из своих возможностей
        //   запоминать их отражение в мире: запах, визуальный образ и т.п..
        { F_STORE_LOCATION_INFO, 10 },

        // storeLikeInfo
        { F_STORE_LIKE_INFO, 50 }

        // storePresenceInfo
        {},

        // storeSmellInfo
        // # Может помнить запахи, но не помнить место, где их ощущал.
        { F_STORE_SMELL_INFO, 20 },

        // storeSoundInfo
        {},

        // storeTactilInfo
        {},

        // storeTasteInfo
        {},

        // storeVisionInfo
        {},

        // transferComponent
        {},

        // transferPart
        {},
    }
},
#endif

#endif




/**
* Пастбищная трава.
* Многолетняя.
* Произрастает на равнинах и в лесах.
*
* @prototype http://dfwk.ru/Grama
* @prototype http://ru.wikipedia.org/wiki/%D0%9E%D0%B2%D1%81%D1%8F%D0%BD%D0%B8%D1%86%D0%B0_%D0%BB%D1%83%D0%B3%D0%BE%D0%B2%D0%B0%D1%8F
*
* @see Питательные вещества > http://big-fermer.ru/zelenyi-korm
* @see Питательность корма > http://furazh.ru/dictoth/?data=18453
* @see Масса семян > http://prasemena.ru/blog/skolko_semian_v_odnom_gramme
* @see Питание растений > http://floragrow.ru/blog/pischa/13.html
*/
#if 1
{
},
#endif

};


                } // physics
            } // living
        } // dungeoncrawl
    } // world
} // portulan
