#pragma once

#include "../../Portulan3D.h"
#include <Sign.h>



/**
* ������� ����� ������ ��� �������� ����.
*/
namespace portulan {
    namespace command {


template< typename T >
struct cmd {
    /**
    * ���� ������� ������������ ������� Portulan3D ��� ����� �������������.
    * ������ ������ � ��� ���� ������ � ��������� Portulan3D, � ������ �������
    * ���� � ����� ������ � �������� ��� ��������� ���������.
    */
    virtual void operator()( T& ) const = 0;
};




template< typename T >
struct elevationMap : public cmd< T > {
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
