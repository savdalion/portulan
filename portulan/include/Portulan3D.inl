namespace portulan {


template< size_t SX, size_t SY, size_t SZ, typename Number >
template< typename T >
inline Portulan3D< SX, SY, SZ, Number >&
Portulan3D< SX, SY, SZ, Number >::operator<<( const command::cmd< T >&  functor ) {

    functor( *this );

    return *this;
}



} // portulan
