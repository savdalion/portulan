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
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
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

// ����������� �����
//   # ����� �� �������������, ���� �� ������ ���� �� ���� �� ����� ����.
// ����������������� �����������
#define TL_DAMAGE_REGENERATION     (1ULL << 2)

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
    // ��������� ����� ���������
    TAL_SHOOT_CRUSH,
    // ��������� ����� (��������, ������� ���� / ������� / ��������)
    TAL_SHOOT_GAS,
    // ��������� ��������� (��������, �������)
    TAL_SHOOT_LIQUID,
    // ��������� ������ (�������������) ���������
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
    //   # ����� ���������� ��������
    //     http://crawl.chaosforge.org/index.php?title=Poison#Poison_Types
    //       10 - ������� (regular)
    //       20 - ������� (medium)
    //       40 - ������� (strong)
    //       80 - ������� (nasty)
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
} aboutAttack_t;



/**
* �����, ��������� �����.
*/
typedef aboutAttack_t  attackLiving_t[ ATTACK_PART_LIVING ];





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
} aboutResist_t;



/**
* ������ �� ��������� ����.
*/
typedef aboutResist_t  resistLiving_t[ RESIST_PART_LIVING ];




/**
* �� ����� ����������� ������� �����.
*/
typedef portionComponent_t  compositionPortionLiving_t[ COMPONENT_COMPOSITION_LIVING ];




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
    * �������� ����������� ����� �� �����������, �/�.
    * ���������� ���������� ��� ������������� ������������.
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


// @see struct planet::l0::topology_t
typedef struct __attribute__ ((packed)) {
    /**
    * ���������� �����������, �������.
    * [ K0; + ]
    */
    cl_float temperature;

    /**
    * ���������� ���-�� ����������� �������.
    */
    cl_float rainfall;

    /**
    * ���������� ������.
    */
    cl_float drainage;

    /**
    * ���������� ���������.
    */
    cl_float illuminance;

    // @todo extend �������� ��� �������������� �� planet::l0::topology_t.

    /**
    * ������������ ������, � ������� ����� ��������� ���� ���������.
    * ������ � ����������: ����� �������� �� ������ �����������,
    * ���. �������, ������� - �� ��� ����� ��������� ��� ����������
    * ������.
    *//* - �������� ������������� ������. ��. ����.
    enum CODE_BIOME  biome[ BIOME_COMFORT_SURVIVOR_LIVING ];
    */

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
    cl_float adaptability;

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
    * �����, ��������� �����.
    *   # ��-�� �������� �������� ������������ ����, ��� ����� �� �������
    *     "����� �����" (��� ��� ������ "resist"): ��� ����� ��������
    *     ���������� ��������.
    */
    attackLiving_t  attack;


    /**
    * ������ ����� �� �����������.
    *
    *   # ���������� ���������� �������� AC � MR ��
    *     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # ����� ���������� ������ �� ����� ������������
    *     ����� TAL_MAGIC + FAL_ANY � ��������� MR ��
    *     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # ���� ����� ������� � �����. ���� �����������, �������� ������ <= -1.0.
    *
    * @see ���������� � ������ � aboutOnePartLiving_t::resist.
    * @see ����. � aboutOnePartLiving_t::attack � aboutOnePartLiving_t::resist.
    * @see Armour class > http://crawl.chaosforge.org/index.php?title=AC
    * @see Magic resistance > http://crawl.chaosforge.org/index.php?title=MR
    * @see ���������� > http://crawl.chaosforge.org/index.php?title=AC_calculations
    */
    resistLiving_t resist;


    /**
    * ��������� ����� �� ����.
    *
    * @see ���������� > http://crawl.chaosforge.org/index.php?title=Evasion
    */
    cl_float evasion;


    /**
    * ��������� ������ ����� (���������).
    * ������ ���������.
    * ������ �� ����������� ����� ������� �����������.
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
    *   # ������������� �������� �������� ��������, ��� ����� �� �����
    *     ������������ � �������� �����.
    */
    moveSolidSurfaceLiving_t   moveSolidSurface;
    moveLiquidSurfaceLiving_t  moveLiquidSurface;
    moveSolidInsideLiving_t    moveSolidInside;
    moveLiquidInsideLiving_t   moveLiquidInside;
    moveGasInsideLiving_t      moveGasInside;


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
    * ������� �������� �������.
    *
    * @todo extend? ��������� ������� �� ���������� ����� ����� LIFE_CYCLE.
    */
    cl_float immunity;


    /**
    * �� ����� ����������� ������� �����.
    * ��������: ����, ����� (����), ����, �������� (������, �������).
    */
    compositionPortionLiving_t composition;


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
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
