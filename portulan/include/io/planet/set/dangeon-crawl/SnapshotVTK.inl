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
    assert( p && "�������� ������ ���� ���������������." );
}




inline SnapshotVTK::~SnapshotVTK() {
}






inline SnapshotVTK& SnapshotVTK::operator<<( const option_t& json ) {
    // @todo ...
    assert( false && "�� �����������." );

    return *this;
}







inline void SnapshotVTK::component( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;
    namespace pc = portulan::planet::set::dungeoncrawl::component;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ����������� ��������� � ���� \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::COMPONENT_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content = mPortulan->topology().topology().component.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    // �������� �������� "count" �� portionComponent_t
    // ��������� ��� �������� ��������� � ������� ������� �����������; ����
    // ����������� �������� � ����� �� ���� �� ���������, ������� ��������
    // ����������� ���������, ������� �� ������ ������������� ��-�� ��������
    // �������� (�������, � ���� ��, ���������� � Debug � Release)
    typedef vtkSmartPointer< vtkFloatArray >  componentCountArray_t;
    std::map< pc::CODE_COMPONENT, componentCountArray_t >  component;
    std::set< pc::CODE_COMPONENT >  uniqueComponent;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::COMPONENT_CELL; ++k) {
            uniqueComponent.insert( cell[k].code );
        }
    }
    for (auto itr = uniqueComponent.cbegin(); itr != uniqueComponent.cend(); ++itr) {
        const pc::CODE_COMPONENT code = *itr;
        auto ftr = component.emplace( std::make_pair( code, vtkSmartPointer< vtkFloatArray >::New() ) ).first;
        ftr->second->Initialize();
        std::ostringstream ss;
        ss << "code " << std::setw( 3 ) << std::setfill( '0' ) << code;
        ftr->second->SetName( ss.str().c_str() );
        ftr->second->SetNumberOfComponents( 1 );
        ftr->second->SetNumberOfValues( G3 );
        // ������ ��������� ��������
        /* - ��������. ��. ����.
        for (size_t n = 0; n < G3; ++n) {
            ftr->second->SetValue( n, 0.0f );
        }
        */
        ftr->second->FillComponent( 0, 0.0f );
    }

    size_t n = 0;
    typedef typelib::StaticMapContent3D< grid, grid, grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const typelib::coordInt_t c = smc_t::ci( i );
        const float cf[3] = {
            static_cast< float >( c.x ),
            static_cast< float >( c.y ),
            static_cast< float >( c.z )
        };
        vtkIdType pid[ 1 ];
        pid[ 0 ] = points->InsertNextPoint( cf );
        vertices->InsertNextCell( 1, pid );

        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::COMPONENT_CELL; ++k) {
            const pc::CODE_COMPONENT code = cell[k].code;
            if (code == pc::CC_NONE) {
                // ���������� ������ ��������� - ������ ������ ���
                break;
            }
            // ��� ������ ������������ � ������������������� ������ ����
            auto ftr = component.find( code );
            assert( (ftr != component.cend())
                && "�� ��������� ����� ��� ����������." );
            ftr->second->SetValue( n,  cell[k].count );
        }

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    for (auto itr = component.cbegin(); itr != component.cend(); ++itr) {
        polydata->GetPointData()->AddArray( itr->second );
    }


    // ����������
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
    std::cout << "��" << std::endl;
#endif
}







inline void SnapshotVTK::temperature( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;
    namespace pt = portulan::planet::set::dungeoncrawl::temperature;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ����������� ��������� � ���� \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content = mPortulan->topology().topology().temperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    auto averageTemperature = vtkSmartPointer< vtkFloatArray >::New();
    averageTemperature->Initialize();
    averageTemperature->SetName( "average" );
    averageTemperature->SetNumberOfComponents( 1 );
    averageTemperature->SetNumberOfValues( G3 );

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
        averageTemperature->SetValue(    n,  cell.average );
        dispersionTemperature->SetValue( n,  cell.dispersion );
        rateTemperature->SetValue(       n,  cell.rate );

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    polydata->GetPointData()->AddArray( averageTemperature );
    polydata->GetPointData()->AddArray( dispersionTemperature );
    polydata->GetPointData()->AddArray( rateTemperature );


    // ����������
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
    std::cout << "��" << std::endl;
#endif
}


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan
