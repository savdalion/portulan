namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {


inline Topology::Topology() {
    /* - ���������� ����.
    mTopology.planet.content = new aboutPlanet_t[ PLANET_COUNT ];
    ...
    */

    // # ��� ��������� �������������� ������. ������ ��� �������.

    std::memset( &mTopology.aboutStarSystem, 0, sizeof( mTopology.aboutStarSystem ) );

    std::memset( &mTopology.asteroid, 0, sizeof( mTopology.asteroid ) );
    std::memset( &mTopology.planet, 0, sizeof( mTopology.planet ) );
    std::memset( &mTopology.star, 0, sizeof( mTopology.star ) );
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
