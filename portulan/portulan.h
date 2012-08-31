#pragma once

#include "configure.h"
#include "include/command.h"
#include "include/Portulan.h"
#include "include/Topology.h"
#include "include/io/VolumeVTKVisual.h"


// Некоторые классы доступны только при включённом OpenCL.
// @see configure.h
#ifdef OPENCL_PORTULAN
#include "include/planet/Portulan.h"
#include "include/planet/Topology.h"

#else
#pragma message( "Class portulan::planet::Portulan not included in project: OpenCL disable" )

#endif
