#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"


/**
* Ландшафт (географический ландшафт) для моделирования планеты
* на основе мира игры Dungeon Crawl.
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
* Элементы геоландшафта.
* Перечисление кодов элементов (гео)ландшафта из группы
* GROUP_ELEMENT::GE_ELEMENT_LANDSCAPE.
*
* @todo Формы рельефа > http://ru.wikipedia.org/wiki/%D0%A4%D0%BE%D1%80%D0%BC%D0%B0_%D1%80%D0%B5%D0%BB%D1%8C%D0%B5%D1%84%D0%B0
*/
enum CODE_ELEMENT_LANDSCAPE {
    // отсутствует или не определён
    CEL_NONE = 0,

    // любой
    CEL_ANY = CEL_NONE,

    // гора, холм
    // любая возвышенность
    // образуют горные массивы
    CEL_MOUNTAIN,

    // котловина
    // любое углубление
    CEL_BASIN,

    // хребет
    CEL_RANGE,

    // ложбина, ущелье, лощина, овраг
    CEL_RAVINE,

    // озеро, море, пруд, океан
    // заполненное жидким компонентом углубление
    CEL_LAKE,
    CEL_SEA   = CEL_LAKE,
    CEL_POND  = CEL_LAKE,
    CEL_OCEAN = CEL_LAKE,

    // река
    // перемещающейся по углублению жидкий компонент
    CEL_RIVER,

    // водопад
    // падающий с высоты жидкий компонент
    CEL_CASCADE,

    // дорога
    // лента из твёрдых компонентов, вдоль которой можно перемещаться
    CEL_ROAD,

    // последний
    CEL_last,
};





/**
* Создаём объединение, позволяющее эффективно декларировать
* различные элементы ландшафта.
*   # Для каждого элемента ландшафта создаётся одноимённая структура
*     с суффиксом Landscape_t.
*   # Все структуры сбрасываются в объединение для эффективного хранения
*     и удобного доступа к информации об элементе.
*   # Т.к. хранить будем информацию о множестве подобных объединений,
*     декларируется "коэффициент разброса" 
*/

typedef struct __attribute__ ((packed)) {

    cl_float height;

    /**
    * Крутизна склонов, градусы.
    * [0; 90]
    * @todo extend Можно круче: отвесные скалы.
    */
    cl_float slope;

} mountainLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float depth;

    /**
    * Крутизна склонов, градусы.
    * [0; 90]
    * @todo extend Можно круче: отвесные стены.
    */
    cl_float slope;

} basinLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float height;

    /**
    * Протяжённость, м.
    */
    cl_float length;

} rangeLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float depth;

    /**
    * Протяжённость, м.
    */
    cl_float length;

} ravineLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float depth;

    /**
    * Каким компонентом заполнено.
    */
    CODE_COMPONENT component;

} lakeLandscape_t;


typedef struct __attribute__ ((packed)) {

    /**
    * Глубина реки.
    * @todo Водоёмы могут находиться в углублении.
    */
    cl_float depth;

    /**
    * Какой компонент течёт.
    */
    CODE_COMPONENT component;

    /**
    * Скорость течения, м/с.
    */
    cl_float drift;

    /**
    * Направление течения: север, юг, ...
    */
    ...

} riverLandscape_t;


// итог
typedef union __attribute__ ((packed)) {
    mountainLandscape_t  mountain;
    basinLandscape_t     basin;
    rangeLandscape_t     range;
    ravineLandscape_t    ravine;
    lakeLandscape_t      lake;
    riverLandscape_t     river;

    @todo ...

} aboutElementLandscape_t;







/**
* Описание элемента ландшафта.
*
* @see landscapeCell_t
*/
typedef struct __attribute__ ((packed)) {

    enum CODE_ELEMENT_GEOLANDSCAPE  code;

    aboutElementLandscape_t         about;

    /**
    * Коэффициент разброса параметров для элемента.
    * Функция - та же, что survivorLiving_t::adaptability.
    * Введён, т.к. хранить будем информацию о множестве подобных объединений.
    */
    cl_float scattering;

} elementLandscape_t;




/**
* Описание ландшафта.
* Ячейка портулана с информацией об элементах ландшафта.
* Т.к. территория планеты - большая, одна ячейка простирается на сотни км,
* поэтому может содержать множество - LANDSCAPE_CELL - ландшафтов.
*/
typedef elementLandscape_t  landscapeCell_t[ LANDSCAPE_CELL ];




/**
* Ландшафт планеты.
*/
typedef landscapeCell_t*  landscapeContent_t;
typedef struct __attribute__ ((packed)) {
    landscapeContent_t content;
} landscape_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
