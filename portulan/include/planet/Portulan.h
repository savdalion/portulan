#pragma once

#include "../../configure.h"
#ifdef OPENCL_PORTULAN

#include "../command.h"
#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>



namespace portulan {
    namespace planet {

class Portulan;

    }
}


/* - @todo ...
namespace std {

std::ostream& operator<<( std::ostream&, const portulan::planet::Portulan& );

} // std
*/



namespace portulan {
    namespace planet {


/**
* ����� ��� ������������ �������� � ��������� 3D-������ ������� �� �����������
* ����������� (OpenCL, Cuda).
*
* ����������
*   # ������� ������� (��������) ������� �� SX � SY � SZ �������������� �����. ���
*     ������� I.
*   # �� ������ I �������� ���� 3D-������� � ���� ���� (����������) �
*     ���������� ����������, ����������� ���������� ����� (���������) �
*     "������� �������".
*   # �� ������ I ����������� ���������� ��������.
*   # ����� �������� ��������������� �� ����� �������.
*
*/
class Portulan {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Portulan >  Ptr;
    typedef std::unique_ptr< Portulan >  UPtr;
    typedef std::weak_ptr< Portulan >    WPtr;


public:

    inline Portulan() {
    }




    inline virtual ~Portulan() {
    }




    inline Topology const& topology() const {
        return mTopology;
    }



    inline Topology& topology() {
        return mTopology;
    }







private:
    /**
    * ��������� �������.
    */
    Topology mTopology;

};



    } // planet
} // portulan








#include "Portulan.inl"


#else
#pragma message( "Class portulan::planet::Portulan not included in project: OpenCL disable" )

#endif
