#pragma once

#include "../../../../../configure.h"

#ifdef OPENCL_PORTULAN

#ifdef DUNGEON_CRAWL_WORLD_PORTULAN
#include "set/topology.h"
#include "set/utils.h"

#else
#pragma message( "File configure.h don't include any set of portulan. Build of portulan is not complete." )

#endif


#include <typelib/typelib.h>
#include <memory>



namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

/**
* Обёртка для работы с топологией звёздной системы на C++.
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


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan







/*
namespace std {

std::ostream& operator<<( std::ostream&, const portulan::planet::Topology& );

std::ostream& operator<<( std::ostream&, const portulan::planet::structure::euid_t& );

std::ostream& operator<<( std::ostream&, const portulan::planet::structure::eportion_t& );

//std::ostream& operator<<( std::ostream&, const portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t& );
//std::ostream& operator<<( std::ostream&, const portulan::planet::Topology< 81, 81, 81 >::living_t::specimen_t::metabolism_t& );

} // std
*/





#include "Topology.inl"



#else
#pragma message( "Class portulan::world::Topology not included in project: OpenCL disabled in configure.h." )

#endif
