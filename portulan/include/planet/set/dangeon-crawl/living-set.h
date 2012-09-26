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
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace living {


namespace pc = portulan::planet::set::dungeoncrawl::component;
namespace tc = typelib::constant::physics;


static const aboutLiving_t aboutLiving = {
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

    // part[ PART_LIVING_COUNT ]
    //   # Указываем только имеющиеся у особи части: остальные будут
    //     заполнены нулями компилятором.
    //     @todo Проверить соглашение для Release-версии.
    {
        // 0 - часть тела, орган
        {
            // code
            { CL_NONE, CPL_NONE,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_NONE,         0.0f },
            },
            // function
            FPL_LIVE |
            // ...
            0ULL,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE }},
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // ...
    },

    // tag
    TL_DAMAGE_REGENERATION,

    // lifetime, дни
    0.0f,

    // immunity
    0.0f,

    // metabolism
    {
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // кг / день
        {
            { pc::CC_NONE,         0.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // кг / день
        {
            { pc::CC_NONE,         0.0f },
        },

        // energyNeed
        {
            { pc::CE_NONE,  0.0f },
        },

        // energyWaste
        {
            { pc::CE_NONE,  0.0f },
        },
    },

    // survivor
    {
        // habitat
        {
            //HL_* [ | HL_* ]
            0U,
            0U,
            0U,
            0U,
            0U
        },

        // temperatureRange
        {
            // comfort
            { 0.0f - tc::CK,  0.0f - tc::CK },
            // limit
            { 0.0f - tc::CK,  0.0f - tc::CK },
        }
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
    // В качестве массы для взрослой особи взята 20-я часть массы из http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
    { 0.5f,  10.0f,  20.0f,  25.0f,  20.0f,  30.0f },

    // maxGroupSize
    1000,

    // hitDice
    3.0f,

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

    // перемещение
    // moveSolidSurface
    { 12.0f },
    // moveLiquidSurface
    { 0.0f },
    // moveSolidInside
    { 0.12f, 12.0f },
    // moveLiquidInside
    { 0.0f },
    // moveGasInside
    { 0.0f },

    // part[ PART_LIVING_COUNT ]
    //   # Указываем только имеющиеся у особи части: остальные будут
    //     заполнены нулями компилятором.
    //     @todo Проверить соглашение выше для Release-версии.
    {
        // 0 - голова
        {
            // code
            { CL_WORKER_ANT, CPL_HEAD,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.2f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.5f },
                { pc::CC_PROTEIN,       0.1f },
                { pc::CC_FAT,           0.1f },
                { pc::CC_CARBOHYDRATE,  0.2f },
                { pc::CC_SPARSE,        0.1f }
            },
            // function
            FPL_LIVE |
            // муравей ощущает мир усиками, но прикосновения чувствует и головой
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE }},
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // голова не атакует (это делают мандибулы)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Голова лучше защищена от некоторых видов воздействий.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 0 - голова

        // 1 - грудь (средняя часть тела)
        {
            // code
            { CL_WORKER_ANT, CPL_BREAST,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
            // mass
            0.3f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.4f },
                { pc::CC_PROTEIN,       0.2f },
                { pc::CC_FAT,           0.1f },
                { pc::CC_CARBOHYDRATE,  0.2f },
                { pc::CC_SPARSE,        0.1f }
            },
            // function
            FPL_LIVE |
            // муравей ощущает мир усиками, но прикосновения чувствует и грудью
            FPL_TOUCH_NORMAL_SIGNAL |
            // дышит
            FPL_UPTAKE_GAS |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_AIR },  1.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_CARBON_ACID } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // грудь не атакует (это делают мандибулы)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 1 - грудь (средняя часть тела)

        // 2 - брюшко (задняя часть тела)
        {
            // code
            { CL_WORKER_ANT, CPL_BELLY,  LXL_CENTER, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.3f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.4f },
                { pc::CC_PROTEIN,       0.2f },
                { pc::CC_FAT,           0.1f },
                { pc::CC_CARBOHYDRATE,  0.2f },
                { pc::CC_SPARSE,        0.1f }
            },
            // function
            FPL_LIVE |
            // муравей ощущает мир усиками, но прикосновения чувствует и брюшком
            FPL_TOUCH_NORMAL_SIGNAL |
            // усваивает твёрдую и жидкую пищу
            FPL_UPTAKE_SOLID | FPL_UPTAKE_LIQUID |
            // выделяет экскременты
            FPL_EXCRETION_SOLID | FPL_EXCRETION_LIQUID |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_PROTEIN, pc::CC_FAT, pc::CC_CARBOHYDRATE, pc::CC_SPARSE },  0.0f },
            // uptakeLiquid
            { { pc::CC_WATER },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_FECES } },
            // excretionLiquid
            { { pc::CC_URINE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // брюшко не атакует (это делают мандибулы)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 2 - брюшко (задняя часть тела)

        // 3 - мозг (находится внутри головы)
        {
            // code
            { CL_WORKER_ANT, CPL_BRAIN,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_HEAD, CPL_NONE },
            // mass
            0.02f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.7f },
                { pc::CC_PROTEIN,       0.2f },
                { pc::CC_FAT,           0.1f },
                { pc::CC_CARBOHYDRATE,  0.095f },
                { pc::CC_SPARSE,        0.005f }
            },
            // function
            FPL_LIVE |
            // муравей ощущает мир усиками, прикосновений мозг не чувствует
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // мозг отвечает за интеллект особи
            FPL_INTELLECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // мозг муравья не атакует (это делают мандибулы)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Мозг очень уязвим, но защиту даёт голова (мозг
            // находится внутри головы).
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 3 - мозг (находится внутри головы)

        // 4 - жвалы или мандибулы (прикреплены к голове)
        {
            // code
            { CL_WORKER_ANT, CPL_MANDIBLE,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.1f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.2f },
                { pc::CC_PROTEIN,       0.1f },
                { pc::CC_FAT,           0.05f },
                { pc::CC_CARBOHYDRATE,  0.6f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // жвалы не являются жизненно необходимым органом (не умирает сразу)
            // муравей ощущает мир усиками, жвалы чувствуют вкус и прикосновение
            FPL_TASTE_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            // поглощает твёрдую и жидкую пищу, дышит
            FPL_EAT_SOLID | FPL_EAT_LIQUID | FPL_EAT_GAS |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                // не может жвалами пронзить, но раздробить / разрезать - вполне
                // @see http://crawl.chaosforge.org/index.php?title=Worker_ant
                { TAL_CRUSH,     FAL_PLAIN,  4.0f },
                { TAL_CUTTING,   FAL_PLAIN,  8.0f },
                // впрыскивает отраву
                // @see http://crawl.chaosforge.org/index.php?title=Poison
                { TAL_ANY,       FAL_POISON,            -1.0f },
                // .
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Жвалы защищены лучше.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 4 - жвалы (прикреплены к голове)

        // 5 - левый глаз (прикреплён к голове)
        {
            // code
            { CL_WORKER_ANT, CPL_EYE,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.05f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.80f },
                { pc::CC_PROTEIN,       0.15f },
                { pc::CC_FAT,           0.01f },
                { pc::CC_CARBOHYDRATE,  0.01f },
                { pc::CC_SPARSE,        0.03f }
            },
            // function
            // глаз не являются жизненно необходимым органом (не умирает сразу)
            // муравей ощущает мир усиками, глаза - видят видимое и ощущают прикосновения
            FPL_VISION_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Глаза очень уязвимы.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 5 - левый глаз (прикреплён к голове)

        // 6 - правый глаз (прикреплён к голове)
        {
            // code
            { CL_WORKER_ANT, CPL_EYE,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.05f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.80f },
                { pc::CC_PROTEIN,       0.15f },
                { pc::CC_FAT,           0.01f },
                { pc::CC_CARBOHYDRATE,  0.01f },
                { pc::CC_SPARSE,        0.03f }
            },
            // function
            // глаз не являются жизненно необходимым органом (не умирает сразу)
            // муравей ощущает мир усиками, глаза - видят видимое и ощущают прикосновения
            FPL_VISION_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Глаза очень уязвимы.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 6 - правый глаз (прикреплён к голове)

        // 7 - левый усик (прикреплён к голове)
        {
            // code
            { CL_WORKER_ANT, CPL_FEELER,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.01f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.05f },
                { pc::CC_PROTEIN,       0.15f },
                { pc::CC_FAT,           0.01f },
                { pc::CC_CARBOHYDRATE,  0.29f },
                // усик большей частью состоит из редких элементов
                { pc::CC_SPARSE,        0.50f }
            },
            // function
            // усик не является жизненно необходимым органом (не умирает сразу)
            // муравей ощущает мир усиками
            FPL_TASTE_NORMAL_SIGNAL | FPL_SMELL_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // муравей с помощью движений усиками может передавать информацию
            FPL_EMIT_NORMAL_VISION,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Усик хорошо защищён от многих видов аттак.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 7 - левый усик (прикреплён к голове)

        // 8 - правый усик (прикреплён к голове)
        {
            // code
            { CL_WORKER_ANT, CPL_FEELER,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.01f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.05f },
                { pc::CC_PROTEIN,       0.15f },
                { pc::CC_FAT,           0.01f },
                { pc::CC_CARBOHYDRATE,  0.29f },
                // усик большей частью состоит из редких элементов
                { pc::CC_SPARSE,        0.50f }
            },
            // function
            // усик не является жизненно необходимым органом (не умирает сразу)
            // муравей ощущает мир усиками
            FPL_TASTE_NORMAL_SIGNAL | FPL_SMELL_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // муравей с помощью движений усиками может передавать информацию
            FPL_EMIT_NORMAL_VISION,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo Усик хорошо защищён от многих видов аттак.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 8 - правый усик (прикреплён к голове)

        // 9 - левая передняя лапка (прикреплена к груди)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            // остаток массы распределим между лапками (см. соглашение для "mass" особи)
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.20f },
                { pc::CC_PROTEIN,       0.20f },
                { pc::CC_FAT,           0.20f },
                { pc::CC_CARBOHYDRATE,  0.35f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // лапка не является жизненно необходимым органом (не умирает сразу)
            // передними лапками муравей может копать нору
            FPL_MOVE_SOLID_INSIDE_DIG |
            // лапка вносит свой вклад в скорость перемещения муравья
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // муравей чувствует прикосновения лапками
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 9 - левая передняя лапка (прикреплена к груди)

        // 10 - левая средняя лапка (прикреплена к груди)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_LEFT, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.20f },
                { pc::CC_PROTEIN,       0.20f },
                { pc::CC_FAT,           0.20f },
                { pc::CC_CARBOHYDRATE,  0.35f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // лапка не является жизненно необходимым органом (не умирает сразу)
            // лапка вносит свой вклад в скорость перемещения муравья
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // муравей чувствует прикосновения лапками
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 10 - левая средняя лапка (прикреплена к груди)

        // 11 - левая задняя лапка (прикреплена к груди)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_LEFT, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.20f },
                { pc::CC_PROTEIN,       0.20f },
                { pc::CC_FAT,           0.20f },
                { pc::CC_CARBOHYDRATE,  0.35f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // лапка не является жизненно необходимым органом (не умирает сразу)
            // лапка вносит свой вклад в скорость перемещения муравья
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // муравей чувствует прикосновения лапками
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 11 - левая задняя лапка (прикреплена к груди)


        // 12 - правая передняя лапка (прикреплена к груди)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.20f },
                { pc::CC_PROTEIN,       0.20f },
                { pc::CC_FAT,           0.20f },
                { pc::CC_CARBOHYDRATE,  0.35f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // лапка не является жизненно необходимым органом (не умирает сразу)
            // передними лапками муравей может копать нору
            FPL_MOVE_SOLID_INSIDE_DIG |
            // лапка вносит свой вклад в скорость перемещения муравья
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // муравей чувствует прикосновения лапками
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 12 - правая передняя лапка (прикреплена к груди)

        // 13 - правая средняя лапка (прикреплена к груди)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_RIGHT, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.20f },
                { pc::CC_PROTEIN,       0.20f },
                { pc::CC_FAT,           0.20f },
                { pc::CC_CARBOHYDRATE,  0.35f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // лапка не является жизненно необходимым органом (не умирает сразу)
            // лапка вносит свой вклад в скорость перемещения муравья
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // муравей чувствует прикосновения лапками
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 13 - правая средняя лапка (прикреплена к груди)

        // 14 - правая задняя лапка (прикреплена к груди)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_RIGHT, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.20f },
                { pc::CC_PROTEIN,       0.20f },
                { pc::CC_FAT,           0.20f },
                { pc::CC_CARBOHYDRATE,  0.35f },
                { pc::CC_SPARSE,        0.05f }
            },
            // function
            // лапка не является жизненно необходимым органом (не умирает сразу)
            // лапка вносит свой вклад в скорость перемещения муравья
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // муравей чувствует прикосновения лапками
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // энергии
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 14 - правая задняя лапка (прикреплена к груди)
    },

    // tag
    //   - муравей не относится ни к теплокровным, ни к холоднокровным особям
    //   - муравей может излечивать свои повреждённые органы, но не может
    //     восстанавливать утерянные
    TL_DAMAGE_REGENERATION,

    // lifetime, дни
    2.0f * 400.0f,

    // immunity
    1.0f,

    // metabolism
    {
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // кг / день
        {
            // ~ 3 л воды / день (1 л = 1 кг)
            { pc::CC_WATER,         3.0f },
            // белки ~ 0.5 г / кг веса / день
            { pc::CC_PROTEIN,       0.5f * 30.0f / 1000.0f },
            // жиры ~ 10 г / день
            { pc::CC_FAT,           10.0f / 1000.0f },
            // углеводы ~ ...
            { pc::CC_CARBOHYDRATE,  100.0f / 1000.0f },
            // редкие элементы ~ ...
            { pc::CC_SPARSE,        1.0f / 1000.0f },
            // ~ 5 тыс. л воздуха / день ( 1 л = 1.2 г)
            { pc::CC_AIR,           5000.0f * 1.2f / 1000.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // кг / день
        {
            { pc::CC_FECES,        50.0f / 1000.0f },
            { pc::CC_URINE,        500.0f / 1000.0f },
            // углекислый газ ~ 200 л / день
            { pc::CC_CARBON_ACID,  200.0f * 1.02f / 1000.0f },
        },

        // energyNeed
        {
            { pc::CE_NONE,  0.0f },
        },

        // energyWaste
        {
            { pc::CE_NONE,  0.0f },
        },
    },

    // survivor
    {
        // habitat
        // муравей может жить на границе твёрдой и газообразной сред, а также
        // внутри твёрдой среды (норы, муравейники)
        {
            HL_GAS | HL_SOLID,
            HL_SOLID,
            0U,
            0U,
            0U,
        },

        // temperatureRange
        {
            // comfort
            { 15.0f - tc::CK,  30.0f - tc::CK },
            // limit
            { 0.0f - tc::CK,  50.0f - tc::CK },
        }
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
    { 0.0f },
    // moveLiquidSurface
    { 0.0f },
    // moveSolidInside
    { 0.0f, 0.0f },
    // moveLiquidInside
    { 0.0f },
    // moveGasInside
    { 0.0f },

    // part[ PART_LIVING_COUNT ]
    //   # Указываем только имеющиеся у особи части: остальные будут
    //     заполнены нулями компилятором.
    //     @todo Проверить соглашение выше для Release-версии.
    {
        // 0 - листья
        {
            // code
            { CL_GRAMA, CPL_LEAF,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
            // mass
            0.4f,
            // composition
            // @see Питательные вещества > http://big-fermer.ru/zelenyi-korm
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { pc::CC_WATER,         0.800f },
                { pc::CC_CARBOHYDRATE,  0.150f },
                { pc::CC_PROTEIN,       0.049f },
                { pc::CC_SPARSE,        0.001f },
            },
            // function
            // растение продолжает жить без этого органа... пока есть пища
            // чувствует прикосновения
            FPL_TOUCH_NORMAL_SIGNAL |
            // поглощает и усваивает свет
            FPL_EAT_ENERGY | FPL_UPTAKE_ENERGY |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // пища
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            // CC_SPARSE здесь растворены в воде, а не жидкие от высокой температуры
            { { pc::CC_WATER, pc::CC_SPARSE },  0.0f },
            // uptakeGas
            { { pc::CC_CARBON_ACID },  0.0f },
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_AIR }},
            // энергии
            // uptakeEnergy
            { { pc::CE_NORMAL_LIGHT } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 0 - листья
    },

    // tag
    //   - растение не относится ни к теплокровным, ни к холоднокровным особям
    //   - растение может излечивать свои повреждённые органы и может
    //     восстанавливать утерянные
    TL_DAMAGE_REGENERATION | TL_LOSE_PART_REGENERATION,

    // lifetime, дни
    5.0f * 400.0f,

    // immunity
    1.0f,

    // metabolism
    // @see Потребность в кислороде > http://www.dissercat.com/content/pogloshchenie-kisloroda-sistemoi-pochva-rastenii-pri-raznykh-urovnyakh-pitaniya-rastenii
    // @see Питание растений > http://floragrow.ru/blog/pischa/13.html
    {
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
            { pc::CC_WATER,        0.001f * 0.010f },
            // кислород ~ 120 мл / кг веса / день (1 л = 1.2 г)
            // # Углекислый газ *потребляется* этим растением в тёмное время
            //   суток, кислород - в светлое; поэтому делим на 2.
            { pc::CC_AIR,          120.0f / 1000.0f * 0.010f * 0.0012f / 2.0f },
            // углекислый газ
            // ~ 240 мл / кг веса / день (1 л = 1.98 г)
            { pc::CC_CARBON_ACID,  240.0f / 1000.0f * 0.010f * 0.00198f / 2.0f },
            // редкие элементы ~ меньше самой меньшей потребности
            { pc::CC_SPARSE,       1.0f / 1000.0f },
            // @todo Добавить продукты разложения, экскременты др. особей.
            //       Сделать это в отдельной, не фатальной для жизни
            //       растения структуре.
            //       { pc::CC_DETRITUS,  ... },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // кг / день
        {
            // кислород ~ 240 мл / кг веса / день (см. выше componentNeed_t)
            // # Углекислый газ *выделяется* этим растением в светлое время
            //   суток, кислород - в тёмное; поэтому делим на 2.
            { pc::CC_AIR,          240.0f / 1000.0f * 0.010f * 0.0012f / 2.0f },
            // углекислый газ
            // ~ 50 мл / кг веса / день (1 л = 1.98 г)
            { pc::CC_CARBON_ACID,  50.0f / 1000.0f * 0.010f * 0.00198f / 2.0f },
        },

        // energyNeed
        {
            // для жизни требуется световой поток в 1000 люкс / день
            // # Т.к. полдня длится ночь, делим необходимый поток на 2.
            { pc::CE_NORMAL_LIGHT,  1000.0f / 2.0f },
        },

        // energyWaste
        {
            { pc::CE_NONE,  0.0f },
        },
    },

    // survivor
    {
        // habitat
        // это растение может жить на границе твёрдой и газообразной сред
        {
            HL_GAS | HL_SOLID,
        },

        // temperatureRange
        {
            // comfort
            { 10.0f - tc::CK,  30.0f - tc::CK },
            // limit
            { -5.0f - tc::CK,  55.0f - tc::CK },
        }
    }
},
#endif

};


                } // living
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
