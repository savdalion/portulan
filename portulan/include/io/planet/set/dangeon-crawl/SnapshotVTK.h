#pragma once

#include "../../../../planet/Portulan.h"
#include <typelib/typelib.h>

/*
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkTransform.h>
#include <vtkAxesActor.h>
#include <vtkCubeSource.h>
#include <vtkRegularPolygonSource.h>
#include <vtkCubeAxesActor.h>
#include <vtkLookupTable.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
*/

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
* ��������� ��� Dungeon Crawl � ������� VTK.
* ����������� ����� ���������������, ������� �������� ������ VTK:
*   - ParaView  http://paraview.org
*   - VisIt     https://wci.llnl.gov
*/
class SnapshotVTK {
public:
    /**
    * ��� ��� ������� �����.
    */
    typedef typelib::json::Variant  option_t;


public:
    SnapshotVTK( const portulan::planet::Portulan* );


    virtual ~SnapshotVTK();




    /**
    * @todo ��������� ������ �� ���� �������� ������������� ������.
    */
    SnapshotVTK& operator<<( const option_t& );




    /**
    * ��������� � ���� ������ � �����������.
    */
    void averageTemperature( const std::string& file = "average-temperature" );





private:
    /**
    * ��������.
    */
    const portulan::planet::Portulan*  mPortulan;

};


                } // dungeoncrawl
            } // set
        } // planet
    } // io
} // portulan








#include "SnapshotVTK.inl"
