#pragma once

#include "../../configure.h"
#ifdef OPENCL_PORTULAN

#ifdef DUNGEON_CRAWL_SET_PLANET_PORTULAN
#include "set/dangeon-crawl/topology.h"

#else
#pragma message( "File configure.h don't include any set of portulan. Build of portulan is not complete." )

#endif


#include <typelib/typelib.h>
#include <memory>



namespace portulan {
    namespace planet {

class Topology;

    }
}





namespace portulan {
    namespace planet {

/**
* Обёртка для работы с топологией планеты на C++.
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




    set::topology_t const& topology() const;
    set::topology_t& topology();




private:
    set::topology_t mTopology;

};



    } // planet
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
#pragma message( "Class portulan::planet::Topology not included in project: OpenCL disabled in configure.h." )

#endif
