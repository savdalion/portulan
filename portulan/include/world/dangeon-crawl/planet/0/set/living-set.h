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
            namespace planet {
                namespace l0 {

namespace tc = typelib::constant::physics;


// # Здесь не помешает хранение 'static', но CPU OpenCL не воспринимает его.
const aboutLiving_t aboutLiving[ LIVING_COUNT ] = {
/**
* Пустая особь.
* Используется для выравнивания индексов списка по CODE_LIVING.
*/
#if 1
{
    // code
    CL_NONE,

    // size
    SL_ATOMIC,

    // mass[ LIFE_CYCLE_COUNT ]
    // # Цикл обрисован группами:
    //     0    Эмбрионы особей, семена.
    //     1    Дети, ростки.
    //     2    Взрослые.
    //     3    Старики.
    //     4    Мёртвые особи - тела, скелеты.
    //     5    Бессмертные особи.
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    // maxGroupSize
    0,

    // hitDice
    0.0f,

    // attack
    {},

    // resist
    {
        { TAL_NONE,  FAL_NONE,  0.0f }
    },

    // evasion
    0.0f,

    // vitality
    0.0f,

    // noise
    { 0.0f, 0.0f },

    // перемещение
    // moveSolidSurface
    { 0.0f },
    // moveLiquidSurface
    { 0.0f },
    // moveSolidInside
    { 0.0f, 0.0f },
    // moveLiquidInside
    { 0.0f },
    // moveGasInside
    { 0.0f },

    // tag
    TL_DAMAGE_REGENERATION,

    // lifetime, дни
    0.0f,

    // immunity
    0.0f,

    // composition
    {},

    // metabolism
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // кг / день
        {
            { CC_NONE,         0.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // кг / день
        {
            { CC_NONE,         0.0f },
        },

        // energyNeed
        {
            { CE_NONE,  0.0f },
        },

        // energyWaste
        {
            { CE_NONE,  0.0f },
        },
#endif
    },

    // survivor
    {
#if 1
        // habitat
        {
            0U,
            0U,
            0U,
            0U,
            0U
        },

        // comfort
        {
        },

        //adaptability
        0.0f
#endif
    }
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
{
    // code
    CL_WORKER_ANT,

    // size
    // ~70 см
    SL_SMALL,

    // mass[ LIFE_CYCLE_COUNT ]
    // # Цикл обрисован группами:
    //     0    Эмбрионы особей, семена.
    //     1    Дети, ростки.
    //     2    Взрослые.
    //     3    Старики.
    //     4    Мёртвые особи - тела, скелеты.
    //     5    Бессмертные особи.
    // В качестве массы для взрослой особи взята 20-я часть массы
    // из http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
    { 0.5f,  10.0f,  20.0f,  25.0f,  20.0f,  30.0f },

    // maxGroupSize
    1000,

    // hitDice
    3.0f,

    // attack
    {
    },

    // resist
    {
        // общая защита от физ. атаки
        { TAL_CRUSH,     FAL_PLAIN,  4.0f },
        { TAL_CUTTING,   FAL_PLAIN,  5.0f },
        { TAL_CLAW,      FAL_PLAIN,  3.0f },
        { TAL_CONSTRICT, FAL_PLAIN,  4.0f },
        { TAL_ENGULF,    FAL_PLAIN,  4.0f },
        { TAL_PIERCE,    FAL_PLAIN,  6.0f },
        { TAL_SHOOT_CRUSH,  FAL_PLAIN,  4.0f },
        { TAL_SHOOT_GAS,    FAL_PLAIN,  0.0f },
        { TAL_SHOOT_LIQUID, FAL_PLAIN,  0.0f },
        { TAL_SHOOT_PIERCE, FAL_PLAIN,  6.0f },
        { TAL_TOUCH,     FAL_PLAIN,  0.0f },
        { TAL_TRAMPLE,   FAL_PLAIN,  0.0f },
        // общая защита от маг. атаки
        { TAL_MAGIC,     FAL_ANY,    12.0f },
        // общая защита от вкуса атаки
        { TAL_ANY,       FAL_ACID,               4.0f },
        { TAL_ANY,       FAL_BLINK,              0.0f },
        { TAL_ANY,       FAL_COLD,               0.0f },
        { TAL_ANY,       FAL_CONFUSE,            0.0f },
        { TAL_ANY,       FAL_ELECTRICITY,        2.0f },
        { TAL_ANY,       FAL_FIRE,               2.0f },
        { TAL_ANY,       FAL_HELLFIRE,           0.0f },
        // муравей неуязвим для этой магии, т.к. не является нежитью
        { TAL_ANY,       FAL_HOLYWORD,           IMMUNE },
        { TAL_ANY,       FAL_NEGATIVE,           0.0f },
        { TAL_ANY,       FAL_PARALYZE,           0.0f },
        { TAL_ANY,       FAL_POISON,            -1.0f },
        { TAL_ANY,       FAL_VAMPIRIC_DRAINING,  0.0f },
        // признак завершения списка
        { TAL_NONE,  FAL_NONE,  0.0f }
    },

    // evasion
    10.0f,

    // vitality
    17.0f,

    // noise
    { 0.0f, 3.0f },

    // перемещение в разных средах
    // moveSolidSurface
    { 12.0f },
    // moveLiquidSurface
    { -1.0f },
    // moveSolidInside
    { 0.12f, 12.0f },
    // moveLiquidInside
    { -1.0f },
    // moveGasInside
    { -1.0f },

    // tag
    //   - муравей не относится ни к теплокровным, ни к холоднокровным особям
    //   - муравей может излечивать свои повреждённые органы, но не может
    //     восстанавливать утерянные
    TL_DAMAGE_REGENERATION,

    // lifetime, дни
    //   - муравей живёт ~ 2 года
    2.0f * 365.0f,

    // immunity
    1.0f,

    // composition
    {
    },

    // metabolism
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // кг / день
        {
            // ~ 3 л воды / день (1 л = 1 кг)
            { CC_WATER,         3.0f },
            // белки ~ 0.5 г / кг веса / день
            { CC_PROTEIN,       0.5f * 30.0f / 1000.0f },
            // жиры ~ 10 г / день
            { CC_FAT,           10.0f / 1000.0f },
            // углеводы ~ ...
            { CC_CARBOHYDRATE,  100.0f / 1000.0f },
            // редкие элементы ~ ...
            { CC_SPARSE,        1.0f / 1000.0f },
            // ~ 5 тыс. л воздуха / день ( 1 л = 1.2 г)
            { CC_AIR,           5000.0f * 1.2f / 1000.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // кг / день
        {
            { CC_FECES,        50.0f / 1000.0f },
            { CC_URINE,        500.0f / 1000.0f },
            // углекислый газ ~ 200 л / день
            { CC_CARBON_ACID,  200.0f * 1.02f / 1000.0f },
        },

        // energyNeed
        {
            { CE_NONE,  0.0f },
        },

        // energyWaste
        {
            { CE_NONE,  0.0f },
        },
#endif
    },

    // survivor
    {
#if 1
        // habitat
        //   - муравей способен жить на границе твёрдой и газообразной сред,
        //     а также внутри твёрдой среды (норы, муравейники)
        {
            HL_GAS | HL_SOLID,
            HL_SOLID,
            0U,
        },

        // comfort
        {
            // temperature
            30.0f,
            // @todo ...
            // rainfall
            // drainage
            // illuminance
        },

        // adaptability
        0.5f
#endif
    }
},
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
    // code
    CL_GRAMA,

    // size
    // высота ~40 см
    SL_LITTLE,

    // mass[ LIFE_CYCLE_COUNT ]
    // # Цикл обрисован группами:
    //     0    Эмбрионы особей, семена.
    //     1    Дети, ростки.
    //     2    Взрослые.
    //     3    Старики.
    //     4    Мёртвые особи - тела, скелеты.
    //     5    Бессмертные особи.
    // @see Масса семян > http://prasemena.ru/blog/skolko_semian_v_odnom_gramme
    { 0.001 / 1000.0f,  0.005f,  0.010f,  0.015f,  0.005f,  0.020f },

    // maxGroupSize
    0,

    // hitDice
    0.0f,

    // attack
    {},

    // resist
    {
        // признак завершения списка
        { TAL_NONE,  FAL_NONE,  0.0f }
    },

    // evasion
    0.0f,

    // vitality
    1.0f,

    // noise
    { 0.0f, 0.0f },

    // перемещение
    // moveSolidSurface
    { -1.0f },
    // moveLiquidSurface
    { -1.0f },
    // moveSolidInside
    { -1.0f, 0.0f },
    // moveLiquidInside
    { -1.0f },
    // moveGasInside
    { -1.0f },

    // tag
    //   - растение не относится ни к теплокровным, ни к холоднокровным особям
    //   - растение может излечивать свои повреждённые органы и может
    //     восстанавливать утерянные
    TL_DAMAGE_REGENERATION,

    // lifetime, дни
    5.0f * 365.0f,

    // immunity
    1.0f,

    // composition
    {
        // @todo ...
    },

    // metabolism
    // @see Потребность в кислороде > http://www.dissercat.com/content/pogloshchenie-kisloroda-sistemoi-pochva-rastenii-pri-raznykh-urovnyakh-pitaniya-rastenii
    // @see Питание растений > http://floragrow.ru/blog/pischa/13.html
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // кг / день
        {
            // #i Испарение - наибольший расход воды для многих деревьев.
            //    Взрослая берёза за сутки испаряет в среднем 75 л воды,
            //    бук — 100, липа — 200 л.
            //    @source http://kurdyumov.ru/knigi/plodorodie/temiriazev/temir03.php
            // # Чтобы упростить процесс моделирования, примем, что растение
            //   не испаряет воду, а лишь потребляет *необходимое* ему кол-во.
            // вода: испарённая ~ 0.01 л / кг веса / день (1 л = 1 кг)
            //       необх. для жизни ~ 0.001 л / кг веса / день
            // масса этого растения = 0.010 кг
            { CC_WATER,        0.001f * 0.010f },
            // кислород ~ 120 мл / кг веса / день (1 л = 1.2 г)
            // # Углекислый газ *потребляется* этим растением в тёмное время
            //   суток, кислород - в светлое; поэтому делим пополам.
            { CC_AIR,          120.0f / 1000.0f * 0.010f * 0.0012f / 2.0f },
            // углекислый газ
            // ~ 240 мл / кг веса / день (1 л = 1.98 г)
            { CC_CARBON_ACID,  240.0f / 1000.0f * 0.010f * 0.00198f / 2.0f },
            // редкие элементы ~ меньше самой меньшей потребности
            { CC_SPARSE,       1.0f / 1000.0f },
            // @todo Добавить продукты разложения, экскременты др. особей.
            //       Сделать это в отдельной, не фатальной для жизни
            //       растения структуре.
            //       { CC_DETRITUS,  ... },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // кг / день
        {
            // кислород ~ 240 мл / кг веса / день (см. выше componentNeed_t)
            // # Углекислый газ *выделяется* этим растением в светлое время
            //   суток, кислород - в тёмное; поэтому делим пополам.
            { CC_AIR,          240.0f / 1000.0f * 0.010f * 0.0012f / 2.0f },
            // углекислый газ
            // ~ 50 мл / кг веса / день (1 л = 1.98 г)
            { CC_CARBON_ACID,  50.0f / 1000.0f * 0.010f * 0.00198f / 2.0f },
        },

        // energyNeed
        {
            // для жизни требуется световой поток в 1000 люкс / день
            // # Т.к. полдня длится ночь, делим необходимый поток пополам.
            { CE_NORMAL_LIGHT,  1000.0f / 2.0f },
        },

        // energyWaste
        {
            { CE_NONE,  0.0f },
        },
#endif
},

    // survivor
    // #i Как правило, для растений родиной которых являются влажные
    //    тропические леса, оптимальной является 80-95 % относительная
    //    влажность воздуха (зимой может быть снижена до 65-75 %). Для
    //    растений тёплых субтропиков — 75-80 %, холодных субтропиков —
    //    50-75 % (левкои, цикламены, цинерарии и др.).
    {
#if 1
        // habitat
        // это растение может жить на границе твёрдой и газообразной сред
        {
            HL_GAS | HL_SOLID,
        },

        // comfort
        {
            // temperature
            20.0f,
            // @todo ...
            // rainfall
            // drainage
            // illuminance
        },

        // adaptability
        0.5f
#endif
    }
},
#endif

};


                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
