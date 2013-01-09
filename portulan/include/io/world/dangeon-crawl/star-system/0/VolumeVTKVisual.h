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
* ������������ ������� ������� ������� ���������� VTK.
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
    VolumeVTKVisual& operator<<( const pns::Portulan& );



    /**
    * ��������� ����� �������������.
    */
    VolumeVTKVisual& operator<<( const option_t& );



    /**
    * ������� �������� ���� ������������.
    *
    * @param frequence ��� ����� ����� ���������� ����� ������, ��.
    *        ���� == 0, ��������� �� ���������� (������ 'engine' �� ���
    *        �� ��������� �������).
    */
    void wait(
        pes::Engine* = nullptr,
        int pulse = 1,
        size_t frequence = 1,
        int needStep = 0,
        bool closeWindow = false
    );




    /**
    * ������� ���� �������������.
    */
    void clear();





private:
    void drawTopology( const pns::topology_t& );




private:
    /**
    * ����� ��� ������������� ������ � ����������� ������.
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
            cb->needStep = 0;
            cb->currentStep = 0;
            cb->closeWindow = false;
            cb->complete = true;
            return cb;
        }


        void init(
            VolumeVTKVisual* parent,
            pes::Engine* engine,
            int pulse,
            int needStep = -1,
            bool closeWindow = false
        ) {
            assert( parent &&
                "�������� ������ ���� ������." );
            assert( engine &&
                "������ ������ ���� ������." );
            assert( (pulse > 0) &&
                "����� ������ ���� �������������." );
            this->parent   = parent;
            this->engine   = engine;
            this->pulse    = pulse;
            this->needStep = needStep;
            this->currentStep = 0;
            this->closeWindow = closeWindow;
            this->complete = true;
        }


        virtual inline void Execute(
            vtkObject*     caller,
            unsigned long  eventId,
            void*          vtkNotUsed( callData )
        ) {
            // ������� �� ������ ���������� ���� �� ��������� ����������
            // @todo optimize ������? ��������� ���������� ��� VTK::Execute().
            if ( !complete ) {
                return;
            }

            // ���������� ���������� �� ���������� 'needStep' �����
            if ( (needStep > 0) && (currentStep > needStep) ) {
                auto rwi = static_cast< vtkRenderWindowInteractor* >( caller );
                rwi->TerminateApp();
                if ( closeWindow ) {
                    rwi->GetRenderWindow()->Finalize();
                }
                return;
            }

            // ������ ���������� ���������
            *engine << pulse;

            // ��������� ���������� �����
            // @todo optimize �� �������������� ��� ��������, ������
            //       ������ ��������� Actor's.
            const auto p = engine->portulan();
            p->draw( parent );

            /* - ��. todo ����.
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

            // ������� "����"
            ++currentStep;

            // ������� ���������, ����� �������� ���������
            complete = true;
        }


    private:
        VolumeVTKVisual* parent;
        pes::Engine* engine;
        
        /**
        * ���������� �������, ������� ������ ��������� ������
        * �� ������������ ����������.
        */
        int pulse;

        /**
        * ������ ����� "����������".
        * �� ���������� ��������� ���-�� ����� ���������� ������������
        * ���������� ����� wait*().
        * ���� (needStep <= 0), wait*() ����������� ����������.
        */
        int needStep;

        /**
        * ��������� ����� � ������� �������.
        */
        int currentStep;

        /**
        * ������� ���� ��� �������� ����������.
        *
        * @see needStep
        */
        bool closeWindow;

        /**
        * �� ��������� �������� ������������� - ����������.
        */
        bool complete;
    };



private:
    /**
    * ����� �������������.
    */
    option_t mOption;

    vtkSmartPointer< vtkRenderer >      renderer;
    vtkSmartPointer< vtkRenderWindow >  renderWindow;

    bool alreadyAutoScaleCamera;

    /**
    * ��� ��������� ���������������.
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
