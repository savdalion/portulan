#pragma once

#include <typelib/typelib.h>

#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
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
* ������������ ������� ������� ���������� VTK.
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
    explicit VolumeVTKVisual( const option_t& );



    virtual ~VolumeVTKVisual();




    /**
    * ������������� �������. ���� ���� ������������ ��� �� ���� �������, ���
    * ��������. �����, �������� ����������� � �������� ����.
    */
    VolumeVTKVisual& operator<<( const pnp::illuminanceBody_t& );



    /**
    * ��������� ����� �������������.
    */
    VolumeVTKVisual& operator<<( const option_t& );



    /**
    * ������� �������� ���� ������������.
    *
    * @param frequence ��� ����� ����� ���������� ������, ��.
    *        ���� == 0, ��������� �� ����������.
    */
    void waitCircleEngine(
        pnp::illuminanceBody_t*,
        size_t frequence = 1
    );

    void wait();




    /**
    * ������� ���� �������������.
    */
    void clear();





private:
    /**
    * ������ ����� ������� ������ "�����->�������".
    */
    void drawMacro( const pnp::illuminanceBody_t& );


    /**
    * ������ ���� � �������������.
    * ��������, ���������� ������������ ������� �������.
    */
    void drawDetail( const pnp::illuminanceBody_t& );




private:
    /**
    * ������� �������� ������ ������ ������.
    * ����� ��� ������������� ������ � ����������� ������.
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
                "�������� ������ ���� ������." );
            assert( ib &&
                "��������� ��� ������� ��������� ������ ���� �������." );
            assert( (startTime >= 0) &&
                "����� ������ ���� �������������." );
            this->parent = parent;
            this->ib     = ib;
            // ������ ������ ��� ���������� OX (��. ���������� 'ib')
            this->orbit  = ib->coord[ 0 ];
            this->time   = startTime;
        }


        virtual inline void Execute(
            vtkObject*     caller,
            unsigned long  eventId,
            void*          vtkNotUsed( callData )
        ) {
            // ������ ���������� ���������
#if 0
            // �������� ������� ������ ������������ ���
            ib->omega[ 0 ] += 180.0f / 10.0f;
#endif

#if 1
            // �������� ������� �� ������
            const float t = static_cast< float >( time ) / 18.0f;
            ib->coord[ 0 ] = orbit * cos( t ) * 0.9f;
            ib->coord[ 1 ] = orbit * sin( t );
            //ib->coord[ 2 ] = ��� ���������
#endif

            // ������������� ����� ���������
            // @see illuminance-utils-test.h
            static const size_t VOLUME =
                pnp::ILLUMINANCE_GRID * pnp::ILLUMINANCE_GRID * pnp::ILLUMINANCE_GRID;
            std::memset( ib->result, 0, sizeof( pnp::illuminanceCell_t ) * VOLUME );
            typedef typelib::CubeSMC3D< pnp::ILLUMINANCE_GRID >  smc_t;
            for (size_t k = 0; k < pnp::ILLUMINANCE_STAR_COUNT; ++k) {
                const pnp::aboutIlluminanceStar_t& ais = ib->source.star[ k ];
                if (ais.radius <= 0) {
                    // # ������ star � ������ radius - ������� ���������� ������.
                    break;
                }
                // # ����� ��� ������� ��������� ������������ ���
                //   ���������� � ����� OpenCL. �������...
                for (size_t i = 0; i < VOLUME; ++i) {
                    const typelib::coordInt_t c = smc_t::ci( i );
                    pnp::starIlluminancePlanet(
                        ib->result[ i ],
                        c.x, c.y, c.z,
                        // �������
                        ib->radius,
                        ib->coord,
                        ib->omega,
                        // ������
                        &ais
                    );
                }
            }

            ++time;

            // ��������� ���������� �����
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
    * ����� �������������.
    */
    option_t mOption;

    vtkSmartPointer< vtkRenderer >      renderer;
    vtkSmartPointer< vtkRenderWindow >  renderWindow;

    vtkSmartPointer< vtkRenderer >      rendererDetail;
    vtkSmartPointer< vtkRenderWindow >  renderWindowDetail;

    bool alreadyAutoScaleCamera;

    /**
    * ��� ��������� ���������������.
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
