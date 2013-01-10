#pragma once

#include "VolumeVTKVisual.h"
#include <array>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricEllipsoid.h>


namespace portulan {
    namespace io {
        namespace world {
            namespace dungeoncrawl {
                namespace starsystem {
                    namespace l0 {

/**
* Визуализация области звёздной системы средствами VTK.
* Помимо размещения в пространстве, визуализируются формы элементов.
*/
class FormVTKVisual : public VolumeVTKVisual {
public:
    explicit FormVTKVisual( const option_t& );



    virtual ~FormVTKVisual();




private:
    /**
    * @virtual VolumeVTKVisual
    */
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

};


                    } // l0
                } // starsystem
            } // dungeoncrawl
        } // world
    } // io
} // portulan








#include "FormVTKVisual.inl"
