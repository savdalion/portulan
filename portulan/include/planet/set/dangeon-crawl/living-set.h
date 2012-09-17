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
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace living {


namespace pc = portulan::planet::set::dungeoncrawl::component;
namespace tc = typelib::constant::physics;


static const aboutLiving_t aboutLiving = {
/**
* ������� �������.
* @see http://crawl.chaosforge.org/index.php?title=Worker_ant
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html#MONS_WORKER_ANT
*/
{
    // code
    CL_ANT_WORKER,

    // size
    SL_SMALL,

    // mass[ LIFE_CYCLE ]
    // # ���� ��������� ��������:
    //     0    �������� ������, ������.
    //     1    ����, ������.
    //     2    ��������.
    //     3    �������.
    //     4    ̸����� ����� - ����, �������.
    //     5    ����������� �����.
    // � �������� ����� ��� �������� ����� ����� 10-��� ����� ����� �� http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
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
        //   # ������ ��� �����, � ���� ����� ��� �� ���� ������.
        0.0f,
        // holyword
        // ������� �������� ��� ���� �����, �.�. �� �������� �������
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

    // part[ PART_LIVING_COUNT ]
    //   # ��������� ������ ��������� � ����� �����: ��������� �����
    //     ��������� ������ ������������.
    //     @todo ��������� ���������� ��� Release-������.
    {
        // 0 - ������
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
            // ������� ������� ��� �������, �� ������������� ��������� � �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE }},
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������ �� ������� (��� ������ ���������)
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
            // ������ �������� �� ��������� ����� �����������
            {
                // crush, cutting, thrust
                2.0f, 2.0f, 2.0f,
                // acid
                // �� ����������� ������� �������� �����
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
                // �� ������� ���������� ������
                -2.0f
            }
        }, // 0 - ������

        // 1 - ����� (������� ����� ����)
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
            // ������� ������� ��� �������, �� ������������� ��������� � ������
            FPL_TOUCH_NORMAL_SIGNAL |
            // �����
            FPL_UPTAKE_GAS |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_AIR },  1.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_CARBON_ACID } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ����� �� ������� (��� ������ ���������)
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
                // �� ����������� ������� �������� �����
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
        }, // 1 - ����� (������� ����� ����)

        // 2 - ������ (������ ����� ����)
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
            // ������� ������� ��� �������, �� ������������� ��������� � �������
            FPL_TOUCH_NORMAL_SIGNAL |
            // ��������� ������ � ������ ����
            FPL_UPTAKE_SOLID | FPL_UPTAKE_LIQUID |
            // �������� �����������
            FPL_EXCRETION_SOLID | FPL_EXCRETION_LIQUID |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_PROTEIN, pc::CC_FAT, pc::CC_CARBOHYDRATE, pc::CC_SPARSE },  0.0f },
            // uptakeLiquid
            { { pc::CC_WATER },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_FECES } },
            // excretionLiquid
            { { pc::CC_URINE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������ �� ������� (��� ������ ���������)
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
                // �� ����������� ������� ������� �������� ������ �����
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
                // ������ ������� ��� ���
                -1.0f
            }
        }, // 2 - ������ (������ ����� ����)

        // 3 - ���� (��������� ������ ������)
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
            // ������� ������� ��� �������, ������������� ���� �� ���������
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // ���� �������� �� ��������� �����
            FPL_INTELLECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ���� ������� �� ������� (��� ������ ���������)
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
            // ���� ����� ������, �� ������ ��� ������ (����
            // ��������� ������ ������)
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
                // ���� ������� ��������� ��
                5.0f
            }
        }, // 3 - ���� (��������� ������ ������)

        // 4 - ����� ��� ��������� (����������� � ������)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������, ����� ��������� ���� � �������������
            FPL_TASTE_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            // ��������� ������ � ������ ����, �����
            FPL_EAT_SOLID | FPL_EAT_LIQUID | FPL_EAT_GAS |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            {
                // crush, cutting, thrust
                // �� ����� ������� ���������, �� ���������� / ��������� - ������
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
                // ����������� ������
                // @see http://crawl.chaosforge.org/index.php?title=Poison
                10.0f
            },
            // resist
            {
                // crush, cutting, thrust
                3.0f, 2.0f, 1.0f,
                // acid
                // �� ����������� ������� �������� �����
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
                // ������� �������� �� ���
                10.0f
            }
        }, // 4 - ����� (����������� � ������)

        // 5 - ����� ���� (��������� � ������)
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
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������, ����� - ����� ������� � ������� �������������
            FPL_VISION_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
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
            // ���� ������ ��� ������ ����� �����
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
        }, // 5 - ����� ���� (��������� � ������)

        // 6 - ������ ���� (��������� � ������)
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
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������, ����� - ����� ������� � ������� �������������
            FPL_VISION_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
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
            // ���� ������ ��� ������ ����� �����
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
        }, // 6 - ������ ���� (��������� � ������)

        // 7 - ����� ���� (��������� � ������)
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
                // ���� ������� ������ ������� �� ������ ���������
                { pc::CC_SPARSE,        0.50f }
            },
            // function
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������
            FPL_TASTE_NORMAL_SIGNAL | FPL_SMELL_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // ������� � ������� �������� ������� ����� ���������� ����������
            FPL_EMIT_NORMAL_VISION,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
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
            // ���� ������ ������� �� ������ ����� �����
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
        }, // 7 - ����� ���� (��������� � ������)

        // 8 - ������ ���� (��������� � ������)
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
                // ���� ������� ������ ������� �� ������ ���������
                { pc::CC_SPARSE,        0.50f }
            },
            // function
            // ���� �� �������� �������� ����������� ������� (�� ������� �����)
            // ������� ������� ��� �������
            FPL_TASTE_NORMAL_SIGNAL | FPL_SMELL_NORMAL_SIGNAL | FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT |
            // ������� � ������� �������� ������� ����� ���������� ����������
            FPL_EMIT_NORMAL_VISION,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
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
            // ���� ������ ������� �� �����
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
        }, // 8 - ������ ���� (��������� � ������)

        // 9 - ����� �������� ����� (����������� � �����)
        {
            // code
            { CL_ANT_WORKER, CPL_TARSUS,  LXL_LEFT, LYL_TOP, LZL_CENTER,  CPL_NONE, CPL_BREAST },
            // mass
            // ������� ����� ����������� ����� ������� (��. ���������� ��� "mass" �����)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ��������� ������� ������� ����� ������ ����
            FPL_MOVE_SOLID_INSIDE_DIG |
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������� �� ����� ���-���� ��������� ������
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
            // ����� ������� �������� �� �����
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
        }, // 9 - ����� �������� ����� (����������� � �����)

        // 10 - ����� ������� ����� (����������� � �����)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������� �� ����� ���-���� ��������� ������
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
            // ����� ������� �������� �� �����
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
        }, // 10 - ����� ������� ����� (����������� � �����)

        // 11 - ����� ������ ����� (����������� � �����)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������� �� ����� ���-���� ��������� ������
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
            // ����� ������� �������� �� �����
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
        }, // 11 - ����� ������ ����� (����������� � �����)


        // 12 - ������ �������� ����� (����������� � �����)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ��������� ������� ������� ����� ������ ����
            FPL_MOVE_SOLID_INSIDE_DIG |
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������� �� ����� ���-���� ��������� ������
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
            // ����� ������� �������� �� �����
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
        }, // 12 - ������ �������� ����� (����������� � �����)

        // 13 - ������ ������� ����� (����������� � �����)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������� �� ����� ���-���� ��������� ������
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
            // ����� ������� �������� �� �����
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
        }, // 13 - ������ ������� ����� (����������� � �����)

        // 14 - ������ ������ ����� (����������� � �����)
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
            // ����� �� �������� �������� ����������� ������� (�� ������� �����)
            // ����� ������ ���� ����� � �������� ����������� �������
            FPL_MOVE_SOLID_INSIDE_BURROW | FPL_MOVE_SOLID_SURFACE |
            // ������� ��������� ������������� �������
            FPL_TOUCH_NORMAL_SIGNAL |
            FPL_VISION_REFLECT_NORMAL_EFFECT,
            // ��������
            // uptakeSolid
            { { pc::CC_NONE },  0.0f },
            // uptakeLiquid
            { { pc::CC_NONE },  0.0f },
            // uptakeGas
            { { pc::CC_NONE },  0.0f },
            // uptakeNormalLight
            { 0.0f },
            // ���������
            // excretionSolid
            { { pc::CC_NONE } },
            // excretionLiquid
            { { pc::CC_NONE } },
            // excretionGas
            { { pc::CC_NONE } },
            // �������
            // uptakeEnergy
            { { pc::CE_NONE } },
            // excretionEnergy
            { { pc::CE_NONE } },
            // attack
            // ������� �� ����� ���-���� ��������� ������
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
            // ����� ������� �������� �� �����
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
        }, // 14 - ������ ������ ����� (����������� � �����)
    },

    // tag
    //   - ������� �� ��������� �� � ������������, �� � �������������� ������
    //   - ������� ����� ���������� ���� ����������� ������, �� �� �����
    //     ��������������� ���������
    TL_DAMAGE_REGENERATION,

    // lifetime, ���
    1000.0f,

    // immunity
    1.0f,

    // metabolism
    {
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // �� / ����
        {
            // ~ 3 � ���� / ���� (1 � = 1 ��)
            { pc::CC_WATER,         3.0f },
            // ����� ~ 0.5 � / �� ���� / ����
            { pc::CC_PROTEIN,       0.5f * 30.0f / 1000.0f },
            // ���� ~ 10 � / ����
            { pc::CC_FAT,           10.0f / 1000.0f },
            // �������� ~ ...
            { pc::CC_CARBOHYDRATE,  100.0f / 1000.0f },
            // ������ �������� ~ ...
            { pc::CC_SPARSE,        1.0f / 1000.0f },
            // ~ 5 ���. � ������� / ���� ( 1 � = 1.2 �)
            { pc::CC_AIR,           5000.0f * 1.2f / 1000.0f },
        },

        // componentWaste_t[ COMPONENT_WASTE_LIVING ]
        // �� / ����
        {
            { pc::CC_FECES,        50.0f / 1000.0f },
            { pc::CC_URINE,        500.0f / 1000.0f },
            // ���������� ��� ~ 200 � / ����
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
        // ������� ����� ���� �� ������� ������ � ������������ ����, � �����
        // ������ ������ ����� (����, �����������)
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
} // �������

};


                } // living
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
