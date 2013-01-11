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
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkLegendScaleActor.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricEllipsoid.h>

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
* Помимо размещения в пространстве, визуализируются формы элементов.
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
    explicit VolumeVTKVisual( const option_t& );



    virtual ~VolumeVTKVisual();




    /**
    * Визуализирует область. Если окно визуализации ещё не было создано, оно
    * создаётся. Иначе, портулан добавляется к текущему окну.
    */
    virtual VolumeVTKVisual& operator<<( const pns::Portulan& );



    /**
    * Обновляет опции визуализатора.
    */
    virtual VolumeVTKVisual& operator<<( const option_t& );



    /**
    * Ожидает закрытия окна визуализации.
    *
    * @template frequence Как часто будет вызываться пульс движка, мс.
    *           Если == 0, пульсации не происходит (движок 'engine' на мир
    *           не оказывает влияния).
    * @template pulse Количество пульсов, которые должен выполнить движок
    *           до визуализации результата.
    * @template needStep Скольк шагов "прокрутить".
    *           По прошествии заданного кол-ва шагов управление возвращается
    *           вызвавшему метод wait*().
    *           Если (needStep <= 0), wait*() выполняется бесконечно.
    * @template closeWindow Закрыть окно визуализатора при возврате управления.
    * @template showPulse Печатать текущий пульс каждый шаг.
    */
    template<
        size_t frequence,
        int pulse,
        int needStep,
        bool closeWindow,
        bool showPulse
    >
    void wait( pes::Engine* = nullptr );




    /**
    * Очищает окно визаулизатора.
    */
    virtual void clear();





protected:
    virtual void drawTopology( const pns::topology_t& );




    void drawTopology( const pns::starContent_t,  pns::real_t csDIVws );
    void drawTopology( const pns::planetContent_t,  pns::real_t csDIVws );
    void drawTopology( const pns::asteroidContent_t,  pns::real_t csDIVws );




    void insertPoint(
        vtkSmartPointer< vtkPoints >,
        vtkSmartPointer< vtkCellArray >,
        const pns::real_t  coord[ 3 ]
    );


    void drawPoints(
        vtkSmartPointer< vtkPoints >,
        vtkSmartPointer< vtkCellArray >,
        size_t  sizePoint,
        const typelib::vector_t&  color
    );


    void drawSphere(
        const pns::real_t  coord[ 3 ],
        const pns::real_t  radius,
        const typelib::vector_t&  color
    );


    void drawEllipsoid(
        const pns::real_t  coord[ 3 ],
        const pns::real_t  radius[ 3 ],
        const typelib::vector_t&  color
    );




private:
    /**
    * Введён для синхронизации движка и визуального образа.
    *
    * @see http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/Animation
    */
    template<
        int pulse,
        int needStep,
        bool closeWindow,
        bool showPulse
    >
    class vtkPulseCallback : public vtkCommand {
    public:
        static vtkPulseCallback* New() {
            static_assert( (pulse > 0),
                "Пульс должен быть положительным." );
            vtkPulseCallback* cb = new vtkPulseCallback;
            cb->parent = nullptr;
            cb->engine = nullptr;
            cb->currentStep = 0;
            cb->complete = true;
            return cb;
        }


        void init(
            VolumeVTKVisual* parent,
            pes::Engine* engine
        ) {
            assert( parent &&
                "Родитель должен быть указан." );
            assert( engine &&
                "Движок должен быть указан." );

            this->parent   = parent;
            this->engine   = engine;
            this->currentStep = 0;
            this->complete = true;
        }


        virtual inline void Execute(
            vtkObject*     caller,
            unsigned long  eventId,
            void*          vtkNotUsed( callData )
        ) {
            // команда не должна вызываться пока не завершена предыдущая
            // @todo optimize Лишнее? Проверить соглашения для VTK::Execute().
            if ( !complete ) {
                return;
            }

            // возвращаем управление по прошествии 'needStep' шагов
            if ( (needStep > 0) && (currentStep > needStep) ) {
                auto rwi = static_cast< vtkRenderWindowInteractor* >( caller );
                rwi->TerminateApp();
                if ( closeWindow ) {
                    rwi->GetRenderWindow()->Finalize();
                }
                return;
            }

            // печатаем пульс
            if ( showPulse ) {
                std::cout << engine->live() << std::endl;
            }

            // меняем внутреннее состояние
            *engine << pulse;

            // обновляем визуальный образ
            // @todo optimize Не перерисовывать всю картинку, менять
            //       только положение Actor's.
            const auto p = engine->portulan();
            p->draw( parent );

            /* - См. todo выше.
            vtkRenderWindowInteractor* rw =
                vtkRenderWindowInteractor::SafeDownCast( caller );
            rw->GetRenderWindow()->Render();
            */

#if 0
            // @test
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

            // считаем "шаги"
            ++currentStep;

            // команда завершена, можно вызывать следующую
            complete = true;
        }


    private:
        VolumeVTKVisual* parent;
        pes::Engine* engine;
        
        /**
        * Выполнено шагов с момента запуска.
        */
        int currentStep;

        /**
        * Не позволяем командам накапливаться - блокировки.
        */
        bool complete;
    };



protected:
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
