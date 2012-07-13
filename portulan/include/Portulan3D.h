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
*   # �������� �������� ������ �������� � ���� float-�����.
*
* 
* @template Number � ����� ������� ����� ���������� �����. ������������:
*             - "float" - ��� ������� ��������
*             - "char" - ��� ������������ ��������
*/
template< size_t SX, size_t SY, size_t SZ >
class Portulan3D : public Booster {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Portulan3D >  Ptr;
    typedef std::unique_ptr< Portulan3D >  UPtr;


public:
    /**
    * ���� 3D-������� �����.
    */
    typedef typelib::SignBitMap< SX, SY, SZ >  signBitLayer_t;

    //typedef typelib::SignNumberMap< float, SX, SY, SZ >  signNumberLayer_t;


    /**
    * ��������� 3D-����.
    */
    typedef typelib::NumberMap< float, SX, SY, SZ >  numberLayer_t;




    /**
    * �������� (���������) �����.
    */
    struct topology_t {
        /**
        * ���� � ����������� �� ��������� � �� "�����������" �� �����.
        */
        signBitLayer_t presence;

        
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


        /**
        * ����������� � ������� �����.
        * ���� ���� ���������� �� ��� �����.
        * ����������� � �������������� ��������� ���������� ����������
        * ��������� ����������� � ������ ��������� (�������).
        */
        numberLayer_t temperature;


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




    /**
    * ��������� ��� ��������� ������ � ������.
    * ������ �������� � ����, ���������� ��� ��������� �������������
    * ����������� (���������� OpenCL, Cuda).
    */
    struct booster_t {
        float temperature[ SX * SY * SZ ];
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





protected:
    /**
    * ������ ��� ������ ������ ��������� � ��������� booster_t.
    */
    virtual void toBooster();



    /**
    * ������ ��� ������ ������ �� ��������� booster_t � ��������.
    */
    virtual void fromBooster();





private:
    /**
    * ��������� �����.
    */
    topology_t mTopology;


    /**
    * ��������� ��� ������� ������ � ������.
    */
    booster_t mBooster;

};




} // portulan








#include "Portulan3D.inl"
