#pragma once

#include "../../../../../configure.h"
#ifdef OPENCL_PORTULAN

#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

/**
* Класс для эффективного хранения и обработки 3D-модели звёздной системы
* на графических процессорах (OpenCL, Cuda).
*/
class Portulan {
public:
    /**
    * Ссылки.
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
    * Топология.
    */
    Topology mTopology;

};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan





#else
#pragma message( "Class portulan::world::dungeoncrawl::planet::l0::Portulan not included in project: OpenCL disable" )

#endif
