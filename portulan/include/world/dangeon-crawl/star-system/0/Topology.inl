namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {


inline Topology::Topology() {
    // # Все структуры инициализируем нулями. Удобно для отладки.

    std::memset( &mTopology.aboutStarSystem, 0, sizeof( mTopology.aboutStarSystem ) );

    mTopology.asteroid.content = new aboutAsteroid_t[ ASTEROID_COUNT ];
    std::memset( mTopology.asteroid.content, 0, sizeof( *mTopology.asteroid.content ) );

    mTopology.planet.content = new aboutPlanet_t[ PLANET_COUNT ];
    std::memset( mTopology.planet.content, 0, sizeof( *mTopology.planet.content ) );

    mTopology.star.content = new aboutStar_t[ STAR_COUNT ];
    std::memset( mTopology.star.content, 0, sizeof( *mTopology.star.content ) );
}



inline Topology::~Topology() {
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


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
