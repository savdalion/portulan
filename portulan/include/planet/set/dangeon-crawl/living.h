#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"


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
* Перечисление общих частей тела живых существ.
*   # Деление на группы животных / растений - чисто условное.
*/
enum COMMON_PART_LIVING {
    // пустая часть или часть не определена
    // используется как признак, что орган не прикреплён ни к какому
    // другому органу
    CPL_NONE = 0,

    /* животные, насекомые */
    // голова
    CPL_HEAD,
    // грудь
    CPL_BREAST,
    // брюшко
    CPL_BELLY,
    // мозг
    CPL_BRAIN,
    // жвалы
    CPL_MANDIBLE,
    // глаз
    CPL_EYE,
    // усик
    CPL_FEELER,
    // лапка насекомого
    CPL_TARSUS,
    // лапа животного
    CPL_LEG,
    /* - @todo extend Добавление железы повлечёт за собой усложнение структуры.
         Сейчас яд будет создаваться в том же органе, который воздействует
         на окр. среду.
    // ядовитая железа
    CPL_VENOM_GLAND
    */

    /* растения */
    // корень
    CPL_ROOT,
    // стебель, ствол
    CPL_STEM,
    // листва, листья
    CPL_LEAF,
    // колосок
    CPL_SPIKELET,
    // семя
    CPL_SEED,
    // плод, зародыш, эмбрион
    //CPL_FETUS, - ограничиться семенем?

    // последняя
    CPL_last
};





/**
* Местоположение органа особи по координатным осям XYZ.
*   # Наблюдатель смотрит навстречу оси Z, ось X направлена вправо, Y - вверх.
*/
#if 1

enum LOCUS_X_PART_LIVING {
    LXL_UNDEFINED = 0,
    LXL_LEFT,
    LXL_CENTER,
    LXL_RIGHT,
    // орган расположен по всей особи (например, кровеносные сосуды)
    LXL_EXTENT,

    // последний
    LXL_last
};

enum LOCUS_Y_PART_LIVING {
    LYL_UNDEFINED = 0,
    LYL_BOTTOM,
    LYL_CENTER,
    LYL_TOP,
    LYL_EXTENT,

    // последний
    LYL_last
};

enum LOCUS_Z_PART_LIVING {
    LZL_UNDEFINED = 0,
    LZL_FAR,
    LZL_CENTER,
    LZL_NEAR,
    LZL_EXTENT,

    // последний
    LZL_last
};

#endif





/**
* Код органа особи.
* Код разделён на несколько частей, чтобы обеспечить дополн. динамику
* без лишнего кодирования.
*/
typedef struct __attribute__ ((packed)) {
    // какой особи принадлежит орган
    enum CODE_LIVING specimen;

    // часть органа
    enum COMMON_PART_LIVING part;

    // местоположение органа относительно особи
    //   # Особь разворачивается головой вверх, спиной к наблюдателю и т.о.,
    //     чтобы её проекция относительно взгляда наблюдателя была
    //     максимальной.
    //   # Смотрим на особь сверху: ось Z - навстречу наблюдателю, ось X -
    //     направо, ось Y - вверх.
    enum LOCUS_X_PART_LIVING lx;
    enum LOCUS_Y_PART_LIVING ly;
    enum LOCUS_Z_PART_LIVING lz;

    // орган находится внутри другого органа
    // Например: мозг, сердце.
    enum COMMON_PART_LIVING inner;

    // орган находится на поверхности или прикреплён к другому органу
    // Например: глаз, рука.
    //   # Если к органу прикреплены неск. меньших по размеру органов,
    //     факт прикрепления указывается для меньших органов.
    //   # Если скреплены близкие по размеру органы, факт прикрепления
    //     указывается для нижнего органа. См. выше "местоположение органа".
    enum COMMON_PART_LIVING outer;

} codePartLiving_t;






/**
* Функция части тела особи.
*/
#if 1

// жизненно важная часть (летальный исход при отсутствии)
#define FPL_LIVE                          (1ULL << 0)

// перемещение по твёрдой поверхности
#define FPL_MOVE_SOLID_SURFACE            (1ULL << 1)
// перемещение по жидкой поверхности
#define FPL_MOVE_LIQUID_SURFACE           (1ULL << 2)

// перемещение внутри твёрдой поверхности с копанием норы
#define FPL_MOVE_SOLID_INSIDE_DIG         (1ULL << 3)
// перемещение внутри твёрдой поверхности по готовой норе
#define FPL_MOVE_SOLID_INSIDE_BURROW      (1ULL << 4)
// перемещение внутри жидкой поверхности
#define FPL_MOVE_LIQUID_INSIDE            (1ULL << 5)
// перемещение внутри газообразной поверхности (полёт по воздуху)
#define FPL_MOVE_GAS_INSIDE               (1ULL << 6)

// # Что конкретно поглощает - указано для каждого органа.
// поглощение твёрдых питательных компонентов (пища, рот)
#define FPL_EAT_SOLID                     (1ULL << 7)
// поглощение жидких питательных компонентов (вода, хобот)
#define FPL_EAT_LIQUID                    (1ULL << 8)
// поглощение газообразных питательных компонентов (воздух, лёгкие)
#define FPL_EAT_GAS                       (1ULL << 9)
// поглощение энергий
#define FPL_EAT_ENERGY                    (1ULL << 10)

// # Что конкретно усваивает - указано для каждого органа.
// усвоение твёрдых питательных компонентов (пища)
#define FPL_UPTAKE_SOLID                  (1ULL << 11)
// усвоение жидких питательных компонентов (вода)
#define FPL_UPTAKE_LIQUID                 (1ULL << 12)
// усвоение газообразных питательных компонентов (воздух)
#define FPL_UPTAKE_GAS                    (1ULL << 13)
// усвоение энергий
#define FPL_UPTAKE_ENERGY                 (1ULL << 14)

// выделение твёрдых питательных компонентов (кал)
#define FPL_EXCRETION_SOLID               (1ULL << 15)
// выделение жидких питательных компонентов (моча)
#define FPL_EXCRETION_LIQUID              (1ULL << 16)
// выделение газообразных питательных компонентов (газы)
#define FPL_EXCRETION_GAS                 (1ULL << 17)
// выделение света (светлячок)
#define FPL_EXCRETION_NORMAL_LIGHT        (1ULL << 18)

//   # Особь перерабатывает питательные компоненты в энергию для жизни.

// рецепторы особи (экстероцепторы, что способна чувствовать в окр. среде)
// # @todo extend? Каждый рецептор содержит уровень воспринимаемого
//   сигнала по шкале
//     - ультра (например, ультрафиолетовое излучение)
//     - нормально (например, видимый свет)
//     - инфра (например, инфракрасное излучение)
// @see http://ru.wikipedia.org/wiki/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BC%D0%B0%D0%B3%D0%BD%D0%B8%D1%82%D0%BD%D1%8B%D0%B9_%D1%81%D0%BF%D0%B5%D0%BA%D1%82%D1%80
// вкус
#define FPL_TASTE_NORMAL_SIGNAL           (1ULL << 19)
// обоняние
#define FPL_SMELL_NORMAL_SIGNAL           (1ULL << 20)
// осязание
#define FPL_TOUCH_NORMAL_SIGNAL           (1ULL << 21)
// слух
#define FPL_HEARING_NORMAL_SIGNAL         (1ULL << 22)
// зрение
#define FPL_VISION_NORMAL_SIGNAL          (1ULL << 23)
// чужое присутствие (помним: это мир Dungeon Crawl)
#define FPL_PRESENCE_NORMAL_SIGNAL        (1ULL << 24)

// эффекты, производимые особью
// отражаемое излучение (в каком свете особь или её орган видны)
#define FPL_VISION_REFLECT_NORMAL_EFFECT  (1ULL << 25)
/* - Для шума - см. noise в инф. об особи.
// шумит (издаёт шум) при передвижении
#define FPL_NOISE_MOVE_NORMAL_EFFECT      (1ULL << ..)
*/

// возможность физической атаки (челюсти, жало)
#define FPL_PHYSICAL_ATTACK               (1ULL << 26)

// возможность магической атаки (мозг)
#define FPL_MAGIC_ATTACK                  (1ULL << 27)

// интеллект (мозг)
#define FPL_INTELLECT                     (1ULL << 28)

//   # Общение - выделение вкусовых компонентов, запахов (вкусовые комп.
//     в виде газов), звуков, особые прикосновения, движения (танцы), которые
//     несут в себе смысловую информацию и могут быть восприняты другими
//     особями при наличии соотв. рецептора.
// общение с помощью вкусовых сигналов
// @see Трофаллаксис > http://ru.wikipedia.org/wiki/%D0%A2%D1%80%D0%BE%D1%84%D0%B0%D0%BB%D0%BB%D0%B0%D0%BA%D1%81%D0%B8%D1%81
#define FPL_EMIT_NORMAL_TASTE             (1ULL << 29)
// общение с помощью запахов
#define FPL_EMIT_NORMAL_SMELL             (1ULL << 30)
// общение с помощью прикосновений
#define FPL_EMIT_NORMAL_TOUCH             (1ULL << 31)
// общение с помощью звуков (сигналы, речь)
#define FPL_EMIT_NORMAL_SOUND             (1ULL << 32)
// общение с помощью наблюдения (визуальные сигналы)
#define FPL_EMIT_NORMAL_VISION            (1ULL << 33)

#endif





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

// регенерация особи (органа особи)
//   # Особь не регениерирует, если не указан хотя бы один из тегов ниже.
// восстанавливаются повреждения
#define TL_DAMAGE_REGENERATION     (1ULL << 2)
// восстанавливаются утерянные части тела
#define TL_LOSE_PART_REGENERATION  (1ULL << 3)

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
    // попадание тупой пулей
    TAL_SHOOT_CRUSH,
    // попадание газом (например, дыхание огнём / холодом / брызгами)
    TAL_SHOOT_GAS,
    // попадание жидкостью (например, кислота)
    TAL_SHOOT_LIQUID,
    // попадание острой пулей
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
    //   # Шкала отравлений согласно http://crawl.chaosforge.org/index.php?title=Poison#Poison_Types
    //     10 - обычная (regular)
    //     20 - средняя (medium)
    //     40 - сильная (strong)
    //     80 - мерзкая (nasty)
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
} aboutOnePartAttack_t;



/**
* Атаки, известные органу особи.
*/
typedef aboutOnePartAttack_t  attackPartLiving_t[ ATTACK_PART_LIVING_COUNT ];





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
} aboutOnePartResist_t;



/**
* Защиты от известных атак.
*/
typedef aboutOnePartResist_t  resistPartLiving_t[ RESIST_PART_LIVING_COUNT ];





/**
* Информация об органе особи.
*   # Размер органа особи определяется размером самой особи и массой органа.
*/
#if 1

typedef __structPortionComponent_t  compositionPortionLiving_t[ COMPONENT_COMPOSITION_LIVING ];
typedef __enumCodeComponent  componentCodeNeedLiving_t[ COMPONENT_NEED_LIVING ];

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


typedef __enumCodeComponent  componentCodeWasteLiving_t[ COMPONENT_WASTE_LIVING ];

typedef struct __attribute__ ((packed)) {
    componentCodeWasteLiving_t componentWaste;
} excretionSolidLiving_t;

typedef struct __attribute__ ((packed)) {
    componentCodeWasteLiving_t componentWaste;
} excretionLiquidLiving_t;

typedef struct __attribute__ ((packed)) {
    componentCodeWasteLiving_t componentWaste;
} excretionGasLiving_t;


typedef __enumCodeEnergy  energyCodeNeedLiving_t[ ENERGY_NEED_LIVING ];

typedef struct __attribute__ ((packed)) {
    energyCodeNeedLiving_t energyNeed;
} uptakeEnergyLiving_t;

// выделение энергий (см. выше - усвоение энергий)
typedef __enumCodeEnergy  energyCodeWasteLiving_t[ ENERGY_WASTE_LIVING ];

typedef struct __attribute__ ((packed)) {
    energyCodeWasteLiving_t energyWaste;
} excretionEnergyLiving_t;

typedef struct __attribute__ ((packed)) {
    /**
    * Код органа особи.
    */
    codePartLiving_t code;

    /**
    * Масса органа особи относительно общей массы особи, части.
    *   # Всегда <= 1.0.
    *   # Масса всех органов особи должна быть <= 1.0.
    *   # Если масса органа = 0.0, остаток массы распределиться
    *     равномерно между всеми органами с нулевой массой (чтобы
    *     привести сумму частей к 1.0).
    */
    cl_float mass;

    /**
    * Из каких компонентов состоит орган особи.
    * Массовые доли (от общей массы органа), сумма = 1.0.
    * Например: вода, белки (мясо), жиры, углеводы (скелет, панцирь).
    */
    compositionPortionLiving_t composition;


    /**
    * Характеристики органа в зависимости от его функциональности.
    *   # Орган может обладать сразу неск. функциями.
    *   # Наличие заданной функции определяется битами FPL_*.
    */

    /**
    * Какие функции выполняет орган, его важность для особи
    * (битовое перечисление FPL_*).
    */
    cl_ulong function;


    // Перемещение особи в разных средах.
    // Задаётся в "function" и в самой особи.


    // поглощение компонентов (см. ниже - усвоение)
    //   # Наличие органа поглощения указывает на возможность организму принять
    //     компоненты для усвоения.
    // Не требует параметров.


    // усвоение компонентов (см. выше - поглощение)
    // Перечисляется список компонентов, которые орган способен усвоить
    // из особи.
    //   # Для органа указывается только *возможность* усвоения компонента.
    //     Требуемое кол-во компонента декларировано в информации об особи.
    //   # 1 литр воздуха (CC_AIR) весит 1.2 грамма.
    // Орган переводит компоненты (пищу) в энергию.
    // Энергия = количеству энергии, освобождаемой при сгорании компонента.
    // КПД органа усвоения определяет, какая часть комп. усвоится организмом.
    uptakeSolidLiving_t       uptakeSolid;
    uptakeLiquidLiving_t      uptakeLiquid;
    uptakeGasLiving_t         uptakeGas;


    // выделение компонентов (см. выше - поглощение и усвоение компонентов)
    excretionSolidLiving_t  excretionSolid;
    excretionLiquidLiving_t excretionLiquid;
    excretionGasLiving_t    excretionGas;


    // усвоение и выделение энергий
    // Перечисляется список энергий, которые орган способен усвоить
    // из окр. среды.
    //   # Для органа указывается только *возможность* усвоения энергии.
    //     Требуемое кол-во энергии указано в информации об особи.
    uptakeEnergyLiving_t    uptakeEnergy;
    excretionEnergyLiving_t excretionEnergy;


    /**
    * Атаки, известные органу особи.
    *   # Из-за относительно большого разброса возможностей атак, для особи
    *     не задаётся "общая атака" (как для защиты "resist"): все атаки
    *     содержат абсолютные значения.
    */
    attackPartLiving_t attack;


    /**
    * Защита органа относительно общей защиты особи.
    * Как надёжно орган защищён от воздействия.
    *   # Защита части тела = resist особи + Относительная защита органа
    *   # Для относительной защиты органа никогда не пишется IMMUNE (достаточно
    *     записи для особи).
    *   # Защита для вкусов TAL_SHOOT_CRUSH и TAL_SHOOT_PIERCE совпадает соотв.
    *     с TAL_CRUSH и TAL_PIERCE.
    */
    resistPartLiving_t resist;

} aboutOnePartLiving_t;

#endif





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
    * Максимальная скорость перемещения особи по поверхности, которую
    * даёт этот орган.
    * м/с
    * Определяет инициативу при моделировании столкновений.
    *   # В обычных (не боевых) условиях, скорость перемещения
    *     считается в 2 раза меньшей.
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
typedef __structPortionComponent_t  componentPortionNeedLiving_t[ COMPONENT_NEED_LIVING ];


/**
* *Разные* компоненты, которые выделяет особь при жизнедеятельности.
* кг / день
*   # Выделяемые компоненты распределяются также, как выделяемые энергии.
*   # Выбран "день" для гибкой аппроксимации выделяемого
*     кол-ва на пульс, на ход (зависит от скорости перемещения).
*
* @see Соглашения о распределении энергий по жизненным циклам особи - energyWaste_t.
*/
typedef __structPortionComponent_t  componentPortionWasteLiving_t[ COMPONENT_WASTE_LIVING ];


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
typedef __structPortionEnergy_t  energyPortionNeedLiving_t[ ENERGY_NEED_LIVING ];

/**
* Энергия, выделяемая особью в процессе своей жизнедеятельности.
* едениц / день
*
* @see CODE_ENERGY
*/
typedef __structPortionEnergy_t  energyPortionWasteLiving_t[ ENERGY_WASTE_LIVING ];


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
/**
* Температура комфорта.
* Вне этого диапазона - повышенная смертность и пониженная
* рождаемость особей.
* Для цивилизованных особей диапазон может варьироваться очень
* широко благодаря использованию ц. о. домов / огня / одежды.
*/
typedef struct __attribute__ ((packed)) {
    cl_float min;
    cl_float max;
} temperatureComfortLiving_t;

/**
* Температура выживания.
* Существование особи вне этого предела невозможно
* (100% летальный исход за 1 пульс).
*/
typedef struct __attribute__ ((packed)) {
    cl_float min;
    cl_float max;
} temperatureLimitLiving_t;

typedef struct __attribute__ ((packed)) {
    temperatureComfortLiving_t comfort;
    temperatureLimitLiving_t limit;
} temperatureRangeLiving_t;

typedef struct __attribute__ ((packed)) {
    /**
    * В каких средах может жить особь.
    *   # Среды обитания задаются комбинацией бит из HL_*.
    *   # В любых других средах особь погибает.
    *
    * Например, если особь может жить на границе газообразной и
    * твёрдой сред, пишем:
    *   HL_GAS | HL_SOLID
    * Если жизнь возможна только в твёрдой среде (кроты):
    *   HL_SOLID
    *
    * @see http://crawl.chaosforge.org/index.php?title=Habitat
    */
    cl_uint  habitat[ HABITAT_LIVING_COUNT ];

    /**
    * Диапазон температур в которых способна жить особь согласно
    * жизненному циклу "countByAge".
    */
    temperatureRangeLiving_t temperatureRange;

} survivorLiving_t;


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
    * Защита особи от воздействий.
    * Определяет базовые значения защиты частей тела (органов).
    *
    *   # Творческая компиляция значений AC и MR из http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # Общая магическая защита от атаки записывается
    *     парой TAL_MAGIC + FAL_ANY и значением MR из http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # Если особь уязвима к опред. виду воздействия, значение защиты <= -1.0.
    *
    * @see Соглашение о защите в aboutOnePartLiving_t::resist.
    * @see Комм. к aboutOnePartLiving_t::attack и aboutOnePartLiving_t::resist.
    * @see Armour class > http://crawl.chaosforge.org/index.php?title=AC
    * @see Magic resistance > http://crawl.chaosforge.org/index.php?title=MR
    * @see Вычисление > http://crawl.chaosforge.org/index.php?title=AC_calculations
    */
    resistPartLiving_t resist;


    /**
    * Уклонение особи от атак.
    *   # Уклонение зависит линейно и прямо пропорционально от кол-ва
    *     неповреждённых органов особи.
    *     @todo extend? Учитывать размер органа (вклад в уклонение).
    *
    * @see Вычисление > http://crawl.chaosforge.org/index.php?title=Evasion
    */
    cl_float evasion;


    /**
    * Насколько крепка особь (живучесть).
    * Аналог хитпоинта.
    * Влияет на способность органов особи держать повреждения.
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
    *   # Орган, отвечающий за перемещение, задаётся в "function" органа.
    *   # Скорость перемещения особи вычисляется как равновесовой вклад
    *     каждого органа, отвечающего за перемещение.
    */
    moveSolidSurfaceLiving_t moveSolidSurface;
    moveLiquidSurfaceLiving_t moveLiquidSurface;
    moveSolidInsideLiving_t moveSolidInside;
    moveLiquidInsideLiving_t moveLiquidInside;
    moveGasInsideLiving_t moveGasInside;


    /**
    * Из каких частей (органов) состоит особь.
    */
    aboutOnePartLiving_t  part[ PART_LIVING_COUNT ];


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
    * которые здоровы.
    *
    * @todo extend? Иммунитет зависит от жизненного цикла особи LIFE_CYCLE.
    */
    cl_float immunity;


    /**
    * Метаболизм особи.
    */
    metabolismLiving_t metabolism;


    /**
    * Условия выживания данной особи.
    *   # Условия выживания одинаковы для всех жизненных циклов особи.
    */
    survivorLiving_t survivor;

} aboutOneLiving_t;

#endif





/**
* Информация об особях.
*   #! В этом списке индекс особи соотв. коду особи.
*/
typedef aboutOneLiving_t  aboutLiving_t[ LIVING_COUNT ];



/**
* Примерное кол-во особей в области планеты (в портулане) с указанием
* размеров групп. Эти данные используются для формирования
* ареалов обитания в области планеты.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_LIVING code;
    // *примерное* кол-во особей в ячейке области планеты
    cl_float count;
    // # Размер группы декларирован в aboutOneLiving_t::maxGroupSize.
} zoneLiving_t;

// # Берётся LIVING_CELL вместо LIVING_COUNT, т.к. эта структура
//   используется лишь при инициализации, а кол-во особей в 1-й ячейке
//   в любом случае не будет превышать LIVING_CELL особей.
typedef zoneLiving_t  livingAll_t[ LIVING_CELL ];




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
                } // living
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
