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
* (��. � Portulan).
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
    typedef float Number;
    typedef typelib::SignNumberMap< Number, SX, SY, SZ >  signNumberLayer_t;


    /**
    * ��������� 3D-����.
    */
    typedef typelib::NumberMap< Number, SX, SY, SZ >  numberLayer_t;


    /**
    * ���� �������� ���.
    */
    typedef typelib::VectorMap< Number, SX, SY, SZ >  vectorLayer_t;



    // �������� ������������� - ��. � Topology::private


    /**
    * @return �����������.
    */
    signBitLayer_t const& presence() const;
    signBitLayer_t& presence();


    /**
    * @return �������� ��� �������� �����.
    */
    typename signBitLayer_t::layerRaw_t const&  presence( const typelib::Sign<>& ) const;


    /**
    * @return ����������� �������� ����� �� �������� �������.
    *         false, ���� ����� �� �������.
    */
    bool presence( const typelib::Sign<>&, size_t i ) const;



    /**
    * @return �������������.
    */
    signNumberLayer_t const& plenum() const;
    signNumberLayer_t& plenum();


    /**
    * @return �������� "�������������". ����������� ���� "�������������" �
    *         "�����������". ��. ������� ����������� �
    *         Portulan::harmonizePresenceToPlenum().
    *         0, ���� ����� �����������.
    *
    * @see Portulan::harmonize()
    */
    Number plenum( const typelib::Sign<>&, size_t i ) const;



    /**
    * @return �����������.
    */
    numberLayer_t const& temperature() const;
    numberLayer_t& temperature();



    /**
    * @return ����.
    */
    vectorLayer_t const& force() const;
    vectorLayer_t& force();




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
    *//* - @todo ...
    signNumberLayer_t mPlenum;
    */


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
    * ������� ���, ����������� �� ������ �����.
    * ���� ���� ��� �� ��� �����.
    *//* - @todo ...
    vectorLayer_t mForce;
    */

};




} // portulan








#include "Topology.inl"
