#pragma once

#include "../../../../../configure.h"
#ifdef OPENCL_PORTULAN

#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {

/**
* ����� ��� ������������ �������� � ��������� ������ ������ �������� ��
* ����������� ����������� (OpenCL, Cuda).
* ���������� �������.
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


                } // physics
            } // living
        } // dungeoncrawl
    } // world
} // portulan





#else
#pragma message( "Class pnp::Portulan not included in project: OpenCL disable" )

#endif
