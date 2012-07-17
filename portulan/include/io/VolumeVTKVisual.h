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
    VolumeVTKVisual( const option_t& option );



    virtual ~VolumeVTKVisual();




    /**
    * Визуализирует карту. Если окно визуализации ещё не было создано, оно
    * создаётся. Иначе, карта добавляется к текущему окну.
    */
    template< size_t SX, size_t SY, size_t SZ >
    VolumeVTKVisual& operator<<( const Portulan3D< SX, SY, SZ >& );



    /**
    * Обновляет опции визуализатора.
    */
    VolumeVTKVisual& operator<<( const option_t& );



    /**
    * Ожидает закрытия окна визуализации.
    */
    void wait();




    /**
    * Очищает окно визаулизатора.
    */
    void clear();




private:
    template< size_t SX, size_t SY, size_t SZ >
    void drawTopologyPresence(
        const typename Portulan3D< SX, SY, SZ >::topology_t::signBitLayer_t&  topologyPresence,
        const typelib::coord_t& shiftCenter
    );


    template< size_t SX, size_t SY, size_t SZ >
    void drawTopologyTemperature(
        const typename Portulan3D< SX, SY, SZ >::topology_t::numberLayer_t&  topologyTemperature,
        const typelib::coord_t& shiftCenter
    );




private:
    /**
    * Опции визуализатора.
    */
    option_t mOption;


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
