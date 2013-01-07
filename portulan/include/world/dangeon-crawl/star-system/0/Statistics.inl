namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {


template< size_t N >
inline void
Statistics< N >::grabPulse( pulse_t pulse ) {
    // пропускаем заданое кол-во пульсов
    ++mCountPulse;
    if (mCountPulse <= mSkipPulse) {
        return;
    }
    mCountPulse = 0;

    // # Итератор указывает на текущую ячейку для записи.

    // делаем снимок состояния элемента
    // подготовим список для выборки и возьмём данные из него
    const auto& l = preparedTopology();
    typelib::CoordT< real_t >  coord;
    real_t                     velocity;
    oneValueTwoElement_t       minDistance;
    oneValueTwoElement_t       maxDistance;
    harvest( l, &coord, &velocity, &minDistance, &maxDistance );
    const dataOnePulse_t data = {
        pulse,
        mUIDElement,
        coord,
        velocity,
        minDistance,
        maxDistance
    };
    *mCurrentItr = data;

    // перемещаемся на след. ячейку
    ++mCurrentItr;
    // сбрасываем собранную статистику в файл
    if (mCurrentItr == mDataPulse.end()) {
        flush();
    }
}




template< size_t N >
inline void
Statistics< N >::flush() {

    if ( empty() ) {
        // нет данных, ничего не пишем
        return;
    }

#ifdef _DEBUG
    std::cout << "Записываем статистику портулана .. ";
#endif

    // # Выше проверили, что данные есть.
    const dataPulse_t::const_iterator first = mDataPulse.cbegin();


    const size_t all = size();

    // соберём все значения в формат VTK
    auto pulse = vtkSmartPointer< vtkLongLongArray >::New();
    {
        pulse->Initialize();
        pulse->SetName( "pulse" );
        pulse->SetNumberOfComponents( 1 );
        pulse->SetNumberOfValues( all );
    }

    auto element = vtkSmartPointer< vtkIntArray >::New();
    {
        element->Initialize();
        element->SetName( "element" );
        element->SetNumberOfComponents( 2 );
        element->SetNumberOfTuples( all );
    }

    auto coord = vtkSmartPointer< vtkDoubleArray >::New();
    {
        coord->Initialize();
        coord->SetName( "coord" );
        coord->SetNumberOfComponents( 3 );
        coord->SetNumberOfTuples( all );
    }

    auto velocity = vtkSmartPointer< vtkDoubleArray >::New();
    {
        velocity->Initialize();
        velocity->SetName( "velocity" );
        velocity->SetNumberOfComponents( 1 );
        velocity->SetNumberOfValues( all );
    }

    // @todo extend Сохранять детализацию расстояний по астероидам, планетам и т.д..
    auto minDistance = vtkSmartPointer< vtkDoubleArray >::New();
    {
        minDistance->Initialize();
        minDistance->SetName( "minDistance" );
        minDistance->SetNumberOfComponents( 1 );
        minDistance->SetNumberOfValues( all );
    }

    auto maxDistance = vtkSmartPointer< vtkDoubleArray >::New();
    {
        maxDistance->Initialize();
        maxDistance->SetName( "maxDistance" );
        maxDistance->SetNumberOfComponents( 1 );
        maxDistance->SetNumberOfValues( all );
    }

    // отметим и точки, чтобы можно было быстро визуализировать
    auto points = vtkSmartPointer< vtkPoints >::New();
    // @todo optimize fine Переписать все insert-point VTK через
    //       статич. размер, как здесь (см. ниже и цикл).
    points->SetNumberOfPoints( all );

    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // # 'mCurrentItr' указывает на текущую (ещё не использованную) ячейку.
    size_t n = 0;
    for (auto itr = first; itr != mCurrentItr; ++itr) {
        const dataOnePulse_t& d = *itr;
        
        pulse->SetValue( n, d.pulse );

        const int uide[ 2 ] = {
            static_cast< int >( d.element.ge ),
            static_cast< int >( d.element.uid )
        };
        element->SetTupleValue( n, uide );

        const double c[ 3 ] = {
            static_cast< double >( d.coord.x ),
            static_cast< double >( d.coord.y ),
            static_cast< double >( d.coord.z )
        };
        coord->SetTupleValue( n, c );

        velocity->SetValue( n, d.velocity );

        minDistance->SetValue( n, d.minDistance.total );
        maxDistance->SetValue( n, d.maxDistance.total );
        
        const vtkIdType pid[ 1 ] = { n };
        points->SetPoint( n, d.coord.x, d.coord.y, d.coord.z );
        vertices->InsertNextCell( 1, pid );

        ++n;
    }

    // собираем вместе
    auto data = vtkSmartPointer< vtkPolyData >::New();
    data->SetPoints( points );
    data->SetVerts( vertices );
    data->GetPointData()->AddArray( pulse );
    data->GetPointData()->AddArray( element );
    data->GetPointData()->AddArray( coord );
    data->GetPointData()->AddArray( velocity );
    data->GetPointData()->AddArray( minDistance );
    data->GetPointData()->AddArray( maxDistance );


    // записываем в файл
    dataPulse_t::const_iterator last = mCurrentItr;
    --last;
    std::ostringstream file;
    // # Имя файла важно для подхвата визуализаци в ParaView > http://paraview.org/Wiki/Animating_legacy_VTK_file_series
    file << mPrefixFile << "-" << mUIDElement << "-" << last->pulse;
    write( file.str(), data );

#ifdef _DEBUG
    std::cout << "ОК " << std::endl <<
        all << " снимков в '" << file.str() << "'" << std::endl;
#endif


    // сбрасываем итератор
    mCurrentItr = mDataPulse.begin();

    // # Инициализируем нулями. Удобно для отладки.
    clear( &mDataPulse );
}




template< size_t N >
inline typename Statistics< N >::preparedTopology_t
Statistics< N >::preparedTopology() const {

    const auto& topology = mTopology->topology();

    // сольём нужные данные в единый список
    preparedTopology_t  l;

    const auto insertElement = [ &l ] (
        const uidElement_t&  uide,
        const real_t         coord[ 3 ],
        const real_t         velocity[ 3 ]
    ) {
        const auto c = typelib::CoordT< real_t >( coord );
        const auto v = typelib::VectorT< real_t >( velocity );
        const element_t element = { c,  v,  v.length() };
        l.insert( std::make_pair( uide, element ) );
    };

    const auto& asteroid = topology.asteroid.content;
    for (size_t i = 0; i < ASTEROID_COUNT; ++i) {
        const auto body = asteroid[ i ];
        if ( presentAsteroid( body ) ) {
            const uidElement_t uid = { GE_ASTEROID, body.uid };
            insertElement( uid, body.coord, body.velocity );
        }
    }

    const auto& planet = topology.planet.content;
    for (size_t i = 0; i < PLANET_COUNT; ++i) {
        const auto body = planet[ i ];
        if ( presentPlanet( body ) ) {
            const uidElement_t uid = { GE_PLANET, body.uid };
            insertElement( uid, body.coord, body.velocity );
        }
    }

    const auto& star = topology.star.content;
    for (size_t i = 0; i < STAR_COUNT; ++i) {
        const auto body = star[ i ];
        if ( presentStar( body ) ) {
            const uidElement_t uid = { GE_STAR, body.uid };
            insertElement( uid, body.coord, body.velocity );
        }
    }

    return l;
}




template< size_t N >
inline void
Statistics< N >::harvest(
    const preparedTopology_t&   l,
    typelib::CoordT< real_t >*  coord,
    real_t*                     velocity,
    oneValueTwoElement_t*       minDistance,
    oneValueTwoElement_t*       maxDistance
) const {
    const auto ftr = l.find( mUIDElement );
    assert( (ftr != l.cend())
        && "Элемент звёздной системы на найден." );

    *coord    = ftr->second.coord;
    *velocity = ftr->second.lVelocity;

    // @todo optimize? Предварительно кластеризировать по координатам,
    //       скоростям. Вести кластера в процессе работы движка?

    // тяжёлая артиллерия
    // расстояния
    static const oneValueTwoElement_t MIN_EMPTY = {
        { std::numeric_limits< real_t >::max(),  { GE_NONE, 0 } },
        { std::numeric_limits< real_t >::max(),  { GE_NONE, 0 } },
        { std::numeric_limits< real_t >::max(),  { GE_NONE, 0 } },
        std::numeric_limits< real_t >::max()
    };
    *minDistance = MIN_EMPTY;

    static const oneValueTwoElement_t MAX_EMPTY = {
        { std::numeric_limits< real_t >::min(),  { GE_NONE, 0 } },
        { std::numeric_limits< real_t >::min(),  { GE_NONE, 0 } },
        { std::numeric_limits< real_t >::min(),  { GE_NONE, 0 } },
        std::numeric_limits< real_t >::min()
    };
    *maxDistance = MAX_EMPTY;

    for (auto jtr = l.cbegin(); jtr != l.cend(); ++jtr) {
        if (ftr == jtr) {
            continue;
        }
        const uidElement_t& uideOther = jtr->first;
        const enum GROUP_ELEMENT ge = uideOther.ge;
        const uid_t uid = uideOther.uid;
        const real_t distance =
            ftr->second.coord.distance( jtr->second.coord );
        if (ge == GE_ASTEROID) {
            if (distance < minDistance->asteroid.value) {
                minDistance->asteroid.value     = distance;
                minDistance->asteroid.other.ge  = ge;
                minDistance->asteroid.other.uid = uid;
            } else if (distance > maxDistance->asteroid.value) {
                maxDistance->asteroid.value     = distance;
                maxDistance->asteroid.other.ge  = ge;
                maxDistance->asteroid.other.uid = uid;
            }
        } else if (ge == GE_PLANET) {
            if (distance < minDistance->planet.value) {
                minDistance->planet.value     = distance;
                minDistance->planet.other.ge  = ge;
                minDistance->planet.other.uid = uid;
            } else if (distance > maxDistance->planet.value) {
                maxDistance->planet.value     = distance;
                maxDistance->planet.other.ge  = ge;
                maxDistance->planet.other.uid = uid;
            }
        } else if (ge == GE_STAR) {
            if (distance < minDistance->star.value) {
                minDistance->star.value     = distance;
                minDistance->star.other.ge  = ge;
                minDistance->star.other.uid = uid;
            } else if (distance > maxDistance->star.value) {
                maxDistance->star.value     = distance;
                maxDistance->star.other.ge  = ge;
                maxDistance->star.other.uid = uid;
            }
        }

    } // for (auto jtr = element.cbegin() ...

    // вычислим результирующие минимаксы
    minDistance->total = typelib::min(
        minDistance->asteroid.value,
        minDistance->planet.value,
        minDistance->star.value
    );
    maxDistance->total = typelib::max(
        maxDistance->asteroid.value,
        maxDistance->planet.value,
        maxDistance->star.value
    );

}




template< size_t N >
inline void
Statistics< N >::write(
    const std::string& file,
    const vtkSmartPointer< vtkPolyData >  data
) {
    auto writer = vtkSmartPointer< vtkXMLPolyDataWriter >::New();
    const std::string fileName = file + ".vtp";
    writer->SetFileName( fileName.c_str() );
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput( data );
#else
    writer->SetInputData( polydata );
#endif
    writer->SetDataModeToBinary();
    //writer->SetDataModeToAscii();
    writer->Write();
}


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
