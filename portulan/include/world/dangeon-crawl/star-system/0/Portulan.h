#pragma once

#include "../../../../../configure.h"

#ifdef OPENCL_PORTULAN

#include "Topology.h"
#include "Statistics.h"
#include "set/structure.h"
#include <typelib/typelib.h>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>


namespace boost {

size_t hash_value(
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  uide
);

} // boost




namespace std {

std::ostream& operator<<(
    std::ostream& out,
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  uide
);

bool operator==(
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  a,
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  b
);

} // std




namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {

/**
* Класс для эффективного хранения и обработки 3D-модели звёздной системы
* на графических процессорах (OpenCL, Cuda).
*
* @todo fine Создать базовый класс. Наследовать от базового класса.
*/
class Portulan :
    public std::enable_shared_from_this< Portulan >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Portulan >  Ptr;
    typedef std::unique_ptr< Portulan >  UPtr;
    typedef std::weak_ptr< Portulan >    WPtr;

    /**
    * Заявки на сбор статистики об элементе портулана.
    */
    typedef Statistics< STATISTICS_BUFFER_COUNT >  statistics_t;
    typedef std::unique_ptr< statistics_t >  statisticsPtr_t;
    typedef boost::unordered_map< uidElement_t, statisticsPtr_t >  orderStatistics_t;


public:

    inline Portulan() {
    }




    inline virtual ~Portulan() {
        /* - @todo fine Сделать это здесь или в ~Statistics().
        // дозаписываем собранную статистику
        for (auto itr = mOrderStatistics.cbegin(); itr != mOrderStatistics.cend(); ++itr) {
            itr->second->flush();
        }
        */
    }




    inline Topology const& topology() const {
        return mTopology;
    }


    inline Topology& topology() {
        return mTopology;
    }




    inline orderStatistics_t const& orderStatistics() const {
        return mOrderStatistics;
    }




    /**
    * @param skipPulse  Сколько пульсов пропускать, не собирая данные. От
    *        этого зависит точность собираемых данных и скорость заполнения
    *        буфера статистики STATISTICS_BUFFER_COUNT.
    */
    inline void addOrderStatistics( const uidElement_t& uide,  size_t skipPulse ) {
        mOrderStatistics.insert( std::make_pair(
            uide,  new statistics_t( uide, &mTopology, skipPulse, "starsystem" )
        ) );
    }




    /**
    * Визуализирует портулан с помощью 'visualizer'.
    *
    * #! 'visualizer' должен реализовывать метод operator<<().
    */
    template< class V >
    inline void draw( V* visualizer ) const {
        *visualizer << *this;
    }




private:
    /**
    * Топология.
    */
    Topology mTopology;

    /**
    * Заявки на сбор статистики об элементе портулана.
    */
    orderStatistics_t mOrderStatistics;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan








namespace boost {

inline size_t hash_value(
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  uide
) {
    size_t seed = hash_value( uide.uid );
    hash_combine( seed,  static_cast< int >( uide.ge ) );
    return seed;
}

} // boost




namespace std {

inline std::ostream& operator<<(
    std::ostream& out,
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  uide
) {
    using namespace ::portulan::world::dungeoncrawl::starsystem::l0;
    const std::string gen =
        (uide.ge == GE_NONE)     ? "none" :
        (uide.ge == GE_ASTEROID) ? "asteroid" :
        (uide.ge == GE_PLANET)   ? "planet" :
        (uide.ge == GE_STAR)     ? "star" :
        "x";
    out << gen << "-" << uide.uid;
    return out;
}


inline bool operator==(
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  a,
    const ::portulan::world::dungeoncrawl::starsystem::l0::uidElement_t&  b
) {
    return (a.uid == b.uid) && (a.ge == b.ge);
}

} // std







#else
#pragma message( "Class pnp::Portulan not included in project: OpenCL disable" )

#endif
