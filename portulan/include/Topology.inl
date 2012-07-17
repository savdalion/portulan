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
inline typename Topology< SX, SY, SZ >::signNumberLayer_t const& Topology< SX, SY, SZ >::plenum() const {
    return mPlenum;
}




template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::signNumberLayer_t& Topology< SX, SY, SZ >::plenum() {
    return mPlenum;
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
