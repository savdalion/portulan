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
* ����� ��� ������������ �������� � ��������� 3D-���� �� �����������
* ����������� (OpenCL, Cuda).
*
* ����������
*   # �������� (�����) ������(�) �� ������ � �������������� ������.
*   # ����� ������ ���������� � ���� ���������, ����������� ������.
*   # �������� ������������ ����� "����� �� ��������" (������, ������
*     ������, ������ ���. �������� � �.�.).
*   # �������� ��������������� �� ����� �������.
*   # ���� �� ������� ��������� (��. ��-�� "plenum"), ������� ���������
*     ����� ��� ������.
*
* 
* @template Number � ����� ������� ����� ���������� �����. ������������:
*             - "float" - ��� ������� ��������
*             - "char" - ��� ������������ ��������
*/
template< size_t SX, size_t SY, size_t SZ, typename Number >
class Portulan3D {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Portulan3D >  Ptr;
    typedef std::unique_ptr< Portulan3D >  UPtr;


public:
    /**
    * ���� 3D-�������.
    */
    typedef typelib::SignBitMap< SX, SY, SZ >  bitLayer_t;
    typedef std::shared_ptr< bitLayer_t >  bitLayerPtr_t;

    /* - @todo ...
    typedef typelib::SignNumberMapContent3D< Number, SX, SY, SZ >  numberLayer_t;
    typedef std::shared_ptr< numberLayer_t >  numberLayerPtr_t;
    */


    /**
    * �������� (���������) �����.
    */
    struct topology_t {
        /**
        * ���� � ����������� �� ��������� � �� "�����������" �� �����.
        */
        bitLayer_t present;

        
        // �������������� �������������� ���������.

        /**
        * �������������.
        * �� ������� % ������ ��������� ���������. ������, ����� "�������������"
        * ��� ����� ������ == 100%. ���� �� % ��������������� �� ��������� (����
        * �������� ��� � ������ "plenum"). �� @todo ���������� �������� � ������
        * ���������� ���������. �, ��������, ��������� ������ ������ �����
        * ������� � ���� ������ ��������� % ���� ��� ������������� �����. ���
        * ���� % ������ � ������ ������� ����������.
        *//* - @todo ...
        numberLayer_t plenum;
        */

        /**
        * ������������ / ����������.
        *   # ������� ��������� �������.
        *   # ������������ = 1 / ������� �������.
        *//* - @todo ... �������� ����� �������� "������� �������".
        */

    };




    inline Portulan3D() {
        // ��� ������ ����� �� ������ ����
    }




    inline virtual ~Portulan3D() {
    }



    inline topology_t const& topology() const {
        return mTopology;
    }



    inline topology_t& topology() {
        return mTopology;
    }



    /* - �������� �� ������� ������ - ��. portulan::command.
    Portulan3D& operator<<( const command::cmd< SX, SY, SZ, Number >& );
    */





private:
    /**
    * ��������� �����.
    */
    topology_t mTopology;

};




} // portulan








#include "Portulan3D.inl"
