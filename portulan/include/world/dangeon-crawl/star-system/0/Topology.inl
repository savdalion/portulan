namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {


inline Topology::Topology() {
    // # Все структуры инициализируем нулями. Удобно для отладки.

    std::memset( &mTopology.aboutStarSystem, 0, sizeof( mTopology.aboutStarSystem ) );

    initContent< aboutAsteroid_t, ASTEROID_COUNT >( &mTopology.asteroid.content );
    initContent< aboutPlanet_t,   PLANET_COUNT >( &mTopology.planet.content );
    initContent< aboutStar_t,     STAR_COUNT >( &mTopology.star.content );
}



inline Topology::~Topology() {
    // @todo fine Переписать через unique_ptr.
    delete[] mTopology.asteroid.content;
    delete[] mTopology.planet.content;
    delete[] mTopology.star.content;
}





inline topology_t const& Topology::topology() const {
    return mTopology;
}



inline topology_t& Topology::topology() {
    return mTopology;
}




template< class T, size_t N >
inline void Topology::initContent( T** content ) {
    *content = new T[ N ];
    std::memset( *content,  0,  sizeof( T ) * N );
}


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
