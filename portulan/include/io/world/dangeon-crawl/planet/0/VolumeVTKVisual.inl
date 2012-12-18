namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {


namespace pnp = portulan::world::dungeoncrawl::planet::l0;


inline VolumeVTKVisual::VolumeVTKVisual(
    const option_t& json
) :
    mOption( json ),
    renderer( vtkSmartPointer< vtkRenderer >::New() ),
    rendererDetail( vtkSmartPointer< vtkRenderer >::New() ),
    renderWindow( vtkSmartPointer< vtkRenderWindow >::New() ),
    renderWindowDetail( vtkSmartPointer< vtkRenderWindow >::New() ),
    alreadyAutoScaleCamera( false ),
    hasAxes( false )
{
    renderWindow->AddRenderer( renderer );
    renderWindowDetail->AddRenderer( rendererDetail );

    const size_t sizeWindow =
        mOption.has( "size-window" ) ?
            mOption[ "size-window" ] : 500;
    renderWindow->SetSize( sizeWindow, sizeWindow );
    const size_t sizeWindowDetail =
        mOption.has( "size-window-detail" ) ?
            mOption[ "size-window-detail" ] : (sizeWindow / 2);
    renderWindowDetail->SetSize( sizeWindowDetail, sizeWindowDetail );

    // Настраиваем камеры
    auto camera = renderer->GetActiveCamera();
    // перспективная проекция сильно искажает картину
    camera->SetParallelProjection( true );
    // направление осей: X - вправо, Y - вверх, Z - к наблюдателю
    //camera->SetPosition( 0, -1, 0 );
    camera->SetFocalPoint( 0, 0, 0 );
    //camera->SetViewUp( 0, 1, 1 );

    auto cameraDetail = rendererDetail->GetActiveCamera();
    cameraDetail->SetParallelProjection( true );
    cameraDetail->SetFocalPoint( 0, 0, 0 );
}




inline VolumeVTKVisual::~VolumeVTKVisual() {
    // используются умные указатели, красота
}






inline VolumeVTKVisual& VolumeVTKVisual::operator<<(
    const pnp::illuminanceBody_t&  ib
) {
    // Очищаем образ
    const bool withoutClear = mOption[ "without-clear" ];
    if ( !withoutClear ) {
        clear();
    }


    // Переводим полученную карту в формат VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html


    // визуализируем систему "звёзды->планета" и покажем карту
    // освещённости на самой планете
    drawMacro( ib );
    drawDetail( ib );


    // шкала масштабирования
#if 0
    const auto legendScaleActor =
        vtkSmartPointer< vtkLegendScaleActor >::New();
    renderer->AddActor( legendScaleActor );
#endif


    // Обновляем что нарисовали
    const bool autoScaleCamera = mOption[ "auto-scale-camera" ];
    if ( !alreadyAutoScaleCamera || autoScaleCamera ) {
        renderer->ResetCamera();
        rendererDetail->ResetCamera();
        alreadyAutoScaleCamera = true;
    }

    renderWindow->Render();
    renderWindowDetail->Render();

    return *this;
}






inline VolumeVTKVisual& VolumeVTKVisual::operator<<( const option_t& json ) {

    mOption = json;

    if ( mOption.has( "size-window" ) ) {
        const size_t sizeWindow = mOption[ "size-window" ];
        renderWindow->SetSize( sizeWindow, sizeWindow );
    }

    if ( mOption.has( "size-window-detail" ) ) {
        const size_t sizeWindowDetail = mOption[ "size-window-detail" ];
        renderWindowDetail->SetSize( sizeWindowDetail, sizeWindowDetail );
    }

    renderer->ResetCamera();
    renderWindow->Render();

    rendererDetail->ResetCamera();
    renderWindowDetail->Render();

    return *this;
}





inline void VolumeVTKVisual::waitCircleEngine(
    pnp::illuminanceBody_t*  ib,
    size_t                   frequence
) {
    assert( ib && "Структура для визуализации не задана." );

    //renderer->ResetCamera();

    // основное окно
    auto rwi = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwi->SetRenderWindow( renderWindow );
    renderWindow->Render();
    rwi->Initialize();
    if (frequence != 0) {
        auto cb = vtkSmartPointer< IlluminanceCircleCallback >::New();
        cb->init( this, ib, 0 );
        rwi->AddObserver( vtkCommand::TimerEvent, cb );
        const int tid = rwi->CreateRepeatingTimer( frequence );
    }
    //rwi->Start();

    // окно детальной инфо
    auto rwiDetail = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwiDetail->SetRenderWindow( renderWindowDetail );
    renderWindowDetail->Render();
    rwiDetail->Initialize();
    rwiDetail->Start();
}





inline void VolumeVTKVisual::wait() {

    //renderer->ResetCamera();

    // основное окно
    auto rwi = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwi->SetRenderWindow( renderWindow );
    renderWindow->Render();
    rwi->Initialize();
    //rwi->Start();

    // окно детальной инфо
    auto rwiDetail = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwiDetail->SetRenderWindow( renderWindowDetail );
    renderWindowDetail->Render();
    rwiDetail->Initialize();
    rwiDetail->Start();
}






inline void VolumeVTKVisual::clear() {
    const auto fn = [] ( vtkSmartPointer< vtkRenderer >  r ) {
        auto al = r->GetActors();
        al->InitTraversal();
        auto itr = al->GetNextItem();
        while ( itr ) {
            r->RemoveActor( itr );
            itr = al->GetNextItem();
        }
    };

    fn( renderer );
    fn( rendererDetail );
}








inline void VolumeVTKVisual::drawMacro( const pnp::illuminanceBody_t&  ib ) {
    // звёзды
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pnp::ILLUMINANCE_STAR_COUNT; ++i) {
            const pnp::aboutIlluminanceStar_t& s = ib.source.star[ i ];
            const bool absent = typelib::empty( s.radius );
            if ( absent ) {
                // # Завершаем поиск, как только встречается
                //   отсутствующая звезда.
                break;
            }
            vtkIdType pid[ 1 ];
            pid[ 0 ] = points->InsertNextPoint(
                s.coord[ 0 ], s.coord[ 1 ], s.coord[ 2 ]
            );
            vertices->InsertNextCell( 1, pid );
        }

        if (points->GetNumberOfPoints() > 0) {
            auto point = vtkSmartPointer< vtkPolyData >::New(); 
            point->SetPoints( points );
            point->SetVerts( vertices );
            auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
            mapper->SetInput( point );
#else
            mapper->SetInputData( point );
#endif
            auto contentActor = vtkSmartPointer< vtkActor >::New();
            contentActor->SetMapper( mapper );
            const size_t sizePoint = mOption.has( "star-size-point" ) ?
                mOption[ "star-size-point" ] : 10;
            contentActor->GetProperty()->SetPointSize( sizePoint );
            contentActor->GetProperty()->SetColor( 1.0, 1.0, 0.0 );
            renderer->AddActor( contentActor );
        }
    }


    // планета
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint(
            ib.coord[ 0 ], ib.coord[ 1 ], ib.coord[ 2 ]
        );
        vertices->InsertNextCell( 1, pid );

        auto point = vtkSmartPointer< vtkPolyData >::New(); 
        point->SetPoints( points );
        point->SetVerts( vertices );
        auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
        mapper->SetInput( point );
#else
        mapper->SetInputData( point );
#endif
        auto contentActor = vtkSmartPointer< vtkActor >::New();
        contentActor->SetMapper( mapper );
        const size_t sizePoint = mOption.has( "planet-size-point" ) ?
            mOption[ "planet-size-point" ] : 5;
        contentActor->GetProperty()->SetPointSize( sizePoint );
        contentActor->GetProperty()->SetColor( 0.0, 0.0, 1.0 );
        renderer->AddActor( contentActor );
    }

}








inline void VolumeVTKVisual::drawDetail( const pnp::illuminanceBody_t&  ib ) {

    // нарисуем карту освещённости планеты

    static const size_t grid = pnp::ILLUMINANCE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content = ib.result;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    auto star = vtkSmartPointer< vtkFloatArray >::New();
    star->Initialize();
    star->SetName( "star" );
    star->SetNumberOfComponents( 1 );
    star->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const auto& cell = content[ i ];
        if ( typelib::empty( cell[ 0 ].star ) ) {
            continue;
        }

        const typelib::coordInt_t c = smc_t::ci( i );
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint( c.x, c.y, c.z );

        vertices->InsertNextCell( 1, pid );
        star->SetValue( n,  cell[ 0 ].star );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto data = vtkSmartPointer< vtkPolyData >::New();
    data->SetPoints( points );
    data->SetVerts( vertices );
    data->GetPointData()->AddArray( star );


    // визуализируем
    auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInput( data );
#else
    mapper->SetInputData( data );
#endif

    // цвет точек
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    auto lookupTable = vtkSmartPointer< vtkLookupTable >::New();
    float range[ 2 ];
    star->GetValueRange( range );
    lookupTable->SetTableRange( range[ 0 ], range[ 1 ] );
    lookupTable->SetHueRange( 0.667, 0.0 );
    lookupTable->Build();

    mapper->SetLookupTable( lookupTable );
    mapper->SetScalarRange( range[ 0 ], range[ 1 ] );
    mapper->ScalarVisibilityOn();
    mapper->SelectColorArray( "star" );
    mapper->SetScalarModeToUsePointFieldData();
    mapper->SetColorModeToMapScalars();


    auto actor = vtkSmartPointer< vtkActor >::New();
    actor->SetMapper( mapper );
    actor->GetProperty()->SetPointSize( 3 );
    rendererDetail->AddActor( actor );
}


                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan
