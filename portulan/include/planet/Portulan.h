#pragma once

#include "../../configure.h"
#ifdef OPENCL_PORTULAN

#include "../command.h"
#include "Topology.h"
#include <typelib/typelib.h>
#include <memory>



namespace portulan {
    namespace planet {

class Portulan;

    }
}


/* - @todo ...
namespace std {

std::ostream& operator<<( std::ostream&, const portulan::planet::Portulan& );

} // std
*/



namespace portulan {
    namespace planet {


/**
* Класс для эффективного хранения и обработки 3D-модели планеты на графических
* процессорах (OpenCL, Cuda).
*
* Соглашения
*   # Область планеты (портулан) разбита на SX х SY х SZ равносторонних ячеек. Это
*     уровень I.
*   # На уровне I выделены свои 3D-области в виде карт (портуланов) с
*     уникальной структурой, максимально обобщающей жизнь (изменение) в
*     "области планеты".
*   # На уровне I отсутствуют конкретные сущности.
*   # Общие сущности позиционируются по целым ячейкам.
*
*/
class Portulan {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Portulan >  Ptr;
    typedef std::unique_ptr< Portulan >  UPtr;
    typedef std::weak_ptr< Portulan >    WPtr;


public:

    inline Portulan() {
    }




    inline virtual ~Portulan() {
    }




    inline Topology const& topology() const {
        return mTopology;
    }



    inline Topology& topology() {
        return mTopology;
    }







private:
    /**
    * Топология планеты.
    */
    Topology mTopology;

};



    } // planet
} // portulan








#include "Portulan.inl"


#else
#pragma message( "Class portulan::planet::Portulan not included in project: OpenCL disable" )

#endif
