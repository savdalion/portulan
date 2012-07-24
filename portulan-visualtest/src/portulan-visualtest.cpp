#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <portulan/portulan.h>
#include <typelib/typelib.h>



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





    assert( false
        && "(i) Визуальные тесты проекта \"portulan\" реализованы в проекте \"porte\". @see https://github.com/savdalion/porte" );





    EZLOGGERVLSTREAM( axter::log_always ) << "Portulan -> END" << std::endl;

    std::cout << std::endl << "^" << std::endl;
    //std::cin.ignore();

    return 0;

} // main()
