namespace portulan {


template< size_t SX, size_t SY, size_t SZ >
inline void Portulan3D< SX, SY, SZ >::harmonize() {
    // (!) ���������� - �����.
    harmonizePlenum( false, false );
    harmonizePresenceToPlenum();
}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan3D< SX, SY, SZ >::harmonizePlenum( bool saveCorrect, bool strictHarmonize ) {

    // # �������� "plenum" ����� � ��������� [0.0; 1.0]. ���� ��� �� ���,
    //   ��� �������� ���������� � ����� ���������.
    //   ����� �������� "saveCorrect" == true, ������������ �������� ������
    //   ��� � � ������ �������� ��������� �� ������� ��������� [0.0; 1.0].

    // ������� ��������
    const float max = mTopology.plenum().max();
    if ( typelib::between( max, 0.0f, 1.0f ) && !strictHarmonize ) {
        // ��� �������������
        return;
    }

    // �����������
    for (auto itr = mTopology.plenum().raw().begin(); itr != mTopology.plenum().raw().end(); ++itr) {
        const float t = *itr;
        if ( typelib::between( t, 0.0f, 1.0f ) && saveCorrect ) {
            // ������������ �������� �� ���������
            continue;
        }
        *itr /= max;
    }

}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan3D< SX, SY, SZ >::harmonizePresenceToPlenum() {

    // # "plenum" � "presence" ��������� ���� �����. ����
    //   "presence" == true, � "plenum" == 0.0, "plenum"
    //    ��������������� � 1.0.
    // # ���� "presence" == false, � "plenum" != 0.0, "plenum"
    //   ��������������� � 0.0.
    for (size_t i = 0; i < mTopology.plenum().volume(); ++i) {
        const bool presence = mTopology.presence().test( i );
        float* t = &mTopology.plenum()[ i ];
        const bool emptyPlenum = typelib::empty( t );
        if ( presence ) {
            if ( emptyPlenum ) {
                //mTopology.plenum().set( i, 1.0f );
                *t = 1.0f;
            }
        } else {
            if ( !emptyPlenum ) {
                //mTopology.plenum().set( i, 0.0f );
                *t = 0.0f;
            }
        }
    }

}



} // portulan
