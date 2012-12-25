#pragma once

#include "../../../../../world/dangeon-crawl/planet/0/Portulan.h"
#include <typelib/typelib.h>

#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkCharArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>



namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

namespace pnp = portulan::world::dungeoncrawl::planet::l0;


/**
* Сохраняет мир Dungeon Crawl в формате VTK.
* Просмотреть можно визуализаторами, которые понимают формат VTK:
*   - ParaView  http://paraview.org
*   - VisIt     https://wci.llnl.gov
*/
class SnapshotVTK {
public:
    /**
    * Тип для задания опций.
    */
    typedef typelib::json::Variant  option_t;


public:
    explicit SnapshotVTK( const std::shared_ptr< pnp::Portulan > );


    virtual ~SnapshotVTK();




    /**
    * @todo Выгружает данные на диск согласно установленным опциям.
    */
    SnapshotVTK& operator<<( const option_t& );




    /**
    * Сохраняет в файл данные о топологии портулана.
    */
    // @todo void all();

    void component(   const std::string& file = "component" );
    void temperature( const std::string& file = "temperature" );
    void surfaceTemperature( const std::string& file = "surface-temperature" );
    void rainfall(    const std::string& file = "rainfall" );
    void drainage(    const std::string& file = "drainage" );
    void landscape(   const std::string& file = "landscape" );
    void illuminance( const std::string& file = "illuminance" );
    void biome(       const std::string& file = "biome" );
    void living(      const std::string& file = "living" );





private:
    /**
    * Записывает данные в указанный файл.
    */
    static void write(
        const std::string& fileName,
        const vtkSmartPointer< vtkStructuredGrid > data
    );

    static void write(
        const std::string& fileName,
        const vtkSmartPointer< vtkPolyData > data
    );




private:
    /**
    * Портулан.
    */
    const std::weak_ptr< pnp::Portulan >  mPortulan;

};

                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan








#include "SnapshotVTK.inl"
