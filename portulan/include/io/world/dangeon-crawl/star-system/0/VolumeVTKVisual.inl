namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace starsystem {
                    namespace l0 {


namespace pd = portulan::world::dungeoncrawl::starsystem::l0;
namespace pe = porte::world::dungeoncrawl::starsystem::l0;


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

    const size_t sizeWindow =
        mOption.has( "size-window" ) ? mOption[ "size-window" ] : 500;
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
    const pd::Portulan&  portulan
) {
    if (pd::BODY_COUNT == 0) {
        return *this;
    }

    // Очищаем образ
    const bool withoutClear = mOption[ "without-clear" ];
    if ( !withoutClear ) {
        clear();
    }


    // Получаем карту (топологию портулана)
    const auto& topology = portulan.topology().topology();


    // Отмечаем границы холста
    const double extent = mOption[ "extent" ];
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


    // Переводим полученную карту в формат VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html


    // портулан звёздной системы - это набор физ. тел, которые надо
    // визуализировать в 3D-пространстве

    //const int timestep = mOption[ "timestep" ];

    // проходим по всем физ. телам, собираем точки в объёме
    drawTopology( topology );


    // Обновляем что нарисовали
    const bool autoScaleCamera = mOption[ "auto-scale-camera" ];
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
        const size_t sizeWindow = mOption[ "size-window" ];
        renderWindow->SetSize( sizeWindow, sizeWindow );
    }

    renderer->ResetCamera();
    renderWindow->Render();

    return *this;
}





inline void VolumeVTKVisual::wait( pe::Engine* engine, int pulse ) {
    //renderer->ResetCamera();

    auto rwi = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwi->SetRenderWindow( renderWindow );
    renderWindow->Render();
    rwi->Initialize();

    if ( engine ) {
        auto cb = vtkSmartPointer< vtkPulseCallback >::New();
        cb->init( this, engine, pulse );
        rwi->AddObserver( vtkCommand::TimerEvent, cb );
        const int tid = rwi->CreateRepeatingTimer( 1 );
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
    const portulan::world::dungeoncrawl::starsystem::l0::topology_t&  topology
) {
    auto pointsPlanets = vtkSmartPointer< vtkPoints >::New();
    pointsPlanets->SetDataTypeToDouble();
    auto verticesPlanets = vtkSmartPointer< vtkCellArray >::New();

    auto pointsStars = vtkSmartPointer< vtkPoints >::New();
    pointsStars->SetDataTypeToDouble();
    auto verticesStars = vtkSmartPointer< vtkCellArray >::New();

    for (size_t i = 0; i < pd::BODY_COUNT; ++i) {
        const pd::aboutBody_t& b = topology.body.content[ i ];

        // # Поля для физ. тел. могут располагаться в любом порядке.
        double radius;
        typelib::coordDouble_t coord;
        vtkIdType pid[ 1 ];
        switch ( b.group ) {
            case pd::GE_PLANET:
                radius = b.content.planet.radius;
                coord  = b.content.planet.coord;
                pid[ 0 ] =
                    pointsPlanets->InsertNextPoint( coord.x, coord.y, coord.z );
                verticesPlanets->InsertNextCell( 1, pid );
                break;

            case pd::GE_STAR:
                radius = b.content.star.radius;
                coord  = b.content.star.coord;
                pid[ 0 ] =
                    pointsStars->InsertNextPoint( coord.x, coord.y, coord.z );
                verticesStars->InsertNextCell( 1, pid );
                break;

            default:
                // не обрабатываем другие элементы
                continue;
        }

    } // for (size_t i = 0; i < pd::BODY_COUNT; ++i)


    // планеты
    if (pointsPlanets->GetNumberOfPoints() > 0) {
        auto point = vtkSmartPointer< vtkPolyData >::New(); 
        point->SetPoints( pointsPlanets );
        point->SetVerts( verticesPlanets );
        auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
        mapper->SetInput( point );
#else
        mapper->SetInputData( point );
#endif
        auto contentActor = vtkSmartPointer< vtkActor >::New();
        contentActor->SetMapper( mapper );
        const size_t sizePoint = mOption.has( "planet-size-point" ) ?
            mOption[ "planet-size-point" ] : 3;
        contentActor->GetProperty()->SetPointSize( sizePoint );
        contentActor->GetProperty()->SetColor( 0.0, 0.0, 1.0 );
        renderer->AddActor( contentActor );
    }


    // звёзды
    if (pointsStars->GetNumberOfPoints() > 0){
        auto point = vtkSmartPointer< vtkPolyData >::New(); 
        point->SetPoints( pointsStars );
        point->SetVerts( verticesStars );
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


                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan
