namespace portulan {
    namespace io {

        
inline VolumeVTKVisual::VolumeVTKVisual(
    const io::VolumeVTKVisual::option_t& json
) :
    option( json ),
    renderer( vtkSmartPointer< vtkRenderer >::New() ),
    renderWindow( vtkSmartPointer< vtkRenderWindow >::New() ),
    hasAxes( false )
{
    renderWindow->AddRenderer( renderer );

    const size_t sizeWindow = option[ "size-window" ];
    renderWindow->SetSize( sizeWindow, sizeWindow );

    // ����������� ������
    auto camera = renderer->GetActiveCamera();
    // ������������� �������� ������ �������� �������
    camera->SetParallelProjection( true );
    // ����������� ����: X - ������, Y - � �����������, Z - �����
    camera->SetPosition( 0, -1, 0 );
    camera->SetFocalPoint( 0, 0, 0 );
    //camera->SetViewUp( 0, 1, 1 );

    /* @todo ��������� ���������
    vtkLightCollection* lc = vtkLightCollection::New();

    vtkLight* lTop = vtkLight::New();
    lTop->SetPosition( 1.0, 0, 0 );
    lTop->SetColor( 0.5, 1.0, 0.5 );

    lc->AddItem( lTop );
    renderer->SetLightCollection( lc );
    */
}




inline VolumeVTKVisual::~VolumeVTKVisual() {
    // ������������ ����� ���������, �������
}






template< size_t SX, size_t SY, size_t SZ, typename Number >
inline VolumeVTKVisual& VolumeVTKVisual::operator<<(
    const typename Portulan3D< SX, SY, SZ, Number >&  portulan
) {
    const auto& topology = portulan.topology();
    const auto& tp = topology.present;
    if ( tp.empty() ) {
        // �� ������ �� �����, �� ���� - ���. �������
        return *this;
    }

    typedef typelib::BitMap< SX, SY, SZ >  bm_t;

    // ��������� ���������� ����� � ������ VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html

    // ��� ������������� � ������� ������ �����
    const typelib::coord_t halfN =
        (typelib::coord_t( SX, SY, SZ ) - 1.0f) / 2.0f;
    const typelib::coord_t shiftCenter = typelib::coord_t::ZERO();

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();


    // �������� ������
    // �������� - ��� ����� �������, ������� ���� ���������� ������ �������

    // �������� �� ���� ������, �������� ����� � ������
    for (auto itr = tp.raw().cbegin(); itr != tp.raw().cend(); ++itr) {
        const typelib::Sign<>& sign = itr->first;
        const bm_t& bm = itr->second;
        if ( bm.empty() ) {
            continue;
        }

        size_t n = 0;
        size_t i = bm.first();
        do {
            const typelib::coordInt_t c = bm_t::ci( i );
            const float cf[3] = {
                static_cast< float >( c.x ) + shiftCenter.x,
                static_cast< float >( c.y ) + shiftCenter.y,
                static_cast< float >( c.z ) + shiftCenter.z
            };
            vtkIdType pid[ 1 ];
            // @todo optimize ������������ ����� ������� ���������� ������� � ���������.
            pid[ 0 ] = points->InsertNextPoint( cf );
            vertices->InsertNextCell( 1, pid );

            i = bm.next( i );
            ++n;

#ifdef _DEBUG
            if (i >= bm_t::volume()) {
                // ���������� �� ��������� �����, ������ ���� �� ������
                // �������, ������� ��� ��������� ��������� ���
                // �������� ������ ������
                size_t n = 0;
                do {
                    ++n;
                } while (i != 0);
                assert( (n == 0) && "���������� ������ �� ��������� �����." );
                break;
            }
#endif

        } while (i != 0);


        // ������
        auto point = vtkSmartPointer< vtkPolyData >::New(); 
        point->SetPoints( points );
        point->SetVerts( vertices );


        auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
        mapper->SetInput( point );
#else
        mapper->SetInputData( point );
#endif

        // ���� ����� ������� �����
        auto rgba = option[ "rgba" ];
        /* - �� ���������. ��������. ��. ����.
        std::string hexColor = rgba[ sign.name() ];
        if ( !boost::starts_with( hexColor, "0x" ) ) {
            hexColor = "0x" + hexColor;
        }
        size_t color;
        try {
            color = boost::lexical_cast< size_t >( hexColor );
        } catch ( const boost::bad_lexical_cast& ex ) {
            std::cerr << "���� \"" << hexColor << "\" ��� ����� \"" << sign.name() << "\" �� ���������."
                << " �������: \"" << ex.what() << "\"."
                << " ������ ��� \"�����\"." << std::endl;
            color = 0xFFFFFFFF;
        }
        */
        std::string hexColor = rgba[ sign.name() ];
        size_t color;
        std::stringstream ss;
        ss << std::hex << hexColor;
        ss >> color;

        const float r = static_cast< float >( (color >> 24) & 0x000000ff ) / 255.0f;
        const float g = static_cast< float >( (color >> 16) & 0x000000ff ) / 255.0f;
        const float b = static_cast< float >( (color >> 8)  & 0x000000ff ) / 255.0f;
        const float a = static_cast< float >( (color)       & 0x000000ff ) / 255.0f;

        // ���� ������ Actor'��
        auto contentActor = vtkSmartPointer< vtkActor >::New();
        contentActor->SetMapper( mapper );
        const size_t sizePoint = option[ "size-point" ];
        contentActor->GetProperty()->SetPointSize( sizePoint );
        contentActor->GetProperty()->SetColor( r, g, b );
        // @todo contentActor->GetProperty()->SetAlpha( a );

        renderer->AddActor( contentActor );

    } // for (auto itr = tp.cbegin(); itr != tp.cend(); ++itr)


    // �������� ������� ������
    auto cornerPoints = vtkSmartPointer< vtkPoints >::New();
    const bool showCorner = option[ "show-corner" ];
    if ( showCorner ) {
        auto cornerVertices = vtkSmartPointer< vtkCellArray >::New();
        const size_t NP = 1 + 8;
        const float p[ NP ][ 3 ] = {
            {  0.0f,     0.0f,     0.0f     },
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
        cornerActor->GetProperty()->SetPointSize( 3.0f );
        cornerActor->GetProperty()->SetColor( 1.0, 0.0, 0.0 );

        renderer->AddActor( cornerActor );

    } // if ( showCornerT )


    // ������ ���
    const bool showAxes = option[ "show-axes" ];
    if ( !hasAxes && showAxes ) {
        // ��� ������ ����� ������������, �.�. ������� �� ��������� ������ ����. ������.
        /*
        {
            auto axesActor = vtkSmartPointer< vtkAxesActor >::New();
            axesActor->SetAxisLabels( 0 );
            renderer->AddActor( axesActor );
        }
        */

        {
            auto cubeAxesActor = vtkSmartPointer< vtkCubeAxesActor >::New();
            // Xmin,Xmax,Ymin,Ymax,Zmin,Zmax
            double bounds[6] = {
                -halfN.x,  halfN.x,
                -halfN.y,  halfN.y,
                -halfN.z,  halfN.z
            };
            cubeAxesActor->SetBounds( bounds );
            //cubeAxesActor->SetBounds( points->GetBounds() );
            cubeAxesActor->SetCamera( renderer->GetActiveCamera() );
            cubeAxesActor->GetProperty()->SetColor( 0.3, 0.3, 0.3 );
            //cubeAxesActor->SetXTitle( "X" );
            //cubeAxesActor->SetYTitle( "Y" );
            //cubeAxesActor->SetZTitle( "Z" );
            cubeAxesActor->SetFlyModeToStaticEdges();
            renderer->AddActor( cubeAxesActor );
        }

        hasAxes = true;

    } // if ( showAxesT )


    // ��������� ��� ����������
    renderer->GetActiveCamera()->ParallelProjectionOn();
    renderer->GetActiveCamera()->SetFocalPoint( 0, 0, 0 );
    //renderer->GetActiveCamera()->SetPosition( 0, -1, 0 );
    //renderer->GetActiveCamera()->SetViewUp( 0, 0, 1 ); 
    renderer->ResetCamera();

    renderWindow->Render();

    return *this;
}






inline void VolumeVTKVisual::wait() {
    auto renderWindowInteractor = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    renderWindowInteractor->SetRenderWindow( renderWindow );
    renderer->ResetCamera();
    renderWindow->Render();
    renderWindowInteractor->Start();
}


    } // io

} // portulan
