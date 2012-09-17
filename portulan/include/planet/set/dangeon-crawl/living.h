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

/**
* Перечисление кодов в группе живого мира
* GROUP_ELEMENT::GE_LIVING.
*
*   # Животные, насекомые, растения и др. подобные группы именуются "особями".
*
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html
*/
enum CODE_LIVING {
    // код отсутствует или неопределён
    CL_NONE = 0,

    // @see http://koti.welho.com/jarmoki/crawl/monsters/worker_ant.html
    CL_ANT_WORKER,

    // цветы (абстракция)
    CL_FLOWER,

    // деревья (абстракция)
    //  - карликовые
    //  - средние
    //  - высокие
    CL_TREE_TINY,
    CL_TREE_AVERAGE,
    CL_TREE_HIGH
};





/**
* Код элемента (компонента, особи) и массовая доля в целом элементе или
* количество элемента.
*
* Например: муравьи = 0.2, деревья = 0.1, цветы = 0.7.
* Например: муравьи = 6e6, деревья = 3e3, цветы = 4e4.
*/
typedef struct {
    CODE_LIVING code;
    cl_float count;
} portionLiving_t;






/**
* Перечисление общих частей тела живых существ.
*/
enum COMMON_PART_LIVING {
    // пустая часть или часть неопределена
    // используется как признак, что орган не прикреплён ни к какому
    // другому органу
    CPL_NONE = 0,

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
    CPL_LEG
    /* - @todo extend Добавление железы повлечёт за собой усложнение структуры.
         Сейчас яд будет создаваться в органе, который воздействует на окр. среду.
    // ядовитая железа
    CPL_VENOM_GLAND
    */
};





/**
* Местоположение органа особи по координатным осям XYZ.
*   # Наблюдатель смотрит навстречу оси Z, ось X направлена вправо, Y - вверх.
*/
enum LOCUS_X_PART_LIVING {
    LXL_UNDEFINED = 0,
    LXL_LEFT,
    LXL_CENTER,
    LXL_RIGHT,
    // орган расположен по всей особи (например, кровеносные сосуды)
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
* Код органа особи.
* Код разделён на несколько частей, чтобы обеспечить дополн. динамику
* без лишнего кодирования.
*/
typedef struct {
    // какой особи принадлежит орган
    CODE_LIVING specimen;

    // часть органа
    COMMON_PART_LIVING part;

    // местоположение органа относительно особи
    //   # Особь разворачивается головой вверх, спиной к наблюдателю и т.о.,
    //     чтобы её проекция относительно взгляда наблюдателя была
    //     максимальной.
    //   # Смотрим на особь сверху: ось Z - навстречу наблюдателю, ось X -
    //     направо, ось Y - вверх.
    LOCUS_X_PART_LIVING lx;
    LOCUS_Y_PART_LIVING ly;
    LOCUS_Z_PART_LIVING lz;

    // орган находится внутри другого органа
    // Например: мозг, сердце.
    COMMON_PART_LIVING inner;

    // орган находится на поверхности или прикреплён к другому органу
    // Например: глаз, рука.
    //   # Если к органу прикреплены неск. меньших по размеру органов,
    //     факт прикрепления указывается для меньших органов.
    //   # Если скреплены близкие по размеру органы, факт прикрепления
    //     указывается для нижнего органа. См. выше "местоположение органа".
    COMMON_PART_LIVING outer;

} codePartLiving_t;






/**
* Функция части тела особи.
*/
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

// поглощение твёрдых питательных компонентов (пища, рот)
#define FPL_EAT_SOLID                     (1ULL << 7)
// поглощение жидких питательных компонентов (вода, хобот)
#define FPL_EAT_LIQUID                    (1ULL << 8)
// поглощение газообразных питательных компонентов (воздух, лёгкие)
#define FPL_EAT_GAS                       (1ULL << 9)
// поглощение света (листья)
// # Делится на диапазоны электромагнитного излучения.
//   См. ниже "рецепторы особи".
#define FPL_EAT_NORMAL_LIGHT              (1ULL << 10)

// усвоение твёрдых питательных компонентов (пища)
#define FPL_UPTAKE_SOLID                  (1ULL << 11)
// усвоение жидких питательных компонентов (вода)
#define FPL_UPTAKE_LIQUID                 (1ULL << 12)
// усвоение газообразных питательных компонентов (воздух)
#define FPL_UPTAKE_GAS                    (1ULL << 13)
// усвоение света (листья)
#define FPL_UPTAKE_NORMAL_LIGHT           (1ULL << 14)

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
#define FPL_EMIT_NORMAL_TASTE             (1ULL << 30)
// общение с помощью запахов
#define FPL_EMIT_NORMAL_SMELL             (1ULL << 31)
// общение с помощью прикосновений
#define FPL_EMIT_NORMAL_TOUCH             (1ULL << 32)
// общение с помощью звуков (сигналы, речь)
#define FPL_EMIT_NORMAL_SOUND             (1ULL << 33)
// общение с помощью наблюдения (визуальные сигналы)
#define FPL_EMIT_NORMAL_VISION            (1ULL << 34)






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
    // семена растений
    SL_ATOMIC = 1,
    // крысы, летучие мыши
    SL_TINY,
    // спригганы
    SL_LITTLE,
    // полурослики, кобольды
    SL_SMALL,
    // люди, эльфы, дварфы
    SL_MEDIUM,
    // троли, огры, кентавры, наги
    SL_LARGE,
    // четвероногие животные
    SL_BIG,
    // гиганты
    SL_GIANT,
    // драконы
    SL_HUGE
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
    HL_UNDEAD
};





/**
* Уточняющие теги к особи.
* По этим тегам динамический движок - porte - может строить
* собственные решения.
*//* - Заменено на define. См. ниже.
enum TAG_LIVING {
*/

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






/**
* Виды воздействия органа особи.
*/
typedef struct {
    // механическое действие
    //   - дробящий удар
    //   - режущий удар
    //   - колющий удар
    cl_float crush;
    cl_float cutting;
    cl_float thrust;

    // @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_flags_by_name.html

    cl_float acid;
    cl_float cold;
    cl_float electricity;
    cl_float fire;
    cl_float hellfire;
    cl_float holyword;
    cl_float negative;

    //   # Шкала отравлений согласно http://crawl.chaosforge.org/index.php?title=Poison#Poison_Types
    //     10 - обычная (regular)
    //     20 - средняя (medium)
    //     40 - сильная (strong)
    //     80 - мерзкая (nasty)
    cl_float poison;

} impactLiving_t;






/**
* Информация об органе особи.
*   # Размер органа особи определяется размером самой особи и массой органа.
*/
typedef struct {
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
    typedef component::portionComponent_t  composition_t[ COMPONENT_COMPOSITION_LIVING ];
    composition_t composition;


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
    //   # Для органа указывается только *возможность* усвоения компонента.
    //     Требуемое кол-во компонента указано в информации об особи.
    //   # 1 литр воздуха (CC_AIR) весит 1.2 грамма.
    // Орган переводит компоненты (пищу) в энергию.
    // Энергия = количеству энергии, освобождаемой при сгорании компонента.
    // КПД органа усвоения определяет, какая часть комп. усвоится организмом.
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


    // выделение компонентов (см. выше - поглощение и усвоение компонентов)
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


    // поглощение и усвоение энергий (см. ниже - выделение энергий)
    //   # Для органа указывается только *возможность* усвоения энергии.
    //     Требуемое кол-во энергии указано в информации об особи.
    typedef component::CODE_ENERGY  energyNeed_t[ ENERGY_NEED_LIVING ];
    typedef struct {
        energyNeed_t energyNeed;
    } uptakeEnergy_t;
    uptakeEnergy_t uptakeEnergy;

    // выделение энергий (см. выше - усвоение энергий)
    typedef component::CODE_ENERGY  energyWaste_t[ ENERGY_WASTE_LIVING ];
    typedef struct {
        energyWaste_t energyWaste;
    } excretionEnergy_t;
    excretionEnergy_t excretionEnergy;


    /**
    * Силы действия органа особи.
    * Как орган может воздействовать на окружающую среду.
    */
    impactLiving_t attack;


    /**
    * Защита органа относительно общей защиты особи.
    * Как надёжно орган защищён от воздействия окружающей среды.
    *   # Защита части тела = resist особи + Относительная защита органа
    *   # Для относительной защиты органа никогда не пишется IMMUNE (достаточно
    *     записи для особи).
    */
    impactLiving_t resist;

} aboutOnePartLiving_t;






/**
* Информация об особи.
*/
typedef struct {
    /**
    * Код вида особи.
    */
    CODE_LIVING code;


    /**
    * Размер особи.
    */
    SIZE_LIVING size;


    /**
    * Масса особи согласно жизненному циклу "countByAge", кг.
    */
    cl_float mass[ LIFE_CYCLE ];


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
    * @see http://crawl.chaosforge.org/index.php?title=Hit_dice
    */
    cl_float hitDice;


    /**
    * Защита особи от воздействий.
    * Определяет базовые значения защиты частей тела (органов).
    *
    *   # Творческая компиляция значений AC и MR из http://koti.welho.com/jarmoki/crawl/crawl_ss_monster_combat_by_name.html
    *   # Если особь уязвима к опред. виду воздействия, значение защиты = -1.0.
    *
    * @see aboutOnePartLiving_t::resist
    * @see Armour class > http://crawl.chaosforge.org/index.php?title=AC
    * @see Magic resistance > http://crawl.chaosforge.org/index.php?title=MR
    * @see Вычисление > http://crawl.chaosforge.org/index.php?title=AC_calculations
    */
    impactLiving_t resist;


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
    typedef struct {
        // когда стоит неподвижно
        cl_float immovable;
        // когда движется с нормальной скоростью
        cl_float move;
    } noise_t;
    noise_t noise;


    /**
    * Перемещение особи в разных средах.
    *   # Орган, отвечающий за перемещение, задаётся в "function" органа.
    *   # Скорость перемещения особи вычисляется как равновесовой вклад
    *     каждого органа, отвечающего за перемещение.
    */
    typedef struct {
        /**
        * Максимальная скорость перемещения особи по поверхности, которую
        * даёт этот орган.
        * м/с
        * Определяет инициативу при моделировании столкновений.
        *   # В обычных (не боевых) условиях, скорость перемещения
        *     считается в 2 раза меньшей.
        */
        cl_float speed;

    } moveSolidSurface_t;
    moveSolidSurface_t moveSolidSurface;

    typedef struct {
        cl_float speed;
    } moveLiquidSurface_t;
    moveLiquidSurface_t moveLiquidSurface;

    typedef struct {
        // скорость копания норы
        cl_float speedDigBurrow;
        // скорость перемещения по готовой норе
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
    * *Разные* компоненты, которые необходимы особи для жизни.
    * кг / день
    *   # Необходимые компоненты распределяются также, как необходимые энергии.
    *   # Выбран "день" для гибкой аппроксимации необходимого
    *     кол-ва на пульс, на ход (зависит от скорости перемещения).
    *
    * @see Соглашения о распределении энергий по жизненным циклам особи - energyNeed_t.
    */
    typedef component::portionComponent_t  componentNeed_t[ COMPONENT_NEED_LIVING ];


    /**
    * *Разные* компоненты, которые выделяет особь при жизнедеятельности.
    * кг / день
    *   # Выделяемые компоненты распределяются также, как выделяемые энергии.
    *   # Выбран "день" для гибкой аппроксимации выделяемого
    *     кол-ва на пульс, на ход (зависит от скорости перемещения).
    *
    * @see Соглашения о распределении энергий по жизненным циклам особи - energyWaste_t.
    */
    typedef component::portionComponent_t  componentWaste_t[ COMPONENT_WASTE_LIVING ];


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
    typedef component::portionEnergy_t  energyNeed_t[ ENERGY_NEED_LIVING ];

    /**
    * Энергия, выделяемая особью в процессе своей жизнедеятельности.
    * едениц / день
    *
    * @see CODE_ENERGY
    */
    typedef component::portionEnergy_t  energyWaste_t[ ENERGY_WASTE_LIVING ];


    /**
    * Метаболизм особи.
    */
    typedef struct {
        componentNeed_t   componentNeed;
        componentWaste_t  componentWaste_t;

        energyNeed_t      energyNeed;
        energyWaste_t     energyWaste;

    } metabolism_t;

    metabolism_t metabolism;



    /**
    * Условия выживания данной особи.
    */
    typedef struct {
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
        typedef struct {
            /**
            * Температура комфорта.
            * Вне этого диапазона - повышенная смертность и пониженная
            * рождаемость особей.
            * Для цивилизованных особей диапазон может варьироваться очень
            * широко благодаря использованию ц. о. домов / огня / одежды.
            */
            typedef struct {
                cl_float min;
                cl_float max;
            } comfort_t;
            comfort_t comfort;

            /**
            * Температура выживания.
            * Существование особи вне этого предела невозможно
            * (100% летальный исход за 1 пульс).
            */
            typedef struct {
                cl_float min;
                cl_float max;
            } limit_t;
            limit_t limit;

        } temperatureRange_t;

        temperatureRange_t temperatureRange;

    } survivor_t;

    //   # Условия выживания одинаковы для всех жизненных циклов особи.
    survivor_t survivor;

} aboutOneLiving_t;




/**
* Информация об особях.
*/
typedef aboutOneLiving_t  aboutLiving_t[ LIVING_COUNT ];



/**
* Макс. кол-во особей с указанием количества, которые находятся
* в области планеты (в портулане). Эти данные используются для формирования
* ареалов обитания в области планеты.
*/
typedef portionLiving_t  livingAll_t[ LIVING_COUNT ];



/**
* Макс. кол-во особей с указанием количества, которые могут
* *одновременно* находиться в 1-й ячейке портулана.
*/
typedef portionLiving_t  livingCell_t[ LIVING_COUNT ];



                } // living
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
