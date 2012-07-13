#pragma once

#include "command.h"
#include "Booster.h"
#include <typelib/typelib.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ >
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
*   # Числовые значения объёма хранятся в виде float-чисел.
*
* 
* @template Number В каком формате будут задаваться числа. Рекомендации:
*             - "float" - для быстрых расчётов
*             - "char" - для оптимального хранения
*/
template< size_t SX, size_t SY, size_t SZ >
class Portulan3D : public Booster {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Portulan3D >  Ptr;
    typedef std::unique_ptr< Portulan3D >  UPtr;


public:
    /**
    * Слои 3D-наборов меток.
    */
    typedef typelib::SignBitMap< SX, SY, SZ >  signBitLayer_t;

    //typedef typelib::SignNumberMap< float, SX, SY, SZ >  signNumberLayer_t;


    /**
    * Одиночные 3D-слои.
    */
    typedef typelib::NumberMap< float, SX, SY, SZ >  numberLayer_t;




    /**
    * Строение (топология) карты.
    */
    struct topology_t {
        /**
        * Слой с информацией об элементах и их "присутствии" на карты.
        */
        signBitLayer_t presence;

        
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


        /**
        * Температура в ячейках карты.
        * Один слой температур на всю карту.
        * Температура и характеристика элементов определяют агрегатное
        * состояние находящихся в ячейке элементов (веществ).
        */
        numberLayer_t temperature;


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




    /**
    * Структура для ускорения работы с картой.
    * Данные хранятся в виде, подходящем для обработки параллельными
    * алгоритмами (технологии OpenCL, Cuda).
    */
    struct booster_t {
        float temperature[ SX * SY * SZ ];
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





protected:
    /**
    * Методы для записи данных портулана в структуру booster_t.
    */
    virtual void toBooster();



    /**
    * Методы для записи данных из структуры booster_t в портулан.
    */
    virtual void fromBooster();





private:
    /**
    * Топология карты.
    */
    topology_t mTopology;


    /**
    * Структура для быстрой работы с картой.
    */
    booster_t mBooster;

};




} // portulan








#include "Portulan3D.inl"
