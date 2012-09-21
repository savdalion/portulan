#pragma once

#include "../../../../planet/Portulan.h"
#include <typelib/typelib.h>


namespace portulan {
    namespace io {
        namespace planet {
            namespace set {
                namespace dungeoncrawl {

/**
* ����� ���������� � ��������� ������� ������� ���� Dungeon Crawl
* � ���� ������.
*/
class TextVisual {
public:
    /**
    * ��� ��� ������� �����.
    */
    typedef typelib::json::Variant  option_t;


public:
    TextVisual( std::ostream&,  const option_t& );



    virtual ~TextVisual();



    /**
    * �������� � ������� �����.
    */
    TextVisual& operator<<( const portulan::planet::Portulan& );



    /**
    * ��������� �����.
    */
    TextVisual& operator<<( const option_t& );



    /**
    * ������� ������� Enter.
    */
    void wait();




private:
    void drawTopologySizeInMemory(
        const portulan::planet::set::topology_t&
    );




private:
    /**
    * ����� �������������.
    */
    option_t mOption;

    /**
    * ����� ��� ������ ������;
    */
    std::ostream*  out;

};


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan








#include "TextVisual.inl"
