#pragma once

#include <typelib/include/mapcontent3d/BitMap.h>
#include <typelib/include/other.h>
#include <typelib/include/json.h>

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

#include <boost/lexical_cast.hpp>


// @todo extend ������� ��������� ������������ > http://www.bu.edu/tech/research/training/tutorials/vtk/#CONTOUR


namespace portulan {
    namespace io {


/**
* ������������ ���������� VTK � ���� ������ �����.
*
* @template sizeWindowT ������ ���� ������������, ���. ���� - ����������.
* @template sizePointT ������ �����, ���.
* @template showCornerT �������� ���� ���������������� ��������.
* @template showAxesT ���������� ��� ���������� ���������.
* @template rgb ������ 4 ����� ������ ���� �� ��������� ��� ���������������
*           ������. ���� 0, ������ �������������� � ����� ���������
*           [ ����� (�������); ������� (��������) ].
*           ������ ��� �������� �����: 0xFF0000FF
*
* @source http://vtk.org
*/
class VolumeVTKVisual {
public:
    /**
    * ��� ��� ������� ����� �������������.
    */
    typedef typelib::json::Variant  option_t;


public:
    /**
    * ��������� ���� ��� ������������.
    */
    VolumeVTKVisual( const io::VolumeVTKVisual::option_t& option );



    virtual ~VolumeVTKVisual();




    /**
    * ������������� �����. ���� ���� ������������ ��� �� ���� �������, ���
    * ��������. �����, ����� ����������� � �������� ����.
    */
    template< size_t SX, size_t SY, size_t SZ, typename Number >
    VolumeVTKVisual& operator<<( const typename Portulan3D< SX, SY, SZ, Number >& );



    /**
    * ������� �������� ���� ������������.
    */
    void wait();





private:
    /**
    * ����� �������������.
    */
    typelib::json::Variant option;


    vtkSmartPointer< vtkRenderer >  renderer;
    vtkSmartPointer< vtkRenderWindow >  renderWindow;

    /**
    * ��� ��������� ���������������.
    */
    bool hasAxes;

};


    } // io

} // portulan








#include "VolumeVTKVisual.inl"
