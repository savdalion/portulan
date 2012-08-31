#pragma once

/**
* ¬се известные наборы команд дл€ создани€ карт.
*/

#include "command/common.h"


#include "../configure.h"
#ifdef OPENCL_PORTULAN

#include "command/planet.h"

#else
#pragma message( "Commands portulan::command::planet not included in project: OpenCL disable" )

#endif
