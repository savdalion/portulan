#pragma once

#include "../../../../../world/dangeon-crawl/planet/0/Portulan.h"
#include <typelib/typelib.h>


namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

/**
* Вывод информации о состоянии области планеты мира Dungeon Crawl
* в виде текста.
*/
class TextVisual {
public:
    /**
    * Тип для задания опций.
    */
    typedef typelib::json::Variant  option_t;


public:
    TextVisual( std::ostream&,  const option_t& );



    virtual ~TextVisual();



    /**
    * Печатает в текущий поток.
    */
    TextVisual& operator<<( const portulan::world::dungeoncrawl::planet::l0::Portulan& );
    TextVisual& operator<<( const std::string& );



    /**
    * Обновляет опции.
    */
    TextVisual& operator<<( const option_t& );



    /**
    * Ожидает нажатия Enter.
    */
    void wait();




private:
    void drawTopologySizeInMemory(
        const portulan::world::dungeoncrawl::planet::l0::topology_t&
    );




private:
    /**
    * Опции визуализатора.
    */
    option_t mOption;

    /**
    * Поток для вывода текста;
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
