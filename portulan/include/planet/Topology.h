#pragma once

#include "../../configure.h"
#ifdef OPENCL_PORTULAN

#include <typelib/typelib.h>
#include <memory>
#include <CL/cl_platform.h>
#include <CL/cl.h>



namespace portulan {
    namespace planet {

template< size_t SX, size_t SY, size_t SZ >
struct Topology;

    }
}


/* - @todo ...
namespace std {

template< size_t SX, size_t SY, size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::Topology< SX, SY, SZ >& );

} // std
*/



namespace portulan {
    namespace planet {


/**
* ��������� ��� ������ � ���������� �������.
* ������ ��������, ��� ��������� ���������� ��������� ����������
* (��. planet::Portulan).
*
* ����������
*   # ������� ��������� ������� ������ 3.
*   # ������� ����� � ������������ ��������� � ������ ��������� �������
*     ������� �� 81 x 81 x 81 ������.
*   # ���� ������ ��������� ����� ������ � �������� OpenCL: ��� ��������
*     �������� �������� booster-��������� (��. porte::Booster).
*/
template< size_t SX, size_t SY, size_t SZ >
struct Topology {
    /**
    * ������.
    */
    typedef std::shared_ptr< Topology >  Ptr;
    typedef std::unique_ptr< Topology >  UPtr;
    typedef std::weak_ptr< Topology >    WPtr;



    /**
    * ������� ���� ������.
    *//* - ��������� ���� �� ������������� ��������� ���������
           booster-��������� ��� ������������ ������ ������� �����
           CPU � GPU. ��. ����.
    typedef typelib::SignBitMap< SX, SY, SZ >  signBitLayer_t;
    typedef typelib::SignNumberMap< float, SX, SY, SZ >  signNumberLayer_t;
    typedef typelib::NumberMap< float, SX, SY, SZ >  numberLayer_t;
    typedef typelib::VectorMap< float, SX, SY, SZ >  vectorLayer_t;
    */
    typedef cl_float numberLayer_t[ SX * SY * SZ ];



    /**
    * ����. ���-�� ���. ���������� (�������), ������� ����� �������� � ���������.
    * ��������, ��� ������ ���� ����� ������� ����. ������������:
    *   (0)O, (1)Si, Al, Fe, Ca, Na, K, (7)Mg, (8)H, (9)������
    */
    static const size_t CHEMICAL_SUBSTANCE = 15;
    typedef cl_float chemicalSubstance_t[ CHEMICAL_SUBSTANCE ];


    /**
    * ������ ����� ��������� ������� � ������� �������.
    */
    static const size_t ATMOSPHERE_GRID = SX;


    /**
    * ������ ����� �������� ��������� �������.
    *
    * ��������, ������� ������� ����������� �� ����� 27�27�27 � ��� ������
    * ���������� ������ ����������� �������� � ��; �.�. �� ������ I
    * �������� 19683 �������� �� ������� ������� ���� ��, ����������
    * ������� - ��. ���� - ��� ��������� �� ������; ������� ��
    * ����������� - ��. ���� ������������ ��������������;
    * ��������� ������� � ��������� ��������� �����, �������.
    */
    static const size_t PRESSURE_ATMOSPHERE_GRID = SX / 3;


    /**
    * ������ ����� ������ � ��������� �������.
    *
    * ����� - ����� 54�54�54, 157464 ������ - � 2 ���� ������ �����
    * ��������, ��� ��������� ���������� ����������� ������ - 4 ����� -
    * ������ ������ ������ ��������.
    */
    static const size_t WIND_ATMOSPHERE_GRID = SX / 3 * 2;


    /**
    * ��������� �������.
    */
    typedef struct {
        /**
        * ����� ���������, ��.
        */
        cl_float mass;

        /**
        * ���������� ������ ���������, �.
        * ������ �����. ������� �������.
        */
        cl_float innerRadius;

        /**
        * ������� ���������, �.
        */
        cl_float depth;

        /**
        * ���������� (�� ������).
        * ����������� � ���� % / 100 ������������ ���. ���������.
        * ����� ���� ��������� = 1.0.
        *//* - ��������. ��. ����.
        typedef struct {
            numberLayer_t N2;
            numberLayer_t O2;
            numberLayer_t Ar;
            numberLayer_t CO2;
            numberLayer_t sparse;
        } content_t;
        */

        typedef chemicalSubstance_t content_t[ ATMOSPHERE_GRID * ATMOSPHERE_GRID * ATMOSPHERE_GRID ];
        content_t content;

        /**
        * �������� ���������, ��.
        *//* - ��������� ���� �� ������������� ��������� ���������
               booster-��������� ��� ������������ ������ ������� �����
               CPU � GPU. ��� ����� ���������� ������� ���� C. ��. ����.
        typedef typelib::NumberMap< float, SX / 3, SY / 3, SZ / 3 >  pressure_t;
        */
        typedef cl_float pressure_t[ PRESSURE_ATMOSPHERE_GRID * PRESSURE_ATMOSPHERE_GRID * PRESSURE_ATMOSPHERE_GRID ];
        pressure_t pressure;


        /**
        * �����.
        * ������� ��������, �/�.
        *//* - ��. ����. � pressure_t ����.
        typedef typelib::NumberMap< float, SX / 3 * 2, SY / 3 * 2, SZ / 3 * 2 >  wind_t;
        */
        typedef cl_float wind_t[ WIND_ATMOSPHERE_GRID * WIND_ATMOSPHERE_GRID * WIND_ATMOSPHERE_GRID ];
        wind_t wind;

    } atmosphere_t;




    /**
    * ������ ����� ����������� ���� � ������� �������.
    */
    static const size_t CRUST_GRID = SX;


    /**
    * ������ ����� � ����������� � ����������� ����������� ����
    * � ������� �������.
    */
    static const size_t SURFACE_CRUST_GRID = SX / 3;


    /**
    * ���� �������.
    */
    typedef struct {
        /**
        * ����� ����, ��.
        */
        cl_float mass;

        /**
        * ���������� ������ ����, �.
        * ������ �����. ������� ������� ����� ������� ����.
        */
        cl_float innerRadius;

        /**
        * ������� ����, �.
        */
        cl_float depth;

        /**
        * ����������.
        * ����������� � ���� % / 100 ������������ ���. ���������.
        * ����� ���� ��������� = 1.0.
        *//* - ��������. ��. ����.
        typedef struct {
            numberLayer_t O;
            numberLayer_t Si;
            numberLayer_t Al;
            numberLayer_t Fe;
            numberLayer_t Ca;
            numberLayer_t Na;
            numberLayer_t K;
            numberLayer_t Mg;
            numberLayer_t H;
            numberLayer_t sparse;
        } content_t;
        */

        typedef chemicalSubstance_t content_t[ CRUST_GRID * CRUST_GRID * CRUST_GRID ];
        content_t content;


        /**
        * �����������.
        */
        typedef struct {
            /**
            * ������������ ������� � ������ �� ����������� �������.
            */
            cl_float depth;
            cl_float height;

            /**
            * �������� �����������.
            * ������� ����������� ���������� ��������� (������ - �������),
            * ������������ �����������, �� ������� �������� ���� ������� �
            * ���-��� ��������� � ������� 27x27x27 �����.
            */
            typedef struct {
                cl_float drop;
                cl_float distance;
            } jamb_t;
            jamb_t jamb;

        } structSurface_t;

        typedef structSurface_t surface_t[ SURFACE_CRUST_GRID * SURFACE_CRUST_GRID * SURFACE_CRUST_GRID ];
        surface_t surface;

    } crust_t;



    /**
    * ��������� ���� ����� �� ������� (���������, ��������).
    *
    * # ���� ��������� ��������:
    *     0    �������� ������, ������.
    *     1    ����, ������.
    *     2    ��������.
    *     3    �������.
    *     4    ̸����� ����� - ����, �������.
    *     5    ����������� �����.
    */
    static const size_t LIFE_CYCLE = 6;


    /**
    * ������ ����� ������� �������� ����� ���������� � ������� �������.
    */
    static const size_t LIVING_GRID = SX / 3;


    /**
    * ����������� ��������� ���-�� *���������* ������ � ������� �������.
    */
    static const size_t SPECIMEN_COUNT = 100;


    /**
    * ������������ ���� �������� ������ ������ ����.
    */
    typedef struct {
        /**
        * ��������� �� ����������.
        */
        static const size_t UNDEFINED = (0);

        /**
        * ������ ��������.
        * ��������: �����.
        */
        static const size_t SOLID = (1 << 1);

        /**
        * ������ ��������.
        * ��������: ����.
        */
        static const size_t LIQUID = (1 << 2);

        /**
        * ������������ ��������.
        * ��������: ������.
        */
        static const size_t GAS = (1 << 3);

        /**
        * ������.
        */
        static const size_t PLASM = (1 << 4);

        // @todo �������, ������, �����, ������������, ... - ��� �����������.

    } Environment;


    /**
    * ����� ��� (��������, �������� � ��.; ����� - �����).
    * ���-�� ������ �� ������� ��������; ������� ������� ����������� �� �����
    * 27�27�27 � ������ ���������� ������ ��������� ������� �������� �����
    * ������; �.�. *������* ������ ������ ���� �������������� 19683 �������
    * ��������.
    */
    typedef struct {
        /**
        * ����� ��� ����� �������� ������.
        *//* - ���. ��������� ������ ���� ������� � OpenCL. ��������. ��. ����.
        typedef std::array< float, 20 >  age_t;
        */


        /**
        * ���������� �������� � ������� ������.
        * ������ ����� �������� ���������� � ���-�� ������ � ������������
        * �� �������. ���-�� ������ ��������� �� ����� ������ � ������.
        */
        typedef struct {
            cl_float healthy[ LIFE_CYCLE ];
            cl_float sick[ LIFE_CYCLE ];
        } count_t;

        /**
        * ��������� ��� ������ � ���-��� ������ � ������� ������� �� �������.
        */
        typedef count_t group_t[ SPECIMEN_COUNT ];
        typedef group_t content_t[ LIVING_GRID * LIVING_GRID * LIVING_GRID ];
        content_t content;


        /**
        * ���������� �� �����.
        */
        typedef struct {
            /**
            * ������� ����� ����� ������ ����� � ������� (�������� -> ������).
            * ��� ����������� � ������ ������ �� ����� ������.
            */
            cl_float lifetime;

            /**
            * ����� ����� (����, �����, �������, ������, ���� � �.�.) ��������
            * ���������� ����� "countByAge", ��.
            */
            cl_float mass[ LIFE_CYCLE ];


            /**
            * ������������ ���-�� *������* ���. �����������, �� ������� �����
            * �������� �����.
            */
            static const size_t CHEMICAL_COMPOSITION = 5;

            /**
            * ������������ ���-�� *������* ���. �����������, ������� �����
            * ����� ��� ����������� �����.
            */
            static const size_t CHEMICAL_NEED = 5;

            /**
            * ������������ ���-�� *������* ���. �����������, ������� ��������
            * ����� ��� �����������������.
            */
            static const size_t CHEMICAL_WASTE = 5;

            /**
            * ������������ ���-�� *������* ����� �������, ������� ����������
            * ����� ��� ����������� �����.
            * ��������: ��������� ����, ����� �� ���. �����, ������������� ���.
            */
            static const size_t ENERGY_NEED = 2;

            /**
            * ������������ ���-�� *������* ����� �������, ������ ��������
            * ����� ��� �����������������.
            * ��������: ����, �����, ������������� ���, ��������.
            */
            static const size_t ENERGY_WASTE = 2;

            /**
            * ���. ������ �����.
            * �������� ���� (�� ����� ����� �����), ����� = 1.0.
            * ��������: ����� (����), ����, �������� (������).
            */
            typedef cl_float chemicalComposition_t[ CHEMICAL_COMPOSITION ];
            chemicalComposition_t chemicalComposition;


            /**
            * ���������� ����� (����, �������������� ����������� ������
            * � �.�.) �������� ���������� ����� "countByAge".
            *
            * @see ���������� > http://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%B0%D0%B1%D0%BE%D0%BB%D0%B8%D0%B7%D0%BC
            */
            typedef struct {
                typedef struct {
                    /**
                    * ����������� � ���. �����������.
                    * ��������: �����, ����, ��������, ��������, ��������.
                    */
                    cl_float need[ CHEMICAL_NEED ];

                    /**
                    * �������� ����������������� ����� (���. ����������).
                    * ��������: ���, ����, ���, ���������� ���, ��������.
                    */
                    cl_float waste[ CHEMICAL_WASTE ];

                } chemical_t;

                chemical_t chemical;

                typedef struct {
                    /**
                    * �������, ����������� ����� ��� ����������� �����, ��
                    * ����������� �������, ���������� �� ����������� ����
                    * (���. �����������). ������ ������� ����� ����������
                    * ������ � ���� ����� (��. ����).
                    * ��/�����
                    *
                    * ��������: ��������� ����, ����� �����. �����.
                    */
                    cl_float need[ ENERGY_NEED ];

                    /**
                    * �������, ���������� ������ � �������� �����
                    * �����������������.
                    * ��/�����
                    *
                    * ��������: ����, �����, ������������� ���.
                    */
                    cl_float waste[ ENERGY_WASTE ];

                } energy_t;

                energy_t energy;

            } metabolism_t;

            metabolism_t metabolism[ LIFE_CYCLE ];


            /**
            * ������� ��������� ������ �����.
            */
            typedef struct {
                /**
                * ������������ ���������� ����, ��� ����� ������� �����.
                */
                static const size_t ENVIRONMENT_SURVIVOR = 5;

                /**
                * � ����� ������ ����� ���� �����.
                *   # ����� �������� �������� ����������� ��� �� Environment.
                *   # � ����� ������ ������ ����� *�����������* ��������.
                *
                * ��������, ���� ����� ����� ���� �� ������� ������������ �
                * ������ ����, �����:
                *   topology_t::Environment::GAS | topology_t::Environment::SOLID
                */
                size_t environment[ ENVIRONMENT_SURVIVOR ];

                /**
                * �������� ���������� � ������� �������� ���� ����� ��������
                * ���������� ����� "countByAge".
                */
                typedef struct {
                    /**
                    * ����������� ��������.
                    * ��� ����� ��������� - ���������� ���������� � ����������
                    * ����������� ������.
                    * ��� �������������� ������ �������� ����� ������������� �����
                    * ������ ��������� ������������� �. �. ����� / ���� / ������.
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } comfort_t;
                    comfort_t comfort;

                    /**
                    * ����������� ���������.
                    * ������������� ����� ��� ����� ������� ����������
                    * (100% ��������� ����� �� 1 �����).
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } limit_t;
                    limit_t limit;

                } temperatureRange_t;

                temperatureRange_t temperatureRange[ LIFE_CYCLE ];

            } survivor_t;

            survivor_t survivor;

        } specimen_t;

        specimen_t specimen[ SPECIMEN_COUNT ];

    } living_t;




    /**
    * ������ ����� ����������� � ������� �������.
    */
    static const size_t COMPONENT_GRID = LIVING_GRID;


    /**
    * ����������� ��������� ���-�� *���������* ����������� � ������� �������.
    */
    static const size_t TYPE_COMPONENT_COUNT = 100;



    /**
    * ����������� ����������.
    * ���������� ����� ���� ������ � ����� �����, �� ����� �� ���������.
    *
    * ��������, ����� ����� ���������� (1) �������� � �������� (2) ����������
    * ���. �� ������� ��������� ��� 2 ��������� ����������.
    * ��������, ����� (�������� ��� ��������) ����� ��������� � ������������
    * ���������� (1) ����������� �����.
    */
    typedef struct {
        /**
        * ��������� ��� ������ � ���-��� ����������� � ������� �������
        * �� �������.
        */
        typedef cl_float group_t[ TYPE_COMPONENT_COUNT ];
        typedef group_t content_t[ COMPONENT_GRID * COMPONENT_GRID * COMPONENT_GRID ];
        content_t content;


        /**
        * ���������� � ����������.
        */
        typedef struct {
            /**
            * ����� ����������, ��.
            */
            cl_float mass;


            /**
            * ������������ ���-�� *������* �����������, �� ������� �����
            * �������� ���� ���������.
            */
            static const size_t COMPONENT_COMPOSITION = 5;

            /**
            * ������ ����������.
            * ����� ���� ������ (��� �������� UID == 0).
            * ������������ UID ����������� � �� �������� ���� � ���� ����������.
            * ��������: ����� = 0.2, ���� = 0.1, �������� = 0.7.
            */
            typedef struct {
                cl_uchar uid;
                cl_float count;
            } portion_t;
            typedef portion_t �omposition_t[ COMPONENT_COMPOSITION ];
            �omposition_t �omposition;


            /**
            * ������� ���������� ������� ���������� ���������.
            * ������ "������� ���������" ��� ����� �����.
            */
            typedef struct {
                /**
                * �������� ���������� � ������� �������� ��������� ���������.
                * ������ living_t::specimen_t::survivor_t::temperatureRange_t.
                */
                typedef struct {
                    /**
                    * ����������� ��������.
                    * ��� ����� ��������� - ���������� ���������� ����������.
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } comfort_t;
                    comfort_t comfort;

                    /**
                    * ����������� ��������.
                    * ������������� ���������� ���������� ��� ����� �������
                    * ���������� (100% ���������� �� 1 �����).
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } limit_t;
                    limit_t limit;

                } temperatureRange_t;

                temperatureRange_t temperatureRange;

            } survivor_t;

            survivor_t survivor;

        } type_t;

        type_t type[ TYPE_COMPONENT_COUNT ];

    } component_t;




    /**
    * ������ ����� ������������� ����������� � ������� �������.
    */
    static const size_t TEMPERATURE_GRID = SX / 3;


    /**
    * ����������� ������� �������.
    */
    typedef struct {
        typedef cl_float content_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
        content_t content;
    } temperature_t;




    /**
    * ������ ����� ������������� ������� � ������� �������.
    */
    static const size_t PRECIPITATIONS_GRID = SX / 3;


    /**
    * ���-�� ������� � ������� �������.
    */
    typedef struct {
        typedef cl_float content_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
        content_t content;
    } precipitations_t;




    Topology();


    virtual ~Topology();




    /**
    * @return ���������.
    */
    atmosphere_t atmosphere();



    /**
    * @return ���� �������.
    */
    crust_t crust();



    /**
    * @return ����� ���.
    */
    living_t living();



    /**
    * @return ����������.
    */
    component_t component();



    /**
    * @return �����������.
    */
    temperature_t temperature();



    /**
    * @return ������.
    */
    precipitations_t precipitations();






private:
    atmosphere_t mAtmosphere;
    crust_t mCrust;
    living_t mLiving;
    component_t mComponent;
    temperature_t mTemperature;
    precipitations_t mPrecipitations;

};



    } // planet
} // portulan








#include "Topology.inl"



#else
#pragma message( "Class portulan::planet::Topology not included in project: OpenCL disable" )

#endif
