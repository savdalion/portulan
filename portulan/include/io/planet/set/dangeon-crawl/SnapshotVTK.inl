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







inline void SnapshotVTK::averageTemperature( const std::string& file ) {
    assert( !file.empty() && "Название файла должно быть указано." );

    namespace pd = portulan::planet::set::dungeoncrawl;
    namespace pc = portulan::planet::set::dungeoncrawl::component;
    namespace pl = portulan::planet::set::dungeoncrawl::living;
    namespace pt = portulan::planet::set::dungeoncrawl::temperature;

    const auto& tp = mPortulan->topology().topology().temperature.content;
    static const size_t TG = pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID * pd::TEMPERATURE_GRID;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // значения температур
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    auto averageTemperature = vtkSmartPointer< vtkFloatArray >::New();
    averageTemperature->Initialize();
    averageTemperature->SetName( "average" );
    averageTemperature->SetNumberOfComponents( 1 );
    averageTemperature->SetNumberOfValues( TG ); 

    auto dispersionTemperature = vtkSmartPointer< vtkFloatArray >::New();
    dispersionTemperature->Initialize();
    dispersionTemperature->SetName( "dispersion" );
    dispersionTemperature->SetNumberOfComponents( 1 );
    dispersionTemperature->SetNumberOfValues( TG ); 

    auto rateTemperature = vtkSmartPointer< vtkFloatArray >::New();
    rateTemperature->Initialize();
    rateTemperature->SetName( "rate" );
    rateTemperature->SetNumberOfComponents( 1 );
    rateTemperature->SetNumberOfValues( TG ); 

    size_t n = 0;
    typedef typelib::StaticMapContent3D< pd::TEMPERATURE_GRID, pd::TEMPERATURE_GRID, pd::TEMPERATURE_GRID >  smc_t;
    for (size_t i = 0; i < TG; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        const float cf[3] = {
            static_cast< float >( c.x ),
            static_cast< float >( c.y ),
            static_cast< float >( c.z )
        };
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint( cf );
        vertices->InsertNextCell( 1, pid );

        const auto& t = tp[ i ];
        averageTemperature->SetValue(    n,  t.average );
        dispersionTemperature->SetValue( n,  t.dispersion );
        rateTemperature->SetValue(       n,  t.rate );

        ++n;
    } // for (size_t i


    // собираем вместе
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    polydata->GetPointData()->AddArray( averageTemperature );
    polydata->GetPointData()->AddArray( dispersionTemperature );
    polydata->GetPointData()->AddArray( rateTemperature );


    // записываем
    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "Снимок температуры сохраняем в файл \"" << (file + ".vtp") << "\" ... ";
#endif

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
