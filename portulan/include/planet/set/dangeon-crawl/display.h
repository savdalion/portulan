#pragma once

#include "topology.h"


/**
* Вывод в поток информации о топологии портулана.
* Для отладки.
*/


std::ostream& operator<<( std::ostream&,  const portulan::planet::set::topology_t& );







#include "display.inl"
