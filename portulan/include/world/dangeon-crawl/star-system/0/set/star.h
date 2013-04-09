#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "../../../../../portulan/Element.h"


/**
* Информация о звёздах в звёздной системе.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* Информация о звезде в звёздной системе.
*
* # Хранить будем по координатам: сетка MapContent3D - слишком накладно.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Идентификатор звезды.
    */
    uid_t uid;

    /**
    * Звезда взаимодействует с другими элементами звёздной системы.
    */
    bool live;

    /**
    * Масса звезды, кг.
    */
    real_t mass;

    /**
    * Радиус звезды, м.
    */
    real_t radius;

    /**
    * Температура ядра звезды, К.
    */
    real_t kernelTemperature;

    /**
    * Температура поверхности звезды, К.
    * Введена для расчёта светимости.
    * #! Не путать с температурой короны звезды.
    */
    real_t surfaceTemperature;

    /**
    * Координаты звезды в звёздной системе, XYZ, м.
    */
    real3_t coord;

    /**
    * Наклон звезды по XYZ.
    */
    real3_t rotation;

    /**
    * Скорость движения звезды в звёздной системе, XYZ, м/с.
    */
    real3_t velocity;

    /**
    * Светимость звезды.
    */
    real_t luminosity;

} characteristicStar_t;




/**
* Состояние звезды на данном пульсе.
*/
typedef characteristicStar_t  todayStar_t;




/**
* События, выпущенные звездой за 1 пульс.
*
* # Хранятся отдельно от звезды, чтобы можно было гибче оптимизировать
*   обработку на OpenCL.
*/
typedef eventTwo_t  emitterEventStar_t[ EMIT_EVENT_STAR_COUNT ];








#ifndef PORTULAN_AS_OPEN_CL_STRUCT

/**
* Класс для работы со звёздами.
*
* # Отсутствующий в содержании элемент - сигнал конца списка.
*/
class Star :
    public Element
{
public:
    typedef std::unique_ptr< todayStar_t >         todayContent_t;
    typedef std::unique_ptr< emitterEventStar_t >  emitterEventContent_t;




public:
    inline Star() {
        mToday = createContent< characteristicStar_t, STAR_COUNT >();
        mEmitterEvent = createContent< eventTwo_t,    STAR_COUNT >();
    }




    inline characteristicStar_t* today() const {
        return mToday.get();
    }


    inline characteristicStar_t* today() {
        return mToday.get();
    }




    inline eventTwo_t* emitterEvent() const {
        return mEmitterEvent.get();
    }


    inline eventTwo_t* emitterEvent() {
        return mEmitterEvent.get();
    }




private:
    todayContent_t         mToday;
    emitterEventContent_t  mEmitterEvent;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
