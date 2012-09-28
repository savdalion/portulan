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

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ����������� ��������� � \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::COMPONENT_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().component.content;

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
    std::map< pd::CODE_COMPONENT, componentCountArray_t >  component;
    std::set< pd::CODE_COMPONENT >  uniqueComponent;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::COMPONENT_CELL; ++k) {
            const auto code = cell[ k ].code;
            // �� ������������� ������ ������
            if (code != pd::CC_NONE) {
                uniqueComponent.insert( code );
            }
        }
    }
    for (auto itr = uniqueComponent.cbegin(); itr != uniqueComponent.cend(); ++itr) {
        const pd::CODE_COMPONENT code = *itr;
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
            const pd::CODE_COMPONENT code = cell[k].code;
            if (code == pd::CC_NONE) {
                // ���������� ������ ��������� - ������ � ������ ������ ���
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
    write( fileName, polydata );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::temperature( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ����������� ��������� � \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().temperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    /* - @todo
    auto dispersion = vtkSmartPointer< vtkFloatArray >::New();
    dispersion->Initialize();
    dispersion->SetName( "dispersion" );
    dispersion->SetNumberOfComponents( 1 );
    dispersion->SetNumberOfValues( G3 );

    auto rate = vtkSmartPointer< vtkFloatArray >::New();
    rate->Initialize();
    rate->SetName( "rate" );
    rate->SetNumberOfComponents( 1 );
    rate->SetNumberOfValues( G3 );
    */

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
        average->SetValue(    n,  cell[0].average );
        //dispersion->SetValue( n,  cell[0].dispersion );
        //rate->SetValue(       n,  cell[0].rate );

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    polydata->GetPointData()->AddArray( average );
    //polydata->GetPointData()->AddArray( dispersion );
    //polydata->GetPointData()->AddArray( rate );


    // ����������
    write( fileName, polydata );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::surfaceTemperature( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ����������� ����������� ��������� � \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::SURFACE_TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().surfaceTemperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

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
        average->SetValue(    n,  cell[0].average );

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    polydata->GetPointData()->AddArray( average );


    // ����������
    write( fileName, polydata );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::rainfall( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ����������� ������� ��������� � \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::RAINFALL_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().rainfall.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

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
        average->SetValue(    n,  cell[0].average );

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    polydata->GetPointData()->AddArray( average );


    // ����������
    write( fileName, polydata );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::drainage( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ������� ��������� � \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::DRAINAGE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().drainage.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

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
        average->SetValue(    n,  cell[0].average );

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    polydata->GetPointData()->AddArray( average );


    // ����������
    write( fileName, polydata );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::living( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pd = portulan::planet::set::dungeoncrawl;

    const std::string fileName = file + ".vtp";
#ifdef _DEBUG
    std::cout << "������ ������ ��������� � \"" << (file + ".vtp") << "\" ... ";
#endif

    static const size_t grid = pd::LIVING_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().living.content;

    auto points = vtkSmartPointer< vtkPoints >::New();
    auto vertices = vtkSmartPointer< vtkCellArray >::New();

    // ����������
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    // �������� �������� "count" � "group" �� portionLiving_t
    // ��������� ��� �������� ��������� � ������� ������� ������ ����������
    // �����; ���� ����������� �������� � ����� �� ���� �� ���������, �������
    // �������� ����������� ���������, ������� �� ������ ������������� ��-��
    // �������� �������� (�������, � ���� ��, ���������� � Debug � Release)
    typedef vtkSmartPointer< vtkFloatArray >  livingCountArray_t;
    typedef std::pair< int /* pd::CODE_LIVING */,  int /* pd::LIFE_CYCLE */ >  codeLivingAndLifeCycle_t;
    std::map< codeLivingAndLifeCycle_t, livingCountArray_t >  livingCount;
    std::set< codeLivingAndLifeCycle_t >  uniqueLiving;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pd::LIVING_CELL; ++k) {
            // ���������� �� ������ ������������� �� LIFE_CYCLE
            // @todo optimize ����� ������ ���� ���� (������ �����������).
            for (size_t l = static_cast< size_t >( pd::LC_EMBRYO);
                    l < static_cast< size_t >( pd::LC_last );  ++l
            ) {
                const auto code = cell[ k ][ l ].code;
                // �� ������������� ������ ������
                if (code != pd::CL_NONE) {
                    uniqueLiving.insert( std::make_pair( code,  l ) );
                }
            }
        }
    }
    for (auto itr = uniqueLiving.cbegin(); itr != uniqueLiving.cend(); ++itr) {
        const pd::CODE_LIVING code = static_cast< pd::CODE_LIVING >( itr->first );
        const pd::LIFE_CYCLE l = static_cast< pd::LIFE_CYCLE >( itr->second );
        const auto searchCode = std::make_pair( code, l );
        std::ostringstream ss;
        ss << "c " << std::setw( 3 ) << std::setfill( '0' ) << code << " lc " << l;
        // livingCount
        {
            auto ftr = livingCount.emplace( std::make_pair( searchCode, vtkSmartPointer< vtkFloatArray >::New() ) ).first;
            ftr->second->Initialize();
            ftr->second->SetName( ("count " + ss.str()).c_str() );
            ftr->second->SetNumberOfComponents( 1 );
            ftr->second->SetNumberOfValues( G3 );
            ftr->second->FillComponent( 0, 0.0f );
        }
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
        for (size_t k = 0; k < pd::LIVING_CELL; ++k) {
            for (size_t l = static_cast< size_t >( pd::LC_EMBRYO);
                    l < static_cast< size_t >( pd::LC_last );  ++l
            ) {
                const pd::CODE_LIVING code = cell[ k ][ l ].code;
                if (code == pd::CL_NONE) {
                    // �� ��������� ������ ������
                    continue;
                }
                const auto searchCode = std::make_pair( code, l );
                // ������ ������������ � ������������������� ������ ����
                // livingCount
                {
                    auto ftr = livingCount.find( searchCode );
                    assert( (ftr != livingCount.cend())
                        && "�� ��������� ����� ��� ����������." );
                    ftr->second->SetValue( n,  cell[ k ][ l ].count );
                }

            } // for (size_t l

        } // for (size_t k

        ++n;
    } // for (size_t i


    // �������� ������
    auto polydata = vtkSmartPointer< vtkPolyData >::New(); 
    polydata->SetPoints( points );
    polydata->SetVerts( vertices );
    for (auto itr = livingCount.cbegin(); itr != livingCount.cend(); ++itr) {
        polydata->GetPointData()->AddArray( itr->second );
    }


    // ����������
    write( fileName, polydata );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::write(
    const std::string& fileName,
    const vtkSmartPointer< vtkPolyData > data
) {
    auto writer = vtkSmartPointer< vtkXMLPolyDataWriter >::New();
    writer->SetFileName( fileName.c_str() );
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput( data );
#else
    writer->SetInputData( polydata );
#endif
    writer->SetDataModeToBinary();
    //writer->SetDataModeToAscii();
    writer->Write();
}


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan
