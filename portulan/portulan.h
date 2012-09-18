#pragma once

#include "configure.h"
#include "include/command.h"
#include "include/Portulan.h"
#include "include/Topology.h"
#include "include/io/VolumeVTKVisual.h"


// ��������� ������ �������� ������ ��� ���������� OpenCL.
// @see configure.h
#ifdef OPENCL_PORTULAN
#include "include/planet/Portulan.h"
#include "include/planet/Topology.h"

#else
#pragma message( "Class portulan::planet::Portulan not included in project: OpenCL disable" )

#endif


#ifdef DUNGEON_CRAWL_SET_PLANET_PORTULAN
/* - ������������ � Topology.h.
#include "include/planet/set/dangeon-crawl/component.h"
#include "include/planet/set/dangeon-crawl/constructor.h"
#include "include/planet/set/dangeon-crawl/living.h"
#include "include/planet/set/dangeon-crawl/living-set.h"
#include "include/planet/set/dangeon-crawl/structure.h"
*/
#include "include/planet/set/dangeon-crawl/display.h"


#else
#pragma message( "File configure.h don't include any set of portulan. Build of portulan is not complete." )

#endif
