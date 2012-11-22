#include "../include/StdAfx.h"
#include "../include/configure.h"

#include "../include/planet/set/dangeon-crawl/biome-utils-test.h"



/**
* Тестирование проекта 'Portulan'.
*/
int main( int argc, char** argv ) {

    using namespace portulan;
    using namespace portulan::test;


    // Приоритет определяет размер лог-файла
    axter::ezlogger<>::set_verbosity_level_tolerance( axter::log_rarely );
    //axter::ezlogger<>::set_verbosity_level_tolerance( axter::log_often );

    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan test -> BEGIN" << std::endl;
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





    // @todo ...





    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan test -> END" << std::endl;

    std::cout << std::endl << "^" << std::endl;
    std::cin.ignore();

    return 0;

} // main()
