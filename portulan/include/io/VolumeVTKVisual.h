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


// @todo extend Создать контурный визуализатор > http://www.bu.edu/tech/research/training/tutorials/vtk/#CONTOUR


namespace portulan {
    namespace io {


/**
* Визуализация средствами VTK в виде облака точек.
*
* @template sizeWindowT Размер окна визуализации, пкс. Окно - квадратное.
* @template sizePointT Размер точки, пкс.
* @template showCornerT Отмечать углы визуализируемого элемента.
* @template showAxesT Показывать оси декартовых координат.
* @template rgb Первые 4 байта задают цвет по умолчанию для визуализируемых
*           данных. Если 0, данные раскрашиваются в цвета диапазона
*           [ синий (минимум); красный (максимум) ].
*           Пример для красного цвета: 0xFF0000FF
*
* @source http://vtk.org
*/
class VolumeVTKVisual {
public:
    /**
    * Тип для задания опций визуализатору.
    */
    typedef typelib::json::Variant  option_t;


public:
    /**
    * Открывает окно для визуализации.
    */
    VolumeVTKVisual( const io::VolumeVTKVisual::option_t& option );



    virtual ~VolumeVTKVisual();




    /**
    * Визуализирует карту. Если окно визуализации ещё не было создано, оно
    * создаётся. Иначе, карта добавляется к текущему окну.
    */
    template< size_t SX, size_t SY, size_t SZ, typename Number >
    VolumeVTKVisual& operator<<( const typename Portulan3D< SX, SY, SZ, Number >& );



    /**
    * Ожидает закрытия окна визуализации.
    */
    void wait();





private:
    /**
    * Опции визуализатора.
    */
    typelib::json::Variant option;


    vtkSmartPointer< vtkRenderer >  renderer;
    vtkSmartPointer< vtkRenderWindow >  renderWindow;

    /**
    * Оси координат визуализированы.
    */
    bool hasAxes;

};


    } // io

} // portulan








#include "VolumeVTKVisual.inl"
