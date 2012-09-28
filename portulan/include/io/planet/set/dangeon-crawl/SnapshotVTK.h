#pragma once

#include "../../../../planet/Portulan.h"
#include <typelib/typelib.h>

#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>



namespace portulan {
    namespace io {
        namespace planet {
            namespace set {
                namespace dungeoncrawl {


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
    SnapshotVTK( const portulan::planet::Portulan* );


    virtual ~SnapshotVTK();




    /**
    * @todo Выгружает данные на диск согласно установленным опциям.
    */
    SnapshotVTK& operator<<( const option_t& );




    /**
    * Сохраняет в файлы данные о топологии портулана.
    */
    //void all();

    void component(   const std::string& file = "component" );
    void temperature( const std::string& file = "temperature" );
    void surfaceTemperature( const std::string& file = "surface-temperature" );
    void rainfall(    const std::string& file = "rainfall" );
    void drainage(    const std::string& file = "drainage" );
    void living(      const std::string& file = "living" );





private:
    /**
    * Записывает данные в указанный файл.
    */
    static void write(
        const std::string& fileName,
        const vtkSmartPointer< vtkPolyData > data
    );





private:
    /**
    * Портулан.
    */
    const portulan::planet::Portulan*  mPortulan;

};


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan








#include "SnapshotVTK.inl"
