#pragma once

#include "../../../../../configure.h"
#ifdef OPENCL_PORTULAN

#ifdef DUNGEON_CRAWL_WORLD_PORTULAN
#include "set/topology.h"

#else
#pragma message( "File configure.h don't include any set of portulan. Build of portulan is not complete." )

#endif


#include <typelib/typelib.h>
#include <memory>



namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {

/**
* Обёртка для работы с топологией живого организма на C++.
* 
* @see structure::topology_t
*/
class Topology {

public:
    typedef std::shared_ptr< Topology >  Ptr;
    typedef std::unique_ptr< Topology >  UPtr;
    typedef std::weak_ptr< Topology >    WPtr;



    Topology();


    virtual ~Topology();




    topology_t const& topology() const;
    topology_t& topology();





private:
    topology_t mTopology;

};


                } // physics
            } // living
        } // dungeoncrawl
    } // world
} // portulan







#include "Topology.inl"



#else
#pragma message( "Class portulan::world::Topology not included in project: OpenCL disabled in configure.h." )

#endif
