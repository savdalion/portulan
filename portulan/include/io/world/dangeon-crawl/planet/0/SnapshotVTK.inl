namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

        
inline SnapshotVTK::SnapshotVTK(
    const portulan::world::dungeoncrawl::planet::l0::Portulan*  p
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

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ����������� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::COMPONENT_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().component.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    // �������� �������� "count" �� portionComponent_t
    // ��������� ��� �������� ��������� � ������� ������� �����������; ����
    // ����������� �������� � ����� �� ���� �� ���������, ������� ��������
    // ����������� ���������, ������� �� ������ ������������� ��-�� ��������
    // �������� (�������, � ���� ��, ���������� � Debug � Release)
    typedef vtkSmartPointer< vtkFloatArray >  componentCountArray_t;
    std::map< pns::CODE_COMPONENT, componentCountArray_t >  component;
    std::set< pns::CODE_COMPONENT >  uniqueComponent;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::COMPONENT_CELL; ++k) {
            const auto code = cell[ k ].code;
            // �� ������������� ������ ������
            if (code != pns::CC_NONE) {
                uniqueComponent.insert( code );
            }
        }
    }
    for (auto itr = uniqueComponent.cbegin(); itr != uniqueComponent.cend(); ++itr) {
        const pns::CODE_COMPONENT code = *itr;
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
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const typelib::coordInt_t c = smc_t::ci( i );
        //const vtkIdType id =
            points->InsertNextPoint( c.x, c.y, c.z );

        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::COMPONENT_CELL; ++k) {
            const pns::CODE_COMPONENT code = cell[k].code;
            if (code == pns::CC_NONE) {
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
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->SetPoints( points );
    for (auto itr = component.cbegin(); itr != component.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }
    /* - @todo fine ������ ������ �����?
                    ��� �� ��������� ����� ��� �������� (����)?
    if (blankID != -1) {
        data->BlankPoint( blankID );
        auto t = (*data).GetBlanking();
        data->Modified();
    }
    */


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::temperature( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ����������� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().temperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

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
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );
        //dispersion->SetValue( n,  cell[0].dispersion );
        //rate->SetValue(       n,  cell[0].rate );

        ++n;
    } // for (size_t i


    // �������� ������
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    // @source http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ColorLookupTable
    data->GetPointData()->AddArray( average );
    //data->GetPointData()->AddArray( dispersion );
    //data->GetPointData()->AddArray( rate );


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::surfaceTemperature( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ����������� ����������� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::SURFACE_TEMPERATURE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().surfaceTemperature.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );

        ++n;
    } // for (size_t i


    // �������� ������
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    data->GetPointData()->AddArray( average );


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::rainfall( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ����������� ������� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::RAINFALL_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().rainfall.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );

        ++n;
    } // for (size_t i


    // �������� ������
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    data->GetPointData()->AddArray( average );


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::drainage( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ������� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::DRAINAGE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().drainage.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    auto average = vtkSmartPointer< vtkFloatArray >::New();
    average->Initialize();
    average->SetName( "average" );
    average->SetNumberOfComponents( 1 );
    average->SetNumberOfValues( G3 );

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        const auto& cell = content[ i ];
        average->SetValue( n,  cell[0].average );

        ++n;
    } // for (size_t i


    // �������� ������
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    data->GetPointData()->AddArray( average );


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::landscape( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ��������� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::LANDSCAPE_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().landscape.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    // �������� ��������� �� elementLandscape_t
    // ��������� ��� �������� ��������� � ������� ������� ��. ���������; ����
    // ����������� �������� � ����� �� ���� �� ���������, ������� ��������
    // ����������� ���������, ������� �� ������ ������������� ��-�� ��������
    // �������� (�������, � ���� ��, ���������� � Debug � Release)
    typedef vtkSmartPointer< vtkFloatArray >  �ountArray_t;
    std::map< pns::CODE_ELEMENT_LANDSCAPE, �ountArray_t >  landscapeCount;
    typedef vtkSmartPointer< vtkFloatArray >  scatteringArray_t;
    std::map< pns::CODE_ELEMENT_LANDSCAPE, scatteringArray_t >  landscapeScattering;
    std::set< pns::CODE_ELEMENT_LANDSCAPE >  unique;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::LANDSCAPE_CELL; ++k) {
            const auto code = cell[ k ].code;
            // �� ������������� ������ ��������
            if (code != pns::CC_NONE) {
                unique.insert( code );
            }
        }
    }
    for (auto itr = unique.cbegin(); itr != unique.cend(); ++itr) {
        const pns::CODE_ELEMENT_LANDSCAPE code = *itr;
        std::ostringstream ss;
        ss << "code " << std::setw( 2 ) << std::setfill( '0' ) << code;
        // count
        {
            auto ftr = landscapeCount.emplace(
                std::make_pair( code, �ountArray_t::New() )
            ).first;
            ftr->second->Initialize();
            const std::string name = "count " + ss.str();
            ftr->second->SetName( name.c_str() );
            ftr->second->SetNumberOfComponents( 1 );
            ftr->second->SetNumberOfValues( G3 );
            ftr->second->FillComponent( 0, 0.0f );
        }
        // scattering
        {
            auto ftr = landscapeScattering.emplace(
                std::make_pair( code, scatteringArray_t::New() )
            ).first;
            ftr->second->Initialize();
            const std::string name = "scattering " + ss.str();
            ftr->second->SetName( name.c_str() );
            ftr->second->SetNumberOfComponents( 1 );
            ftr->second->SetNumberOfValues( G3 );
            ftr->second->FillComponent( 0, 0.0f );
        }
    }

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const typelib::coordInt_t c = smc_t::ci( i );
        //const vtkIdType id =
            points->InsertNextPoint( c.x, c.y, c.z );

        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::LANDSCAPE_CELL; ++k) {
            const pns::CODE_ELEMENT_LANDSCAPE code = cell[k].code;
            if (code == pns::CEL_NONE) {
                // ���������� ������ ��. ��������� - ������ � ������ ������ ���
                break;
            }
            // ��� ������ ������������ � ������������������� ������ ����
            // count
            {
                auto ftr = landscapeCount.find( code );
                assert( (ftr != landscapeCount.cend())
                    && "�� ��������� ����� ��� �������� ���������." );
                ftr->second->SetValue( n,  cell[k].count );
            }
            // scattering
            {
                auto ftr = landscapeScattering.find( code );
                assert( (ftr != landscapeScattering.cend())
                    && "�� ��������� ����� ��� �������� ���������." );
                ftr->second->SetValue( n,  cell[k].scattering );
            }
        }

        ++n;
    } // for (size_t i


    // �������� ������
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->SetPoints( points );
    for (auto itr = landscapeCount.cbegin(); itr != landscapeCount.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }
    for (auto itr = landscapeScattering.cbegin(); itr != landscapeScattering.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::biome( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ����� ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::BIOME_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().biome.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    // �������� ����� �� presentBiome_t
    // ��������� ��� �������� ��������� � "content" ������; ����
    // ����������� �������� � ����� �� ���� �� ���������, ������� ��������
    // ����������� ���������, ������� �� ������ ������������� ��-�� ��������
    // �������� (�������, � ���� ��, ���������� � Debug � Release)
    // #i vtkBitArray ����� ��� �� ������ �������������, �� � ���
    //    �� �������� write() ����.
    typedef vtkSmartPointer< vtkCharArray >  biomePresentArray_t;
    std::map< pns::CODE_BIOME, biomePresentArray_t >  biome;
    std::set< pns::CODE_BIOME >  uniqueBiome;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::BIOME_CELL; ++k) {
            const auto code = cell[ k ].code;
            // �� ������������� ������ ������
            if (code != pns::CB_NONE) {
                uniqueBiome.insert( code );
            }
        }
    }
    for (auto itr = uniqueBiome.cbegin(); itr != uniqueBiome.cend(); ++itr) {
        const pns::CODE_BIOME code = *itr;
        auto ftr = biome.emplace( std::make_pair( code, vtkSmartPointer< vtkCharArray >::New() ) ).first;
        ftr->second->Initialize();
        std::ostringstream ss;
        ss << "code " << std::setw( 2 ) << std::setfill( '0' ) << code;
        ftr->second->SetName( ss.str().c_str() );
        ftr->second->SetNumberOfComponents( 1 );
        ftr->second->SetNumberOfValues( G3 );
        // ������ ��������� ��������
        ftr->second->FillComponent( 0, 0 );
    }

    size_t n = 0;
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::BIOME_CELL; ++k) {
            const pns::CODE_BIOME code = cell[k].code;
            // �������� ������ � �� ������� �������
            if (code != pns::CB_NONE) {
                // ��� ������ ������������ � ������������������� ������ ����
                auto ftr = biome.find( code );
                assert( (ftr != biome.cend())
                    && "�� ��������� ����� ��� ����������." );
                ftr->second->SetValue( n,  1 );
            }
        }

        ++n;
    } // for (size_t i


    // �������� ������
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    for (auto itr = biome.cbegin(); itr != biome.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::living( const std::string& file ) {
    assert( !file.empty() && "�������� ����� ������ ���� �������." );

    namespace pns = portulan::world::dungeoncrawl::planet::l0;

#ifdef _DEBUG
    std::cout << "������ ������ ��������� � \"" << file << "\" ... ";
#endif

    static const size_t grid = pns::LIVING_GRID;
    static const size_t G3 = grid * grid * grid;

    const auto& content =
        mPortulan->topology().topology().living.content;

    auto points = vtkSmartPointer< vtkPoints >::New();

    // ����������
    // @source http://vtk.1045678.n5.nabble.com/How-to-use-vtkRibbonFilter-to-show-a-scalar-field-td1237601.html
    // �������� �������� "count" � "group" �� portionLiving_t
    // ��������� ��� �������� ��������� � ������� ������� ������ ����������
    // �����; ���� ����������� �������� � ����� �� ���� �� ���������, �������
    // �������� ����������� ���������, ������� �� ������ ������������� ��-��
    // �������� �������� (�������, � ���� ��, ���������� � Debug � Release)
    typedef vtkSmartPointer< vtkFloatArray >  livingCountArray_t;
    typedef std::pair< int /* pns::CODE_LIVING */,  int /* pns::LIFE_CYCLE */ >  codeLivingAndLifeCycle_t;
    std::map< codeLivingAndLifeCycle_t, livingCountArray_t >  livingCount;
    std::set< codeLivingAndLifeCycle_t >  uniqueLiving;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::LIVING_CELL; ++k) {
            // ���������� �� ������ ������������� �� LIFE_CYCLE
            // @todo optimize ����� ������ ���� ���� (������ �����������).
            for (size_t l = static_cast< size_t >( pns::LC_EMBRYO);
                    l < static_cast< size_t >( pns::LC_last );  ++l
            ) {
                const auto code = cell[ k ][ l ].code;
                // �� ������������� ������ ������
                if (code != pns::CL_NONE) {
                    uniqueLiving.insert( std::make_pair( code,  l ) );
                }
            }
        }
    }
    for (auto itr = uniqueLiving.cbegin(); itr != uniqueLiving.cend(); ++itr) {
        const pns::CODE_LIVING code = static_cast< pns::CODE_LIVING >( itr->first );
        const pns::LIFE_CYCLE l = static_cast< pns::LIFE_CYCLE >( itr->second );
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
    typedef typelib::CubeSMC3D< grid >  smc_t;
    for (size_t i = 0; i < G3; ++i) {
        // ���������� ������
        const typelib::coordInt_t c = smc_t::ci( i );
        points->InsertNextPoint( c.x, c.y, c.z );

        // ���������� ������
        const auto& cell = content[ i ];
        for (size_t k = 0; k < pns::LIVING_CELL; ++k) {
            for (size_t l = static_cast< size_t >( pns::LC_EMBRYO);
                    l < static_cast< size_t >( pns::LC_last );  ++l
            ) {
                const pns::CODE_LIVING code = cell[ k ][ l ].code;
                if (code == pns::CL_NONE) {
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
    auto data = vtkSmartPointer< vtkStructuredGrid >::New();
    data->SetDimensions( grid, grid, grid );
    data->Modified();
    data->SetPoints( points );
    for (auto itr = livingCount.cbegin(); itr != livingCount.cend(); ++itr) {
        data->GetPointData()->AddArray( itr->second );
    }


    // ����������
    write( file, data );

#ifdef _DEBUG
    std::cout << "��" << std::endl;
#endif
}






inline void SnapshotVTK::write(
    const std::string& file,
    const vtkSmartPointer< vtkStructuredGrid > data
) {
    auto writer = vtkSmartPointer< vtkXMLStructuredGridWriter >::New();
    const std::string fileName = file + ".vts";
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






inline void SnapshotVTK::write(
    const std::string& file,
    const vtkSmartPointer< vtkPolyData > data
) {
    auto writer = vtkSmartPointer< vtkXMLPolyDataWriter >::New();
    const std::string fileName = file + ".vtp";
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


                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan
