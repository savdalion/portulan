#pragma once

#include "configure.h"
#include "include/command.h"
#include "include/Portulan.h"
#include "include/Topology.h"
#include "include/io/VolumeVTKVisual.h"


// Некоторые классы доступны только при включённом OpenCL.
// @see configure.h
#ifdef OPENCL_PORTULAN
#include "include/world/dangeon-crawl/planet/0/Portulan.h"
#include "include/world/dangeon-crawl/planet/0/Topology.h"
#include "include/world/dangeon-crawl/star-system/0/Portulan.h"
#include "include/world/dangeon-crawl/star-system/0/Topology.h"

#else
#pragma message( "The class pnp = portulan::world::dungeoncrawl::planet::l0::Portulan not included in project because the OpenCL is disable." )

#endif


#ifdef DUNGEON_CRAWL_WORLD_PORTULAN
#include "include/io/world/dangeon-crawl/planet/0/SnapshotVTK.h"
#include "include/io/world/dangeon-crawl/planet/0/TextVisual.h"

#include "include/io/world/dangeon-crawl/star-system/0/VolumeVTKVisual.h"


#else
#pragma message( "The file configure.h don't include any set of portulan. Build of the portulan is not complete." )

#endif
