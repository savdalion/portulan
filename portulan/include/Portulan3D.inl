namespace portulan {


#if 0
// - �������� �� ����� ������� ������.
template< size_t SX, size_t SY, size_t SZ, typename Number >
inline Portulan3D< SX, SY, SZ, Number >&
Portulan3D< SX, SY, SZ, Number >::operator<<(
    const command::cmd< SX, SY, SZ, Number >&  functor
) {
    functor( *this );

    return *this;
}
#endif




} // portulan
