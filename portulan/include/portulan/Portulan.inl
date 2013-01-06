namespace portulan {


template< size_t SX, size_t SY, size_t SZ >
inline void Portulan< SX, SY, SZ >::XXharmonize() {
    // (!) ���������� - �����.
    harmonizePlenum( false, false );
    harmonizePresenceToPlenum();
}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan< SX, SY, SZ >::harmonizePlenum( bool saveCorrect, bool strictHarmonize ) {

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
inline void Portulan< SX, SY, SZ >::harmonizePresenceToPlenum() {

    // # "plenum" � "presence" ��������� ���� �����. ����
    //   "presence" == true, � "plenum" == 0.0, "plenum"
    //    ��������������� � 1.0.
    // # ���� "presence" == false, � "plenum" != 0.0, "plenum"
    //   ��������������� � 0.0.

    // �������� �� ������ �����
    const auto& tpr = mTopology.presence().raw();
    for (auto str = std::begin( tpr ); str != std::end( tpr ); ++str) {
        const typelib::Sign<>& sign = str->first;

        // �� ������ ����� ����� ���� �� ����� "�������������"
        auto& pr = mTopology.plenum().raw();
        const auto ptr = pr.find( sign );
        const bool onPlenum = (ptr != pr.cend());
        // (!) ���� ����� �� ����� "�������������" ���, *�� ���������* �
        if ( !onPlenum ) {
            continue;
        }

        // ����� �� ����� "plenum" ����, �������� �� ���
        const auto& nm = ptr->second;
        const auto& bm = str->second;
        for (size_t i = 0; i < mTopology.presence().volume(); ++i) {
            const bool presence = bm.test( i );
            float* t = &nm[ i ];
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

}



} // portulan
