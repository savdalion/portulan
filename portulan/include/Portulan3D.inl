namespace portulan {


template< size_t SX, size_t SY, size_t SZ >
inline void Portulan3D< SX, SY, SZ >::harmonize() {
    // (!) ќчерЄдность - важна.
    harmonizePlenum( false, false );
    harmonizePresenceToPlenum();
}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan3D< SX, SY, SZ >::harmonizePlenum( bool saveCorrect, bool strictHarmonize ) {

    // # «начени€ "plenum" лежат в диапазоне [0.0; 1.0]. ≈сли это не так,
    //   все значени€ привод€тс€ к этому диапазону.
    //    огда параметр "saveCorrect" == true, нормализаци€ проходит только
    //   дл€ и с учЄтом значений выход€щих за пределы диапазона [0.0; 1.0].

    // находим максимум
    const float max = mTopology.plenum().max();
    if ( typelib::between( max, 0.0f, 1.0f ) && !strictHarmonize ) {
        // уже нормализовано
        return;
    }

    // нормализуем
    for (auto itr = mTopology.plenum().raw().begin(); itr != mTopology.plenum().raw().end(); ++itr) {
        const float t = *itr;
        if ( typelib::between( t, 0.0f, 1.0f ) && saveCorrect ) {
            // нормализаци€ значени€ не требуетс€
            continue;
        }
        *itr /= max;
    }

}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan3D< SX, SY, SZ >::harmonizePresenceToPlenum() {

    // # "plenum" и "presence" дублируют друг друга. ≈сли
    //   "presence" == true, а "plenum" == 0.0, "plenum"
    //    устанавливаетс€ в 1.0.
    // # ≈сли "presence" == false, а "plenum" != 0.0, "plenum"
    //   устанавливаетс€ в 0.0.
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
