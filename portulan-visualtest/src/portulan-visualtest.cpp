#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <Portulan3D.h>
#include <command.h>



/**
* Визуальное тестирование для проекта 'Portulan'.
*/
int main( int argc, char** argv ) {

    using namespace portulan;
    using namespace portulan::visualtest;

    namespace co = portulan::command;


    // Приоритет определяет размер лог-файла
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
    // Для разделителя '.' вместо ','
    setlocale( LC_NUMERIC, "C" );




    // Соберём карту из готовой карты высот
    const size_t GRID = 81;
    typedef Portulan3D< GRID, GRID, GRID, float >  city_t;
    city_t city;

    // холм из каменной соли
    const std::string elevationFile = PATH_MEDIA + "a/center-hill-elevation-map.png";
    // картинка "a/center-hill-elevation-map.png" протяжённостью
    // 400 пкс (размер изображения) или ~30 км (размер создаваемой карты)
    const double scaleXY = 30.0 / 400.0;
    // т.к. высота много меньше размера поверхности, вводим "коэффициент для
    // наглядности"; чтобы увидеть реальный масштаб, пишем "clearness = 1".
    // (!) Сейчас не отрабатывается момент, когда размер по Z превышает размеры XY.
    const double clearness = 5;
    const double hMin = -10.0 * clearness;
    const double hMax = 20.0 * clearness;
    city << co::elevationMap< city_t >( "NaCl", elevationFile, scaleXY, hMin, hMax );

    // заливаем водой места, которые задаёт маска
    const std::string waterFile = PATH_MEDIA + "a/water1-mask-map.png";
    const double depth = 10.0 * clearness;
    //city << co::flood( "H2O", waterFile, depth );


    // показываем результат
    // @todo ...




    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan -> END" << std::endl;

    std::cout << std::endl << "^" << std::endl;
    std::cin.ignore();

    return 0;

} // main()
