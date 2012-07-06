#pragma once

#include "command.h"
#include <SignBitMapContent3D.h>
#include <SignNumberMapContent3D.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ, typename Number = float >
class Portulan;

/* - @todo ...
template<>
typedef std::shared_ptr< Portulan<> >  PortulanPtr;
*/

}


/* - @todo ...
namespace std {

template< typename Number, size_t SX, size_t SY, size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::Portulan< SX, SY, SZ, Number >& );

} // std
*/



namespace portulan {


/**
* Класс для эффективного хранения и обработки 3D-карт на графических
* процессорах (OpenCL, Cuda).
*
* Соглашения
*   # Портулан (карта) разбит(а) на равные ячейки.
*   # Карта хранит информацию в виде элементов, заполняющих ячейки.
*   # Элементы представляют собой "блоки из вещества" (воздух, горные
*     породы, чистые хим. элементы и т.п.).
*   # Элементы позиционируются по целым ячейкам.
*   # Если не указано обратного (см. "plenum"), элемент заполняет собой
*     всю ячейку.
*
* 
* @template Number В каком формате будут задаваться числа. Рекомендации:
*             - "float" - для эффективных рассчётов
*             - "char" - для оптимального хранения
*/
template< size_t SX, size_t SY, size_t SZ, typename Number >
class Portulan3D {
public:
    /**
    * Слои 3D-наборов.
    */
    typedef typelib::SignBitMapContent3D< SX, SY, SZ >  bitLayer_t;
    typedef std::shared_ptr< bitLayer_t >  bitLayerPtr_t;

    typedef typelib::SignNumberMapContent3D< Number, SX, SY, SZ >  numberLayer_t;
    typedef std::shared_ptr< numberLayer_t >  numberLayerPtr_t;


    /**
    * Строение (топология) карты.
    */
    struct topology_t {
        /**
        * Слой с информацией об элементах и их "присутствии" на карты.
        */
        bitLayer_t present;

        
        // Количественные характеристики элементов.

        /**
        * Заполненность.
        * На сколько % ячейка заполнена элементом. Обычно, сумма "заполненности"
        * для одной ячейки == 100%. Этот же % подразумевается по умолчанию (если
        * элемента нет в списке "plenum"). Но @todo существуют элементы в разном
        * дисперсном состоянии. И, например, кварцевая галька вполне может
        * принять в свою ячейку некоторый % воды или магнетитового песка. При
        * этом % гальки в ячейке остаётся неизменным.
        *//* - @todo ...
        numberLayer_t plenum;
        */

        /**
        * Дисперсность / пористость.
        *   # Частицы считаются сферами.
        *   # Дисперсность = 1 / диаметр частицы.
        *//* - @todo ...
        */

    };




    inline Portulan3D() {
        // для пустых меток не создаём слой
    }




    inline virtual ~Portulan3D() {
    }



    inline topology_t const& topology() const {
        return mTopology;
    }



    inline topology_t& topology() {
        return mTopology;
    }




    template< typename T >
    Portulan3D& operator<<( const command::cmd< T >& );





private:
    /**
    * Топология карты.
    */
    topology_t mTopology;

};




} // portulan








#include "Portulan3D.inl"
