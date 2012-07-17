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
* ��������� ��� ������ � ����������.
* ������ ��������, ��� ��������� ���������� ��������� ����������
* (��. � Portulan3D).
*/
template< size_t SX, size_t SY, size_t SZ >
struct Topology {
    /**
    * ������.
    */
    typedef std::shared_ptr< Topology >  Ptr;
    typedef std::unique_ptr< Topology >  UPtr;
    typedef std::weak_ptr< Topology >    WPtr;


    /**
    * ���� 3D-������� �����.
    */
    typedef typelib::SignBitMap< SX, SY, SZ >  signBitLayer_t;
    typedef typelib::SignNumberMap< float, SX, SY, SZ >  signNumberLayer_t;


    /**
    * ��������� 3D-����.
    */
    typedef typelib::NumberMap< float, SX, SY, SZ >  numberLayer_t;



    // �������� ������������� - ��. � Topology::private


    /**
    * @return �����������.
    */
    signBitLayer_t const& presence() const;
    signBitLayer_t& presence();



    /**
    * @return �������������.
    */
    signNumberLayer_t const& plenum() const;
    signNumberLayer_t& plenum();



    /**
    * @return �����������.
    */
    numberLayer_t const& temperature() const;
    numberLayer_t& temperature();




private:
    /**
    * ���� � ����������� �� ��������� � �� "�����������" �� �����.
    *
    * @see plenum
    * @see harmonize()
    */
    signBitLayer_t mPresence;

        
    // �������������� �������������� ���������.

    /**
    * �������������.
    * �� ������� ������ ��������� ���������. ������, ����� "�������������"
    * ���� ����������� � ������ ��������� == 1.0 (100%). ���� �� %
    * ��������������� �� ���������, ����� �������� ��� � "plenum", �� ����
    * � "presence". �� @todo ���������� �������� � ������ ����������
    * ���������. �, ��������, ��������� ������ ������ ����� ������� � ����
    * ������ ��������� ���-�� ���� ��� ������������� �����. ��� ���� %
    * ������ � ������ ������� ����������.
    *
    * @see harmonize()
    */
    signNumberLayer_t mPlenum;


    /**
    * ������������ / ����������.
    *   # ������� ��������� �������.
    *   # ������������ = 1 / ������� �������.
    *//* - @todo ... �������� ����� �������� "������� �������".
    */


    /**
    * ����������� � ������� �����.
    * ���� ���� ���������� �� ��� �����.
    * ����������� � �������������� ��������� ���������� ����������
    * ��������� ����������� � ������ ��������� (�������).
    */
    numberLayer_t mTemperature;


    /**
    * �������� � ������� �����.
    * ���� ���� �������� �� ��� �����.
    */
    //numberLayer_t pressure;


    /**
    * ����������� ���, ����������� �� ������ �����.
    * ? ���� ���� ��� �� ��� �����.
    */
    //numberLayer_t force;

};




} // portulan








#include "Topology.inl"
