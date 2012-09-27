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





/*
inline void SnapshotVTK::all() {
    component();
    living();
    temperature();
}
*/





inline void SnapshotVTK::component( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "Снимок компонентов сохраняем в файл \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::COMPONENT_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content = mPortulan->topology().topology().component.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

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
    typedef typelib::StaticMapContent3D< grid, grid, grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // координата ячейки
        const typelib::coordInt_t c = smc_t::ci( i );
        const float cf[3] = {
            static_cast< float >( c.x ),
            static_cast< float >( c.y ),
            static_cast< float >( c.z )
        };
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint( cf );
        vertices->InsertNextCell( 1, pid );

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
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    for (auto itr = component.cbegin(); itr != component.cend(); ++itr) {
        polydata->GetPointData()->AddArray( itr->second );
    }


    // записываем
    auto writer = vtkSmartPointer< vtkXMLPolyDataWriter >::New();
    writer->SetFileName( fileName.c_str() );
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput( polydata );
#else
    writer->SetInputData( polydata );
#endif

    writer->SetDataModeToBinary();
    //writer->SetDataModeToAscii();
 
    writer->Write();

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::living( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "Снимок особей сохраняем в файл \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::LIVING_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content = mPortulan->topology().topology().living.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

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
    typedef typelib::StaticMapContent3D< grid, grid, grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // координата ячейки
        const typelib::coordInt_t c = smc_t::ci( i );
        const float cf[3] = {
            static_cast< float >( c.x ),
            static_cast< float >( c.y ),
            static_cast< float >( c.z )
        };
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint( cf );
        vertices->InsertNextCell( 1, pid );

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
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    for (auto itr = livingCount.cbegin(); itr != livingCount.cend(); ++itr) {
        polydata->GetPointData()->AddArray( itr->second );
    }


    // записываем
    auto writer = vtkSmartPointer< vtkXMLPolyDataWriter >::New();
    writer->SetFileName( fileName.c_str() );
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput( polydata );
#else
    writer->SetInputData( polydata );
#endif

    writer->SetDataModeToBinary();
    //writer->SetDataModeToAscii();
 
    writer->Write();

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}






inline void SnapshotVTK::temperature( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "Снимок температуры сохраняем в файл \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content = mPortulan->topology().topology().temperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // содержимое
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    auto averageTemperature = vtkSmartPointer< vtkFloatArray >::New();
    averageTemperature->Initialize();
    averageTemperature->SetName( "average" );
    averageTemperature->SetNumberOfComponents( 1 );
    averageTemperature->SetNumberOfValues( G3 );

    /* - @todo
    auto dispersionTemperature = vtkSmartPointer< vtkFloatArray >::New();
    dispersionTemperature->Initialize();
    dispersionTemperature->SetName( "dispersion" );
    dispersionTemperature->SetNumberOfComponents( 1 );
    dispersionTemperature->SetNumberOfValues( G3 );

    auto rateTemperature = vtkSmartPointer< vtkFloatArray >::New();
    rateTemperature->Initialize();
    rateTemperature->SetName( "rate" );
    rateTemperature->SetNumberOfComponents( 1 );
    rateTemperature->SetNumberOfValues( G3 );
    */

    size_t n = 0;
    typedef typelib::StaticMapContent3D< grid, grid, grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        const float cf[3] = {
            static_cast< float >( c.x ),
            static_cast< float >( c.y ),
            static_cast< float >( c.z )
        };
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint( cf );
        vertices->InsertNextCell( 1, pid );

        const auto& cell = content[ i ];
        averageTemperature->SetValue(    n,  cell[0].average );
        //dispersionTemperature->SetValue( n,  cell[0].dispersion );
        //rateTemperature->SetValue(       n,  cell[0].rate );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    polydata->GetPointData()->AddArray( averageTemperature );
    //polydata->GetPointData()->AddArray( dispersionTemperature );
    //polydata->GetPointData()->AddArray( rateTemperature );


    // записываем
    auto writer = vtkSmartPointer< vtkXMLPolyDataWriter >::New();
    writer->SetFileName( fileName.c_str() );
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput( polydata );
#else
    writer->SetInputData( polydata );
#endif

    writer->SetDataModeToBinary();
    //writer->SetDataModeToAscii();
 
    writer->Write();

#ifdef _DEBUG
    std::cout << "ОК" << std::endl;
#endif
}


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan
