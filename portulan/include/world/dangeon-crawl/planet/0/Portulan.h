#pragma once

#include "../../../../../configure.h"
#ifdef OPENCL_PORTULAN

#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {

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
    * ���������.
    */
    Topology mTopology;

};


                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan





#else
#pragma message( "Class portulan::world::dungeoncrawl::planet::l0::Portulan not included in project: OpenCL disable" )

#endif
