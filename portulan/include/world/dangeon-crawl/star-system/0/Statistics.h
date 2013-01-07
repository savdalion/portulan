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
* Собирает статистику для заданного элемента.
*
* @template N Количество пульсов, которые могут храниться в памяти.
*/
template< size_t N >
class Statistics {
public:
    /**
    * Тип для хранения номера пульса.
    */
    typedef long long  pulse_t;


    /**
    * Позволяет хранить одно значение для события с информацией о втором
    * участнике события.
    */
    typedef struct {
        real_t        value;
        uidElement_t  other;
    } oneValue_t;

    typedef struct {
        oneValue_t  asteroid;
        oneValue_t  planet;
        oneValue_t  star;
        // результирующее по всем 'onVelue_t' выше
        real_t  total;
    } oneValueTwoElement_t;


    /**
    * Структура для хранения статистики по одному пульсу.
    */
    typedef struct {
        /**
        * Пульс, для которого сделана запись.
        */
        pulse_t  pulse;

        /**
        * Элемент звёздной системы, для которого сделана запись.
        */
        uidElement_t  element;

        /**
        * Координата элемента.
        */
        typelib::CoordT< real_t >  coord;

        /**
        * Орбитальная скорость элемента.
        */
        real_t  velocity;

        /**
        * Минимальное расст. между этим элементом и другими в звёздной системе.
        */
        oneValueTwoElement_t  minDistance;

        /**
        * Максимальное расст. между этим элементом и другими в звёздной системе.
        */
        oneValueTwoElement_t  maxDistance;

    } dataOnePulse_t;


    /**
    * Структура для хранения статистики по N пульсам.
    */
    typedef std::array< dataOnePulse_t, N >  dataPulse_t;


    /**
    * Топология, оптимизированная для извлечения данных.
    */
    typedef struct {
        typelib::CoordT< real_t >   coord;
        typelib::VectorT< real_t >  velocity;
        real_t                      lVelocity;
    } element_t;

    typedef boost::unordered_map< uidElement_t, element_t >  preparedTopology_t;



public:
    /**
    * @param uide        Элемент, для которого собирается статистика.
    * @param skipPulse   Сколько пульсов пропускать без сбора данных.
    * @param prefixFile  Префикс файла, в котором статистика сохранится.
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
            && "Группа элемента портулана должна быть указана." );
        assert( (uide.uid != 0)
            && "Элемент портулана должен быть указан." );
        assert( topology
            && "Топология портулана должна быть указана." );

        // # Инициализируем нулями. Удобно для отладки.
        clear( &mDataPulse );
    }




    /**
    * @todo fine Сбрасывать данные в файл.
    *
    * @see flush()
    */
    inline ~Statistics() {
        /* - @todo Сбой при вызове vtkSmartPointer< vtkPolyData >::New() в flush().
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
    * Собирает данные о пульсе звёздной системы.
    * Если данные не помещаются в выделенную классом память (см. параметр
    * шаблона), вызывается flush().
    */
    void grabPulse( pulse_t );




    /**
    * Записывает собранные данные в файл.
    * Буфер 'mDataPulse' сбрасывается.
    * Если данных нет, никаких действий не происходит.
    */
    void flush();




    /**
    * @return Количество собранных, но не сохранённых данных.
    */
    inline size_t size() const {
        return std::distance(
            mDataPulse.cbegin(),
            static_cast< dataPulse_t::const_iterator >( mCurrentItr )
        ) ;
    }




    /**
    * @return Не сохранённых данных нет.
    */
    inline bool empty() const {
        return (mCurrentItr == mDataPulse.begin());
    }




protected:
    /**
    * Топология, оптимизированная для извлечения данных.
    */
    preparedTopology_t preparedTopology() const;



    /**
    * Метод для сбора / вычисления требуемых статистикой данных.
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
    * Записывает данные в формате VTK.
    *
    * @see http://vtk.org/doc/release/5.0/html/a02235.html
    */
    static void write( const std::string& file,  const vtkSmartPointer< vtkPolyData > );




private:
    /**
    * Элемент и топология, для которых собирается статистика.
    */
    const uidElement_t  mUIDElement;
    const Topology*     mTopology;

    /**
    * Количество пульсов, которые пропускаются (данные не собираются).
    */
    const size_t  mSkipPulse;
    size_t  mCountPulse;

    /**
    * Суффикс файла, в котором статистика сохранится.
    */
    const std::string  mPrefixFile;

    /**
    * Собранные данные.
    */
    dataPulse_t  mDataPulse;

    /**
    * Итератор на текущую свободную ячейку для записи данных.
    */
    typename dataPulse_t::iterator  mCurrentItr;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan







#include "Statistics.inl"
