namespace portulan {


template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::signBitLayer_t const& Topology< SX, SY, SZ >::presence() const {
    return mPresence;
}




template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::signBitLayer_t& Topology< SX, SY, SZ >::presence() {
    return mPresence;
}




template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::signBitLayer_t::layerRaw_t const&
Topology< SX, SY, SZ >::presence( const typelib::Sign<>& sign ) const {
    const auto itr = mTopology.presence().raw().find( sign );
    assert( (itr != mTopology.presence().raw().cend()) && "Метка на найдена на карте присутствия." );

    return itr->second;
}




template< size_t SX, size_t SY, size_t SZ >
inline bool Topology< SX, SY, SZ >::presence( const typelib::Sign<>& sign, size_t i ) const {
    const auto itr = mTopology.presence().raw().find( sign );

    return (itr == mTopology.presence().raw().cend()) ? false : itr->second[ i ];
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::signNumberLayer_t const& Topology< SX, SY, SZ >::plenum() const {
    return mPlenum;
}




template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::signNumberLayer_t& Topology< SX, SY, SZ >::plenum() {
    return mPlenum;
}




template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::Number Topology< SX, SY, SZ >::plenum(
    const typelib::Sign<>& sign,
    size_t i
) const {
    // каждая метка должна быть на карте "присутствия"...
    const auto& ps = mTopology.presence( sign );
    const bool presence = ps.test( i );

    // ...но не каждая метка может быть на карте "заполненности"
    auto& pr = mTopology.plenum().raw();
    const auto ptr = pr.find( sign );
    const bool onPlenum = (ptr != pr.cend());
    if ( !onPlenum ) {
        // метки на карте "plenum" нет: значение "заполненности"
        // определяется значением "присутствия"
        return presence ? 1.0f : 0.0f;
    }

    // метка на карте "plenum" есть, возвращаем значение
    const auto& nm = ptr->second;
    const float t = nm[ i ];

    return t;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::numberLayer_t const& Topology< SX, SY, SZ >::temperature() const {
    return mTemperature;
}




template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::numberLayer_t& Topology< SX, SY, SZ >::temperature() {
    return mTemperature;
}



} // portulan
