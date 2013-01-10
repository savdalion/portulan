#pragma once

#include "../../Portulan.h"
#include <silhouette/include/shape/ElevationMap.h>
#include <silhouette/include/Shaper.h>
#include <typelib/typelib.h>
#include <boost/function.hpp>
#include <Magick++.h>


namespace portulan {

template< size_t SX, size_t SY, size_t SZ >
class Portulan;

}



/**
* ������� ����� ������ ��� �������� ����.
*/
namespace portulan {
    namespace command {
        namespace common {


#if 0
// - �������� �� ����� ������� ������. ��. ����.
template< size_t SX, size_t SY, size_t SZ, typename Number >
struct cmd {
    /**
    * ���� ������� ������������ ������� Portulan ��� ����� �������������.
    * ������ ������ � ��� ���� ������ � ��������� Portulan, � ������ �������
    * ���� � ����� ������ � �������� ��� ��������� ���������.
    */
    virtual void operator()( typename Portulan< SX, SY, SZ, Number >& ) const = 0;
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



    virtual void operator()( typename Portulan< SX, SY, SZ, Number >& ) const;

};

#endif





/**
* � ������� ������ �������� ����� ����� �������� ���������� �����-���������.
*/
template< size_t SX, size_t SY, size_t SZ >
void elevationMap(
    typename Portulan< SX, SY, SZ >&,
    const std::string& sign,
    const std::string& source,
    double scaleXY,
    double hMin,
    double hMax,
    const typelib::coordInt_t& shiftArea = typelib::coordInt_t::UNDEFINED(),
    const typelib::sizeInt_t& sizeArea = typelib::sizeInt_t::ONE()
);






/**
* ����������� ���������� (������� �����), �������� ������� ������ (0 - ���
* ��������, >0 - ���������), ��������� ��������� (������� ������).
* �������� ������ ������� ����� ������������� �� ��� ����������� SX, SY.
* ������� ���������� ������������ ����������� "gridHMin" � "gridHMax" �
* ������� ��������.
*/
template< size_t SX, size_t SY, size_t SZ >
void flood(
    typename Portulan< SX, SY, SZ >&,
    const std::string& sign,
    const std::string& source,
    int gridHMin,
    int gridHMax
);






/**
* ������������� ����������� � �������, ��������� �������� �������.
*/
typedef boost::function< float( const typelib::coordInt_t& c ) >  fnTemperature_t;

template< size_t SX, size_t SY, size_t SZ >
void temperature(
    typename Portulan< SX, SY, SZ >&,
    const fnTemperature_t&
);







        } // common
    } // command
} // portulan












#include "common.inl"
