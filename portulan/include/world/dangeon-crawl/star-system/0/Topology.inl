namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {


inline Topology::Topology() {
    /* - Используем стек.
    mTopology.planet.content = new aboutPlanet_t[ PLANET_COUNT ];
    ...
    */
}



inline Topology::~Topology() {
    //delete[] mTopology.planet.content;
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
