#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <portulan/include/Portulan3D.h>
#include <portulan/include/io/VolumeVTKVisual.h>
#include <portulan/include/command.h>
#include <json.h>



/**
* ���������� ������������ ��� ������� 'Portulan'.
*/
int main( int argc, char** argv ) {

    using namespace portulan;
    using namespace portulan::visualtest;

    namespace co = portulan::command;


    // ��������� ���������� ������ ���-�����
    axter::ezlogger<>::set_verbosity_level_tolerance( axter::log_rarely );
    //axter::ezlogger<>::set_verbosity_level_tolerance( axter::log_often );

    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan -> BEGIN" << std::endl;
    #ifdef _MSC_VER
        #ifdef _DEBUG
            EZLOGGERVLSTREAM( axter::log_always ) << "Debug." << std::endl;
        #else
            EZLOGGERVLSTREAM( axter::log_always ) << "Release." << std::endl;
        #endif
    #endif

            
    setlocale( LC_ALL, "Russian" );
    // ��� ����������� '.' ������ ','
    setlocale( LC_NUMERIC, "C" );




    // ������ ����� �� ����� �����
    const size_t GRID = 81;
    typedef Portulan3D< GRID, GRID, GRID, float >  city_t;
    city_t city;

    // ���� �� �������� ����
    const std::string elevationFile = PATH_MEDIA + "a/center-plato-elevation-map.png";
    //const std::string elevationFile = PATH_MEDIA + "a/minimax-elevation-map.png";
    // ������� �������� � ��
    // �������� "a/center-hill-elevation-map.png" �������������
    // = 100 � (������ ����������� = 400 ���)
    // ���������� ��������
    const size_t sizeImage = 400;
    const double scaleXY = 0.100 / static_cast< double>( sizeImage );
    // ������ ����� = 50 �
    const double hMin = -0.010;
    const double hMax =  0.040;
    const double h = hMax - hMin;
    /* - �������� �����. ��. ����.
    city << co::elevationMap< GRID, GRID, GRID, float >( "NaCl", elevationFile, scaleXY, hMin, hMax );
    */
    co::elevationMap( city, "NaCl", elevationFile, scaleXY, hMin, hMax );

    // �������� ����� �����, ������� ����� �����
    const std::string waterFile = PATH_MEDIA + "a/water1-mask-map.png";
    const size_t gridHMin = static_cast< size_t >( hMin * h * scaleXY * static_cast< double >( GRID ) );
    const size_t gridHMax = static_cast< size_t >( hMax * h * scaleXY * static_cast< double >( GRID ) );
    co::flood( city, "H2O", waterFile, gridHMin, gridHMax );


    // ���������� ���������
    io::VolumeVTKVisual::option_t o;
    o[ "size-window" ] = 700;
    o[ "size-point" ] = 1;
    o[ "show-corner" ] = true;
    o[ "show-axes" ] = false;
    auto color = typelib::json::Variant( "{ 'NaCl': 'FFFFFFFF',  'H2O': '0000FFFF' }" );
    o[ "rgba" ] = color;

    io::VolumeVTKVisual visual( o );
    visual << city;
    visual.wait();




    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan -> END" << std::endl;

    std::cout << std::endl << "^" << std::endl;
    //std::cin.ignore();

    return 0;

} // main()
