#include "../include/StdAfx.h"
#include "../include/configure.h"

#include "../include/planet/set/dangeon-crawl/illuminance-utils-test.h"



/**
* ����-����� ��� ������� 'Portulan'.
*/
int main( int argc, char** argv ) {

    using namespace portulan;
    using namespace portulan::test;


    setlocale( LC_ALL, "Russian" );
    // ��� ����������� '.' ������ ','
    setlocale( LC_NUMERIC, "C" );



    ::testing::InitGoogleTest( &argc, argv );
    ::testing::FLAGS_gtest_death_test_style = "fast";
    int result = 0;
    try {
        result = RUN_ALL_TESTS();
    } catch ( ... ) {
        // @todo fine ��������� assert() � ��������� - ��������� ����:
        //       ��������� ����� ������ � �������. �������� assert'� ��
        //       exception?
    }



    std::cout << std::endl << "^" << std::endl;
    //std::cin.ignore();

    return result;

} // main()
