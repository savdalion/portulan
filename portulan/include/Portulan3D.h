#pragma once

#include "command.h"
#include <SignBitMapContent3D.h>
#include <SignNumberMapContent3D.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ, typename Number = float >
class Portulan;

/* - @todo ...
template<>
typedef std::shared_ptr< Portulan<> >  PortulanPtr;
*/

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
*   # �������� (�����) ������(�) �� ������ ������.
*   # ����� ������ ���������� � ���� ���������, ����������� ������.
*   # �������� ������������ ����� "����� �� ��������" (������, ������
*     ������, ������ ���. �������� � �.�.).
*   # �������� ��������������� �� ����� �������.
*   # ���� �� ������� ��������� (��. "plenum"), ������� ��������� �����
*     ��� ������.
*
* 
* @template Number � ����� ������� ����� ���������� �����. ������������:
*             - "float" - ��� ����������� ���������
*             - "char" - ��� ������������ ��������
*/
template< size_t SX, size_t SY, size_t SZ, typename Number >
class Portulan3D {
public:
    /**
    * ���� 3D-�������.
    */
    typedef typelib::SignBitMapContent3D< SX, SY, SZ >  bitLayer_t;
    typedef std::shared_ptr< bitLayer_t >  bitLayerPtr_t;

    typedef typelib::SignNumberMapContent3D< Number, SX, SY, SZ >  numberLayer_t;
    typedef std::shared_ptr< numberLayer_t >  numberLayerPtr_t;


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
        *//* - @todo ...
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




    template< typename T >
    Portulan3D& operator<<( const command::cmd< T >& );





private:
    /**
    * ��������� �����.
    */
    topology_t mTopology;

};




} // portulan








#include "Portulan3D.inl"
