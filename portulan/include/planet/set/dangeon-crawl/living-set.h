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
* Рабочий муравей.
* @see http://crawl.chaosforge.org/index.php?title=Worker_ant
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html#MONS_WORKER_ANT
*/
{
    // code
    CL_ANT_WORKER,

    // size
    SL_SMALL,

    // mass[ LIFE_CYCLE ]
    // # Цикл обрисован группами:
    //     0    Эмбрионы особей, семена.
    //     1    Дети, ростки.
    //     2    Взрослые.
    //     3    Старики.
    //     4    Мёртвые особи - тела, скелеты.
    //     5    Бессмертные особи.
    // В качестве массы для взрослой особи взята 10-тая часть массы из http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
    { 1.0f, 20.0f, 45.0f, 50.0f, 45.0f, 55.0f },

    // maxGroupSize
    0,

    // hitDice
    3.0f,

    // resist
    {
        // crush, cutting, thrust
        4.0f, 5.0f, 6.0f,
        // acid
        4.0f,
        // cold
        4.0f,
        // electricity
        4.0f,
        // fire
        4.0f,
        // helfire
        //   # Особый вид магии, у этой особи нет от него защиты.
        0.0f,
        // holyword
        // муравей неуязвим для этой магии, т.к. не является нежитью
        IMMUNE,
        // negative
        4.0f,
        // poison
        -1.0f
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
    //     @todo Проверить соглашение для Release-версии.
    {
        // 0 - голова
        {
            // code
            { CL_ANT_WORKER, CPL_HEAD,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // голова защищена от некоторых видов воздействий
            {
                // crush, cutting, thrust
                2.0f, 2.0f, 2.0f,
                // acid
                // от воздействия кислоты защищает хитин
                3.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                // яд быстрее повреждает голову
                -2.0f
            }
        }, // 0 - голова

        // 1 - грудь (средняя часть тела)
        {
            // code
            { CL_ANT_WORKER, CPL_BREAST,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_AIR },  1.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            {
                // crush, cutting, thrust
                1.0f, 1.0f, 1.0f,
                // acid
                // от воздействия кислоты защищает хитин
                2.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                -1.0f
            }
        }, // 1 - грудь (средняя часть тела)

        // 2 - брюшко (задняя часть тела)
        {
            // code
            { CL_ANT_WORKER, CPL_BELLY,  LXL_CENTER, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_PROTEIN, pc::CC_FAT, pc::CC_CARBOHYDRATE, pc::CC_SPARSE },  0.0f },
            // uptakeLiquid
            { { pc::CC_WATER },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                // от воздействия кислоты немного защищает тонкий хитин
                1.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                // брюшко уязвимо для яда
                -1.0f
            }
        }, // 2 - брюшко (задняя часть тела)

        // 3 - мозг (находится внутри головы)
        {
            // code
            { CL_ANT_WORKER, CPL_BRAIN,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_HEAD, CPL_NONE },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // мозг очень уязвим, но защиту даёт голова (мозг
            // находится внутри головы)
            {
                // crush, cutting, thrust
                -10.0f, -20.0f, -30.0f,
                // acid
                -10.0f,
                // cold
                -10.0f,
                // electricity
                -10.0f,
                // fire
                -10.0f,
                // helfire
                -10.0f,
                // holyword
                0.0f,
                // negative
                -20.0f,
                // poison
                // мозг неплохо переносит яд
                5.0f
            }
        }, // 3 - мозг (находится внутри головы)

        // 4 - жвалы или мандибулы (прикреплены к голове)
        {
            // code
            { CL_ANT_WORKER, CPL_MANDIBLE,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                // не может жвалами проколоть, но раздробить / разрезать - вполне
                // @see http://crawl.chaosforge.org/index.php?title=Worker_ant
                4.0f, 8.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                // впрыскивает отраву
                // @see http://crawl.chaosforge.org/index.php?title=Poison
                10.0f
            },
            // resist
            {
                // crush, cutting, thrust
                3.0f, 2.0f, 1.0f,
                // acid
                // от воздействия кислоты защищает хитин
                5.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                // неплохо защищены от яда
                10.0f
            }
        }, // 4 - жвалы (прикреплены к голове)

        // 5 - левый глаз (прикреплён к голове)
        {
            // code
            { CL_ANT_WORKER, CPL_EYE,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // глаз уязвим для многих видов аттак
            {
                // crush, cutting, thrust
                -10.0f, -15.0f, -30.0f,
                // acid
                -50.0f,
                // cold
                -10.0f,
                // electricity
                -10.0f,
                // fire
                -10.0f,
                // helfire
                -10.0f,
                // holyword
                0.0f,
                // negative
                -10.0f,
                // poison
                -5.0f
            }
        }, // 5 - левый глаз (прикреплён к голове)

        // 6 - правый глаз (прикреплён к голове)
        {
            // code
            { CL_ANT_WORKER, CPL_EYE,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // глаз уязвим для многих видов аттак
            {
                // crush, cutting, thrust
                -10.0f, -15.0f, -30.0f,
                // acid
                -50.0f,
                // cold
                -10.0f,
                // electricity
                -10.0f,
                // fire
                -10.0f,
                // helfire
                -10.0f,
                // holyword
                0.0f,
                // negative
                -10.0f,
                // poison
                -5.0f
            }
        }, // 6 - правый глаз (прикреплён к голове)

        // 7 - левый усик (прикреплён к голове)
        {
            // code
            { CL_ANT_WORKER, CPL_FEELER,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // усик хорошо защищён от многих видов аттак
            {
                // crush, cutting, thrust
                50.0f, 10.0f, 20.0f,
                // acid
                30.0f,
                // cold
                10.0f,
                // electricity
                10.0f,
                // fire
                10.0f,
                // helfire
                10.0f,
                // holyword
                0.0f,
                // negative
                10.0f,
                // poison
                10.0f
            }
        }, // 7 - левый усик (прикреплён к голове)

        // 8 - правый усик (прикреплён к голове)
        {
            // code
            { CL_ANT_WORKER, CPL_FEELER,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // усик хорошо защищён от аттак
            {
                // crush, cutting, thrust
                50.0f, 10.0f, 20.0f,
                // acid
                30.0f,
                // cold
                10.0f,
                // electricity
                10.0f,
                // fire
                10.0f,
                // helfire
                10.0f,
                // holyword
                0.0f,
                // negative
                10.0f,
                // poison
                10.0f
            }
        }, // 8 - правый усик (прикреплён к голове)

        // 9 - левая передняя лапка (прикреплена к груди)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
            // муравей не может что-либо повредить лапкой
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // лапка неплохо защищена от аттак
            {
                // crush, cutting, thrust
                20.0f, 5.0f, 10.0f,
                // acid
                10.0f,
                // cold
                5.0f,
                // electricity
                5.0f,
                // fire
                5.0f,
                // helfire
                5.0f,
                // holyword
                0.0f,
                // negative
                5.0f,
                // poison
                5.0f
            }
        }, // 9 - левая передняя лапка (прикреплена к груди)

        // 10 - левая средняя лапка (прикреплена к груди)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_LEFT, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
            // муравей не может что-либо повредить лапкой
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // лапка неплохо защищена от аттак
            {
                // crush, cutting, thrust
                20.0f, 5.0f, 10.0f,
                // acid
                10.0f,
                // cold
                5.0f,
                // electricity
                5.0f,
                // fire
                5.0f,
                // helfire
                5.0f,
                // holyword
                0.0f,
                // negative
                5.0f,
                // poison
                5.0f
            }
        }, // 10 - левая средняя лапка (прикреплена к груди)

        // 11 - левая задняя лапка (прикреплена к груди)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_LEFT, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
            // муравей не может что-либо повредить лапкой
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // лапка неплохо защищена от аттак
            {
                // crush, cutting, thrust
                20.0f, 5.0f, 10.0f,
                // acid
                10.0f,
                // cold
                5.0f,
                // electricity
                5.0f,
                // fire
                5.0f,
                // helfire
                5.0f,
                // holyword
                0.0f,
                // negative
                5.0f,
                // poison
                5.0f
            }
        }, // 11 - левая задняя лапка (прикреплена к груди)


        // 12 - правая передняя лапка (прикреплена к груди)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
            // муравей не может что-либо повредить лапкой
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // лапка неплохо защищена от аттак
            {
                // crush, cutting, thrust
                20.0f, 5.0f, 10.0f,
                // acid
                10.0f,
                // cold
                5.0f,
                // electricity
                5.0f,
                // fire
                5.0f,
                // helfire
                5.0f,
                // holyword
                0.0f,
                // negative
                5.0f,
                // poison
                5.0f
            }
        }, // 12 - правая передняя лапка (прикреплена к груди)

        // 13 - правая средняя лапка (прикреплена к груди)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_RIGHT, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
            // муравей не может что-либо повредить лапкой
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // лапка неплохо защищена от аттак
            {
                // crush, cutting, thrust
                20.0f, 5.0f, 10.0f,
                // acid
                10.0f,
                // cold
                5.0f,
                // electricity
                5.0f,
                // fire
                5.0f,
                // helfire
                5.0f,
                // holyword
                0.0f,
                // negative
                5.0f,
                // poison
                5.0f
            }
        }, // 13 - правая средняя лапка (прикреплена к груди)

        // 14 - правая задняя лапка (прикреплена к груди)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_RIGHT, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
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
            // усвоение
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // выделение
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
            // муравей не может что-либо повредить лапкой
            {
                // crush, cutting, thrust
                0.0f, 0.0f, 0.0f,
                // acid
                0.0f,
                // cold
                0.0f,
                // electricity
                0.0f,
                // fire
                0.0f,
                // helfire
                0.0f,
                // holyword
                0.0f,
                // negative
                0.0f,
                // poison
                0.0f
            },
            // resist
            // лапка неплохо защищена от аттак
            {
                // crush, cutting, thrust
                20.0f, 5.0f, 10.0f,
                // acid
                10.0f,
                // cold
                5.0f,
                // electricity
                5.0f,
                // fire
                5.0f,
                // helfire
                5.0f,
                // holyword
                0.0f,
                // negative
                5.0f,
                // poison
                5.0f
            }
        }, // 14 - правая задняя лапка (прикреплена к груди)
    },

    // tag
    //   - муравей не относится ни к теплокровным, ни к холоднокровным особям
    //   - муравей может излечивать свои повреждённые органы, но не может
    //     восстанавливать утерянные
    TL_DAMAGE_REGENERATION,

    // lifetime, дни
    1000.0f,

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
            { pc::CC_NONE,         0.0f },
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
        // муравей может жить на границе твёрдой и газообразной сред, а также
        // внутри твёрдой среды (норы, муравейники)
        {
            HL_GAS | HL_SOLID,
            HL_SOLID,
            0.0f,
            0.0f,
            0.0f
        },

        // temperatureRange
        {
            // comfort
            { 15.0f - tc::CK,  30.0f - tc::CK },
            // limit
            { 0.0f - tc::CK,  50.0f - tc::CK },
        }
    }
} // муравей

};


                } // living
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
