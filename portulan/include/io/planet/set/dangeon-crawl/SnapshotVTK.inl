namespace portulan {
    namespace io {
        namespace planet {
            namespace set {
                namespace dungeoncrawl {

        
inline SnapshotVTK::SnapshotVTK(
    const portulan::planet::Portulan*  p
) :
    mPortulan( p )
{
    assert( p && "Портулан должен быть инициализирован." );
}




inline SnapshotVTK::~SnapshotVTK() {
}






inline SnapshotVTK& SnapshotVTK::operator<<( const option_t& json ) {
    // @todo ...
    assert( false && "Не реализовано." );

    return *this;
}






inline void SnapshotVTK::component( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок компонентов сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::COMPONENT_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().component.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    // сохраним значение "count" из portionComponent_t
    // формируем все названия известных в области планеты компонентов; если
    // формировать названия в цикле по мере их появления, получим частично
    // заполненные структуры, которые не удобно анализировать из-за мусорных
    // значений (которые, к тому же, отличаются в Debug и Release)
    typedef vtkSmartPointer< vtkFloatArray >  componentCountArray_t;
    std::map< pd::CODE_COMPONENT, componentCountArray_t >  component;
    std::set< pd::CODE_COMPONENT >  uniqueComponent;
    for (size_t i = 0; i < G3; ++i) {
        // содержимое ячейки
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::COMPONENT_CELL; ++k) {
            const auto code = cell[ k ].code;
            // не рассматриваем пустых особей
            if (code != pd::CC_NONE) {
                uniqueComponent.insert( code );
            }
        }
    }
    for (auto itr = uniqueComponent.cbegin(); itr != uniqueComponent.cend(); ++itr) {
        const pd::CODE_COMPONENT code = *itr;
        auto ftr = component.emplace( std::make_pair( code, vtkSmartPointer< vtkFloatArray >::New() ) ).first;
        ftr->second->Initialize();
        std::ostringstream ss;
        ss << "code " << std::setw( 3 ) << std::setfill( '0' ) << code;
        ftr->second->SetName( ss.str().c_str() );
        ftr->second->SetNumberOfComponents( 1 );
        ftr->second->SetNumberOfValues( G3 );
        // наборы заполняем пустотой
        /* - Заменено. См. ниже.
        for (size_t n = 0; n < G3; ++n) {
            ftr->second->SetValue( n, 0.0f );
        }
        */
        ftr->second->FillComponent( 0, 0.0f );
    }

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // координата ячейки
        const typelib::coordInt_t c = smc_t::ci( i );
        //const vtkIdType id =
            points->InsertNextPoint( c.x, c.y, c.z );

        // содержимое ячейки
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::COMPONENT_CELL; ++k) {
            const pd::CODE_COMPONENT code = cell[k].code;
            if (code == pd::CC_NONE) {
                // встретился пустой компонент - дальше в ячейке ничего нет
                break;
            }
            // все наборы сформированы и проинициализированы нулями выше
            auto ftr = component.find( code );
            assert( (ftr != component.cend())
                && "Не обнаружен набор для компонента." );
            ftr->second->SetValue( n,  cell[k].count );
        }

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->SetPoints( points );
    for (auto itr = component.cbegin(); itr != component.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }
    /* - @todo fine Гасить пустые точки?
                    Или не добавлять точки без значений (выше)?
    if (blankID != -1) {
        data->BlankPoint( blankID );
        auto t = (*data).GetBlanking();
        data->Modified();
    }
    */


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::temperature( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок температуры сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().temperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    /* - @todo
    auto dispersion = vtkSmartPointer< vtkFloatArray >::New();
    dispersion->Initialize();
    dispersion->SetName( "dispersion" );
    dispersion->SetNumberOfComponents( 1 );
    dispersion->SetNumberOfValues( G3 );

    auto rate = vtkSmartPointer< vtkFloatArray >::New();
    rate->Initialize();
    rate->SetName( "rate" );
    rate->SetNumberOfComponents( 1 );
    rate->SetNumberOfValues( G3 );
    */

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );
        //dispersion->SetValue( n,  cell[0].dispersion );
        //rate->SetValue(       n,  cell[0].rate );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    data->GetPointData()->AddArray( average );
    //data->GetPointData()->AddArray( dispersion );
    //data->GetPointData()->AddArray( rate );


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::surfaceTemperature( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок температуры поверхности сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::SURFACE_TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().surfaceTemperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    data->GetPointData()->AddArray( average );


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::rainfall( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок атмосферных осадков сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::RAINFALL_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().rainfall.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    data->GetPointData()->AddArray( average );


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::drainage( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок дренажа сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::DRAINAGE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().drainage.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    data->GetPointData()->AddArray( average );


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::biome( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок биома сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::BIOME_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().biome.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    // сохраним биомы из presentBiome_t
    // формируем все названия известных в "content" биомов; если
    // формировать названия в цикле по мере их появления, получим частично
    // заполненные структуры, которые не удобно анализировать из-за мусорных
    // значений (которые, к тому же, отличаются в Debug и Release)
    // #i vtkBitArray здесь был бы лучшей альтернативой, но с ним
    //    не работает write() ниже.
    typedef vtkSmartPointer< vtkCharArray >  biomePresentArray_t;
    std::map< pd::CODE_BIOME, biomePresentArray_t >  biome;
    std::set< pd::CODE_BIOME >  uniqueBiome;
    for (size_t i = 0; i < G3; ++i) {
        // содержимое ячейки
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::BIOME_CELL; ++k) {
            const auto code = cell[ k ].code;
            // не рассматриваем пустые ячейки
            if (code != pd::CB_NONE) {
                uniqueBiome.insert( code );
            }
        }
    }
    for (auto itr = uniqueBiome.cbegin(); itr != uniqueBiome.cend(); ++itr) {
        const pd::CODE_BIOME code = *itr;
        auto ftr = biome.emplace( std::make_pair( code, vtkSmartPointer< vtkCharArray >::New() ) ).first;
        ftr->second->Initialize();
        std::ostringstream ss;
        ss << "code " << std::setw( 2 ) << std::setfill( '0' ) << code;
        ftr->second->SetName( ss.str().c_str() );
        ftr->second->SetNumberOfComponents( 1 );
        ftr->second->SetNumberOfValues( G3 );
        // наборы заполняем пустотой
        ftr->second->FillComponent( 0, 0 );
    }

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // координата ячейки
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        // содержимое ячейки
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::BIOME_CELL; ++k) {
            const pd::CODE_BIOME code = cell[k].code;
            // работаем только с не пустыми биомами
            if (code != pd::CB_NONE) {
                // все наборы сформированы и проинициализированы нулями выше
                auto ftr = biome.find( code );
                assert( (ftr != biome.cend())
                    && "Не обнаружен набор для компонента." );
                ftr->second->SetValue( n,  1 );
            }
        }

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    for (auto itr = biome.cbegin(); itr != biome.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::living( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "Снимок особей сохраняем в \"" << file << "\" ... ";
#endif

    static const size_t grid = pd::LIVING_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().living.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // содержимое
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    // сохраним значения "count" и "group" из portionLiving_t
    // формируем все названия известных в области планеты особей указанного
    // цикла; если формировать названия в цикле по мере их появления, получим
    // частично заполненные структуры, которые не удобно анализировать из-за
    // мусорных значений (которые, к тому же, отличаются в Debug и Release)
    typedef vtkSmartPointer< vtkFloatArray >  livingCountArray_t;
    typedef std::pair< int /* pd::CODE_LIVING */,  int /* pd::LIFE_CYCLE */ >  codeLivingAndLifeCycle_t;
    std::map< codeLivingAndLifeCycle_t, livingCountArray_t >  livingCount;
    std::set< codeLivingAndLifeCycle_t >  uniqueLiving;
    for (size_t i = 0; i < G3; ++i) {
        // содержимое ячейки
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::LIVING_CELL; ++k) {
            // информация об особях сгруппирована по LIFE_CYCLE
            // @todo optimize Можно убрать цикл ниже (потеря наглядности).
            for (size_t l = static_cast< size_t >( pd::LC_EMBRYO);
                    l < static_cast< size_t >( pd::LC_last );  ++l
            ) {
                const auto code = cell[ k ][ l ].code;
                // не рассматриваем пустых особей
                if (code != pd::CL_NONE) {
                    uniqueLiving.insert( std::make_pair( code,  l ) );
                }
            }
        }
    }
    for (auto itr = uniqueLiving.cbegin(); itr != uniqueLiving.cend(); ++itr) {
        const pd::CODE_LIVING code = static_cast< pd::CODE_LIVING >( itr->first );
        const pd::LIFE_CYCLE l = static_cast< pd::LIFE_CYCLE >( itr->second );
        const auto searchCode = std::make_pair( code, l );
        std::ostringstream ss;
        ss << "c " << std::setw( 3 ) << std::setfill( '0' ) << code << " lc " << l;
        // livingCount
        {
            auto ftr = livingCount.emplace( std::make_pair( searchCode, vtkSmartPointer< vtkFloatArray >::New() ) ).first;
            ftr->second->Initialize();
            ftr->second->SetName( ("count " + ss.str()).c_str() );
            ftr->second->SetNumberOfComponents( 1 );
            ftr->second->SetNumberOfValues( G3 );
            ftr->second->FillComponent( 0, 0.0f );
        }
    }

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // координата ячейки
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        // содержимое ячейки
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::LIVING_CELL; ++k) {
            for (size_t l = static_cast< size_t >( pd::LC_EMBRYO);
                    l < static_cast< size_t >( pd::LC_last );  ++l
            ) {
                const pd::CODE_LIVING code = cell[ k ][ l ].code;
                if (code == pd::CL_NONE) {
                    // не учитываем пустых особей
                    continue;
                }
                const auto searchCode = std::make_pair( code, l );
                // наборы сформированы и проинициализированы нулями выше
                // livingCount
                {
                    auto ftr = livingCount.find( searchCode );
                    assert( (ftr != livingCount.cend())
                        && "Не обнаружен набор для компонента." );
                    ftr->second->SetValue( n,  cell[ k ][ l ].count );
                }

            } // for (size_t l

        } // for (size_t k

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    for (auto itr = livingCount.cbegin(); itr != livingCount.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }


    // записываем
    write( file, data );

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::write(
    const std::string& file,
    const vtkSmartPointer< vtkStructuredGrid > data
) {
    auto writer = vtkSmartPointer< vtkXMLStructuredGridWriter >::New();
    const std::string fileName = file + ".vts";
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






inline void SnapshotVTK::write(
    const std::string& file,
    const vtkSmartPointer< vtkPolyData > data
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


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan
