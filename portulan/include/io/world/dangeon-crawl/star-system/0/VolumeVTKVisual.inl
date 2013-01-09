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

    const size_t sizeWindow =
        mOption.has( "size-window" ) ? mOption[ "size-window" ] : 500;
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


    // ��������� ���������� ����� � ������ VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html


    // �������� ������� ������� - ��� ����� ���. ���, ������� ����
    // ��������������� � 3D-������������

    //const int timestep = mOption[ "timestep" ];

    // �������� �� ���� ���. �����, �������� ����� � ������
    drawTopology( topology );


    // ��������� ��� ����������
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





inline void VolumeVTKVisual::wait(
    pes::Engine* engine, int pulse,
    size_t frequence,
    int needStep,
    bool closeWindow
) {
    //renderer->ResetCamera();

    auto rwi = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    rwi->SetRenderWindow( renderWindow );
    renderWindow->Render();
    rwi->Initialize();

    if ( engine && (frequence != 0) ) {
        auto cb = vtkSmartPointer< vtkPulseCallback >::New();
        cb->init( this, engine, pulse, needStep, closeWindow );
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
    // �����
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pns::STAR_COUNT; ++i) {
            const pns::aboutStar_t& s = topology.star.content[ i ];
            if ( pns::absentStar( s ) ) {
                // # ��������� �����, ��� ������ �����������
                //   ������������� ������.
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


    // �������
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pns::PLANET_COUNT; ++i) {
            const pns::aboutPlanet_t& p = topology.planet.content[ i ];
            if ( pns::absentPlanet( p ) ) {
                // # ��������� �����, ��� ������ �����������
                //   ������������� �������.
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
            const size_t sizePoint = mOption.has( "planet-size-point" ) ?
                mOption[ "planet-size-point" ] : 5;
            contentActor->GetProperty()->SetPointSize( sizePoint );
            contentActor->GetProperty()->SetColor( 0.0, 0.0, 1.0 );
            renderer->AddActor( contentActor );
        }
    }


    // ���������
    {
        auto points = vtkSmartPointer< vtkPoints >::New();
        points->SetDataTypeToDouble();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();
        for (size_t i = 0; i < pns::ASTEROID_COUNT; ++i) {
            const pns::aboutAsteroid_t& a = topology.asteroid.content[ i ];
            if ( pns::absentAsteroid( a ) ) {
                // # ��������� �����, ��� ������ �����������
                //   ������������� ��������.
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
            const size_t sizePoint = mOption.has( "asteroid-size-point" ) ?
                mOption[ "asteroid-size-point" ] : 2;
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
