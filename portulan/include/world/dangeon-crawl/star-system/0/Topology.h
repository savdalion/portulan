#pragma once

#include "../../../../../configure.h"

#ifdef OPENCL_PORTULAN

#ifdef DUNGEON_CRAWL_WORLD_PORTULAN
#include "set/structure.h"
#include "set/star-system.h"
#include "set/star.h"
#include "set/compute-utils.h"
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
class Topology :
    public std::enable_shared_from_this< Topology >
{
public:
    inline Topology(
        const real3_t& size
    ) :
        mAboutStarSystem( size )
    {
    }




    inline virtual ~Topology() {
    }




    inline AboutStarSystem const& aboutStarSystem() const {
        return mAboutStarSystem;
    }


    inline AboutStarSystem& aboutStarSystem() {
        return mAboutStarSystem;
    }




    inline Star const& star() const {
        return mStar;
    }


    inline Star& star() {
        return mStar;
    }




private:
    /**
    * Резервирует место для элементов топологии в куче.
    * Инициализирует элементы нулями.
    */
    template< class T, size_t N >
    static void initContent( T** );




private:
    AboutStarSystem  mAboutStarSystem;

    Star mStar;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan





#else
#pragma message( "Class portulan::world::Topology not included in project: OpenCL disabled in configure.h." )

#endif
