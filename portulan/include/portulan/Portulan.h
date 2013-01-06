#pragma once

#include "command.h"
#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ >
class Portulan;

}


/* - @todo ...
namespace std {

template< size_t SX, size_t SY, size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::Portulan< SX, SY, SZ >& );

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
*   # Числовые значения объёма хранятся в виде float-чисел.
*
*/
template< size_t SX, size_t SY, size_t SZ >
class Portulan {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Portulan >  Ptr;
    typedef std::unique_ptr< Portulan >  UPtr;
    typedef std::weak_ptr< Portulan >    WPtr;


    typedef Topology< SX, SY, SZ>  topology_t;



public:

    inline Portulan() {
    }




    inline virtual ~Portulan() {
    }




    inline topology_t const& topology() const {
        return mTopology;
    }



    inline topology_t& topology() {
        return mTopology;
    }



    /* - Заменено на простые методы - см. portulan::command.
    Portulan& operator<<( const command::cmd< SX, SY, SZ, Number >& );
    */



    /**
    * Согласовывает все характеристики топологии.
    * Правила - см. в коде метода.
    */
    void XXharmonize();



    /**
    * Согласовывает знач. для "заполненности" (топология).
    * Правила - см. в коде метода.
    *
    * @param saveCorrect Нормализация проходит только для значений выходящих
    *        за пределы диапазона [0.0; 1.0]
    * @param strictHarmonize Нормализовать, даже если все значения лежат в
    *        диапазоне [0.0; 1.0].
    */
    void harmonizePlenum( bool saveCorrect, bool strictHarmonize );



    /**
    * Согласовывает знач. "заполненности" с учётом "присутствия" (топология).
    * Правила - см. в коде метода.
    */
    void harmonizePresenceToPlenum();






private:
    /**
    * Топология карты.
    */
    topology_t mTopology;

};




} // portulan








#include "Portulan.inl"
