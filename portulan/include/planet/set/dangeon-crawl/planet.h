#pragma once

#include "structure.h"
#include "component.h"


/**
* Структура планеты.
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {

/**
* Общая информация о планете.
*/
typedef struct {
    /**
    * Радиус планеты, м.
    */
    cl_float radiusPlanet;

    /**
    * Размер области планеты, м.
    * Радиус атмосферы = Размер области планеты / 2
    * Толщина атмосферы = Радиус атмосферы - Радиус планеты
    */
    cl_float sizeArea;

    /**
    * Масса планеты, кг.
    */
    cl_float massPlanet;

    /**
    * Состав планеты, перечисление всех компонентов и их массовой части в целом.
    *
    *   # Для удобства код компонента соотв. его индексу в componentAll_t.
    *   # Неиспользуемые компоненты заполняются нулями.
    */
    component::componentAll_t componentPlanet;

    /**
    * Масса атмосферы, кг.
    */
    cl_float massAtmosphere;

    /**
    * Состав атмосферы, перечисление всех компонентов и их массовой части в целом.
    *
    * @see Соглашения для componentPlanet.
    */
    component::componentAll_t componentAtmosphere;

    /**
    * Жизнь на планете, перечисление особей и их кол-во в области планеты.
    */
    living::livingAll_t livingPlanet;

} aboutPlanet_t;


            } // dungeoncrawl
        } // set
    } // planet
} // portulan
