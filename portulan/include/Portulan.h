#pragma once

#include "command.h"
#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>



namespace portulan {

template< size_t SX, size_t SY, size_t SZ >
class Portulan;

}


/* - @todo ...
namespace std {

template< size_t SX, size_t SY, size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::Portulan< SX, SY, SZ >& );

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
*/
template< size_t SX, size_t SY, size_t SZ >
class Portulan {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Portulan >  Ptr;
    typedef std::unique_ptr< Portulan >  UPtr;
    typedef std::weak_ptr< Portulan >    WPtr;


    typedef Topology< SX, SY, SZ>  topology_t;



public:

    inline Portulan() {
    }




    inline virtual ~Portulan() {
    }




    inline topology_t const& topology() const {
        return mTopology;
    }



    inline topology_t& topology() {
        return mTopology;
    }



    /* - �������� �� ������� ������ - ��. portulan::command.
    Portulan& operator<<( const command::cmd< SX, SY, SZ, Number >& );
    */



    /**
    * ������������� ��� �������������� ���������.
    * ������� - ��. � ���� ������.
    */
    void harmonize();



    /**
    * ������������� ����. ��� "�������������" (���������).
    * ������� - ��. � ���� ������.
    *
    * @param saveCorrect ������������ �������� ������ ��� �������� ���������
    *        �� ������� ��������� [0.0; 1.0]
    * @param strictHarmonize �������������, ���� ���� ��� �������� ����� �
    *        ��������� [0.0; 1.0].
    */
    void harmonizePlenum( bool saveCorrect, bool strictHarmonize );



    /**
    * ������������� ����. "�������������" � ������ "�����������" (���������).
    * ������� - ��. � ���� ������.
    */
    void harmonizePresenceToPlenum();






private:
    /**
    * ��������� �����.
    */
    topology_t mTopology;

};




} // portulan








#include "Portulan.inl"
