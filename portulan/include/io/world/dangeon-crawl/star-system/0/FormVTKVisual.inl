namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace starsystem {
                    namespace l0 {


namespace pns = portulan::world::dungeoncrawl::starsystem::l0;
namespace pes = porte::world::dungeoncrawl::starsystem::l0;


inline FormVTKVisual::FormVTKVisual(
    const option_t& json
) :
    VolumeVTKVisual( json )
{
}




inline FormVTKVisual::~FormVTKVisual() {
}




inline void FormVTKVisual::drawTopology(
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




inline void FormVTKVisual::drawTopology(
    const pns::starContent_t  topo,
    pns::real_t  csDIVws
) {
    auto points = vtkSmartPointer< vtkPoints >::New();
    points->SetDataTypeToDouble();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();
    const size_t sizePoint = mOption.at( "star-size-point", 5u );
    static const typelib::vector_t  color( 1.0, 1.0, 0.0 );
    for (size_t i = 0; i < pns::STAR_COUNT; ++i) {
        const pns::aboutStar_t& a = topo[ i ];
        if ( pns::absentStar( a ) ) {
            // # Завершаем поиск, как только нет элемента.
            break;
        }
        // размер делаем таким, чтобы элемент всегда был показан
        const auto minRealSize = a.radius;
        const auto scale = csDIVws / minRealSize;
        // элемент покажем точкой или формой
        if (scale > 2.0) {
            insertPoint( points, vertices, a.coord );
        } else {
            drawSphere( a.coord, a.radius, color );
        }
    } // for (size_t i = 0; ...
    drawPoints( points, vertices, sizePoint, color );
}




inline void FormVTKVisual::drawTopology(
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
        if ( pns::absentPlanet( a ) ) {
            // # Завершаем поиск, как только нет элемента.
            break;
        }
        // размер делаем таким, чтобы элемент всегда был показан
        const auto minRealSize = a.radius;
        const auto scale = csDIVws / minRealSize;
        // элемент покажем точкой или формой
        if (scale > 2.0) {
            insertPoint( points, vertices, a.coord );
        } else {
            drawSphere( a.coord, a.radius, color );
        }
    } // for (size_t i = 0; ...
    drawPoints( points, vertices, sizePoint, color );
}




inline void FormVTKVisual::drawTopology(
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
        if ( pns::absentAsteroid( a ) ) {
            // # Завершаем поиск, как только нет элемента.
            break;
        }
        // размер делаем таким, чтобы элемент всегда был показан
        const auto realSize = typelib::SizeT< pns::real_t >( a.size );
        const auto minRealSize = realSize.min();
        const auto scale = csDIVws / minRealSize;
        // элемент покажем точкой или формой
        if (scale > 2.0) {
            insertPoint( points, vertices, a.coord );
        } else {
            drawEllipsoid( a.coord, a.size, color );
        }
    } // for (size_t i = 0; ...
    drawPoints( points, vertices, sizePoint, color );
}




inline void FormVTKVisual::insertPoint(
    vtkSmartPointer< vtkPoints >  points,
    vtkSmartPointer< vtkCellArray >  vertices,
    const pns::real_t  coord[ 3 ]
) {
    vtkIdType pid[ 1 ];
    pid[ 0 ] = points->InsertNextPoint( coord[ 0 ],  coord[ 1 ],  coord[ 2 ] );
    vertices->InsertNextCell( 1, pid );
}




inline void FormVTKVisual::drawPoints(
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




inline void FormVTKVisual::drawSphere(
    const pns::real_t  coord[ 3 ],
    const pns::real_t  radius,
    const typelib::vector_t&  color
) {
    const pns::real_t  r[ 3 ] = { radius, radius, radius };
    drawEllipsoid( coord, r, color );
}




inline void FormVTKVisual::drawEllipsoid(
    const pns::real_t  coord[ 3 ],
    const pns::real_t  radius[ 3 ],
    const typelib::vector_t&  color
) {
    const auto vo = vtkSmartPointer< vtkParametricEllipsoid >::New();
    vo->SetXRadius( radius[ 0 ] );
    vo->SetYRadius( radius[ 1 ] );
    vo->SetZRadius( radius[ 2 ] );

    auto pf = vtkSmartPointer< vtkParametricFunctionSource >::New();
    pf->SetParametricFunction( vo );
    pf->Update();

    auto mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
    mapper->SetInputConnection( pf->GetOutputPort() );

    auto actor = vtkSmartPointer< vtkActor >::New();
    actor->SetPosition( coord[ 0 ],  coord[ 1 ],  coord[ 2 ] );
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
