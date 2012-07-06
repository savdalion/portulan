#pragma once

#include "../../Portulan3D.h"
#include <Sign.h>



/**
* Базовый набор команд для создания карт.
*/
namespace portulan {
    namespace command {


template< typename T >
struct cmd {
    /**
    * Этот функтор используется классом Portulan3D для своей трансформации.
    * Внтури метода у нас есть доступ к свойствам Portulan3D, а каждая команда
    * несёт с собой данные и алгоритм для изменения портулана.
    */
    virtual void operator()( T& ) const = 0;
};




template< typename T >
struct elevationMap : public cmd< T > {
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



    virtual void operator()( T& ) const;

};





/*
template< size_t SX, size_t SY, size_t SZ, typename Number >
boost::function< void ( typename Portulan3D< SX, SY, SZ, Number >& ) >
elevationMap = operator( typename Portulan3D< SX, SY, SZ, Number >& ) -> const {

};
*/





    } // command
} // portulan












#include "common.inl"
