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
* ������� ����� ������ ��� �������� ����.
*/
namespace portulan {
    namespace command {


#if 0
// - �������� �� ����� ������� ������. ��. ����.
template< size_t SX, size_t SY, size_t SZ, typename Number >
struct cmd {
    /**
    * ���� ������� ������������ ������� Portulan3D ��� ����� �������������.
    * ������ ������ � ��� ���� ������ � ��������� Portulan3D, � ������ �������
    * ���� � ����� ������ � �������� ��� ��������� ���������.
    */
    virtual void operator()( typename Portulan3D< SX, SY, SZ, Number >& ) const = 0;
};




template< size_t SX, size_t SY, size_t SZ, typename Number >
struct elevationMap : public cmd< SX, SY, SZ, Number > {
    /**
    * ����� ��������.
    */
    const typelib::Sign<> sign;

    /**
    * ���� � ������ �����.
    */
    const std::string source;

    /**
    * ������� ����� � ��������� XY.
    * ��������, �������� ������������� 400 ��� (������ �����������)
    * � ~100 �� (������ ����������� �����) ����� ����� ������� =
    * = 100.0 / 400.0 = 0.25
    */
    const double scaleXY;

    /**
    * ����������� � ������������ ������ �� ����� �����, ��.
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
* ����� ����� �������� � ������� ������ �������� ���������� �����-���������.
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
* ����������� ���������� (������� �����), �������� ������� ������ (0 - ���
* ��������, >0 - ���������), ��������� ��������� (������� ������).
* �������� ������ ������� ����� ������������� �� ��� ����������� SX, SY.
* ������ ���������� ������������ 
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
* ������������� ����������� � �������, ��������� �������� �������.
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
