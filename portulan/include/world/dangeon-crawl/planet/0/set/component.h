#ifndef PORTULAN_AS_OPEN_CL_STRUCT

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
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif



/**
* Перечисление кодов в группе компонентов
* GROUP_ELEMENT::GE_COMPONENT.
*
*   #! Нумерация компонентов должна соотв. индексу в списке aboutComponent_t.
*/
#undef CC_NONE
enum CODE_COMPONENT {
    // компонент отсутствует или не определён
    CC_NONE = 0,

    // любой компонент
    CC_ANY = CC_NONE,

    // @see component-set.h

    // пустота
    CC_VACUUM = CC_NONE,

    // воздух (кислород + азот, #! без CARBON_ACID)
    CC_AIR = 1,

    // почвы
    //   - бесплодная почва
    CC_BARREN_SOIL,
    //   - плодородная почва
    CC_RICH_SOIL,

    // валун
    CC_BOULDER,
    // цельный камень
    CC_ROCK,

    // песок
    CC_SAND,

    // питательные вещества для углеродных особей
    //   - углеводы ( # Клетчатка - те же углеводы )
    CC_CARBOHYDRATE,
    //   - углекислый газ, CO2
    CC_CARBON_ACID,
    //   - жиры
    CC_FAT,
    //   - белки
    CC_PROTEIN,

    // скелет, кости
    CC_BONE,
    // продукт разложения углеродной особи
    CC_DETRITUS,

    // прочие компоненты жизнедеятельности особей (экскременты)
    //   - кал
    CC_FECES,
    //   - моча
    CC_URINE,

    // вода
    CC_WATER,

    // редкие элементы
    CC_SPARSE,

    // последний
    CC_last
};





/**
* Код компонента и массовая доля в целом элементе или
* количество компонента.
* Аналог portionEnergy_t.
*
* Например: белки = 0.2, жиры = 0.1, углеводы = 0.7.
* Например: белки = 6e6, жиры = 3e3, углеводы = 4e4.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_COMPONENT code;
    cl_float count;
} portionComponent_t;





/**
* Перечисление кодов в группе энергий
* GROUP_ELEMENT::GE_ENERGY.
*/
enum CODE_ENERGY {
    // энергия отсутствует или неопределена
    CE_NONE = 0,

    // электричество
    CE_ELECTRICITY,

    // тепло окруж. среды
    CE_HEAT,

    // видимый свет (излучения в видимом человеческому глазу диапазоне)
    CE_NORMAL_LIGHT,

    // радиация (излучения высокой частоты)
    CE_RADIATION,

    // последний
    CE_last
};




/**
* Код энергии и массовая доля в целом наборе энергий элемента или
* количество энергии.
* Аналог portionComponent_t.
*   # Количество энергии нормального света задаётся в люксах / день.
*     См. http://ru.wikipedia.org/wiki/%D0%9B%D1%8E%D0%BA%D1%81
*     Примеры освёщенности
        10?5 	    Свет Сириуса, ярчайшей звезды ночного неба
        0,0003 	    Безлунное звёздное небо
        0,01 	    Четверть Луны
        0,27 	    Полнолуние в ясном небе
        1 	        Полнолуние в тропиках
        до 20 	    В море на глубине ~50 м
        50 	        Жилая комната
        80 	        Подъезд/туалет
        100 	    Очень пасмурный день
        320-500     Рабочий кабинет
        350±150     Восход или закат на Венере
        400 	    Восход или закат в ясный день
        1000 	    Пасмурный день, освещение в телестудии
        1-3 тыс. 	Полдень на Венере
        4-5 тыс. 	Полдень в декабре — январе
        10-25 тыс. 	Ясный солнечный день (в тени)
        32-130 тыс. Под прямым солнцем
        135 тыс. 	Вне атмосферы на среднем расстоянии Земли от Солнца
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_ENERGY code;
    cl_float count;
} portionEnergy_t;







/**
* Информация о компоненте.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Код компонента.
    */
    enum CODE_COMPONENT code;

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
    * Дж / кг = Дж / моль разделить на Молярную массу
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
*   #! В этом списке индекс компонента соотв. коду компонента.
*/
typedef aboutOneComponent_t  aboutComponent_t[ COMPONENT_COUNT ];



/**
* Макс. кол-во компонентов с указанием частей от целого, которые могут
* *одновременно* храниться в 1-й ячейке портулана.
*/
typedef portionComponent_t  componentCell_t[ COMPONENT_CELL ];



/**
* Компоненты планеты. Какую часть объёма занимают в 1-й ячейке портулана.
*
*   # Ячейка области планеты всегда заполнена компонентами на 100%.
*
* Например: воздух 0.1, плодородная почва 0.7, вода 0.05, камень 0.15.
*/
typedef componentCell_t*  componentContent_t;
typedef struct __attribute__ ((packed)) {
    /**
    * Содержание в ячейке (по объёму).
    * Реализовано в виде частей (% / 100) концентрации компонентов.
    * Сумма всех = 1.0.
    */
    /* - Заменено на выделение памяти в куче, т.к. OpenCL при большом размере
         стека не инициализируется.
    typedef componentCell_t content_t[ COMPONENT_GRID * COMPONENT_GRID * COMPONENT_GRID ];
    */
    componentContent_t content;

} component_t;



#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
