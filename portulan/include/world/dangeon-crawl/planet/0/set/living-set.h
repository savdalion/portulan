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


// # ����� �� �������� �������� 'static', �� CPU OpenCL �� ������������ ���.
const aboutLiving_t aboutLiving[ LIVING_COUNT ] = {
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

    // attack
    {},

    // resist
    {},

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

    // tag
    TL_DAMAGE_REGENERATION,

    // lifetime, ���
    0.0f,

    // immunity
    0.0f,

    // composition
    {
        { CC_NONE, 0.0f },
    },

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
        },

        //adaptability
        0.0f
#endif
    },

    // friend
    {},

    // enemy
    {}
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

    // attack
    {
        // �� ����� ������� ��������, �� ���������� / ��������� - ������
        // @see http://crawl.chaosforge.org/index.php?title=Worker_ant
        { TAL_CRUSH,     FAL_PLAIN,   4.0f },
        { TAL_CUTTING,   FAL_PLAIN,   8.0f },
        // ����������� ������
        // @see http://crawl.chaosforge.org/index.php?title=Poison
        { TAL_ANY,       FAL_POISON,  10.0f },
        // ������� ���������� ������
        { TAL_NONE,  FAL_NONE,  0.0f }
    },

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

    // ����������� � ������ ������
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
    //   - ������� �� ��������� �� � ������������, �� � �������������� ������
    //   - ������� ����� ���������� ���� ����������� ������, �� �� �����
    //     ��������������� ���������
    TL_DAMAGE_REGENERATION,

    // lifetime, ���
    //   - ������� ���� ~ 2 ����
    2.0f * 365.0f,

    // immunity
    1.0f,

    // composition
    {
        { CC_WATER,         0.4f },
        { CC_PROTEIN,       0.2f },
        { CC_FAT,           0.1f },
        { CC_CARBOHYDRATE,  0.25f },
        { CC_SPARSE,        0.05f },
        { CC_NONE,          0.0f },
    },

    // metabolism
    {
#if 1
        // componentNeed_t[ COMPONENT_NEED_LIVING ]
        // �� / ����-
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
        //   - ������� �������� ���� �� ������� ������ � ������������ ����,
        //     � ����� ������ ������ ����� (����, �����������)
        {
            HL_SOLID,
            HL_GAS | HL_SOLID,
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
    },

    // friend
    {
        // code, force
        { CL_WORKER_ANT, CRITERIA_D_YELLOW },
    },

    // enemy
    {}
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

    // attack
    {},

    // resist
    {},

    // evasion
    0.0f,

    // vitality
    1.0f,

    // noise
    { 0.0f, 0.0f },

    // �����������
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
    //   - �������� �� ��������� �� � ������������, �� � �������������� ������
    //   - �������� ����� ���������� ���� ����������� ������ � �����
    //     ��������������� ���������
    TL_DAMAGE_REGENERATION,

    // lifetime, ���
    5.0f * 365.0f,

    // immunity
    1.0f,

    // composition
    {
        { CC_WATER,         0.800f },
        { CC_CARBOHYDRATE,  0.150f },
        { CC_PROTEIN,       0.049f },
        { CC_SPARSE,        0.001f },
        { CC_NONE,          0.0f },
    },

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
            20.0f,
            // @todo ...
            // rainfall
            // drainage
            // illuminance
        },

        // adaptability
        0.5f
#endif
    },

    // friend
    {},

    // enemy
    {}
},
#endif

};


                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
