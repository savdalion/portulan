#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"
#include "biome.h"


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
#endif


/**
* Перечисление кодов в группе живого мира
* GROUP_ELEMENT::GE_LIVING.
*
*   # Животные, насекомые, растения и др. подобные группы именуются "особями".
*   #! Нумерация особей должна соотв. индексу в списке aboutLiving_t.
*
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
*/
#undef CL_NONE
enum CODE_LIVING {
    // код отсутствует или не определён
    CL_NONE = 0,

    // любая особь
    CL_ANY = CL_NONE,

    // @see living-set.h

    // рабочий муравей
    CL_WORKER_ANT,

    // пастбищная трава
    CL_GRAMA,

    // последний
    CL_last
};





/**
* Код особи, общее кол-во особей.
*   # Кол-во групп особей определяется по кол-ву особей и
*     размеру групп из декларации aboutOneLiving_t.
*
* Например: муравьи = 6e6, деревья = 3e3, цветы = 4e4.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING code;
    cl_float count;
} portionLiving_t;





/**
* Среды обитания - HABITAT_LIVING - особи.
*/
#define HL_SOLID   (1U << 0)
#define HL_LIQUID  (1U << 1)
#define HL_GAS     (1U << 2)
#define HL_PLASM   (1U << 3)







/**
* Размер особи.
*/
enum SIZE_LIVING {
    // ~0.01-0.2 м:  семена, плоды растений
    SL_ATOMIC = 1,

    // ~0.2-0.3 м:  крысы, летучие мыши
    SL_TINY,

    // ~0.3-0.6 м:  спригганы
    SL_LITTLE,

    // ~0.6-1.2 м:  муравьи, полурослики, кобольды
    SL_SMALL,

    // ~1.2-2.0 м:  люди, эльфы, дварфы
    SL_MEDIUM,

    // ~2.0-3.0 м:  троли, огры, кентавры, наги
    SL_LARGE,

    // ~3.0-4.0 м:  четвероногие животные
    SL_BIG,

    // ~4.0-6.0 м:  гиганты
    SL_GIANT,

    // ~6.0-9.0 м:  драконы
    SL_HUGE,

    // последний
    SL_last
};





/**
* Праведность.
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

    // последний
    HL_last
};





/**
* Уточняющие теги к особи.
* По этим тегам динамический движок - porte - может строить
* собственные решения.
*//* - Заменено на define. См. ниже.
enum TAG_LIVING {
*/
#if 1

// теплокровная особь
#define TL_WARM_BLOODED            (0ULL)

// холоднокровная особь
#define TL_COLD_BLOODED            (1ULL << 1)

// регенерация особи
//   # Особь не регениерирует, если не указан хотя бы один из тегов ниже.
// восстанавливаются повреждения
#define TL_DAMAGE_REGENERATION     (1ULL << 2)

#endif




/**
* Тип атаки особи.
*
* @see http://crawl.chaosforge.org/index.php?title=Attack_type
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_flags_by_name.html
*/
enum TYPE_ATTACK_LIVING {
    // нет атаки (служит признаком завершения списка атак)
    TAL_NONE = 0,

    // любая атака (исп. для задания защиты от атак, поиска атак в паре тип + вкус)
    TAL_ANY = 1,

    // раздробить, нанести тупой удар
    TAL_CRUSH,
    // порезать, нанести режущий удар, перекусить клешнями
    TAL_CUTTING,
    // разорвать когтями, руками
    TAL_CLAW,
    // сжать / душить руками, клешнями, щупальцами
    TAL_CONSTRICT,
    // поглотить
    TAL_ENGULF,
    // пронзить, нанести колющий удар
    TAL_PIERCE,

    // выстрелить, метнуть, брызнуть, плюнуть, выдохнуть в заданном направлении
    // @see TAL_MAGIC
    // @see Соглашение о защите в aboutOnePartLiving_t::resist.
    // попадание тупым предметом
    TAL_SHOOT_CRUSH,
    // попадание газом (например, дыхание огнём / холодом / брызгами)
    TAL_SHOOT_GAS,
    // попадание жидкостью (например, кислота)
    TAL_SHOOT_LIQUID,
    // попадание острым (пронизывающим) предметом
    TAL_SHOOT_PIERCE,

    // прикоснуться (см. "вкус атаки")
    TAL_TOUCH,
    // толкнуть
    TAL_TRAMPLE,

    // провести магическую атаку
    //   #! Маг. атака - это атака, не требущая физ. контакта с целью. Т.е.,
    //     "магия" - это возможность донести вкус атаки (см. ниже) до цели без
    //     необходимости каким-либо образом касаться цели.
    // @see TAL_SHOOT
    TAL_MAGIC,

    // последний
    TAL_last
};




/**
* Вкус атаки.
*
* @see http://crawl.chaosforge.org/index.php?title=Attack_flavour
*/
enum FLAVOUR_ATTACK_LIVING {
    // нет вкуса, простая атака
    FAL_PLAIN = 0,
    FAL_NONE = FAL_PLAIN,

    // любая атака (исп. для задания защиты от атак, поиска атак в паре тип + вкус)
    FAL_ANY = FAL_PLAIN,

    // действие кислотой
    FAL_ACID,

    // телепортировать близко
    FAL_BLINK,

    // действие холодом
    FAL_COLD,

    // сбить с толку
    FAL_CONFUSE,

    // действие электричеством
    FAL_ELECTRICITY,

    // действие огнём
    FAL_FIRE,

    // действие адским огнём
    FAL_HELLFIRE,

    // действие святым словом
    FAL_HOLYWORD,

    // действие отрицательной энергией
    FAL_NEGATIVE,

    // парализовать
    FAL_PARALYZE,

    // отравить
    //   # Шкала отравлений согласно
    //     http://crawl.chaosforge.org/index.php?title=Poison#Poison_Types
    //       10 - обычная (regular)
    //       20 - средняя (medium)
    //       40 - сильная (strong)
    //       80 - мерзкая (nasty)
    FAL_POISON,

    // лечит атакующего на 1d(нанесённое повреждение)
    FAL_VAMPIRIC_DRAINING,

    // последний
    FAL_last
};




/**
* Структура для описания атаки особи.
* Наряду с типом и вкусом атаки задаётся сила атаки.
* 
*   # Сила атаки - это творческая компиляция значения Damage из
*     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
*/
typedef struct __attribute__ ((packed)) {
    enum TYPE_ATTACK_LIVING     type;
    enum FLAVOUR_ATTACK_LIVING  flavour;
    cl_float                    force;
} aboutAttack_t;



/**
* Атаки, известные особи.
*/
typedef aboutAttack_t  attackLiving_t[ ATTACK_PART_LIVING ];





/**
* Структура для описания защиты особи.
* Наряду с типом и вкусом атаки задаётся сила защиты от этой атаки.
* 
*   # Сила защиты - это творческая компиляция значений AC и MR из
*     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
*/
typedef struct __attribute__ ((packed)) {
    enum TYPE_ATTACK_LIVING     type;
    enum FLAVOUR_ATTACK_LIVING  flavour;
    cl_float                    force;
} aboutResist_t;



/**
* Защиты от известных атак.
*/
typedef aboutResist_t  resistLiving_t[ RESIST_PART_LIVING ];




/**
* Из каких компонентов состоит особь.
*/
typedef portionComponent_t  compositionPortionLiving_t[ COMPONENT_COMPOSITION_LIVING ];




/**
* Информация об особи.
*/
#if 1

// издаваемый шум
typedef struct __attribute__ ((packed)) {
    // когда стоит неподвижно
    cl_float immovable;
    // когда движется с нормальной скоростью
    cl_float move;
} noiseLiving_t;

// перемещение в различных средах
typedef struct __attribute__ ((packed)) {
    /**
    * Скорость перемещения особи по поверхности, м/с.
    * Определяет инициативу при моделировании столкновений.
    */
    cl_float speed;

} moveSolidSurfaceLiving_t;

typedef struct __attribute__ ((packed)) {
    cl_float speed;
} moveLiquidSurfaceLiving_t;

typedef struct __attribute__ ((packed)) {
    // скорость копания норы
    cl_float speedDigBurrow;
    // скорость перемещения по готовой норе
    cl_float speedInBurrow;
} moveSolidInsideLiving_t;

// плавает
typedef struct __attribute__ ((packed)) {
    cl_float speed;
} moveLiquidInsideLiving_t;

// летает
typedef struct __attribute__ ((packed)) {
    cl_float speed;
} moveGasInsideLiving_t;

/**
* *Разные* компоненты, которые необходимы особи для жизни.
* кг / день
*   # Необходимые компоненты распределяются также, как необходимые энергии.
*   # Выбран "день" для гибкой аппроксимации необходимого
*     кол-ва на пульс, на ход (зависит от скорости перемещения).
*
* @see Соглашения о распределении энергий по жизненным циклам особи - energyNeed_t.
*/
typedef portionComponent_t  componentPortionNeedLiving_t[ COMPONENT_NEED_LIVING ];


/**
* *Разные* компоненты, которые выделяет особь при жизнедеятельности.
* кг / день
*   # Выделяемые компоненты распределяются также, как выделяемые энергии.
*   # Выбран "день" для гибкой аппроксимации выделяемого
*     кол-ва на пульс, на ход (зависит от скорости перемещения).
*
* @see Соглашения о распределении энергий по жизненным циклам особи - energyWaste_t.
*/
typedef portionComponent_t  componentPortionWasteLiving_t[ COMPONENT_WASTE_LIVING ];


/**
* Энергии особи.
*   # Т.к. энергий немного, закрепляем их жёстко по индексам.
*   # Распределение энергии по жизненному циклу особи (см. LIFE_CYCLE):
*     0    Эмбрионы, семена.  - прямо пропорционально массе особи в этом жизненном цикле
*     1    Дети, ростки.      - прямо пропорционально массе особи в этом жизненном цикле
*     2    Взрослые.          - значение указано при создании особи
*     3    Старики.           - прямо пропорционально массе особи в этом жизненном цикле
*     4    Мёртвые особи.     - не требуют энергий
*     5    Бессмертные особи. - как для взрослых
*
* @see CODE_ENERGY
*/

/**
* Дополнительная энергия, необходимая особи для поддержания жизни,
* за исключением энергии, выделяемой от потребления пищи
* (хим. компонентов). Лишняя энергия может выделяться
* особью в виде тепла (см. ниже).
* едениц / день
*
* @see CODE_ENERGY
*/
typedef portionEnergy_t  energyPortionNeedLiving_t[ ENERGY_NEED_LIVING ];

/**
* Энергия, выделяемая особью в процессе своей жизнедеятельности.
* едениц / день
*
* @see CODE_ENERGY
*/
typedef portionEnergy_t  energyPortionWasteLiving_t[ ENERGY_WASTE_LIVING ];


/**
* Метаболизм особи.
*/
typedef struct __attribute__ ((packed)) {
    componentPortionNeedLiving_t   componentNeed;
    componentPortionWasteLiving_t  componentWaste_t;

    energyPortionNeedLiving_t      energyNeed;
    energyPortionWasteLiving_t     energyWaste;

} metabolismLiving_t;


/**
* Условия выживания данной особи.
*/

typedef struct __attribute__ ((packed)) {

    enum CODE_COMPONENT code;
    
    /**
    * Важность компонента для особи.
    */
    enum CRITERIA importance;

} preferComponentLiving_t;


// @see struct planet::l0::topology_t
typedef struct __attribute__ ((packed)) {
    /**
    * Комфортная температура, Цельсий.
    * [ K0; + ]
    */
    cl_float temperature;

    /**
    * Комфортное кол-во атмосферных осадков.
    */
    cl_float rainfall;

    /**
    * Комфортный дренаж.
    */
    cl_float drainage;

    /**
    * Комфортное освещение.
    */
    cl_float illuminance;

    // @todo extend Включить все характеристики из planet::l0::topology_t.

    /**
    * Перечисление биомов, в которых особь чувствует себя комфортно.
    * Помним и используем: биомы строятся на основе температуры,
    * атм. осадков, дренажа - всё это можно проверять при расселении
    * особей.
    *//* - Заменено составляющими биомов. См. выше.
    enum CODE_BIOME  biome[ BIOME_COMFORT_SURVIVOR_LIVING ];
    */

} comfortLiving_t;


typedef struct __attribute__ ((packed)) {
    /**
    * В каких средах может жить особь.
    *   # Среды обитания задаются комбинацией бит из HL_*.
    *   # В любых других средах особь погибает.
    *
    * Например, если особь может жить на границе газообразной и
    * твёрдой сред (муравьи, некоторые растения), пишем:
    *   HL_GAS | HL_SOLID
    * Если жизнь возможна только в твёрдой среде (кроты):
    *   HL_SOLID
    *
    * @see http://crawl.chaosforge.org/index.php?title=Habitat
    */
    cl_uint  habitat[ HABITAT_SURVIVOR_LIVING ];

    /**
    * Состояние комфорта для особи.
    */
    comfortLiving_t comfort;

    /**
    * Приспосабливаемость особи.
    * Для цивилизованных особей диапазон может варьироваться очень
    * широко благодаря использованию ц. о. домов / огня / одежды.
    *
    * От этой хар-ки зависит "диапазон комфорта".
    * Например, когда приспосабливаемость == 0.3, это означает,
    * что особь способна нормально жить в диапазоне температур
    * [ t + t * 0.3 * k); t - t * 0.3 * k ], где t - температура комфорта
    * особи, k - спец. коэф. характеристики.
    * Другие виды диапазонов выживания - влажность, дренаж и пр. -
    * определяются тем же образом.
    *
    * ( 0.0; + ]
    */
    cl_float adaptability;

    /**
    * Предпочитаемые / необходимые компоненты для жизни особи.
    * Например, некоторые особи лучше себя чувствуют в песке, кто-то -
    * на камнях, кому-то для жизни необходима вода.
    */
    // @todo preferComponentLiving_t  component[ PREFER_COMPONENT_SURVIVOR_LIVING ];

} survivorLiving_t;




/**
* Друзья.
* # Значение критериев:
*     CRITERIA_B_BLUE    Защита прекращается при малейшей опасности.
*     CRITERIA_C_GREEN   Защита прекращается при серьёзной опасности.
*     CRITERIA_D_YELLOW  Защита прекращается при гарантированной опасности.
*     CRITERIA_E_RED     Будут защищены ценой собственной жизни.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING  code;
    enum CRITERIA     force;
} aboutFriendLiving_t;

typedef aboutFriendLiving_t  friendLiving_t[ FRIEND_COUNT_LIVING ];




/**
* Враги.
* # Значение критериев:
*     CRITERIA_B_BLUE    Будут атакованы при гарантированной угрозе.
*     CRITERIA_C_GREEN   Будут атакованы при серьёзной угрозе.
*     CRITERIA_D_YELLOW  Будут атакованы при малейшей угрозе.
*     CRITERIA_E_RED     Будут атакованы всегда.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING  code;
    enum CRITERIA     force;
} aboutEnemyLiving_t;

typedef aboutEnemyLiving_t  enemyLiving_t[ ENEMY_COUNT_LIVING ];




typedef struct __attribute__ ((packed)) {
    /**
    * Код вида особи.
    */
    enum CODE_LIVING code;


    /**
    * Размер особи.
    */
    enum SIZE_LIVING size;


    /**
    * Масса особи согласно жизненному циклу "countByAge", кг.
    */
    cl_float mass[ LIFE_CYCLE_COUNT ];


    /**
    * Максимальное количество особей в 1-й группе.
    * 0 - кол-во особей в группе не ограничено.
    * Для уникальных особей это кол-во = 1.
    */
    cl_uint maxGroupSize;


    /**
    * Аналог уровня особи.
    * Влияет на защиту и атаку особи.
    *
    * @see Комм. к aboutOnePartLiving_t::attack.
    * @see http://crawl.chaosforge.org/index.php?title=Hit_dice
    */
    cl_float hitDice;


    /**
    * Атаки, известные особи.
    *   # Из-за большого разброса возможностей атак, для особи не задаётся
    *     "общая атака" (как для защиты "resist"): все атаки содержат
    *     абсолютные значения.
    */
    attackLiving_t  attack;


    /**
    * Защита особи от воздействий.
    *
    *   # Творческая компиляция значений AC и MR из
    *     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # Общая магическая защита от атаки записывается
    *     парой TAL_MAGIC + FAL_ANY и значением MR из
    *     http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # Если особь уязвима к опред. виду воздействия, значение защиты <= -1.0.
    *
    * @see Соглашение о защите в aboutOnePartLiving_t::resist.
    * @see Комм. к aboutOnePartLiving_t::attack и aboutOnePartLiving_t::resist.
    * @see Armour class > http://crawl.chaosforge.org/index.php?title=AC
    * @see Magic resistance > http://crawl.chaosforge.org/index.php?title=MR
    * @see Вычисление > http://crawl.chaosforge.org/index.php?title=AC_calculations
    */
    resistLiving_t resist;


    /**
    * Уклонение особи от атак.
    *
    * @see Вычисление > http://crawl.chaosforge.org/index.php?title=Evasion
    */
    cl_float evasion;


    /**
    * Насколько крепка особь (живучесть).
    * Аналог хитпоинта.
    * Влияет на способность особи держать повреждения.
    *
    * @see Hit points > http://crawl.chaosforge.org/index.php?title=HP
    */
    cl_float vitality;


    /**
    * Как сильно шумит.
    *
    * @see http://crawl.chaosforge.org/index.php?title=Noise
    */
    noiseLiving_t noise;


    /**
    * Перемещение особи в разных средах.
    *   # Отрицательное значение скорости означает, что особь не может
    *     перемещаться в заданной среде.
    */
    moveSolidSurfaceLiving_t   moveSolidSurface;
    moveLiquidSurfaceLiving_t  moveLiquidSurface;
    moveSolidInsideLiving_t    moveSolidInside;
    moveLiquidInsideLiving_t   moveLiquidInside;
    moveGasInsideLiving_t      moveGasInside;


    /**
    * Уточняющие теги - TAG_LIVING - к особи.
    */
    cl_ulong tag;


    /**
    * Среднее время жизни особи в днях (старость -> смерть).
    * Для бессмертных и мёртвых особей не имеет смысла.
    */
    cl_float lifetime;


    /**
    * Иммунитет особи к болезням.
    *
    * @todo Болезнь определяется очагами и силой. Произведение
    * иммунитета и силы очага болезни - это % особей (отн. значения 1.0),
    * которые остаются здоровы.
    *
    * @todo extend? Иммунитет зависит от жизненного цикла особи LIFE_CYCLE.
    */
    cl_float immunity;


    /**
    * Из каких компонентов состоит особь.
    * Например: вода, белки (мясо), жиры, углеводы (скелет, панцирь).
    */
    compositionPortionLiving_t composition;


    /**
    * Метаболизм особи.
    */
    metabolismLiving_t metabolism;


    /**
    * Условия выживания данной особи.
    *   # Условия выживания одинаковы для всех жизненных циклов особи.
    */
    survivorLiving_t survivor;


    /**
    * Друзья.
    */
    friendLiving_t friend;


    /**
    * Враги.
    */
    enemyLiving_t enemy;


} aboutOneLiving_t;

#endif





/**
* Информация об особях.
*   #! В этом списке индекс особи соотв. коду особи.
*/
typedef aboutOneLiving_t  aboutLiving_t[ LIVING_COUNT ];




/**
* Макс. кол-во особей с указанием количества, которые могут
* *одновременно* находиться в 1-й ячейке портулана.
*   # Работаем с кол-вами особей по всему жизн. циклу LIFE_CYCLE.
*/
typedef portionLiving_t  livingCount_t[ LIFE_CYCLE_COUNT ];
typedef livingCount_t    livingCell_t[ LIVING_CELL ];




/**
* Живой мир (растения, животные и пр.; далее - особи).
* Кол-во особей по ареалам обитания; область планеты разбивается на объём
* 27х27х27 и каждая полученная ячейка считается ареалом обитания групп
* особей; т.о. *каждой* группе живого мира сопоставляется 19683 ареалов
* обитания.
*/
typedef livingCell_t*  livingContent_t;
typedef struct __attribute__ ((packed)) {
    /**
    * Кол-во особей в ячейке.
    * Кол-во больных особей определяется @todo очагами болезней и
    * иммунитетом особей.
    * Особи собраны по группам.
    */
    /* - Заменено на выделение памяти в куче, т.к. OpenCL при большом размере
         стека не инициализируется.
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
