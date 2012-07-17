#pragma once

#include <typelib/typelib.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ >
struct Topology;

}


/* - @todo ...
namespace std {

template< size_t SX, size_t SY, size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::Topology< SX, SY, SZ >& );

} // std
*/



namespace portulan {


/**
* Структура для работы с топологией.
* Помимо удобства, эта структура декларирут некоторые соглашения
* (см. в Portulan3D).
*/
template< size_t SX, size_t SY, size_t SZ >
struct Topology {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Topology >  Ptr;
    typedef std::unique_ptr< Topology >  UPtr;
    typedef std::weak_ptr< Topology >    WPtr;


    /**
    * Слои 3D-наборов меток.
    */
    typedef typelib::SignBitMap< SX, SY, SZ >  signBitLayer_t;
    typedef typelib::SignNumberMap< float, SX, SY, SZ >  signNumberLayer_t;


    /**
    * Одиночные 3D-слои.
    */
    typedef typelib::NumberMap< float, SX, SY, SZ >  numberLayer_t;



    // Описание характеристик - см. в Topology::private


    /**
    * @return Присутствие.
    */
    signBitLayer_t const& presence() const;
    signBitLayer_t& presence();



    /**
    * @return Заполненность.
    */
    signNumberLayer_t const& plenum() const;
    signNumberLayer_t& plenum();



    /**
    * @return Температура.
    */
    numberLayer_t const& temperature() const;
    numberLayer_t& temperature();




private:
    /**
    * Слой с информацией об элементах и их "присутствии" на карты.
    *
    * @see plenum
    * @see harmonize()
    */
    signBitLayer_t mPresence;

        
    // Количественные характеристики элементов.

    /**
    * Заполненность.
    * На сколько ячейка заполнена элементом. Обычно, сумма "заполненности"
    * всех находящихся в ячейке элементов == 1.0 (100%). Этот же %
    * подразумевается по умолчанию, когда элемента нет в "plenum", но есть
    * в "presence". Но @todo существуют элементы в разном дисперсном
    * состоянии. И, например, кварцевая галька вполне может принять в свою
    * ячейку некоторое кол-во воды или магнетитового песка. При этом %
    * гальки в ячейке остаётся неизменным.
    *
    * @see harmonize()
    */
    signNumberLayer_t mPlenum;


    /**
    * Дисперсность / пористость.
    *   # Частицы считаются сферами.
    *   # Дисперсность = 1 / диаметр частицы.
    *//* - @todo ... Понятней будет включать "диаметр частицы".
    */


    /**
    * Температура в ячейках карты.
    * Один слой температур на всю карту.
    * Температура и характеристика элементов определяют агрегатное
    * состояние находящихся в ячейке элементов (веществ).
    */
    numberLayer_t mTemperature;


    /**
    * Давление в ячейках карты.
    * Один слой давлений на всю карту.
    */
    //numberLayer_t pressure;


    /**
    * Направление сил, действующих на ячейки карты.
    * ? Один слой сил на всю карту.
    */
    //numberLayer_t force;

};




} // portulan








#include "Topology.inl"
