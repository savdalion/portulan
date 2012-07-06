#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <Portulan3D.h>
#include <command.h>



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




    // ������ ����� �� ������� ����� �����
    const size_t GRID = 81;
    typedef Portulan3D< GRID, GRID, GRID, float >  city_t;
    city_t city;

    // ���� �� �������� ����
    const std::string elevationFile = PATH_MEDIA + "a/center-hill-elevation-map.png";
    // �������� "a/center-hill-elevation-map.png" �������������
    // 400 ��� (������ �����������) ��� ~30 �� (������ ����������� �����)
    const double scaleXY = 30.0 / 400.0;
    // �.�. ������ ����� ������ ������� �����������, ������ "����������� ���
    // �����������"; ����� ������� �������� �������, ����� "clearness = 1".
    // (!) ������ �� �������������� ������, ����� ������ �� Z ��������� ������� XY.
    const double clearness = 5;
    const double hMin = -10.0 * clearness;
    const double hMax = 20.0 * clearness;
    city << co::elevationMap< city_t >( "NaCl", elevationFile, scaleXY, hMin, hMax );

    // �������� ����� �����, ������� ����� �����
    const std::string waterFile = PATH_MEDIA + "a/water1-mask-map.png";
    const double depth = 10.0 * clearness;
    //city << co::flood( "H2O", waterFile, depth );


    // ���������� ���������
    // @todo ...




    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan -> END" << std::endl;

    std::cout << std::endl << "^" << std::endl;
    std::cin.ignore();

    return 0;

} // main()
