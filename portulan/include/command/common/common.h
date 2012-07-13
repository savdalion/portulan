#pragma once

#include "../../Portulan3D.h"
#include <silhouette/include/shape/ElevationMap.h>
#include <silhouette/include/Shaper.h>
#include <typelib/typelib.h>
#include <boost/function.hpp>


namespace portulan {

template< size_t SX, size_t SY, size_t SZ >
class Portulan3D;

}



/**
* Базовый набор команд для создания карт.
*/
namespace portulan {
    namespace command {


#if 0
// - Заменено на более простые методы. См. ниже.
template< size_t SX, size_t SY, size_t SZ, typename Number >
struct cmd {
    /**
    * Этот функтор используется классом Portulan3D для своей трансформации.
    * Внтури метода у нас есть доступ к свойствам Portulan3D, а каждая команда
    * несёт с собой данные и алгоритм для изменения портулана.
    */
    virtual void operator()( typename Portulan3D< SX, SY, SZ, Number >& ) const = 0;
};




template< size_t SX, size_t SY, size_t SZ, typename Number >
struct elevationMap : public cmd< SX, SY, SZ, Number > {
    /**
    * Метка элемента.
    */
    const typelib::Sign<> sign;

    /**
    * Файл с картой высот.
    */
    const std::string source;

    /**
    * Масштаб карты в плоскости XY.
    * Например, картинка протяжённостью 400 пкс (размер изображения)
    * и ~100 км (размер создаваемой карты) будет иметь масштаб =
    * = 100.0 / 400.0 = 0.25
    */
    const double scaleXY;

    /**
    * Минимальная и максимальная высота на карте высот, км.
    */
    const double hMin;
    const double hMax;


    elevationMap(
        const std::string& sign,
        const std::string& source,
        double scaleXY, double hMin, double hMax
    );



    virtual void operator()( typename Portulan3D< SX, SY, SZ, Number >& ) const;

};

#endif





/**
* Карта высот создаётся в битовом объёме согласно указанному файлу-источнику.
*/
template< size_t SX, size_t SY, size_t SZ >
void elevationMap(
    typename Portulan3D< SX, SY, SZ >&,
    const std::string& sign,
    const std::string& source,
    double scaleXY,
    double hMin,
    double hMax,
    const typelib::coordInt_t& shiftArea = typelib::coordInt_t::UNDEFINED(),
    const typelib::psizeInt_t& sizeArea = typelib::psizeInt_t::ONE()
);






/**
* Затапливает территорию (битовый объём), заданную битовым файлом (0 - нет
* значения, >0 - заполнить), указанным веществом (задаётся меткой).
* Заданная файлом битовая маска растягивается на всю поверхность SX, SY.
* Высота затопления определяется 
*/
template< size_t SX, size_t SY, size_t SZ >
void flood(
    typename Portulan3D< SX, SY, SZ >&,
    const std::string& sign,
    const std::string& source,
    size_t gridHMin,
    size_t gridHMax
);






/**
* Устанавливает температуру в ячейках, используя заданную функцию.
*/
typedef boost::function< float( const typelib::coordInt_t& c ) >  fnTemperature_t;

template< size_t SX, size_t SY, size_t SZ >
void temperature(
    typename Portulan3D< SX, SY, SZ >&,
    const fnTemperature_t&
);







    } // command
} // portulan












#include "common.inl"
