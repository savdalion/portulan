#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "biome.h"


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
#endif


/**
* ������������ ����� � ������ ������ ����
* GROUP_ELEMENT::GE_LIVING.
*
*   # ��������, ���������, �������� � ��. �������� ������ ��������� "�������".
*   #! ��������� ������ ������ �����. ������� � ������ aboutLiving_t.
*
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
*/
#undef CL_NONE
enum CODE_LIVING {
    // ��� ����������� ��� �� ��������
    CL_NONE = 0,

    // ����� �����
    CL_ANY = CL_NONE,

    // @see living-set.h

    // ������� �������
    CL_WORKER_ANT,

    // ���������� �����
    CL_GRAMA,

    // ���������
    CL_last
};





/**
* ��� �����, ����� ���-�� ������.
*   # ���-�� ����� ������ ������������ �� ���-�� ������ �
*     ������� ����� �� ���������� aboutOneLiving_t.
*
* ��������: ������� = 6e6, ������� = 3e3, ����� = 4e4.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING code;
    cl_float count;
} portionLiving_t;






/**
* ������������ ����� ������ ���� ����� �������.
*   # ������� �� ������ �������� / �������� - ����� ��������.
*/
enum COMMON_PART_LIVING {
    // ������ ����� ��� ����� �� ����������
    // ������������ ��� �������, ��� ����� �� ��������� �� � ������
    // ������� ������
    CPL_NONE = 0,

    /* ��������, ��������� */
    // ������
    CPL_HEAD,
    // �����
    CPL_BREAST,
    // ������
    CPL_BELLY,
    // ����
    CPL_BRAIN,
    // �����
    CPL_MANDIBLE,
    // ����
    CPL_EYE,
    // ����
    CPL_FEELER,
    // ����� ����������
    CPL_TARSUS,
    // ���� ���������
    CPL_LEG,
    /* - @todo extend ���������� ������ �������� �� ����� ���������� ���������.
         ������ �� ����� ����������� � ��� �� ������, ������� ������������
         �� ���. �����.
    // �������� ������
    CPL_VENOM_GLAND
    */

    /* �������� */
    // ������
    CPL_ROOT,
    // �������, �����
    CPL_STEM,
    // ������, ������
    CPL_LEAF,
    // �������
    CPL_SPIKELET,
    // ����
    CPL_SEED,
    // ����, �������, �������
    //CPL_FETUS, - ������������ �������?

    // ���������
    CPL_last
};





/**
* �������������� ������ ����� �� ������������ ���� XYZ.
*   # ����������� ������� ��������� ��� Z, ��� X ���������� ������, Y - �����.
*/
#if 1

enum LOCUS_X_PART_LIVING {
    LXL_UNDEFINED = 0,
    LXL_LEFT,
    LXL_CENTER,
    LXL_RIGHT,
    // ����� ���������� �� ���� ����� (��������, ����������� ������)
    LXL_EXTENT,

    // ���������
    LXL_last
};

enum LOCUS_Y_PART_LIVING {
    LYL_UNDEFINED = 0,
    LYL_BOTTOM,
    LYL_CENTER,
    LYL_TOP,
    LYL_EXTENT,

    // ���������
    LYL_last
};

enum LOCUS_Z_PART_LIVING {
    LZL_UNDEFINED = 0,
    LZL_FAR,
    LZL_CENTER,
    LZL_NEAR,
    LZL_EXTENT,

    // ���������
    LZL_last
};

#endif





/**
* ��� ������ �����.
* ��� ������� �� ��������� ������, ����� ���������� ������. ��������
* ��� ������� �����������.
*/
typedef struct __attribute__ ((packed)) {
    // ����� ����� ����������� �����
    enum CODE_LIVING specimen;

    // ����� ������
    enum COMMON_PART_LIVING part;

    // �������������� ������ ������������ �����
    //   # ����� ��������������� ������� �����, ������ � ����������� � �.�.,
    //     ����� � �������� ������������ ������� ����������� ����
    //     ������������.
    //   # ������� �� ����� ������: ��� Z - ��������� �����������, ��� X -
    //     �������, ��� Y - �����.
    enum LOCUS_X_PART_LIVING lx;
    enum LOCUS_Y_PART_LIVING ly;
    enum LOCUS_Z_PART_LIVING lz;

    // ����� ��������� ������ ������� ������
    // ��������: ����, ������.
    enum COMMON_PART_LIVING inner;

    // ����� ��������� �� ����������� ��� ��������� � ������� ������
    // ��������: ����, ����.
    //   # ���� � ������ ����������� ����. ������� �� ������� �������,
    //     ���� ������������ ����������� ��� ������� �������.
    //   # ���� ��������� ������� �� ������� ������, ���� ������������
    //     ����������� ��� ������� ������. ��. ���� "�������������� ������".
    enum COMMON_PART_LIVING outer;

} codePartLiving_t;






/**
* ������� ����� ���� �����.
*/
#if 1

// �������� ������ ����� (��������� ����� ��� ����������)
#define FPL_LIVE                          (1ULL << 0)

// ����������� �� ������ �����������
#define FPL_MOVE_SOLID_SURFACE            (1ULL << 1)
// ����������� �� ������ �����������
#define FPL_MOVE_LIQUID_SURFACE           (1ULL << 2)

// ����������� ������ ������ ����������� � �������� ����
#define FPL_MOVE_SOLID_INSIDE_DIG         (1ULL << 3)
// ����������� ������ ������ ����������� �� ������� ����
#define FPL_MOVE_SOLID_INSIDE_BURROW      (1ULL << 4)
// ����������� ������ ������ �����������
#define FPL_MOVE_LIQUID_INSIDE            (1ULL << 5)
// ����������� ������ ������������ ����������� (���� �� �������)
#define FPL_MOVE_GAS_INSIDE               (1ULL << 6)

// # ��� ��������� ��������� - ������� ��� ������� ������.
// ���������� ������ ����������� ����������� (����, ���)
#define FPL_EAT_SOLID                     (1ULL << 7)
// ���������� ������ ����������� ����������� (����, �����)
#define FPL_EAT_LIQUID                    (1ULL << 8)
// ���������� ������������ ����������� ����������� (������, �����)
#define FPL_EAT_GAS                       (1ULL << 9)
// ���������� �������
#define FPL_EAT_ENERGY                    (1ULL << 10)

// # ��� ��������� ��������� - ������� ��� ������� ������.
// �������� ������ ����������� ����������� (����)
#define FPL_UPTAKE_SOLID                  (1ULL << 11)
// �������� ������ ����������� ����������� (����)
#define FPL_UPTAKE_LIQUID                 (1ULL << 12)
// �������� ������������ ����������� ����������� (������)
#define FPL_UPTAKE_GAS                    (1ULL << 13)
// �������� �������
#define FPL_UPTAKE_ENERGY                 (1ULL << 14)

// ��������� ������ ����������� ����������� (���)
#define FPL_EXCRETION_SOLID               (1ULL << 15)
// ��������� ������ ����������� ����������� (����)
#define FPL_EXCRETION_LIQUID              (1ULL << 16)
// ��������� ������������ ����������� ����������� (����)
#define FPL_EXCRETION_GAS                 (1ULL << 17)
// ��������� ����� (���������)
#define FPL_EXCRETION_NORMAL_LIGHT        (1ULL << 18)

//   # ����� �������������� ����������� ���������� � ������� ��� �����.

// ��������� ����� (��������������, ��� �������� ����������� � ���. �����)
// # @todo extend? ������ �������� �������� ������� ���������������
//   ������� �� �����
//     - ������ (��������, ���������������� ���������)
//     - ��������� (��������, ������� ����)
//     - ����� (��������, ������������ ���������)
// @see http://ru.wikipedia.org/wiki/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BC%D0%B0%D0%B3%D0%BD%D0%B8%D1%82%D0%BD%D1%8B%D0%B9_%D1%81%D0%BF%D0%B5%D0%BA%D1%82%D1%80
// ����
#define FPL_TASTE_NORMAL_SIGNAL           (1ULL << 19)
// ��������
#define FPL_SMELL_NORMAL_SIGNAL           (1ULL << 20)
// ��������
#define FPL_TOUCH_NORMAL_SIGNAL           (1ULL << 21)
// ����
#define FPL_HEARING_NORMAL_SIGNAL         (1ULL << 22)
// ������
#define FPL_VISION_NORMAL_SIGNAL          (1ULL << 23)
// ����� ����������� (������: ��� ��� Dungeon Crawl)
#define FPL_PRESENCE_NORMAL_SIGNAL        (1ULL << 24)

// �������, ������������ ������
// ���������� ��������� (� ����� ����� ����� ��� � ����� �����)
#define FPL_VISION_REFLECT_NORMAL_EFFECT  (1ULL << 25)
/* - ��� ���� - ��. noise � ���. �� �����.
// ����� (����� ���) ��� ������������
#define FPL_NOISE_MOVE_NORMAL_EFFECT      (1ULL << ..)
*/

// ����������� ���������� ����� (�������, ����)
#define FPL_PHYSICAL_ATTACK               (1ULL << 26)

// ����������� ���������� ����� (����)
#define FPL_MAGIC_ATTACK                  (1ULL << 27)

// ��������� (����)
#define FPL_INTELLECT                     (1ULL << 28)

//   # ������� - ��������� �������� �����������, ������� (�������� ����.
//     � ���� �����), ������, ������ �������������, �������� (�����), �������
//     ����� � ���� ��������� ���������� � ����� ���� ���������� �������
//     ������� ��� ������� �����. ���������.
// ������� � ������� �������� ��������
// @see ������������ > http://ru.wikipedia.org/wiki/%D0%A2%D1%80%D0%BE%D1%84%D0%B0%D0%BB%D0%BB%D0%B0%D0%BA%D1%81%D0%B8%D1%81
#define FPL_EMIT_NORMAL_TASTE             (1ULL << 29)
// ������� � ������� �������
#define FPL_EMIT_NORMAL_SMELL             (1ULL << 30)
// ������� � ������� �������������
#define FPL_EMIT_NORMAL_TOUCH             (1ULL << 31)
// ������� � ������� ������ (�������, ����)
#define FPL_EMIT_NORMAL_SOUND             (1ULL << 32)
// ������� � ������� ���������� (���������� �������)
#define FPL_EMIT_NORMAL_VISION            (1ULL << 33)

#endif





/**
* ����� �������� - HABITAT_LIVING - �����.
*/
#define HL_SOLID   (1U << 0)
#define HL_LIQUID  (1U << 1)
#define HL_GAS     (1U << 2)
#define HL_PLASM   (1U << 3)







/**
* ������ �����.
*/
enum SIZE_LIVING {
    // ~0.01-0.2 �:  ������, ����� ��������
    SL_ATOMIC = 1,

    // ~0.2-0.3 �:  �����, ������� ����
    SL_TINY,

    // ~0.3-0.6 �:  ���������
    SL_LITTLE,

    // ~0.6-1.2 �:  �������, �����������, ��������
    SL_SMALL,

    // ~1.2-2.0 �:  ����, �����, ������
    SL_MEDIUM,

    // ~2.0-3.0 �:  �����, ����, ��������, ����
    SL_LARGE,

    // ~3.0-4.0 �:  ������������ ��������
    SL_BIG,

    // ~4.0-6.0 �:  �������
    SL_GIANT,

    // ~6.0-9.0 �:  �������
    SL_HUGE,

    // ���������
    SL_last
};





/**
* �����������.
*
* @see http://crawl.chaosforge.org/index.php?title=Holiness
*/
enum HOLYNESS_LIVING {
    HL_UNDEFINED = 0,

    HL_DEMONIC,
    HL_HOLY,
    HL_NATURAL,
    HL_NONLIVING,
    HL_PLANT,
    HL_UNDEAD,

    // ���������
    HL_last
};





/**
* ���������� ���� � �����.
* �� ���� ����� ������������ ������ - porte - ����� �������
* ����������� �������.
*//* - �������� �� define. ��. ����.
enum TAG_LIVING {
*/
#if 1

// ������������ �����
#define TL_WARM_BLOODED            (0ULL)

// �������������� �����
#define TL_COLD_BLOODED            (1ULL << 1)

// ����������� ����� (������ �����)
//   # ����� �� �������������, ���� �� ������ ���� �� ���� �� ����� ����.
// ����������������� �����������
#define TL_DAMAGE_REGENERATION     (1ULL << 2)
// ����������������� ��������� ����� ����
#define TL_LOSE_PART_REGENERATION  (1ULL << 3)

#endif




/**
* ��� ����� �����.
*
* @see http://crawl.chaosforge.org/index.php?title=Attack_type
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_flags_by_name.html
*/
enum TYPE_ATTACK_LIVING {
    // ��� ����� (������ ��������� ���������� ������ ����)
    TAL_NONE = 0,

    // ����� ����� (���. ��� ������� ������ �� ����, ������ ���� � ���� ��� + ����)
    TAL_ANY = 1,

    // ����������, ������� ����� ����
    TAL_CRUSH,
    // ��������, ������� ������� ����, ���������� ��������
    TAL_CUTTING,
    // ��������� �������, ������
    TAL_CLAW,
    // ����� / ������ ������, ��������, ����������
    TAL_CONSTRICT,
    // ���������
    TAL_ENGULF,
    // ��������, ������� ������� ����
    TAL_PIERCE,

    // ����������, �������, ��������, �������, ��������� � �������� �����������
    // @see TAL_MAGIC
    // @see ���������� � ������ � aboutOnePartLiving_t::resist.
    // ��������� ����� �����
    TAL_SHOOT_CRUSH,
    // ��������� ����� (��������, ������� ���� / ������� / ��������)
    TAL_SHOOT_GAS,
    // ��������� ��������� (��������, �������)
    TAL_SHOOT_LIQUID,
    // ��������� ������ �����
    TAL_SHOOT_PIERCE,

    // ������������ (��. "���� �����")
    TAL_TOUCH,
    // ��������
    TAL_TRAMPLE,

    // �������� ���������� �����
    //   #! ���. ����� - ��� �����, �� �������� ���. �������� � �����. �.�.,
    //     "�����" - ��� ����������� ������� ���� ����� (��. ����) �� ���� ���
    //     ������������� �����-���� ������� �������� ����.
    // @see TAL_SHOOT
    TAL_MAGIC,

    // ���������
    TAL_last
};




/**
* ���� �����.
*
* @see http://crawl.chaosforge.org/index.php?title=Attack_flavour
*/
enum FLAVOUR_ATTACK_LIVING {
    // ��� �����, ������� �����
    FAL_PLAIN = 0,
    FAL_NONE = FAL_PLAIN,

    // ����� ����� (���. ��� ������� ������ �� ����, ������ ���� � ���� ��� + ����)
    FAL_ANY = FAL_PLAIN,

    // �������� ��������
    FAL_ACID,

    // ��������������� ������
    FAL_BLINK,

    // �������� �������
    FAL_COLD,

    // ����� � �����
    FAL_CONFUSE,

    // �������� ��������������
    FAL_ELECTRICITY,

    // �������� ����
    FAL_FIRE,

    // �������� ������ ����
    FAL_HELLFIRE,

    // �������� ������ ������
    FAL_HOLYWORD,

    // �������� ������������� ��������
    FAL_NEGATIVE,

    // ������������
    FAL_PARALYZE,

    // ��������
    //   # ����� ���������� �������� http://crawl.chaosforge.org/index.php?title=Poison#Poison_Types
    //     10 - ������� (regular)
    //     20 - ������� (medium)
    //     40 - ������� (strong)
    //     80 - ������� (nasty)
    FAL_POISON,

    // ����� ���������� �� 1d(��������� �����������)
    FAL_VAMPIRIC_DRAINING,

    // ���������
    FAL_last
};




/**
* ��������� ��� �������� ����� �����.
* ������ � ����� � ������ ����� ������� ���� �����.
* 
*   # ���� ����� - ��� ���������� ���������� �������� Damage ��
*     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
*/
typedef struct __attribute__ ((packed)) {
    enum TYPE_ATTACK_LIVING     type;
    enum FLAVOUR_ATTACK_LIVING  flavour;
    cl_float                    force;
} aboutOnePartAttack_t;



/**
* �����, ��������� ������ �����.
*/
typedef aboutOnePartAttack_t  attackPartLiving_t[ ATTACK_PART_LIVING ];





/**
* ��������� ��� �������� ������ �����.
* ������ � ����� � ������ ����� ������� ���� ������ �� ���� �����.
* 
*   # ���� ������ - ��� ���������� ���������� �������� AC � MR ��
*     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
*/
typedef struct __attribute__ ((packed)) {
    enum TYPE_ATTACK_LIVING     type;
    enum FLAVOUR_ATTACK_LIVING  flavour;
    cl_float                    force;
} aboutOnePartResist_t;



/**
* ������ �� ��������� ����.
*/
typedef aboutOnePartResist_t  resistPartLiving_t[ RESIST_PART_LIVING ];





/**
* ���������� �� ������ �����.
*   # ������ ������ ����� ������������ �������� ����� ����� � ������ ������.
*/
#if 1

typedef portionComponent_t  compositionPortionLiving_t[ COMPONENT_COMPOSITION_LIVING ];

typedef enum CODE_COMPONENT  componentCodeNeedLiving_t[ COMPONENT_NEED_LIVING ];

typedef struct __attribute__ ((packed)) {
    componentCodeNeedLiving_t componentNeed;
    cl_float efficiency;
} uptakeSolidLiving_t;

typedef struct __attribute__ ((packed)) {
    componentCodeNeedLiving_t componentNeed;
    cl_float efficiency;
} uptakeLiquidLiving_t;

typedef struct __attribute__ ((packed)) {
    componentCodeNeedLiving_t componentNeed;
    cl_float efficiency;
} uptakeGasLiving_t;


typedef enum CODE_COMPONENT  componentCodeWasteLiving_t[ COMPONENT_WASTE_LIVING ];

typedef struct __attribute__ ((packed)) {
    componentCodeWasteLiving_t componentWaste;
} excretionSolidLiving_t;

typedef struct __attribute__ ((packed)) {
    componentCodeWasteLiving_t componentWaste;
} excretionLiquidLiving_t;

typedef struct __attribute__ ((packed)) {
    componentCodeWasteLiving_t componentWaste;
} excretionGasLiving_t;


typedef enum CODE_ENERGY  energyCodeNeedLiving_t[ ENERGY_NEED_LIVING ];

typedef struct __attribute__ ((packed)) {
    energyCodeNeedLiving_t energyNeed;
} uptakeEnergyLiving_t;

// ��������� ������� (��. ���� - �������� �������)
typedef enum CODE_ENERGY  energyCodeWasteLiving_t[ ENERGY_WASTE_LIVING ];

typedef struct __attribute__ ((packed)) {
    energyCodeWasteLiving_t energyWaste;
} excretionEnergyLiving_t;

typedef struct __attribute__ ((packed)) {
    /**
    * ��� ������ �����.
    */
    codePartLiving_t code;

    /**
    * ����� ������ ����� ������������ ����� ����� �����, �����.
    *   # ������ <= 1.0.
    *   # ����� ���� ������� ����� ������ ���� <= 1.0.
    *   # ���� ����� ������ = 0.0, ������� ����� ��������������
    *     ���������� ����� ����� �������� � ������� ������ (�����
    *     �������� ����� ������ � 1.0).
    */
    cl_float mass;

    /**
    * �� ����� ����������� ������� ����� �����.
    * �������� ���� (�� ����� ����� ������), ����� = 1.0.
    * ��������: ����, ����� (����), ����, �������� (������, �������).
    */
    compositionPortionLiving_t composition;


    /**
    * �������������� ������ � ����������� �� ��� ����������������.
    *   # ����� ����� �������� ����� ����. ���������.
    *   # ������� �������� ������� ������������ ������ FPL_*.
    */

    /**
    * ����� ������� ��������� �����, ��� �������� ��� �����
    * (������� ������������ FPL_*).
    */
    cl_ulong function;


    // ����������� ����� � ������ ������.
    // ������� � "function" � � ����� �����.


    // ���������� ����������� (��. ���� - ��������)
    //   # ������� ������ ���������� ��������� �� ����������� ��������� �������
    //     ���������� ��� ��������.
    // �� ������� ����������.


    // �������� ����������� (��. ���� - ����������)
    // ������������� ������ �����������, ������� ����� �������� �������
    // �� �����.
    //   # ��� ������ ����������� ������ *�����������* �������� ����������.
    //     ��������� ���-�� ���������� ������������� � ���������� �� �����.
    //   # 1 ���� ������� (CC_AIR) ����� 1.2 ������.
    // ����� ��������� ���������� (����) � �������.
    // ������� = ���������� �������, ������������� ��� �������� ����������.
    // ��� ������ �������� ����������, ����� ����� ����. �������� ����������.
    uptakeSolidLiving_t     uptakeSolid;
    uptakeLiquidLiving_t    uptakeLiquid;
    uptakeGasLiving_t       uptakeGas;


    // ��������� ����������� (��. ���� - ���������� � �������� �����������)
    excretionSolidLiving_t  excretionSolid;
    excretionLiquidLiving_t excretionLiquid;
    excretionGasLiving_t    excretionGas;


    // �������� � ��������� �������
    // ������������� ������ �������, ������� ����� �������� �������
    // �� ���. �����.
    //   # ��� ������ ����������� ������ *�����������* �������� �������.
    //     ��������� ���-�� ������� ������� � ���������� �� �����.
    uptakeEnergyLiving_t    uptakeEnergy;
    excretionEnergyLiving_t excretionEnergy;


    /**
    * �����, ��������� ������ �����.
    *   # ��-�� ������������ �������� �������� ������������ ����, ��� �����
    *     �� ������� "����� �����" (��� ��� ������ "resist"): ��� �����
    *     �������� ���������� ��������.
    */
    attackPartLiving_t attack;


    /**
    * ������ ������ ������������ ����� ������ �����.
    * ��� ������ ����� ������� �� �����������.
    *   # ������ ����� ���� = resist ����� + ������������� ������ ������
    *   # ��� ������������� ������ ������ ������� �� ������� IMMUNE (����������
    *     ������ ��� �����).
    *   # ������ ��� ������ TAL_SHOOT_CRUSH � TAL_SHOOT_PIERCE ��������� �����.
    *     � TAL_CRUSH � TAL_PIERCE.
    */
    resistPartLiving_t resist;

} aboutOnePartLiving_t;

#endif





/**
* ���������� �� �����.
*/
#if 1

// ���������� ���
typedef struct __attribute__ ((packed)) {
    // ����� ����� ����������
    cl_float immovable;
    // ����� �������� � ���������� ���������
    cl_float move;
} noiseLiving_t;

// ����������� � ��������� ������
typedef struct __attribute__ ((packed)) {
    /**
    * ������������ �������� ����������� ����� �� �����������, �������
    * ��� ���� �����.
    * �/�
    * ���������� ���������� ��� ������������� ������������.
    *   # � ������� (�� ������) ��������, �������� �����������
    *     ��������� � 2 ���� �������.
    */
    cl_float speed;

} moveSolidSurfaceLiving_t;

typedef struct __attribute__ ((packed)) {
    cl_float speed;
} moveLiquidSurfaceLiving_t;

typedef struct __attribute__ ((packed)) {
    // �������� ������� ����
    cl_float speedDigBurrow;
    // �������� ����������� �� ������� ����
    cl_float speedInBurrow;
} moveSolidInsideLiving_t;

// �������
typedef struct __attribute__ ((packed)) {
    cl_float speed;
} moveLiquidInsideLiving_t;

// ������
typedef struct __attribute__ ((packed)) {
    cl_float speed;
} moveGasInsideLiving_t;

/**
* *������* ����������, ������� ���������� ����� ��� �����.
* �� / ����
*   # ����������� ���������� �������������� �����, ��� ����������� �������.
*   # ������ "����" ��� ������ ������������� ������������
*     ���-�� �� �����, �� ��� (������� �� �������� �����������).
*
* @see ���������� � ������������� ������� �� ��������� ������ ����� - energyNeed_t.
*/
typedef portionComponent_t  componentPortionNeedLiving_t[ COMPONENT_NEED_LIVING ];


/**
* *������* ����������, ������� �������� ����� ��� �����������������.
* �� / ����
*   # ���������� ���������� �������������� �����, ��� ���������� �������.
*   # ������ "����" ��� ������ ������������� �����������
*     ���-�� �� �����, �� ��� (������� �� �������� �����������).
*
* @see ���������� � ������������� ������� �� ��������� ������ ����� - energyWaste_t.
*/
typedef portionComponent_t  componentPortionWasteLiving_t[ COMPONENT_WASTE_LIVING ];


/**
* ������� �����.
*   # �.�. ������� �������, ���������� �� ����� �� ��������.
*   # ������������� ������� �� ���������� ����� ����� (��. LIFE_CYCLE):
*     0    ��������, ������.  - ����� ��������������� ����� ����� � ���� ��������� �����
*     1    ����, ������.      - ����� ��������������� ����� ����� � ���� ��������� �����
*     2    ��������.          - �������� ������� ��� �������� �����
*     3    �������.           - ����� ��������������� ����� ����� � ���� ��������� �����
*     4    ̸����� �����.     - �� ������� �������
*     5    ����������� �����. - ��� ��� ��������
*
* @see CODE_ENERGY
*/

/**
* �������������� �������, ����������� ����� ��� ����������� �����,
* �� ����������� �������, ���������� �� ����������� ����
* (���. �����������). ������ ������� ����� ����������
* ������ � ���� ����� (��. ����).
* ������ / ����
*
* @see CODE_ENERGY
*/
typedef portionEnergy_t  energyPortionNeedLiving_t[ ENERGY_NEED_LIVING ];

/**
* �������, ���������� ������ � �������� ����� �����������������.
* ������ / ����
*
* @see CODE_ENERGY
*/
typedef portionEnergy_t  energyPortionWasteLiving_t[ ENERGY_WASTE_LIVING ];


/**
* ���������� �����.
*/
typedef struct __attribute__ ((packed)) {
    componentPortionNeedLiving_t   componentNeed;
    componentPortionWasteLiving_t  componentWaste_t;

    energyPortionNeedLiving_t      energyNeed;
    energyPortionWasteLiving_t     energyWaste;

} metabolismLiving_t;


/**
* ������� ��������� ������ �����.
*/

typedef struct __attribute__ ((packed)) {

    enum CODE_COMPONENT code;
    
    /**
    * �������� ���������� ��� �����.
    */
    enum CRITERIA importance;

} preferComponentLiving_t;


typedef struct __attribute__ ((packed)) {
    /**
    * ���������� �����������, �������.
    * [ K0; + ]
    */
    float temperature;

    /**
    * ������������ ������, � ������� ����� ��������� ���� ���������.
    * ������ � ����������: ����� �������� �� ������ �����������,
    * ���. �������, ������� - �� ��� ����� ��������� ��� ����������
    * ������.
    */
    enum CODE_BIOME  biome[ BIOME_COMFORT_SURVIVOR_LIVING ];

} comfortLiving_t;


typedef struct __attribute__ ((packed)) {
    /**
    * � ����� ������ ����� ���� �����.
    *   # ����� �������� �������� ����������� ��� �� HL_*.
    *   # � ����� ������ ������ ����� ��������.
    *
    * ��������, ���� ����� ����� ���� �� ������� ������������ �
    * ������ ���� (�������, ��������� ��������), �����:
    *   HL_GAS | HL_SOLID
    * ���� ����� �������� ������ � ������ ����� (�����):
    *   HL_SOLID
    *
    * @see http://crawl.chaosforge.org/index.php?title=Habitat
    */
    cl_uint  habitat[ HABITAT_SURVIVOR_LIVING ];

    /**
    * ��������� �������� ��� �����.
    */
    comfortLiving_t comfort;

    /**
    * ������������������� �����.
    * ��� �������������� ������ �������� ����� ������������� �����
    * ������ ��������� ������������� �. �. ����� / ���� / ������.
    *
    * �� ���� ���-�� ������� "�������� ��������".
    * ��������, ����� ������������������� == 0.3, ��� ��������,
    * ��� ����� �������� ��������� ���� � ��������� ����������
    * [ t + t * 0.3 * k); t - t * 0.3 * k ], ��� t - ����������� ��������
    * �����, k - ����. ����. ��������������.
    * ������ ���� ���������� ��������� - ���������, ������ � ��. -
    * ������������ ��� �� �������.
    *
    * ( 0.0; + ]
    */
    float adaptability;

    /**
    * �������������� / ����������� ���������� ��� ����� �����.
    * ��������, ��������� ����� ����� ���� ��������� � �����, ���-�� -
    * �� ������, ����-�� ��� ����� ���������� ����.
    */
    // @todo preferComponentLiving_t  component[ PREFER_COMPONENT_SURVIVOR_LIVING ];

} survivorLiving_t;


typedef struct __attribute__ ((packed)) {
    /**
    * ��� ���� �����.
    */
    enum CODE_LIVING code;


    /**
    * ������ �����.
    */
    enum SIZE_LIVING size;


    /**
    * ����� ����� �������� ���������� ����� "countByAge", ��.
    */
    cl_float mass[ LIFE_CYCLE_COUNT ];


    /**
    * ������������ ���������� ������ � 1-� ������.
    * 0 - ���-�� ������ � ������ �� ����������.
    * ��� ���������� ������ ��� ���-�� = 1.
    */
    cl_uint maxGroupSize;


    /**
    * ������ ������ �����.
    * ������ �� ������ � ����� �����.
    *
    * @see ����. � aboutOnePartLiving_t::attack.
    * @see http://crawl.chaosforge.org/index.php?title=Hit_dice
    */
    cl_float hitDice;


    /**
    * ������ ����� �� �����������.
    * ���������� ������� �������� ������ ������ ���� (�������).
    *
    *   # ���������� ���������� �������� AC � MR �� http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # ����� ���������� ������ �� ����� ������������
    *     ����� TAL_MAGIC + FAL_ANY � ��������� MR �� http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # ���� ����� ������� � �����. ���� �����������, �������� ������ <= -1.0.
    *
    * @see ���������� � ������ � aboutOnePartLiving_t::resist.
    * @see ����. � aboutOnePartLiving_t::attack � aboutOnePartLiving_t::resist.
    * @see Armour class > http://crawl.chaosforge.org/index.php?title=AC
    * @see Magic resistance > http://crawl.chaosforge.org/index.php?title=MR
    * @see ���������� > http://crawl.chaosforge.org/index.php?title=AC_calculations
    */
    resistPartLiving_t resist;


    /**
    * ��������� ����� �� ����.
    *   # ��������� ������� ������� � ����� ��������������� �� ���-��
    *     ������������� ������� �����.
    *     @todo extend? ��������� ������ ������ (����� � ���������).
    *
    * @see ���������� > http://crawl.chaosforge.org/index.php?title=Evasion
    */
    cl_float evasion;


    /**
    * ��������� ������ ����� (���������).
    * ������ ���������.
    * ������ �� ����������� ������� ����� ������� �����������.
    *
    * @see Hit points > http://crawl.chaosforge.org/index.php?title=HP
    */
    cl_float vitality;


    /**
    * ��� ������ �����.
    *
    * @see http://crawl.chaosforge.org/index.php?title=Noise
    */
    noiseLiving_t noise;


    /**
    * ����������� ����� � ������ ������.
    *   # �����, ���������� �� �����������, ������� � "function" ������.
    *   # �������� ����������� ����� ����������� ��� ������������ �����
    *     ������� ������, ����������� �� �����������.
    */
    moveSolidSurfaceLiving_t moveSolidSurface;
    moveLiquidSurfaceLiving_t moveLiquidSurface;
    moveSolidInsideLiving_t moveSolidInside;
    moveLiquidInsideLiving_t moveLiquidInside;
    moveGasInsideLiving_t moveGasInside;


    /**
    * �� ����� ������ (�������) ������� �����.
    */
    aboutOnePartLiving_t  part[ PART_LIVING ];


    /**
    * ���������� ���� - TAG_LIVING - � �����.
    */
    cl_ulong tag;


    /**
    * ������� ����� ����� ����� � ���� (�������� -> ������).
    * ��� ����������� � ������ ������ �� ����� ������.
    */
    cl_float lifetime;


    /**
    * ��������� ����� � ��������.
    *
    * @todo ������� ������������ ������� � �����. ������������
    * ���������� � ���� ����� ������� - ��� % ������ (���. �������� 1.0),
    * ������� �������.
    *
    * @todo extend? ��������� ������� �� ���������� ����� ����� LIFE_CYCLE.
    */
    cl_float immunity;


    /**
    * ���������� �����.
    */
    metabolismLiving_t metabolism;


    /**
    * ������� ��������� ������ �����.
    *   # ������� ��������� ��������� ��� ���� ��������� ������ �����.
    */
    survivorLiving_t survivor;

} aboutOneLiving_t;

#endif





/**
* ���������� �� ������.
*   #! � ���� ������ ������ ����� �����. ���� �����.
*/
typedef aboutOneLiving_t  aboutLiving_t[ LIVING_COUNT ];




/**
* ����. ���-�� ������ � ��������� ����������, ������� �����
* *������������* ���������� � 1-� ������ ���������.
*   # �������� � ���-���� ������ �� ����� ����. ����� LIFE_CYCLE.
*/
typedef portionLiving_t  livingCount_t[ LIFE_CYCLE_COUNT ];
typedef livingCount_t    livingCell_t[ LIVING_CELL ];




/**
* ����� ��� (��������, �������� � ��.; ����� - �����).
* ���-�� ������ �� ������� ��������; ������� ������� ����������� �� �����
* 27�27�27 � ������ ���������� ������ ��������� ������� �������� �����
* ������; �.�. *������* ������ ������ ���� �������������� 19683 �������
* ��������.
*/
typedef livingCell_t*  livingContent_t;
typedef struct __attribute__ ((packed)) {
    /**
    * ���-�� ������ � ������.
    * ���-�� ������� ������ ������������ @todo ������� �������� �
    * ����������� ������.
    * ����� ������� �� �������.
    */
    /* - �������� �� ��������� ������ � ����, �.�. OpenCL ��� ������� �������
         ����� �� ����������������.
    typedef livingCell_t content_t[ LIVING_GRID * LIVING_GRID * LIVING_GRID ];
    */
    livingContent_t content;

} living_t;





#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
