#pragma once

#include <typelib/typelib.h>

#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <vtkColor.h>
#include <vtkLegendScaleActor.h>
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
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkShrinkFilter.h>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>

#include <boost/lexical_cast.hpp>

#include "../../../../../world/dangeon-crawl/planet/0/set/illuminance-utils.h"


namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace planet {
                    namespace l0 {

namespace pnp = portulan::world::dungeoncrawl::planet::l0;


/**
* Визуализация области планеты средствами VTK.
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
    VolumeVTKVisual& operator<<( const pnp::illuminanceBody_t& );



    /**
    * Обновляет опции визуализатора.
    */
    VolumeVTKVisual& operator<<( const option_t& );



    /**
    * Ожидает закрытия окна визуализации.
    *
    * @param frequence Как часто будет вызываться измене, мс.
    *        Если == 0, пульсации не происходит.
    */
    void waitCircleEngine(
        pnp::illuminanceBody_t*,
        size_t frequence = 1
    );

    void wait();




    /**
    * Очищает окно визаулизатора.
    */
    void clear();





private:
    /**
    * Рисует общую картину системы "звёзды->планета".
    */
    void drawMacro( const pnp::illuminanceBody_t& );


    /**
    * Рисует окно с подробностями.
    * Например, показывает освещённость планеты звёздами.
    */
    void drawDetail( const pnp::illuminanceBody_t& );




private:
    /**
    * Планета движется вокруг первой звезды.
    * Введён для синхронизации движка и визуального образа.
    *
    * @see http://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/Animation
    */
    class IlluminanceCircleCallback : public vtkCommand {
    public:
        static IlluminanceCircleCallback* New() {
            IlluminanceCircleCallback* cb = new IlluminanceCircleCallback;
            cb->parent = nullptr;
            cb->ib = nullptr;
            cb->orbit = 0.0f;
            cb->time = 0;
            return cb;
        }


        void init(
            VolumeVTKVisual*         parent,
            pnp::illuminanceBody_t*  ib,
            int                      startTime
        ) {
            assert( parent &&
                "Родитель должен быть указан." );
            assert( ib &&
                "Структура для расчёта освещения должна быть указана." );
            assert( (startTime >= 0) &&
                "Время должно быть положительным." );
            this->parent = parent;
            this->ib     = ib;
            // орбита возьмём как расстояние OX (см. заполнение 'ib')
            this->orbit  = ib->coord[ 0 ];
            this->time   = startTime;
        }


        virtual inline void Execute(
            vtkObject*     caller,
            unsigned long  eventId,
            void*          vtkNotUsed( callData )
        ) {
            // меняем внутреннее состояние
#if 0
            // вращение планеты вокруг координатной оси
            ib->omega[ 0 ] += 180.0f / 10.0f;
#endif

#if 1
            // движение планеты по орбите
            const float t = static_cast< float >( time ) / 18.0f;
            ib->coord[ 0 ] = orbit * cos( t ) * 0.9f;
            ib->coord[ 1 ] = orbit * sin( t );
            //ib->coord[ 2 ] = без изменений
#endif

            // пересчитываем карту освещения
            // @see illuminance-utils-test.h
            static const size_t VOLUME =
                pnp::ILLUMINANCE_GRID * pnp::ILLUMINANCE_GRID * pnp::ILLUMINANCE_GRID;
            std::memset( ib->result, 0, sizeof( pnp::illuminanceCell_t ) * VOLUME );
            typedef typelib::CubeSMC3D< pnp::ILLUMINANCE_GRID >  smc_t;
            for (size_t k = 0; k < pnp::ILLUMINANCE_STAR_COUNT; ++k) {
                const pnp::aboutIlluminanceStar_t& ais = ib->source.star[ k ];
                if (ais.radius <= 0) {
                    // # Запись star с пустым radius - признак завершения списка.
                    break;
                }
                // # Метод для расчёта освещения предназначен для
                //   исполнения в ядрах OpenCL. Поэтому...
                for (size_t i = 0; i < VOLUME; ++i) {
                    const typelib::coordInt_t c = smc_t::ci( i );
                    pnp::starIlluminancePlanet(
                        ib->result[ i ],
                        c.x, c.y, c.z,
                        // планета
                        ib->radius,
                        ib->coord,
                        ib->omega,
                        // звезда
                        &ais
                    );
                }
            }

            ++time;

            // обновляем визуальный образ
            *parent << *ib;
        }


    private:
        VolumeVTKVisual*         parent;
        pnp::illuminanceBody_t*  ib;
        float                    orbit;
        int                      time;
    };



private:
    /**
    * Опции визуализатора.
    */
    option_t mOption;

    vtkSmartPointer< vtkRenderer >      renderer;
    vtkSmartPointer< vtkRenderWindow >  renderWindow;

    vtkSmartPointer< vtkRenderer >      rendererDetail;
    vtkSmartPointer< vtkRenderWindow >  renderWindowDetail;

    bool alreadyAutoScaleCamera;

    /**
    * Оси координат визуализированы.
    */
    bool hasAxes;

};


                    } // l0
                } // planet
            } // dungeoncrawl
        } // world
    } // io
} // portulan








#include "VolumeVTKVisual.inl"
