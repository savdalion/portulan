#pragma once

#include <typelib/typelib.h>

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
    VolumeVTKVisual( const option_t& option );



    virtual ~VolumeVTKVisual();




    /**
    * ������������� �����. ���� ���� ������������ ��� �� ���� �������, ���
    * ��������. �����, ����� ����������� � �������� ����.
    */
    template< size_t SX, size_t SY, size_t SZ >
    VolumeVTKVisual& operator<<( const typename Portulan3D< SX, SY, SZ >& );



    /**
    * ��������� ����� �������������.
    */
    VolumeVTKVisual& operator<<( const option_t& );



    /**
    * ������� �������� ���� ������������.
    */
    void wait();





private:
    template< size_t SX, size_t SY, size_t SZ >
    void drawTopologyPresence(
        const typename Portulan3D< SX, SY, SZ >::signBitLayer_t&  topologyPresence,
        const typelib::coord_t& shiftCenter
    );


    template< size_t SX, size_t SY, size_t SZ >
    void drawTopologyTemperature(
        const typename Portulan3D< SX, SY, SZ >::numberLayer_t&  topologyTemperature,
        const typelib::coord_t& shiftCenter
    );




private:
    /**
    * ����� �������������.
    */
    option_t mOption;


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
