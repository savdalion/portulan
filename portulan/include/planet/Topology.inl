namespace portulan {
    namespace planet {


template< size_t SX, size_t SY, size_t SZ >
inline Topology< SX, SY, SZ >::Topology() {
    static_assert( ((SX == SY) && (SY == SZ)),
        "@todo extend �������� ������ � ������� ��������� (� ������ � ���� ����)." );
    static_assert( ((SX % 3) == 0), "������ ������� �� X ������ ���� ������ 3." );
    static_assert( ((SY % 3) == 0), "������ ������� �� Y ������ ���� ������ 3." );
    static_assert( ((SZ % 3) == 0), "������ ������� �� Z ������ ���� ������ 3." );
}



template< size_t SX, size_t SY, size_t SZ >
inline Topology< SX, SY, SZ >::~Topology() {    
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::atmosphere_t Topology< SX, SY, SZ >::atmosphere() {
    return mAtmosphere;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::crust_t Topology< SX, SY, SZ >::crust() {
    return mCrust;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::living_t Topology< SX, SY, SZ >::living() {
    return mLiving;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::temperature_t Topology< SX, SY, SZ >::temperature() {
    return mTemperature;
}





template< size_t SX, size_t SY, size_t SZ >
inline typename Topology< SX, SY, SZ >::precipitations_t Topology< SX, SY, SZ >::precipitations() {
    return mPrecipitations;
}



    } // planet
} // portulan
