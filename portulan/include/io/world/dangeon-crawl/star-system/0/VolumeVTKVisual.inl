namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace starsystem {
                    namespace l0 {


namespace pns = portulan::world::dungeoncrawl::starsystem::l0;
namespace pes = porte::world::dungeoncrawl::starsystem::l0;


inline VolumeVTKVisual::VolumeVTKVisual(
    const option_t& json
) :
    mOption( json ),
    renderer( vtkSmartPointer< vtkRenderer >::New() ),
    renderWindow( vtkSmartPointer< vtkRenderWindow >::New() ),
    alreadyAutoScaleCamera( false ),
    hasAxes( false )
{
    const double extent = mOption[ "extent" ];
    assert( !typelib::empty( extent )
        && "Протяжённость картины не задана." );

    renderWindow->AddRenderer( renderer );

    const size_t sizeWindow = mOption.at( "size-window", 500u );
    renderWindow->SetSize( sizeWindow, sizeWindow );

    // Настраиваем камеру
    auto camera = renderer->GetActiveCamera();
    // перспективная проекция сильно искажает картину
    camera->SetParallelProjection( true );
    // направление осей: X - вправо, Y - вверх, Z - к наблюдателю
    //camera->SetPosition( 0, -1, 0 );
    camera->SetFocalPoint( 0, 0, 0 );
    //camera->SetViewUp( 0, 1, 1 );
}




inline VolumeVTKVisual::~VolumeVTKVisual() {
    // используются умные указатели, красота
}






inline VolumeVTKVisual& VolumeVTKVisual::operator<<(
    const pns::Portulan&  portulan
) {
    // Очищаем образ
    const bool withoutClear = mOption[ "without-clear" ];
    if ( !withoutClear ) {
        clear();
    }


    // Получаем карту (топологию портулана)
    const auto& topology = portulan.topology().topology();


    // Отмечаем границы холста
    const double extent = mOption.at( "extent", 0.0 );
    const typelib::coordDouble_t halfN(
        extent / 2.0,
        extent / 2.0,
        extent / 2.0
    );
    static const typelib::coordDouble_t shiftCenter =
        typelib::coordDouble_t::ZERO();

    auto cornerPoints = vtkSmartPointer< vtkPoints >::New();
    cornerPoints->SetDataTypeToDouble();
    auto cornerVertices = vtkSmartPointer< vtkCellArray >::New();
    static const size_t NP = 1 + 8;
    const double p[ NP ][ 3 ] = {
        {  0.0,      0.0,      0.0     },
        {  halfN.x,  halfN.y,  halfN.z },
        {  halfN.x,  halfN.y, -halfN.z },
        {  halfN.x, -halfN.y,  halfN.z },
        {  halfN.x, -halfN.y, -halfN.z },
        { -halfN.x,  halfN.y,  halfN.z },
        { -halfN.x,  halfN.y, -halfN.z },
        { -halfN.x, -halfN.y,  halfN.z },
        { -halfN.x, -halfN.y, -halfN.z }
    };
    vtkIdType pid[ NP ];
    for (size_t i = 0; i < NP; ++i) {
        pid[ i ] = cornerPoints->InsertNextPoint( p[i] );
    }
    cornerVertices->InsertNextCell( NP, pid );

    auto cornerPolydata = vtkSmartPointer< vtkPolyData >::New();
    cornerPolydata->SetPoints( cornerPoints );
    cornerPolydata->SetVerts( cornerVertices );
 
    auto cornerMapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
    cornerMapper->SetInput( cornerPolydata );
#else
    cornerMapper->SetInputData( cornerPolydata );
#endif
    auto cornerActor = vtkSmartPointer< vtkActor >::New();
    cornerActor->SetMapper( cornerMapper );
    cornerActor->GetProperty()->SetPointSize( 1.0f );
    cornerActor->GetProperty()->SetColor( 1.0, 0.0, 0.0 );

    renderer->AddActor( cornerActor );


    // Показываем масштаб
    const bool legendScale = mOption.at( "legend-scale", false );
    if ( legendScale ) {
        auto legendScaleActor = vtkSmartPointer< vtkLegendScaleActor >::New();
        renderer->AddActor( legendScaleActor );
    }


    // Переводим полученную карту в формат VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html


    // портулан звёздной системы - это набор физ. тел, которые надо
    // визуализировать в 3D-пространстве

    //const int timestep = mOption[ "timestep" ];

    // проходим по всем физ. телам, собираем точки в объёме
    drawTopology( topology );


    // Обновляем что нарисовали
    const bool autoScaleCamera = mOption.at( "auto-scale-camera", false );
    if ( !alreadyAutoScaleCamera || autoScaleCamera ) {
        renderer->ResetCamera();
        alreadyAutoScaleCamera = true;
    }

    renderWindow->Render();

    return *this;
}






inline VolumeVTKVisual& VolumeVTKVisual::operator<<( const option_t& json ) {

    mOption = json;

    if ( mOption.has( "size-window" ) ) {
        const size_t sizeWindow = mOption.at( "size-window", 500u );
        renderWindow->SetSize( sizeWindow, sizeWindow );
    }

    renderer->ResetCamera();
    renderWindow->Render();

    return *this;
}





template<
    size_t frequence,
    int pulse,
    int needStep,
    bool closeWindow,
    bool showPulse
>
inline void VolumeVTKVisual::wait( pes::Engine* engine ) {
    //renderer->ResetCamera();

    auto rwi = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwi->SetRenderWindow( renderWindow );
    renderWindow->Render();
    rwi->Initialize();

    if ( engine && (frequence != 0) ) {
        typedef vtkPulseCallback< pulse, needStep, closeWindow, showPulse >
                vtkPulseCallback_t;
        auto cb = vtkSmartPointer< vtkPulseCallback_t >::New();
        cb->init( this, engine );
        rwi->AddObserver( vtkCommand::TimerEvent, cb );
        const int tid = rwi->CreateRepeatingTimer( frequence );
    }

    rwi->Start();
}






inline void VolumeVTKVisual::clear() {
    auto al = renderer->GetActors();
    al->InitTraversal();
    auto itr = al->GetNextItem();
    while ( itr ) {
        renderer->RemoveActor( itr );
        itr = al->GetNextItem();
    }
}








inline void VolumeVTKVisual::drawTopology(
    const pns::topology_t&  topology
) {
    // звёзды
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pns::STAR_COUNT; ++i) {
            const pns::aboutStar_t& s = topology.star.content[ i ];
            if ( pns::absentStar( s ) ) {
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
            const size_t sizePoint = mOption.at( "star-size-point", 10u );
            contentActor->GetProperty()->SetPointSize( sizePoint );
            contentActor->GetProperty()->SetColor( 1.0, 1.0, 0.0 );
            renderer->AddActor( contentActor );
        }
    }


    // планеты
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pns::PLANET_COUNT; ++i) {
            const pns::aboutPlanet_t& p = topology.planet.content[ i ];
            if ( pns::absentPlanet( p ) ) {
                // # Завершаем поиск, как только встречается
                //   отсутствующая планета.
                break;
            }
            vtkIdType pid[ 1 ];
            pid[ 0 ] = points->InsertNextPoint(
                p.coord[ 0 ], p.coord[ 1 ], p.coord[ 2 ]
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
            const size_t sizePoint = mOption.at( "planet-size-point", 5u );
            contentActor->GetProperty()->SetPointSize( sizePoint );
            contentActor->GetProperty()->SetColor( 0.0, 0.0, 1.0 );
            renderer->AddActor( contentActor );
        }
    }


    // астероиды
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pns::ASTEROID_COUNT; ++i) {
            const pns::aboutAsteroid_t& a = topology.asteroid.content[ i ];
            if ( pns::absentAsteroid( a ) ) {
                // # Завершаем поиск, как только встречается
                //   отсутствующий астероид.
                break;
            }
            vtkIdType pid[ 1 ];
            pid[ 0 ] = points->InsertNextPoint(
                a.coord[ 0 ], a.coord[ 1 ], a.coord[ 2 ]
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
            const size_t sizePoint = mOption.at( "asteroid-size-point", 2u );
            contentActor->GetProperty()->SetPointSize( sizePoint );
            contentActor->GetProperty()->SetColor( 0.5, 0.5, 0.5 );
            renderer->AddActor( contentActor );
        }
    }

}


                    } // l0
                } // starsystem
            } // dungeoncrawl
        } // world
    } // io
} // portulan
