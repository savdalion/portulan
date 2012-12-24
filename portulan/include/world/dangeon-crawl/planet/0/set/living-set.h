#pragma once

#include "living.h"
#include <typelib/typelib.h>


/**
* ������ ����� ���������� - ��������, �������� - ��� ������������� �������
* �� ������ ���� ���� Dungeon Crawl.
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


static const aboutLiving_t aboutLiving[ LIVING_COUNT ] = {
/**
* ������ �����.
* ������������ ��� ������������ �������� ������ �� CODE_LIVING.
*/
#if 1
{
    // code
    CL_NONE,

    // size
    SL_ATOMIC,

    // mass[ LIFE_CYCLE_COUNT ]
    // # ���� ��������� ��������:
    //     0    �������� ������, ������.
    //     1    ����, ������.
    //     2    ��������.
    //     3    �������.
    //     4    ̸����� ����� - ����, �������.
    //     5    ����������� �����.
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

    // �����������
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

    // part[ PART_LIVING ]
    //   # ��������� ������ ��������� � ����� �����: ��������� �����
    //     ��������� ������ ������������.
    //     @todo ��������� ���������� ��� Release-������.
    {
#if 1
        // 0 - ����� ����, �����
        {
            // code
            { CL_NONE, CPL_NONE,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_NONE,         0.0f },
            },
            // function
            FPL_LIVE |
            // ...
            0ULL,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE }},
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },
#endif
    },

    // tag
    TL_DAMAGE_REGENERATION,

    // lifetime, ���
    0.0f,

    // immunity
    0.0f,

    // metabolism
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // �� / ����
        {
            { CC_NONE,         0.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // �� / ����
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
            // temperature
            0.0f,
            // biome
            {
            },
        },
        //adaptability
        0.0f
#endif
    }
},
#endif




/**
* ������� �������.
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
    // ~70 ��
    SL_SMALL,

    // mass[ LIFE_CYCLE_COUNT ]
    // # ���� ��������� ��������:
    //     0    �������� ������, ������.
    //     1    ����, ������.
    //     2    ��������.
    //     3    �������.
    //     4    ̸����� ����� - ����, �������.
    //     5    ����������� �����.
    // � �������� ����� ��� �������� ����� ����� 20-� ����� �����
    // �� http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
    { 0.5f,  10.0f,  20.0f,  25.0f,  20.0f,  30.0f },

    // maxGroupSize
    1000,

    // hitDice
    3.0f,

    // resist
    {
        // ����� ������ �� ���. �����
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
        // ����� ������ �� ���. �����
        { TAL_MAGIC,     FAL_ANY,    12.0f },
        // ����� ������ �� ����� �����
        { TAL_ANY,       FAL_ACID,               4.0f },
        { TAL_ANY,       FAL_BLINK,              0.0f },
        { TAL_ANY,       FAL_COLD,               0.0f },
        { TAL_ANY,       FAL_CONFUSE,            0.0f },
        { TAL_ANY,       FAL_ELECTRICITY,        2.0f },
        { TAL_ANY,       FAL_FIRE,               2.0f },
        { TAL_ANY,       FAL_HELLFIRE,           0.0f },
        // ������� �������� ��� ���� �����, �.�. �� �������� �������
        { TAL_ANY,       FAL_HOLYWORD,           IMMUNE },
        { TAL_ANY,       FAL_NEGATIVE,           0.0f },
        { TAL_ANY,       FAL_PARALYZE,           0.0f },
        { TAL_ANY,       FAL_POISON,            -1.0f },
        { TAL_ANY,       FAL_VAMPIRIC_DRAINING,  0.0f },
        // ������� ���������� ������
        { TAL_NONE,  FAL_NONE,  0.0f }
    },

    // evasion
    10.0f,

    // vitality
    17.0f,

    // noise
    { 0.0f, 3.0f },

    // �����������
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

    // part[ PART_LIVING ]
    //   # ��������� ������ ��������� � ����� �����: ��������� �����
    //     ��������� ������ ������������.
    //     @todo ��������� ���������� ���� ��� Release-������.
    {
#if 1
        // 0 - ������
        {
            // code
            { CL_WORKER_ANT, CPL_HEAD,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.2f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.5f },
                { CC_PROTEIN,       0.1f },
                { CC_FAT,           0.1f },
                { CC_CARBOHYDRATE,  0.2f },
                { CC_SPARSE,        0.1f }
            },
            // function
            FPL_LIVE |
            // ������� ������� ��� �������, �� ������������� ��������� � �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE }},
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            // ������ �� ������� (��� ������ ���������)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ������ ����� �������� �� ��������� ����� �����������.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 1 - ����� (������� ����� ����)
        {
            // code
            { CL_WORKER_ANT, CPL_BREAST,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
            // mass
            0.3f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.4f },
                { CC_PROTEIN,       0.2f },
                { CC_FAT,           0.1f },
                { CC_CARBOHYDRATE,  0.2f },
                { CC_SPARSE,        0.1f }
            },
            // function
            FPL_LIVE |
            // ������� ������� ��� �������, �� ������������� ��������� � ������
            FPL_TOUCH_NORMAL_SIGNAL |
            // �����
            FPL_UPTAKE_GAS |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_AIR },  1.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_CARBON_ACID } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            // ����� �� ������� (��� ������ ���������)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 2 - ������ (������ ����� ����)
        {
            // code
            { CL_WORKER_ANT, CPL_BELLY,  LXL_CENTER, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.3f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.4f },
                { CC_PROTEIN,       0.2f },
                { CC_FAT,           0.1f },
                { CC_CARBOHYDRATE,  0.2f },
                { CC_SPARSE,        0.1f }
            },
            // function
            FPL_LIVE |
            // ������� ������� ��� �������, �� ������������� ��������� � �������
            FPL_TOUCH_NORMAL_SIGNAL |
            // ��������� ������ � ������ ����
            FPL_UPTAKE_SOLID | FPL_UPTAKE_LIQUID |
            // �������� �����������
            FPL_EXCRETION_SOLID | FPL_EXCRETION_LIQUID |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_PROTEIN, CC_FAT, CC_CARBOHYDRATE, CC_SPARSE },  0.0f },
            // uptakeLiquid
            { { CC_WATER },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_FECES } },
            // excretionLiquid
            { { CC_URINE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            // ������ �� ������� (��� ������ ���������)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 3 - ���� (��������� ������ ������)
        {
            // code
            { CL_WORKER_ANT, CPL_BRAIN,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_HEAD, CPL_NONE },
            // mass
            0.02f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.7f },
                { CC_PROTEIN,       0.2f },
                { CC_FAT,           0.1f },
                { CC_CARBOHYDRATE,  0.095f },
                { CC_SPARSE,        0.005f }
            },
            // function
            FPL_LIVE |
            // ������� ������� ��� �������, ������������� ���� �� ���������
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // ���� �������� �� ��������� �����
            FPL_INTELLECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            // ���� ������� �� ������� (��� ������ ���������)
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ���� ����� ������, �� ������ ��� ������ (����
            // ��������� ������ ������).
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 4 - ����� ��� ��������� (����������� � ������)
        {
            // code
            { CL_WORKER_ANT, CPL_MANDIBLE,  LXL_CENTER, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.1f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.2f },
                { CC_PROTEIN,       0.1f },
                { CC_FAT,           0.05f },
                { CC_CARBOHYDRATE,  0.6f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������, ����� ��������� ���� � �������������
            FPL_TASTE_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            // ��������� ������ � ������ ����, �����
            FPL_EAT_SOLID | FPL_EAT_LIQUID | FPL_EAT_GAS |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                // �� ����� ������� ��������, �� ���������� / ��������� - ������
                // @see http://crawl.chaosforge.org/index.php?title=Worker_ant
                { TAL_CRUSH,     FAL_PLAIN,  4.0f },
                { TAL_CUTTING,   FAL_PLAIN,  8.0f },
                // ����������� ������
                // @see http://crawl.chaosforge.org/index.php?title=Poison
                { TAL_ANY,       FAL_POISON,            -1.0f },
                // .
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ����� �������� �����.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 5 - ����� ���� (��������� � ������)
        {
            // code
            { CL_WORKER_ANT, CPL_EYE,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.05f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.80f },
                { CC_PROTEIN,       0.15f },
                { CC_FAT,           0.01f },
                { CC_CARBOHYDRATE,  0.01f },
                { CC_SPARSE,        0.03f }
            },
            // function
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������, ����� - ����� ������� � ������� �������������
            FPL_VISION_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ����� ����� �������.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 6 - ������ ���� (��������� � ������)
        {
            // code
            { CL_WORKER_ANT, CPL_EYE,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.05f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.80f },
                { CC_PROTEIN,       0.15f },
                { CC_FAT,           0.01f },
                { CC_CARBOHYDRATE,  0.01f },
                { CC_SPARSE,        0.03f }
            },
            // function
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������, ����� - ����� ������� � ������� �������������
            FPL_VISION_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ����� ����� �������.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 7 - ����� ���� (��������� � ������)
        {
            // code
            { CL_WORKER_ANT, CPL_FEELER,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.01f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.05f },
                { CC_PROTEIN,       0.15f },
                { CC_FAT,           0.01f },
                { CC_CARBOHYDRATE,  0.29f },
                // ���� ������� ������ ������� �� ������ ���������
                { CC_SPARSE,        0.50f }
            },
            // function
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������
            FPL_TASTE_NORMAL_SIGNAL | FPL_SMELL_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // ������� � ������� �������� ������� ����� ���������� ����������
            FPL_EMIT_NORMAL_VISION,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ���� ������ ������� �� ������ ����� �����.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 8 - ������ ���� (��������� � ������)
        {
            // code
            { CL_WORKER_ANT, CPL_FEELER,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_HEAD },
            // mass
            0.01f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.05f },
                { CC_PROTEIN,       0.15f },
                { CC_FAT,           0.01f },
                { CC_CARBOHYDRATE,  0.29f },
                // ���� ������� ������ ������� �� ������ ���������
                { CC_SPARSE,        0.50f }
            },
            // function
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������
            FPL_TASTE_NORMAL_SIGNAL | FPL_SMELL_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // ������� � ������� �������� ������� ����� ���������� ����������
            FPL_EMIT_NORMAL_VISION,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            // @todo ���� ������ ������� �� ������ ����� �����.
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 9 - ����� �������� ����� (����������� � �����)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            // ������� ����� ����������� ����� ������� (��. ���������� ��� "mass" �����)
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.20f },
                { CC_PROTEIN,       0.20f },
                { CC_FAT,           0.20f },
                { CC_CARBOHYDRATE,  0.35f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ��������� ������� ������� ����� ������ ����
            FPL_MOVE_SOLID_INSIDE_DIG |
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 10 - ����� ������� ����� (����������� � �����)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_LEFT, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.20f },
                { CC_PROTEIN,       0.20f },
                { CC_FAT,           0.20f },
                { CC_CARBOHYDRATE,  0.35f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 11 - ����� ������ ����� (����������� � �����)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_LEFT, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.20f },
                { CC_PROTEIN,       0.20f },
                { CC_FAT,           0.20f },
                { CC_CARBOHYDRATE,  0.35f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },


        // 12 - ������ �������� ����� (����������� � �����)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_RIGHT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.20f },
                { CC_PROTEIN,       0.20f },
                { CC_FAT,           0.20f },
                { CC_CARBOHYDRATE,  0.35f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ��������� ������� ������� ����� ������ ����
            FPL_MOVE_SOLID_INSIDE_DIG |
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 13 - ������ ������� ����� (����������� � �����)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_RIGHT, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.20f },
                { CC_PROTEIN,       0.20f },
                { CC_FAT,           0.20f },
                { CC_CARBOHYDRATE,  0.35f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },

        // 14 - ������ ������ ����� (����������� � �����)
        {
            // code
            { CL_WORKER_ANT, CPL_TARSUS,  LXL_RIGHT, LYL_BOTTOM, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            0.0f,
            // composition
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.20f },
                { CC_PROTEIN,       0.20f },
                { CC_FAT,           0.20f },
                { CC_CARBOHYDRATE,  0.35f },
                { CC_SPARSE,        0.05f }
            },
            // function
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            { { CC_NONE },  0.0f },
            // uptakeGas
            { { CC_NONE },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_NONE } },
            // �������
            // uptakeEnergy
            { { CE_NONE } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        },
#endif
    },

    // tag
    //   - ������� �� ��������� �� � ������������, �� � �������������� ������
    //   - ������� ����� ���������� ���� ����������� ������, �� �� �����
    //     ��������������� ���������
    TL_DAMAGE_REGENERATION,

    // lifetime, ���
    2.0f * 400.0f,

    // immunity
    1.0f,

    // metabolism
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // �� / ����
        {
            // ~ 3 � ���� / ���� (1 � = 1 ��)
            { CC_WATER,         3.0f },
            // ����� ~ 0.5 � / �� ���� / ����
            { CC_PROTEIN,       0.5f * 30.0f / 1000.0f },
            // ���� ~ 10 � / ����
            { CC_FAT,           10.0f / 1000.0f },
            // �������� ~ ...
            { CC_CARBOHYDRATE,  100.0f / 1000.0f },
            // ������ �������� ~ ...
            { CC_SPARSE,        1.0f / 1000.0f },
            // ~ 5 ���. � ������� / ���� ( 1 � = 1.2 �)
            { CC_AIR,           5000.0f * 1.2f / 1000.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // �� / ����
        {
            { CC_FECES,        50.0f / 1000.0f },
            { CC_URINE,        500.0f / 1000.0f },
            // ���������� ��� ~ 200 � / ����
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
        // ������� ����� ���� �� ������� ������ � ������������ ����, � �����
        // ������ ������ ����� (����, �����������)
        {
            HL_GAS | HL_SOLID,
            HL_SOLID,
            0U,
            0U,
            0U,
        },
        // comfort
        {
            // temperature
            30.0f,
            // biome
            // ������� �� ����� ����� ������� ����� �������.
            {

            }
        },
        // adaptability
        0.5f
#endif
    }
},
#endif




/**
* ���������� �����.
* �����������.
* ������������ �� �������� � � �����.
*
* @prototype http://dfwk.ru/Grama
* @prototype http://ru.wikipedia.org/wiki/%D0%9E%D0%B2%D1%81%D1%8F%D0%BD%D0%B8%D1%86%D0%B0_%D0%BB%D1%83%D0%B3%D0%BE%D0%B2%D0%B0%D1%8F
*
* @see ����������� �������� > http://big-fermer.ru/zelenyi-korm
* @see ������������� ����� > http://furazh.ru/dictoth/?data=18453
* @see ����� ����� > http://prasemena.ru/blog/skolko_semian_v_odnom_gramme
* @see ������� �������� > http://floragrow.ru/blog/pischa/13.html
*/
#if 1
{
    // code
    CL_GRAMA,

    // size
    // ������ ~40 ��
    SL_LITTLE,

    // mass[ LIFE_CYCLE_COUNT ]
    // # ���� ��������� ��������:
    //     0    �������� ������, ������.
    //     1    ����, ������.
    //     2    ��������.
    //     3    �������.
    //     4    ̸����� ����� - ����, �������.
    //     5    ����������� �����.
    // @see ����� ����� > http://prasemena.ru/blog/skolko_semian_v_odnom_gramme
    { 0.001 / 1000.0f,  0.005f,  0.010f,  0.015f,  0.005f,  0.020f },

    // maxGroupSize
    0,

    // hitDice
    0.0f,

    // resist
    {
        // ������� ���������� ������
        { TAL_NONE,  FAL_NONE,  0.0f }
    },

    // evasion
    0.0f,

    // vitality
    1.0f,

    // noise
    { 0.0f, 0.0f },

    // �����������
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

    // part[ PART_LIVING ]
    //   # ��������� ������ ��������� � ����� �����: ��������� �����
    //     ��������� ������ ������������.
    //     @todo ��������� ���������� ���� ��� Release-������.
    {
#if 1
        // 0 - ������
        {
            // code
            { CL_GRAMA, CPL_LEAF,  LXL_CENTER, LYL_CENTER, LZL_CENTER,  CPL_NONE, CPL_NONE },
            // mass
            0.4f,
            // composition
            // @see ����������� �������� > http://big-fermer.ru/zelenyi-korm
            // 0 .. COMPONENT_COMPOSITION_LIVING
            {
                { CC_WATER,         0.800f },
                { CC_CARBOHYDRATE,  0.150f },
                { CC_PROTEIN,       0.049f },
                { CC_SPARSE,        0.001f },
            },
            // function
            // �������� ���������� ���� ��� ����� ������... ���� ���� ����
            // ��������� �������������
            FPL_TOUCH_NORMAL_SIGNAL |
            // ��������� � ��������� ����
            FPL_EAT_ENERGY | FPL_UPTAKE_ENERGY |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ����
            // uptakeSolid
            { { CC_NONE },  0.0f },
            // uptakeLiquid
            // CC_SPARSE ����� ���������� � ����, � �� ������ �� ������� �����������
            { { CC_WATER, CC_SPARSE },  0.0f },
            // uptakeGas
            { { CC_CARBON_ACID },  0.0f },
            // excretionSolid
            { { CC_NONE } },
            // excretionLiquid
            { { CC_NONE } },
            // excretionGas
            { { CC_AIR }},
            // �������
            // uptakeEnergy
            { { CE_NORMAL_LIGHT } },
            // excretionEnergy
            { { CE_NONE } },
            // attack
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            },
            // resist
            {
                { TAL_NONE,  FAL_NONE,  0.0f }
            }
        }, // 0 - ������
#endif
    },

    // tag
    //   - �������� �� ��������� �� � ������������, �� � �������������� ������
    //   - �������� ����� ���������� ���� ����������� ������ � �����
    //     ��������������� ���������
    TL_DAMAGE_REGENERATION | TL_LOSE_PART_REGENERATION,

    // lifetime, ���
    5.0f * 400.0f,

    // immunity
    1.0f,

    // metabolism
    // @see ����������� � ��������� > http://www.dissercat.com/content/pogloshchenie-kisloroda-sistemoi-pochva-rastenii-pri-raznykh-urovnyakh-pitaniya-rastenii
    // @see ������� �������� > http://floragrow.ru/blog/pischa/13.html
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // �� / ����
        {
            // #i ��������� - ���������� ������ ���� ��� ������ ��������.
            //    �������� ����� �� ����� �������� � ������� 75 � ����,
            //    ��� � 100, ���� � 200 �.
            //    @source http://kurdyumov.ru/knigi/plodorodie/temiriazev/temir03.php
            // # ����� ��������� ������� �������������, ������, ��� ��������
            //   �� �������� ����, � ���� ���������� *�����������* ��� ���-��.
            // ����: ��������� ~ 0.01 � / �� ���� / ���� (1 � = 1 ��)
            //       �����. ��� ����� ~ 0.001 � / �� ���� / ����
            // ����� ����� �������� = 0.010 ��
            { CC_WATER,        0.001f * 0.010f },
            // �������� ~ 120 �� / �� ���� / ���� (1 � = 1.2 �)
            // # ���������� ��� *������������* ���� ��������� � ����� �����
            //   �����, �������� - � �������; ������� ����� �������.
            { CC_AIR,          120.0f / 1000.0f * 0.010f * 0.0012f / 2.0f },
            // ���������� ���
            // ~ 240 �� / �� ���� / ���� (1 � = 1.98 �)
            { CC_CARBON_ACID,  240.0f / 1000.0f * 0.010f * 0.00198f / 2.0f },
            // ������ �������� ~ ������ ����� ������� �����������
            { CC_SPARSE,       1.0f / 1000.0f },
            // @todo �������� �������� ����������, ����������� ��. ������.
            //       ������� ��� � ���������, �� ��������� ��� �����
            //       �������� ���������.
            //       { CC_DETRITUS,  ... },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // �� / ����
        {
            // �������� ~ 240 �� / �� ���� / ���� (��. ���� componentNeed_t)
            // # ���������� ��� *����������* ���� ��������� � ������� �����
            //   �����, �������� - � �����; ������� ����� �������.
            { CC_AIR,          240.0f / 1000.0f * 0.010f * 0.0012f / 2.0f },
            // ���������� ���
            // ~ 50 �� / �� ���� / ���� (1 � = 1.98 �)
            { CC_CARBON_ACID,  50.0f / 1000.0f * 0.010f * 0.00198f / 2.0f },
        },

        // energyNeed
        {
            // ��� ����� ��������� �������� ����� � 1000 ���� / ����
            // # �.�. ������ ������ ����, ����� ����������� ����� �������.
            { CE_NORMAL_LIGHT,  1000.0f / 2.0f },
        },

        // energyWaste
        {
            { CE_NONE,  0.0f },
        },
#endif
},

    // survivor
    // #i ��� �������, ��� �������� ������� ������� �������� �������
    //    ����������� ����, ����������� �������� 80-95 % �������������
    //    ��������� ������� (����� ����� ���� ������� �� 65-75 %). ���
    //    �������� ����� ����������� � 75-80 %, �������� ����������� �
    //    50-75 % (������, ���������, ��������� � ��.).
    {
#if 1
        // habitat
        // ��� �������� ����� ���� �� ������� ������ � ������������ ����
        {
            HL_GAS | HL_SOLID,
        },
        // comfort
        {
            // temperature
            30.0f,
            // biome
            // ���������� ����� �� ����� ���������� ��������� � ����.
            {

            }
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
