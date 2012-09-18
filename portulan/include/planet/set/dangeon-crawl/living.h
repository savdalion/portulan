#pragma once

#include "structure.h"
#include "component.h"


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

/**
* ������������ ����� � ������ ������ ����
* GROUP_ELEMENT::GE_LIVING.
*
*   # ��������, ���������, �������� � ��. �������� ������ ��������� "�������".
*   #! ��������� ������ ������ �����. ������� � ������ aboutLiving_t.
*
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
*/
enum CODE_LIVING {
    // ��� ����������� ��� �� ��������
    CL_NONE = 0,

    // @see http://koti.welho.com/jarmoki/crawl/monsters/worker_ant.html
    CL_WORKER_ANT = 1

    /* - @todo ...
    // ����� (����������)
    CL_FLOWER,

    // ������� (����������)
    //  - ����������
    //  - �������
    //  - �������
    CL_TREE_TINY,
    CL_TREE_AVERAGE,
    CL_TREE_HIGH
    */
};





/**
* ��� �������� (����������, �����) � �������� ���� � ����� �������� ���
* ���������� ��������.
*
* ��������: ������� = 0.2, ������� = 0.1, ����� = 0.7.
* ��������: ������� = 6e6, ������� = 3e3, ����� = 4e4.
*/
typedef struct {
    CODE_LIVING code;
    cl_float count;
} portionLiving_t;






/**
* ������������ ����� ������ ���� ����� �������.
*/
enum COMMON_PART_LIVING {
    // ������ ����� ��� ����� �� ����������
    // ������������ ��� �������, ��� ����� �� ��������� �� � ������
    // ������� ������
    CPL_NONE = 0,

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
    CPL_LEG
    /* - @todo extend ���������� ������ �������� �� ����� ���������� ���������.
         ������ �� ����� ����������� � ��� �� ������, ������� ������������
         �� ���. �����.
    // �������� ������
    CPL_VENOM_GLAND
    */
};





/**
* �������������� ������ ����� �� ������������ ���� XYZ.
*   # ����������� ������� ��������� ��� Z, ��� X ���������� ������, Y - �����.
*/
enum LOCUS_X_PART_LIVING {
    LXL_UNDEFINED = 0,
    LXL_LEFT,
    LXL_CENTER,
    LXL_RIGHT,
    // ����� ���������� �� ���� ����� (��������, ����������� ������)
    LXL_EXTENT
};

enum LOCUS_Y_PART_LIVING {
    LYL_UNDEFINED = 0,
    LYL_BOTTOM,
    LYL_CENTER,
    LYL_TOP,
    LYL_EXTENT
};

enum LOCUS_Z_PART_LIVING {
    LZL_UNDEFINED = 0,
    LZL_FAR,
    LZL_CENTER,
    LZL_NEAR,
    LZL_EXTENT
};





/**
* ��� ������ �����.
* ��� ������� �� ��������� ������, ����� ���������� ������. ��������
* ��� ������� �����������.
*/
typedef struct {
    // ����� ����� ����������� �����
    CODE_LIVING specimen;

    // ����� ������
    COMMON_PART_LIVING part;

    // �������������� ������ ������������ �����
    //   # ����� ��������������� ������� �����, ������ � ����������� � �.�.,
    //     ����� � �������� ������������ ������� ����������� ����
    //     ������������.
    //   # ������� �� ����� ������: ��� Z - ��������� �����������, ��� X -
    //     �������, ��� Y - �����.
    LOCUS_X_PART_LIVING lx;
    LOCUS_Y_PART_LIVING ly;
    LOCUS_Z_PART_LIVING lz;

    // ����� ��������� ������ ������� ������
    // ��������: ����, ������.
    COMMON_PART_LIVING inner;

    // ����� ��������� �� ����������� ��� ��������� � ������� ������
    // ��������: ����, ����.
    //   # ���� � ������ ����������� ����. ������� �� ������� �������,
    //     ���� ������������ ����������� ��� ������� �������.
    //   # ���� ��������� ������� �� ������� ������, ���� ������������
    //     ����������� ��� ������� ������. ��. ���� "�������������� ������".
    COMMON_PART_LIVING outer;

} codePartLiving_t;






/**
* ������� ����� ���� �����.
*/
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

// ���������� ������ ����������� ����������� (����, ���)
#define FPL_EAT_SOLID                     (1ULL << 7)
// ���������� ������ ����������� ����������� (����, �����)
#define FPL_EAT_LIQUID                    (1ULL << 8)
// ���������� ������������ ����������� ����������� (������, �����)
#define FPL_EAT_GAS                       (1ULL << 9)
// ���������� ����� (������)
// # ������� �� ��������� ����������������� ���������.
//   ��. ���� "��������� �����".
#define FPL_EAT_NORMAL_LIGHT              (1ULL << 10)

// �������� ������ ����������� ����������� (����)
#define FPL_UPTAKE_SOLID                  (1ULL << 11)
// �������� ������ ����������� ����������� (����)
#define FPL_UPTAKE_LIQUID                 (1ULL << 12)
// �������� ������������ ����������� ����������� (������)
#define FPL_UPTAKE_GAS                    (1ULL << 13)
// �������� ����� (������)
#define FPL_UPTAKE_NORMAL_LIGHT           (1ULL << 14)

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
#define FPL_EMIT_NORMAL_TASTE             (1ULL << 30)
// ������� � ������� �������
#define FPL_EMIT_NORMAL_SMELL             (1ULL << 31)
// ������� � ������� �������������
#define FPL_EMIT_NORMAL_TOUCH             (1ULL << 32)
// ������� � ������� ������ (�������, ����)
#define FPL_EMIT_NORMAL_SOUND             (1ULL << 33)
// ������� � ������� ���������� (���������� �������)
#define FPL_EMIT_NORMAL_VISION            (1ULL << 34)






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
    // ������ ��������
    SL_ATOMIC = 1,
    // �����, ������� ����
    SL_TINY,
    // ���������
    SL_LITTLE,
    // �����������, ��������
    SL_SMALL,
    // ����, �����, ������
    SL_MEDIUM,
    // �����, ����, ��������, ����
    SL_LARGE,
    // ������������ ��������
    SL_BIG,
    // �������
    SL_GIANT,
    // �������
    SL_HUGE
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
    HL_UNDEAD
};





/**
* ���������� ���� � �����.
* �� ���� ����� ������������ ������ - porte - ����� �������
* ����������� �������.
*//* - �������� �� define. ��. ����.
enum TAG_LIVING {
*/

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
    TAL_MAGIC
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
    FAL_VAMPIRIC_DRAINING
};




/**
* ��������� ��� �������� ����� �����.
* ������ � ����� � ������ ����� ������� ���� �����.
* 
*   # ���� ����� - ��� ���������� ���������� �������� Damage ��
*     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
*/
typedef struct {
    TYPE_ATTACK_LIVING     type;
    FLAVOUR_ATTACK_LIVING  flavour;
    cl_float               force;
} aboutOnePartAttack_t;



/**
* �����, ��������� ������ �����.
*/
typedef aboutOnePartAttack_t  attackPartLiving_t[ ATTACK_PART_LIVING_COUNT ];





/**
* ��������� ��� �������� ������ �����.
* ������ � ����� � ������ ����� ������� ���� ������ �� ���� �����.
* 
*   # ���� ������ - ��� ���������� ���������� �������� AC � MR ��
*     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
*/
typedef struct {
    TYPE_ATTACK_LIVING     type;
    FLAVOUR_ATTACK_LIVING  flavour;
    cl_float               force;
} aboutOnePartResist_t;



/**
* ������ �� ��������� ����.
*/
typedef aboutOnePartResist_t  resistPartLiving_t[ RESIST_PART_LIVING_COUNT ];





/**
* ���������� �� ������ �����.
*   # ������ ������ ����� ������������ �������� ����� ����� � ������ ������.
*/
typedef struct {
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
    typedef component::portionComponent_t  composition_t[ COMPONENT_COMPOSITION_LIVING ];
    composition_t composition;


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
    //   # ��� ������ ����������� ������ *�����������* �������� ����������.
    //     ��������� ���-�� ���������� ������� � ���������� �� �����.
    //   # 1 ���� ������� (CC_AIR) ����� 1.2 ������.
    // ����� ��������� ���������� (����) � �������.
    // ������� = ���������� �������, ������������� ��� �������� ����������.
    // ��� ������ �������� ����������, ����� ����� ����. �������� ����������.
    typedef component::CODE_COMPONENT  componentNeed_t[ COMPONENT_NEED_LIVING ];
    typedef struct {
        componentNeed_t componentNeed;
        cl_float efficiency;
    } uptakeSolid_t;
    uptakeSolid_t uptakeSolid;
    
    typedef struct {
        componentNeed_t componentNeed;
        cl_float efficiency;
    } uptakeLiquid_t;
    uptakeLiquid_t uptakeLiquid;

    typedef struct {
        componentNeed_t componentNeed;
        cl_float efficiency;
    } uptakeGas_t;
    uptakeGas_t uptakeGas;

    typedef struct {
        cl_float efficiency;
    } uptakeNormalLight_t;
    uptakeNormalLight_t uptakeNormalLight;


    // ��������� ����������� (��. ���� - ���������� � �������� �����������)
    typedef component::CODE_COMPONENT  componentWaste_t[ COMPONENT_WASTE_LIVING ];
    typedef struct {
        componentWaste_t componentWaste;
    } excretionSolid_t;
    excretionSolid_t excretionSolid;

    typedef struct {
        componentWaste_t componentWaste;
    } excretionLiquid_t;
    excretionLiquid_t excretionLiquid;

    typedef struct {
        componentWaste_t componentWaste;
    } excretionGas_t;
    excretionGas_t excretionGas;


    // ���������� � �������� ������� (��. ���� - ��������� �������)
    //   # ��� ������ ����������� ������ *�����������* �������� �������.
    //     ��������� ���-�� ������� ������� � ���������� �� �����.
    typedef component::CODE_ENERGY  energyNeed_t[ ENERGY_NEED_LIVING ];
    typedef struct {
        energyNeed_t energyNeed;
    } uptakeEnergy_t;
    uptakeEnergy_t uptakeEnergy;

    // ��������� ������� (��. ���� - �������� �������)
    typedef component::CODE_ENERGY  energyWaste_t[ ENERGY_WASTE_LIVING ];
    typedef struct {
        energyWaste_t energyWaste;
    } excretionEnergy_t;
    excretionEnergy_t excretionEnergy;


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






/**
* ���������� �� �����.
*/
typedef struct {
    /**
    * ��� ���� �����.
    */
    CODE_LIVING code;


    /**
    * ������ �����.
    */
    SIZE_LIVING size;


    /**
    * ����� ����� �������� ���������� ����� "countByAge", ��.
    */
    cl_float mass[ LIFE_CYCLE ];


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
    typedef struct {
        // ����� ����� ����������
        cl_float immovable;
        // ����� �������� � ���������� ���������
        cl_float move;
    } noise_t;
    noise_t noise;


    /**
    * ����������� ����� � ������ ������.
    *   # �����, ���������� �� �����������, ������� � "function" ������.
    *   # �������� ����������� ����� ����������� ��� ������������ �����
    *     ������� ������, ����������� �� �����������.
    */
    typedef struct {
        /**
        * ������������ �������� ����������� ����� �� �����������, �������
        * ��� ���� �����.
        * �/�
        * ���������� ���������� ��� ������������� ������������.
        *   # � ������� (�� ������) ��������, �������� �����������
        *     ��������� � 2 ���� �������.
        */
        cl_float speed;

    } moveSolidSurface_t;
    moveSolidSurface_t moveSolidSurface;

    typedef struct {
        cl_float speed;
    } moveLiquidSurface_t;
    moveLiquidSurface_t moveLiquidSurface;

    typedef struct {
        // �������� ������� ����
        cl_float speedDigBurrow;
        // �������� ����������� �� ������� ����
        cl_float speedInBurrow;
    } moveSolidInside_t;
    moveSolidInside_t moveSolidInside;

    typedef struct {
        cl_float speed;
    } moveLiquidInside_t;
    moveLiquidInside_t moveLiquidInside;

    typedef struct {
        cl_float speed;
    } moveGasInside_t;
    moveGasInside_t moveGasInside;


    /**
    * �� ����� ������ (�������) ������� �����.
    */
    aboutOnePartLiving_t  part[ PART_LIVING_COUNT ];


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
    * *������* ����������, ������� ���������� ����� ��� �����.
    * �� / ����
    *   # ����������� ���������� �������������� �����, ��� ����������� �������.
    *   # ������ "����" ��� ������ ������������� ������������
    *     ���-�� �� �����, �� ��� (������� �� �������� �����������).
    *
    * @see ���������� � ������������� ������� �� ��������� ������ ����� - energyNeed_t.
    */
    typedef component::portionComponent_t  componentNeed_t[ COMPONENT_NEED_LIVING ];


    /**
    * *������* ����������, ������� �������� ����� ��� �����������������.
    * �� / ����
    *   # ���������� ���������� �������������� �����, ��� ���������� �������.
    *   # ������ "����" ��� ������ ������������� �����������
    *     ���-�� �� �����, �� ��� (������� �� �������� �����������).
    *
    * @see ���������� � ������������� ������� �� ��������� ������ ����� - energyWaste_t.
    */
    typedef component::portionComponent_t  componentWaste_t[ COMPONENT_WASTE_LIVING ];


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
    typedef component::portionEnergy_t  energyNeed_t[ ENERGY_NEED_LIVING ];

    /**
    * �������, ���������� ������ � �������� ����� �����������������.
    * ������ / ����
    *
    * @see CODE_ENERGY
    */
    typedef component::portionEnergy_t  energyWaste_t[ ENERGY_WASTE_LIVING ];


    /**
    * ���������� �����.
    */
    typedef struct {
        componentNeed_t   componentNeed;
        componentWaste_t  componentWaste_t;

        energyNeed_t      energyNeed;
        energyWaste_t     energyWaste;

    } metabolism_t;

    metabolism_t metabolism;


    /**
    * ������� ��������� ������ �����.
    */
    typedef struct {
        /**
        * � ����� ������ ����� ���� �����.
        *   # ����� �������� �������� ����������� ��� �� HL_*.
        *   # � ����� ������ ������ ����� ��������.
        *
        * ��������, ���� ����� ����� ���� �� ������� ������������ �
        * ������ ����, �����:
        *   HL_GAS | HL_SOLID
        * ���� ����� �������� ������ � ������ ����� (�����):
        *   HL_SOLID
        *
        * @see http://crawl.chaosforge.org/index.php?title=Habitat
        */
        cl_uint  habitat[ HABITAT_LIVING_COUNT ];

        /**
        * �������� ���������� � ������� �������� ���� ����� ��������
        * ���������� ����� "countByAge".
        */
        typedef struct {
            /**
            * ����������� ��������.
            * ��� ����� ��������� - ���������� ���������� � ����������
            * ����������� ������.
            * ��� �������������� ������ �������� ����� ������������� �����
            * ������ ��������� ������������� �. �. ����� / ���� / ������.
            */
            typedef struct {
                cl_float min;
                cl_float max;
            } comfort_t;
            comfort_t comfort;

            /**
            * ����������� ���������.
            * ������������� ����� ��� ����� ������� ����������
            * (100% ��������� ����� �� 1 �����).
            */
            typedef struct {
                cl_float min;
                cl_float max;
            } limit_t;
            limit_t limit;

        } temperatureRange_t;

        temperatureRange_t temperatureRange;

    } survivor_t;

    //   # ������� ��������� ��������� ��� ���� ��������� ������ �����.
    survivor_t survivor;

} aboutOneLiving_t;




/**
* ���������� �� ������.
*   #! � ���� ������ ������ ����� �����. ���� �����.
*/
typedef aboutOneLiving_t  aboutLiving_t[ LIVING_COUNT ];



/**
* ����. ���-�� ������ � ��������� ����������, ������� ���������
* � ������� ������� (� ���������). ��� ������ ������������ ��� ������������
* ������� �������� � ������� �������.
*/
typedef struct {
    CODE_LIVING code;
    // ����� ������ � ������� �������
    cl_float count;
    // ���. � ����. ���-�� ������ � ������;
    // ��� ���-�� ���������� ������� ��������� ������� �������
    cl_float minGroup;
    cl_float maxGroup;
} portionLivingWithQtyGroup_t;
typedef portionLivingWithQtyGroup_t  livingAll_t[ LIVING_COUNT ];



/**
* ����. ���-�� ������ � ��������� ����������, ������� �����
* *������������* ���������� � 1-� ������ ���������.
*   # �������� � ���-���� ������ �� ����� ����. ����� LIFE_CYCLE.
*/
typedef portionLiving_t  livingCount_t[ LIFE_CYCLE ];
typedef livingCount_t    livingCell_t[ LIVING_CELL ];



/**
* ����� ��� (��������, �������� � ��.; ����� - �����).
* ���-�� ������ �� ������� ��������; ������� ������� ����������� �� �����
* 27�27�27 � ������ ���������� ������ ��������� ������� �������� �����
* ������; �.�. *������* ������ ������ ���� �������������� 19683 �������
* ��������.
*/
typedef struct {
    /**
    * ���-�� ������ � ������.
    * ���-�� ������� ������ ������������ @todo ������� �������� �
    * ����������� ������.
    * ����� ������� �� �������.
    */
    typedef livingCell_t content_t[ LIVING_GRID * LIVING_GRID * LIVING_GRID ];
    content_t content;

} living_t;



                } // living
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
