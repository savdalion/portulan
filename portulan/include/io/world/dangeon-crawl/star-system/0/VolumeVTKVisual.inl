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
        && "������������ ������� �� ������." );

    renderWindow->AddRenderer( renderer );

    // ������� ������ � ���������� ���� �� ������
    // # ���������� ���������� ����������������.
    const int sizeWindow = mOption.at( "size-window", 500 );
    const int* sizeScreen = renderWindow->GetScreenSize();
    int wx = sizeScreen[ 0 ] / 2 - sizeWindow / 2;
    if (wx < 0) { wx = 0; }
    int wy = sizeScreen[ 1 ] / 2 - sizeWindow / 2 - 25;
    if (wy < 0) { wy = 0; }
    renderWindow->SetPosition( wx, wy );
    renderWindow->SetSize( sizeWindow, sizeWindow );

    // ����������� ������
    auto camera = renderer->GetActiveCamera();
    // ������������� �������� ������ �������� �������
    camera->SetParallelProjection( true );
    // ����������� ����: X - ������, Y - �����, Z - � �����������
    //camera->SetPosition( 0, -1, 0 );
    camera->SetFocalPoint( 0, 0, 0 );
    //camera->SetViewUp( 0, 1, 1 );
}




inline VolumeVTKVisual::~VolumeVTKVisual() {
    // ������������ ����� ���������, �������
}






inline VolumeVTKVisual& VolumeVTKVisual::operator<<(
    const pns::Portulan&  portulan
) {
    // ������� �����
    const bool withoutClear = mOption[ "without-clear" ];
    if ( !withoutClear ) {
        clear();
    }


    // �������� ����� (��������� ���������)
    const auto& topology = portulan.topology().topology();


    // �������� ������� ������
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


    // ���������� �������
    const bool legendScale = mOption.at( "legend-scale", false );
    if ( legendScale ) {
        auto legendScaleActor = vtkSmartPointer< vtkLegendScaleActor >::New();
        renderer->AddActor( legendScaleActor );
    }


    // ��������� ���������� ����� � ������ VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html


    // �������� ������� ������� - ��� ����� ���. ���, ������� ����
    // ��������������� � 3D-������������

    // ������������ �� ��������� ���������
    const bool autoScaleCamera = mOption.at( "auto-scale-camera", false );
    if ( !alreadyAutoScaleCamera || autoScaleCamera ) {
        renderer->ResetCamera();
        alreadyAutoScaleCamera = true;
    }


    // ��������� �� ������ ��������� ���������
    drawTopology( topology );


    // ��������� ��� ����������
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
    const auto cameraScale =
        static_cast< pns::real_t >( renderer->GetActiveCamera()->GetParallelScale() );
    const auto windowSize =
        static_cast< pns::real_t >( renderWindow->GetSize()[ 0 ] );
    const auto csDIVws = cameraScale / windowSize;

    drawTopology( topology.star.content,     csDIVws );
    drawTopology( topology.planet.content,   csDIVws );
    drawTopology( topology.asteroid.content, csDIVws );
}




inline void VolumeVTKVisual::drawTopology(
    const pns::starContent_t  topo,
    pns::real_t  csDIVws
) {
    auto points = vtkSmartPointer< vtkPoints >::New();
    points->SetDataTypeToDouble();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();
    const size_t sizePoint = mOption.at( "star-size-point", 5u );
    // @todo ������ ���� ������ � ����������� �� ����������� �����������.
    //       �������� � typelib::compute.
    static const typelib::vector_t  color( 1.0, 1.0, 0.0 );
    for (size_t i = 0; i < pns::STAR_COUNT; ++i) {
        const pns::aboutStar_t& a = topo[ i ];
        if ( pns::absentStar( &a ) ) {
            // # ��������� �����, ��� ������ ��� ��������.
            break;
        }
        // ������ ������ �����, ����� ������� ������ ��� �������
        const auto minRealSize = a.today.radius;
        const auto scale = csDIVws / minRealSize;
        // ������� ������� ������ ��� ������
        const pns::real3_t coord = a.today.coord;
        if (scale > 0.5) {
            insertPoint( points, vertices, coord );
        } else {
            drawSphere( coord, a.today.radius, color );
        }
    } // for (size_t i = 0; ...
    drawPoints( points, vertices, sizePoint, color );
}




inline void VolumeVTKVisual::drawTopology(
    const pns::planetContent_t  topo,
    pns::real_t  csDIVws
) {
    auto points = vtkSmartPointer< vtkPoints >::New();
    points->SetDataTypeToDouble();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();
    const size_t sizePoint = mOption.at( "planet-size-point", 5u );
    static const typelib::vector_t  color( 0.0, 0.0, 1.0 );
    for (size_t i = 0; i < pns::PLANET_COUNT; ++i) {
        const pns::aboutPlanet_t& a = topo[ i ];
        if ( pns::absentPlanet( &a ) ) {
            // # ��������� �����, ��� ������ ��� ��������.
            break;
        }
        // ������ ������ �����, ����� ������� ������ ��� �������
        const auto minRealSize = a.today.radius;
        const auto scale = csDIVws / minRealSize;
        // ������� ������� ������ ��� ������
        const pns::real3_t coord = a.today.coord;
        if (scale > 0.5) {
            insertPoint( points, vertices, coord );
        } else {
            drawSphere( coord, a.today.radius, color );
        }
    } // for (size_t i = 0; ...
    drawPoints( points, vertices, sizePoint, color );
}




inline void VolumeVTKVisual::drawTopology(
    const pns::asteroidContent_t  topo,
    pns::real_t  csDIVws
) {
    auto points = vtkSmartPointer< vtkPoints >::New();
    points->SetDataTypeToDouble();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();
    const size_t sizePoint = mOption.at( "asteroid-size-point", 2u );
    static const typelib::vector_t  color( 0.5, 0.5, 0.5 );
    for (size_t i = 0; i < pns::ASTEROID_COUNT; ++i) {
        const pns::aboutAsteroid_t& a = topo[ i ];
        if ( pns::absentAsteroid( &a ) ) {
            // # ��������� �����, ��� ������ ��� ��������.
            break;
        }
        // ������ ������ �����, ����� ������� ������ ��� �������
        const auto realSize = typelib::SizeT< pns::real_t >(
            a.today.size.s[ 0 ],
            a.today.size.s[ 1 ],
            a.today.size.s[ 2 ]
        );
        const auto minRealSize = realSize.min();
        const auto scale = csDIVws / minRealSize;
        // ������� ������� ������ ��� ������
        const pns::real3_t coord = a.today.coord;
        if (scale > 0.5) {
            insertPoint( points, vertices, coord );
        } else {
            drawEllipsoid( coord, a.today.size, color );
        }
    } // for (size_t i = 0; ...
    drawPoints( points, vertices, sizePoint, color );
}




inline void VolumeVTKVisual::insertPoint(
    vtkSmartPointer< vtkPoints >  points,
    vtkSmartPointer< vtkCellArray >  vertices,
    const pns::real3_t&  coord
) {
    vtkIdType pid[ 1 ];
    pid[ 0 ] = points->InsertNextPoint( coord.s[ 0 ],  coord.s[ 1 ],  coord.s[ 2 ] );
    vertices->InsertNextCell( 1, pid );
}




inline void VolumeVTKVisual::drawPoints(
    vtkSmartPointer< vtkPoints >  points,
    vtkSmartPointer< vtkCellArray >  vertices,
    size_t  sizePoint,
    const typelib::vector_t&  color
) {
    if (points->GetNumberOfPoints() == 0) {
        return;
    }

    auto point = vtkSmartPointer< vtkPolyData >::New(); 
    point->SetPoints( points );
    point->SetVerts( vertices );

    auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInput( point );
#else
    mapper->SetInputData( point );
#endif

    auto actor = vtkSmartPointer< vtkActor >::New();
    actor->SetMapper( mapper );
    actor->GetProperty()->SetPointSize( sizePoint );
    actor->GetProperty()->SetColor( color.x, color.y, color.z );
    renderer->AddActor( actor );
}




inline void VolumeVTKVisual::drawSphere(
    const pns::real3_t&  coord,
    const pns::real_t     radius,
    const typelib::vector_t&  color
) {
    const pns::real3_t  r = { radius, radius, radius };
    drawEllipsoid( coord, r, color );
}




inline void VolumeVTKVisual::drawEllipsoid(
    const pns::real3_t&  coord,
    const pns::real3_t&  radius,
    const typelib::vector_t&  color
) {
    const auto vo = vtkSmartPointer< vtkParametricEllipsoid >::New();
    vo->SetXRadius( radius.s[ 0 ] );
    vo->SetYRadius( radius.s[ 1 ] );
    vo->SetZRadius( radius.s[ 2 ] );

    auto pf = vtkSmartPointer< vtkParametricFunctionSource >::New();
    pf->SetParametricFunction( vo );
    pf->Update();

    auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
    mapper->SetInputConnection( pf->GetOutputPort() );

    auto actor = vtkSmartPointer< vtkActor >::New();
    actor->SetPosition( coord.s[ 0 ],  coord.s[ 1 ],  coord.s[ 2 ] );
    actor->SetMapper( mapper );
    actor->GetProperty()->SetColor( color.x, color.y, color.z );
    renderer->AddActor( actor );
}


                    } // l0
                } // starsystem
            } // dungeoncrawl
        } // world
    } // io
} // portulan
