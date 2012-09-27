#pragma once

#include "component.h"
#include <typelib/typelib.h>


/**
* Наборы компонентов (элементы не живой природы) для декларации
* области планеты.
*
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {


namespace tc = typelib::constant::physics;


static const aboutComponent_t aboutComponent = {
/**
* Пустой компонент для выравнивания индексов списка по CODE_COMPONENT.
*/
{
    // code
    CC_NONE,
    // density
    0.0f,
    // meltingPoint
    0.0f,
    // boilingPoint
    0.0f,
    // enthalpyFusion
    0.0f,
    // enthalpyVaporization
    0.0f,
    // heatCapacity
    0.0f
},



/**
* Вакуум.
*   # Вакуум считаем абсолютным.
*/
{
    // code
    //CC_VACUUM,
    CC_NONE,
    // density
    0.0f,
    // meltingPoint
    0.0f,
    // boilingPoint
    0.0f,
    // enthalpyFusion
    0.0f,
    // enthalpyVaporization
    0.0f,
    // heatCapacity
    0.0f
},



/**
* Воздух.
*   # Некоторые физические хар-ки воздуха взяты по азоту
*     http://ru.wikipedia.org/wiki/%D0%90%D0%B7%D0%BE%D1%82
*/
{
    // code
    CC_AIR,
    // density
    1.3f,
    // meltingPoint
    63.3f,
    // boilingPoint
    77.4f,
    // enthalpyFusion
    720.0f,
    // enthalpyVaporization
    5570.0f,
    // heatCapacity
    1010.0f
},



/**
* Бесплодная почва.
*   # Некоторые физические хар-ки бесплодной почвы взяты по кремнию
*     http://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B5%D0%BC%D0%BD%D0%B8%D0%B9
*
* @source http://enc.sci-lib.com/article0001048.html
*/
{
    // code
    CC_BARREN_SOIL,
    // density
    1500.0f,
    // meltingPoint
    1688.0f / 1.5f,
    // boilingPoint
    2623.0f / 1.5f,
    // enthalpyFusion
    50600.0f / 0.02809f / 1.5f,
    // enthalpyVaporization
    383000.0f / 0.02809f / 1.5f,
    // heatCapacity
    20.16f / 0.02809f / 1.5f
},



/**
* Плодородная почва.
*   # Некоторые физические хар-ки полодородной почвы взяты по кремнию
*     http://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B5%D0%BC%D0%BD%D0%B8%D0%B9
*
* @source http://enc.sci-lib.com/article0001048.html
*/
{
    // code
    CC_RICH_SOIL,
    // density
    1200.0f,
    // meltingPoint
    1688.0f / 2.0f,
    // boilingPoint
    2623.0f / 2.0f,
    // enthalpyFusion
    50600.0f / 0.02809f / 2.0f,
    // enthalpyVaporization
    383000.0f / 0.02809f / 2.0f,
    // heatCapacity
    20.16f / 0.02809f / 2.0f
},



/**
* Валун.
*   # Физ. хар-ки валуна ~ хар-ки камня CC_ROCK.
*/
{
    // code
    CC_BOULDER,
    // density
    2330.0f,
    // meltingPoint
    1688.0f,
    // boilingPoint
    2623.0f,
    // enthalpyFusion
    50600.0f / 0.02809f,
    // enthalpyVaporization
    383000.0f / 0.02809f,
    // heatCapacity
    20.16f / 0.02809f
},



/**
* Цельный камень.
*   # Некоторые физические хар-ки цельного камня взяты по кремнию
*     http://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B5%D0%BC%D0%BD%D0%B8%D0%B9
*/
{
    // code
    CC_ROCK,
    // density
    2330.0f,
    // meltingPoint
    1688.0f,
    // boilingPoint
    2623.0f,
    // enthalpyFusion
    50600.0f / 0.02809f,
    // enthalpyVaporization
    383000.0f / 0.02809f,
    // heatCapacity
    20.16f / 0.02809f
},



// @todo ...

};


            } // dungeoncrawl
        } // set
    } // planet
} // portulan
