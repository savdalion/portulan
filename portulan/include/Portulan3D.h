#pragma once

#include "command.h"
#include <typelib/include/mapcontent3d/SignBitMap.h>
//#include <mapcontent3d/SignNumberMap.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ, typename Number = float >
class Portulan;

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
*   # Портулан (карта) разбит(а) на равные и равносторонние ячейки.
*   # Карта хранит информацию в виде элементов, заполняющих ячейки.
*   # Элементы представляют собой "блоки из вещества" (воздух, горные
*     породы, чистые хим. элементы и т.п.).
*   # Элементы позиционируются по целым ячейкам.
*   # Если не указано обратного (см. св-во "plenum"), элемент заполняет
*     собой всю ячейку.
*
* 
* @template Number В каком формате будут задаваться числа. Рекомендации:
*             - "float" - для быстрых расчётов
*             - "char" - для оптимального хранения
*/
template< size_t SX, size_t SY, size_t SZ, typename Number >
class Portulan3D {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Portulan3D >  Ptr;
    typedef std::unique_ptr< Portulan3D >  UPtr;


public:
    /**
    * Слои 3D-наборов.
    */
    typedef typelib::SignBitMap< SX, SY, SZ >  bitLayer_t;
    typedef std::shared_ptr< bitLayer_t >  bitLayerPtr_t;

    /* - @todo ...
    typedef typelib::SignNumberMapContent3D< Number, SX, SY, SZ >  numberLayer_t;
    typedef std::shared_ptr< numberLayer_t >  numberLayerPtr_t;
    */


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
        *//* - @todo ... Понятней будет включать "диаметр частицы".
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



    /* - Заменено на простые методы - см. portulan::command.
    Portulan3D& operator<<( const command::cmd< SX, SY, SZ, Number >& );
    */





private:
    /**
    * Топология карты.
    */
    topology_t mTopology;

};




} // portulan








#include "Portulan3D.inl"
