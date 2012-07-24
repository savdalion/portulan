namespace portulan {


template< size_t SX, size_t SY, size_t SZ >
inline void Portulan< SX, SY, SZ >::harmonize() {
    // (!) Очерёдность - важна.
    harmonizePlenum( false, false );
    harmonizePresenceToPlenum();
}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan< SX, SY, SZ >::harmonizePlenum( bool saveCorrect, bool strictHarmonize ) {

    // # Значения "plenum" лежат в диапазоне [0.0; 1.0]. Если это не так,
    //   все значения приводятся к этому диапазону.
    //   Когда параметр "saveCorrect" == true, нормализация проходит только
    //   для и с учётом значений выходящих за пределы диапазона [0.0; 1.0].

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
            // нормализация значения не требуется
            continue;
        }
        *itr /= max;
    }

}




template< size_t SX, size_t SY, size_t SZ >
inline void Portulan< SX, SY, SZ >::harmonizePresenceToPlenum() {

    // # "plenum" и "presence" дублируют друг друга. Если
    //   "presence" == true, а "plenum" == 0.0, "plenum"
    //    устанавливается в 1.0.
    // # Если "presence" == false, а "plenum" != 0.0, "plenum"
    //   устанавливается в 0.0.

    // проходим по каждой метке
    const auto& tpr = mTopology.presence().raw();
    for (auto str = std::begin( tpr ); str != std::end( tpr ); ++str) {
        const typelib::Sign<>& sign = str->first;

        // не каждая метка может быть на карте "заполненности"
        auto& pr = mTopology.plenum().raw();
        const auto ptr = pr.find( sign );
        const bool onPlenum = (ptr != pr.cend());
        // (!) если метки на карте "заполненности" нет, *не добавляем* её
        if ( !onPlenum ) {
            continue;
        }

        // метка на карте "plenum" есть, работаем по ней
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
