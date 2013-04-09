#pragma once

#include "Topology.h"
#include "set/structure.h"
#include "set/utils.h"
#include <string>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkLongLongArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {


/**
* �������� ���������� ��� ��������� ��������.
*
* @template N ���������� �������, ������� ����� ��������� � ������.
*/
template< size_t N >
class Statistics {
public:
    /**
    * ��� ��� �������� ������ ������.
    */
    typedef long long  pulse_t;


    /**
    * ��������� ������� ���� �������� ��� ������� � ����������� � ������
    * ��������� �������.
    */
    typedef struct {
        real_t        value;
        uidElement_t  other;
    } oneValue_t;

    typedef struct {
        oneValue_t  asteroid;
        oneValue_t  planet;
        oneValue_t  star;
        // �������������� �� ���� 'onValue_t' ����
        real_t  total;
    } oneValueTwoElement_t;


    /**
    * ��������� ��� �������� ���������� �� ������ ������.
    */
    typedef struct {
        /**
        * �����, ��� �������� ������� ������.
        */
        pulse_t  pulse;

        /**
        * ������� ������� �������, ��� �������� ������� ������.
        */
        uidElement_t  element;

        /**
        * ���������� ��������.
        */
        typelib::CoordT< real_t >  coord;

        /**
        * ����������� �������� ��������.
        */
        real_t  velocity;

        /**
        * ����������� �����. ����� ���� ��������� � ������� � ������� �������.
        */
        oneValueTwoElement_t  minDistance;

        /**
        * ������������ �����. ����� ���� ��������� � ������� � ������� �������.
        */
        oneValueTwoElement_t  maxDistance;

    } dataOnePulse_t;


    /**
    * ��������� ��� �������� ���������� �� N �������.
    */
    typedef std::array< dataOnePulse_t, N >  dataPulse_t;


    /**
    * ���������, ���������������� ��� ���������� ������.
    */
    typedef struct {
        typelib::CoordT< real_t >   coord;
        typelib::VectorT< real_t >  velocity;
        real_t                      lVelocity;
    } element_t;

    typedef boost::unordered_map< uidElement_t, element_t >  preparedTopology_t;



public:
    /**
    * @param uide        �������, ��� �������� ���������� ����������.
    * @param skipPulse   ������� ������� ���������� ��� ����� ������.
    * @param prefixFile  ������� �����, � ������� ���������� ����������.
    */
    inline Statistics(
        const uidElement_t&  uide,
        const Topology*      topology,
        const size_t         skipPulse,
        const std::string&   prefixFile
    ) :
        mUIDElement( uide ),
        mTopology( topology ),
        mSkipPulse( skipPulse ),
        mCountPulse( 0 ),
        mPrefixFile( prefixFile ),
        mDataPulse(),
        mCurrentItr( mDataPulse.begin() )
    {
        assert( (uide.ge != GE_NONE)
            && "������ �������� ��������� ������ ���� �������." );
        assert( (uide.uid != 0)
            && "������� ��������� ������ ���� ������." );
        assert( topology
            && "��������� ��������� ������ ���� �������." );

        // # �������������� ������. ������ ��� �������.
        clear( &mDataPulse );
    }




    /**
    * @todo fine ���������� ������ � ����.
    *
    * @see flush()
    */
    inline ~Statistics() {
        /* - @todo ���� ��� ������ vtkSmartPointer< vtkPolyData >::New() � flush().
        flush();
        */
    }




    inline dataPulse_t const& dataPulse() const {
        return mDataPulse;
    }




    inline dataPulse_t& dataPulse() {
        return mDataPulse;
    }




    /**
    * �������� ������ � ������ ������� �������.
    * ���� ������ �� ���������� � ���������� ������� ������ (��. ��������
    * �������), ���������� flush().
    */
    void grabPulse( pulse_t );




    /**
    * ���������� ��������� ������ � ����.
    * ����� 'mDataPulse' ������������.
    * ���� ������ ���, ������� �������� �� ����������.
    */
    void flush();




    /**
    * @return ���������� ���������, �� �� ���������� ������.
    */
    inline size_t size() const {
        return std::distance(
            mDataPulse.cbegin(),
            static_cast< dataPulse_t::const_iterator >( mCurrentItr )
        ) ;
    }




    /**
    * @return �� ���������� ������ ���.
    */
    inline bool empty() const {
        return (mCurrentItr == mDataPulse.begin());
    }




protected:
    /**
    * ���������, ���������������� ��� ���������� ������.
    */
    preparedTopology_t preparedTopology() const;



    /**
    * ����� ��� ����� / ���������� ��������� ����������� ������.
    */
    void harvest(
        const preparedTopology_t&,
        typelib::CoordT< real_t >*,
        real_t*                velocity,
        oneValueTwoElement_t*  minDistance,
        oneValueTwoElement_t*  maxDistance
    ) const;




private:
    static inline void clear( dataPulse_t* dp ) {
        static const dataOnePulse_t ZERO = {};
        dp->fill( ZERO );
    }




    /**
    * ���������� ������ � ������� VTK.
    *
    * @see http://vtk.org/doc/release/5.0/html/a02235.html
    */
    static void write( const std::string& file,  const vtkSmartPointer< vtkPolyData > );




private:
    /**
    * ������� � ���������, ��� ������� ���������� ����������.
    */
    const uidElement_t  mUIDElement;
    const Topology*     mTopology;

    /**
    * ���������� �������, ������� ������������ (������ �� ����������).
    */
    const size_t  mSkipPulse;
    size_t  mCountPulse;

    /**
    * ������� �����, � ������� ���������� ����������.
    */
    const std::string  mPrefixFile;

    /**
    * ��������� ������.
    */
    dataPulse_t  mDataPulse;

    /**
    * �������� �� ������� ��������� ������ ��� ������ ������.
    */
    typename dataPulse_t::iterator  mCurrentItr;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan







#include "Statistics.inl"
