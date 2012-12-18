#pragma once

#include <typelib/typelib.h>

#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <vtkCommand.h>
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
//#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>

#include <boost/lexical_cast.hpp>

#include <porte/include/world/dungeon-crawl/star-system/0/Engine.h>


namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace starsystem {
                    namespace l0 {

namespace pns = portulan::world::dungeoncrawl::starsystem::l0;
namespace pes = porte::world::dungeoncrawl::starsystem::l0;


/**
* Визуализация области звёздной системы средствами VTK.
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
    VolumeVTKVisual( const option_t& );



    virtual ~VolumeVTKVisual();




    /**
    * Визуализирует область. Если окно визуализации ещё не было создано, оно
    * создаётся. Иначе, портулан добавляется к текущему окну.
    */
    VolumeVTKVisual& operator<<( const pns::Portulan& );



    /**
    * Обновляет опции визуализатора.
    */
    VolumeVTKVisual& operator<<( const option_t& );



    /**
    * Ожидает закрытия окна визуализации.
    *
    * @param frequence Как часто будет вызываться пульс движка, мс.
    *        Если == 0, пульсации не происходит (движок 'engine' на мир
    *        не оказывает влияния).
    */
    void wait( pes::Engine* = nullptr, int pulse = 1, size_t frequence = 1 );




    /**
    * Очищает окно визаулизатора.
    */
    void clear();





private:
    void drawTopology( const pns::topology_t& );




private:
    /**
    * Введён для синхронизации движка и визуального образа.
    *
    * @see http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/Animation
    */
    class vtkPulseCallback : public vtkCommand {
    public:
        static vtkPulseCallback* New() {
            vtkPulseCallback* cb = new vtkPulseCallback;
            cb->parent = nullptr;
            cb->engine = nullptr;
            cb->pulse = 0;
            return cb;
        }


        void init( VolumeVTKVisual* parent, pes::Engine* engine, int pulse ) {
            assert( parent &&
                "Родитель должен быть указан." );
            assert( engine &&
                "Движок должен быть указан." );
            assert( (pulse > 0) &&
                "Пульс должен быть положительным." );
            this->parent = parent;
            this->engine = engine;
            this->pulse  = pulse;
        }


        virtual inline void Execute(
            vtkObject*     caller,
            unsigned long  eventId,
            void*          vtkNotUsed( callData )
        ) {
            // меняем внутреннее состояние
            *engine << pulse;

            // обновляем визуальный образ
            // @todo optimize Не перерисовывать всю картинку, менять
            //       только положение Actor's.
            const pns::Portulan* p = engine->portulan();
            *parent << *p;

            /* - См. todo выше.
            vtkRenderWindowInteractor* rw =
                vtkRenderWindowInteractor::SafeDownCast( caller );
            rw->GetRenderWindow()->Render();
            */

#if 0
            size_t i = 0;
            const auto& tpc =
                engine->portulan()
                ->topology().topology()
                .planet.content[ i ];
            std::cout <<
                "  m " << tpc.mass <<
                "  " << typelib::CoordT< pns::real_t >( tpc.coord ) <<
    #if 1
                "  " << tpc.test[0] <<
                 " " << tpc.test[1] <<
                 " " << tpc.test[2] <<
                 " " << tpc.test[3] <<
                 " " << tpc.test[4] <<
    #endif
            std::endl;
#endif
        }


    private:
        VolumeVTKVisual* parent;
        pes::Engine* engine;
        int pulse;
    };



private:
    /**
    * Опции визуализатора.
    */
    option_t mOption;

    vtkSmartPointer< vtkRenderer >      renderer;
    vtkSmartPointer< vtkRenderWindow >  renderWindow;

    bool alreadyAutoScaleCamera;

    /**
    * Оси координат визуализированы.
    */
    bool hasAxes;

};


                    } // l0
                } // starsystem
            } // dungeoncrawl
        } // world
    } // io
} // portulan








#include "VolumeVTKVisual.inl"
