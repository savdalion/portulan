namespace portulan {


#if 0
// - Заменено на более простые методы.
template< size_t SX, size_t SY, size_t SZ, typename Number >
inline Portulan3D< SX, SY, SZ, Number >&
Portulan3D< SX, SY, SZ, Number >::operator<<(
    const command::cmd< SX, SY, SZ, Number >&  functor
) {
    functor( *this );

    return *this;
}
#endif






template< size_t SX, size_t SY, size_t SZ >
void Portulan3D< SX, SY, SZ >::toBooster() {

    // температура
    std::copy(
        mTopology.temperature.raw().cbegin(),
        mTopology.temperature.raw().cend(),
        std::begin( mBooster.temperature )
    );

}





template< size_t SX, size_t SY, size_t SZ >
void Portulan3D< SX, SY, SZ >::fromBooster() {

    // температура
    std::copy(
        std::begin( mBooster.temperature ),
        std::end( mBooster.temperature ),
        mTopology.temperature.raw().begin()
    );

}




} // portulan
