#pragma once

#include "../../../../planet/Portulan.h"
#include <typelib/typelib.h>


namespace portulan {
    namespace io {
        namespace planet {
            namespace set {
                namespace dungeoncrawl {

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
    TextVisual& operator<<( const portulan::planet::Portulan& );



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
        const portulan::planet::set::topology_t&
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


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan








#include "TextVisual.inl"
