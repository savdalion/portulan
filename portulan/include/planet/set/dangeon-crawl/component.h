#pragma once

#include "structure.h"


/**
* Наборы компонентов для моделирования планеты на основе
* мира игры Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace component {

/**
* Перечисление кодов в группе компонентов
* GROUP_ELEMENT::GE_COMPONENT.
*/
#undef CC_NONE
enum CODE_COMPONENT {
    // компонент отсутствует или неопределён
    CC_NONE = 0,

    // пустота
    CC_VACUUM = 1,

    // воздух (кислород + азот)
    CC_AIR,

    // почвы
    //   - бесплодная почва
    CC_BAREN_SOIL,
    //   - валун
    CC_BOULDER,
    //   - плодородная почва
    CC_RICH_SOIL,
    //   - каменная галька
    CC_PEBBLE,
    //   - цельный камень
    CC_ROCK,
    //   - песок
    CC_SAND,

    // питательные вещества для углеродных особей
    //   - углеводы
    CC_CARBOHYDRATE,
    //   - углекислый газ
    CC_CARBON_ACID,
    //   - жиры
    CC_FAT,
    //   - белки
    CC_PROTEIN,

    // скелет, кости
    CC_BONE,

    // прочие компоненты жизнедеятельности особей (экскременты)
    //   - кал
    CC_FECES,
    //   - моча
    CC_URINE,

    // вода
    CC_WATER,

    // редкие элементы
    CC_SPARSE
};





/**
* Код компонента и массовая доля в целом элементе или
* количество компонента.
* Аналог portionEnergy_t.
*
* Например: белки = 0.2, жиры = 0.1, углеводы = 0.7.
* Например: белки = 6e6, жиры = 3e3, углеводы = 4e4.
*/
typedef struct {
    CODE_COMPONENT code;
    cl_float count;
} portionComponent_t;





/**
* Перечисление кодов в группе компонентов
* GROUP_ELEMENT::GE_ENERGY.
*/
enum CODE_ENERGY {
    // энергия отсутствует или неопределена
    CE_NONE = 0,

    // радиация (излучения высокой частоты)
    CE_RADIATION,

    // видимый свет (излучения в видимом человеческому глазу диапазоне)
    CE_NORMAL_LIGHT,

    // тепло окруж. среды
    CE_HEAT,

    // электричество
    CE_ELECTRICITY
};




/**
* Код энергии и массовая доля в целом наборе энергий элемента или
* количество энергии.
* Аналог portionComponent_t.
*/
typedef struct {
    CODE_ENERGY code;
    cl_float count;
} portionEnergy_t;







/**
* Информация о компоненте.
*
* @see portulan::command::planet::aoc()
*/
typedef struct {
    /**
    * Плотность, кг / м3.
    */
    cl_float density;

    /**
    * Температура плавления, К.
    */
    cl_float meltingPoint;

    /**
    * Температура кипения, К.
    */
    cl_float boilingPoint;

    /**
    * Теплота плавления или кристализации (энтальпия плавления), Дж / кг.
    */
    cl_float enthalpyFusion;

    /**
    * Теплота испарения или парообразования, Дж / кг.
    */
    cl_float enthalpyVaporization;

    /**
    * Теплоёмкость, Дж / (кг * К).
    */
    cl_float heatCapacity;

    /**
    * @todo extend Теплота сгорания http://ru.wikipedia.org/wiki/%D0%A1%D0%BA%D1%80%D1%8B%D1%82%D0%B0%D1%8F_%D1%82%D0%B5%D0%BF%D0%BB%D0%BE%D1%82%D0%B0_%D1%81%D0%B3%D0%BE%D1%80%D0%B0%D0%BD%D0%B8%D1%8F
    */

} aboutOneComponent_t;



/**
* Информация о компонентах.
*/
typedef aboutOneComponent_t  aboutComponent_t[ COMPONENT_COUNT ];



/**
* Макс. кол-во компонентов с указанием частей от целого, которые находятся
* в области планеты (в портулане). Эти данные используются для формирования
* составов атмосферы и планеты.
*/
typedef portionComponent_t  componentAll_t[ COMPONENT_COUNT ];



/**
* Макс. кол-во компонентов с указанием частей от целого, которые могут
* *одновременно* храниться в 1-й ячейке портулана.
*/
typedef portionComponent_t  componentCell_t[ COMPONENT_CELL ];




                } // component
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
