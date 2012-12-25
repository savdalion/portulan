#pragma once

#include "../../../../../world/dangeon-crawl/planet/0/Portulan.h"
#include <typelib/typelib.h>


namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

namespace pnp = portulan::world::dungeoncrawl::planet::l0;


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
    TextVisual& operator<<( const pnp::Portulan& );
    TextVisual& operator<<( const std::string& );



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
        const pnp::topology_t&
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


                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan








#include "TextVisual.inl"
