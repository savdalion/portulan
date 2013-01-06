namespace portulan {
    namespace io {

        
inline VolumeVTKVisual::VolumeVTKVisual(
    const option_t& json
) :
    mOption( json ),
    renderer( vtkSmartPointer< vtkRenderer >::New() ),
    renderWindow( vtkSmartPointer< vtkRenderWindow >::New() ),
    hasAxes( false )
{
    renderWindow->AddRenderer( renderer );

    const size_t sizeWindow =
        mOption.has( "size-window" ) ? mOption[ "size-window" ] : 500;
    renderWindow->SetSize( sizeWindow, sizeWindow );

    // Настраиваем камеру
    auto camera = renderer->GetActiveCamera();
    // перспективная проекция сильно искажает картину
    camera->SetParallelProjection( false );
    // направление осей: X - вправо, Y - к наблюдателю, Z - вверх
    camera->SetPosition( 0, -1, 0 );
    camera->SetFocalPoint( 0, 0, 0 );
    //camera->SetViewUp( 0, 1, 1 );

    /* @todo Добавляем освещение
    vtkLightCollection* lc = vtkLightCollection::New();

    vtkLight* lTop = vtkLight::New();
    lTop->SetPosition( 1.0, 0, 0 );
    lTop->SetColor( 0.5, 1.0, 0.5 );

    lc->AddItem( lTop );
    renderer->SetLightCollection( lc );
    */
}




inline VolumeVTKVisual::~VolumeVTKVisual() {
    // используются умные указатели, красота
}






template< size_t SX, size_t SY, size_t SZ >
inline VolumeVTKVisual& VolumeVTKVisual::operator<<(
    const Portulan< SX, SY, SZ >&  portulan
) {
    // Очищаем образ
    clear();


    const auto& topology = portulan.topology();

    // Переводим полученную карту в формат VTK
    // @todo optimize http://vtk.1045678.n5.nabble.com/Filling-vtkPoints-and-vtkCellArray-fast-td1243607.html

    // для центрирования и отметок границ сетки
    const typelib::coord_t halfN =
        (typelib::coord_t( SX, SY, SZ ) - 1.0f) / 2.0f;
    const typelib::coord_t shiftCenter = typelib::coord_t::ZERO();


    // собираем облако
    // портулан - это набор биткарт, которые надо раскрасить своими цветами

    // смотрим, что нужно показать
    const std::string only = mOption[ "only" ];

    // проходим по всем меткам, собираем точки в объёме
    const bool showAllTopology = only.empty();
    if ( showAllTopology ) {
        drawTopologyPresence< SX, SY, SZ >( topology.presence(), shiftCenter );
    }

    // собираем карту температур
    const bool showTopologyTemperature = (only == ".temperature");
    if ( showTopologyTemperature ) {
        drawTopologyTemperature< SX, SY, SZ >( topology.temperature(), shiftCenter );
    }


    // Отмечаем границы холста
    const bool showCorner = mOption[ "show-corner" ];
    if ( showCorner ) {
        auto cornerPoints = vtkSmartPointer< vtkPoints >::New();
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


    // Рисуем оси
    const bool showAxes = mOption[ "show-axes" ];
    if ( !hasAxes && showAxes ) {
        // Оси рисуем после визуализации, т.к. процесс их отрисовки длится неск. секунд.
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


    // Обновляем что нарисовали
    renderer->GetActiveCamera()->ParallelProjectionOn();
    renderer->GetActiveCamera()->SetFocalPoint( 0, 0, 0 );
    //renderer->GetActiveCamera()->SetPosition( 0, -1, 0 );
    //renderer->GetActiveCamera()->SetViewUp( 0, 0, 1 ); 
    renderer->ResetCamera();

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





inline void VolumeVTKVisual::wait() {
    auto renderWindowInteractor = vtkSmartPointer< vtkRenderWindowInteractor >::New();
    renderWindowInteractor->SetRenderWindow( renderWindow );
    renderer->ResetCamera();
    renderWindow->Render();
    renderWindowInteractor->Start();
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








template< size_t SX, size_t SY, size_t SZ >
inline void VolumeVTKVisual::drawTopologyPresence(
    const typename Portulan< SX, SY, SZ >::topology_t::signBitLayer_t&  topologyPresence,
    const typelib::coord_t& shiftCenter
) {
    typedef typelib::BitMap< SX, SY, SZ >  bm_t;

    if ( topologyPresence.empty() ) {
        return;
    }


    for (auto itr = topologyPresence.raw().cbegin(); itr != topologyPresence.raw().cend(); ++itr) {
        const typelib::Sign<>& sign = itr->first;
        const bm_t bm( itr->second );
        if ( bm.empty() ) {
            continue;
        }

        auto points = vtkSmartPointer< vtkPoints >::New();
        auto vertices = vtkSmartPointer< vtkCellArray >::New();

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
            // @todo optimize Использовать более быстрое заполнение точками и вершинами.
            pid[ 0 ] = points->InsertNextPoint( cf );
            vertices->InsertNextCell( 1, pid );

            i = bm.next( i );
            ++n;

#ifdef _DEBUG
            if (i >= bm_t::volume()) {
                // координата за пределами карты, такого быть не должно
                // смотрим, сколько ещё координат оказались вне
                // заданных картой границ
                size_t n = 0;
                do {
                    ++n;
                } while (i != 0);
                assert( (n == 0) && "Обнаружены данные за пределами карты." );
                break;
            }
#endif

        } while (i != 0);


        // вместе
        auto point = vtkSmartPointer< vtkPolyData >::New(); 
        point->SetPoints( points );
        point->SetVerts( vertices );


        auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
        mapper->SetInput( point );
#else
        mapper->SetInputData( point );
#endif

        // цвет точек текущей метки
        auto rgba = mOption[ "rgba" ];
        /* - Не распознаёт. Заменено. См. ниже.
        std::string hexColor = rgba[ sign.name() ];
        if ( !boost::starts_with( hexColor, "0x" ) ) {
            hexColor = "0x" + hexColor;
        }
        size_t color;
        try {
            color = boost::lexical_cast< size_t >( hexColor );
        } catch ( const boost::bad_lexical_cast& ex ) {
            std::cerr << "Цвет \"" << hexColor << "\" для метки \"" << sign.name() << "\" не распознан."
                << " Причина: \"" << ex.what() << "\"."
                << " Принят как \"белый\"." << std::endl;
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

        // цвет ставим Actor'ом
        auto contentActor = vtkSmartPointer< vtkActor >::New();
        contentActor->SetMapper( mapper );
        const size_t sizePoint = mOption[ "size-point" ];
        contentActor->GetProperty()->SetPointSize( sizePoint );
        contentActor->GetProperty()->SetColor( r, g, b );
        // @todo contentActor->GetProperty()->SetAlpha( a );

        renderer->AddActor( contentActor );

    } // for (auto itr

}








template< size_t SX, size_t SY, size_t SZ >
inline void VolumeVTKVisual::drawTopologyTemperature(
    const typename Portulan< SX, SY, SZ >::topology_t::numberLayer_t&  topologyTemperature,
    const typelib::coord_t& shiftCenter
) {
    typedef Portulan< SX, SY, SZ >::topology_t::numberLayer_t  nm_t;

    if ( topologyTemperature.empty() ) {
        return;
    }


    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // значения для раскраски цветом
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    auto data = vtkSmartPointer< vtkFloatArray >::New();
    data->Initialize();
    const std::string dataName = "TopologyTemperatureData";
    data->SetName( dataName.c_str() );
    data->SetNumberOfComponents( 1 );
    data->SetNumberOfValues( nm_t::volume() ); 

    size_t n = 0;
    for (int z = nm_t::minCoord().z; z <= nm_t::maxCoord().z; ++z) {
        for (int y = nm_t::minCoord().y; y <= nm_t::maxCoord().y; ++y) {
            for (int x = nm_t::minCoord().x; x <= nm_t::maxCoord().x; ++x) {
                const typelib::coordInt_t c( x, y, z );
                const float temperature = topologyTemperature[ c ];

                const float cf[3] = {
                    static_cast< float >( x ) + shiftCenter.x,
                    static_cast< float >( y ) + shiftCenter.y,
                    static_cast< float >( z ) + shiftCenter.z
                };
                vtkIdType pid[ 1 ];
                // @todo optimize Использовать более быстрое заполнение точками и вершинами.
                pid[ 0 ] = points->InsertNextPoint( cf );
                vertices->InsertNextCell( 1, pid );
                data->SetValue( n, temperature );

                ++n;

            } // for (int x

        } // for (int y

    } // for (int z


    // вместе
    auto point = vtkSmartPointer< vtkPolyData >::New(); 
    point->SetPoints( points );
    point->SetVerts( vertices );


    auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInput( point );
#else
    mapper->SetInputData( point );
#endif


    // цвет точек - градиент температур
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    point->GetPointData()->AddArray( data );

    auto lookupTable = vtkSmartPointer< vtkLookupTable >::New();

    const typelib::json::Array colorRange = mOption[ "color-range" ];
    std::pair< float, float > minmaxColor;
    if ( colorRange.empty() ) {
        minmaxColor = topologyTemperature.minmax();
    } else {
        assert( (colorRange.size() == 2)
            && "Опция \"color-range\" должна содержать 2 элемента или отсутствовать." );
        minmaxColor = std::make_pair( colorRange[0], colorRange[1] );
    }

#ifdef _DEBUG
    const auto minmaxNumber = topologyTemperature.minmax();
    std::cout << "Температуры [" << minmaxNumber.first << "; " << minmaxNumber.second << "]"
        << " при диапазоне цвета [" << minmaxColor.first << "; " << minmaxColor.second << "]"
    << std::endl;
#endif

    lookupTable->SetTableRange( minmaxColor.first, minmaxColor.second );
    lookupTable->SetHueRange( 0.667, 0.0 );

    // @example Чёрно-белая картинка > http://wenku.baidu.com/view/c95242f69e31433239689326.html page 44
    // @example Красно-зелёно-синяя картинка > http://wenku.baidu.com/view/c95242f69e31433239689326.html page 44

    lookupTable->Build();


    mapper->SetLookupTable( lookupTable );
    mapper->SetScalarRange( minmaxColor.first, minmaxColor.second );
    mapper->ScalarVisibilityOn();
    mapper->SelectColorArray( dataName.c_str() );
    mapper->SetScalarModeToUsePointFieldData();
    mapper->SetColorModeToMapScalars();


    // цвет ставим Actor'ом
    auto contentActor = vtkSmartPointer< vtkActor >::New();
    contentActor->SetMapper( mapper );
    const size_t sizePoint =
        mOption.has( "size-point" ) ? mOption[ "size-point" ] : 1;
    contentActor->GetProperty()->SetPointSize( sizePoint );
    // @todo contentActor->GetProperty()->SetAlpha( a );

    renderer->AddActor( contentActor );

}





    } // io
} // portulan
