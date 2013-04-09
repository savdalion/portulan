#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "../../../../../portulan/Element.h"


/**
* ���������� � ������ � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ���������� � ������ � ������� �������.
*
* # ������� ����� �� �����������: ����� MapContent3D - ������� ��������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������� ������.
    */
    uid_t uid;

    /**
    * ������ ��������������� � ������� ���������� ������� �������.
    */
    bool live;

    /**
    * ����� ������, ��.
    */
    real_t mass;

    /**
    * ������ ������, �.
    */
    real_t radius;

    /**
    * ����������� ���� ������, �.
    */
    real_t kernelTemperature;

    /**
    * ����������� ����������� ������, �.
    * ������� ��� ������� ����������.
    * #! �� ������ � ������������ ������ ������.
    */
    real_t surfaceTemperature;

    /**
    * ���������� ������ � ������� �������, XYZ, �.
    */
    real3_t coord;

    /**
    * ������ ������ �� XYZ.
    */
    real3_t rotation;

    /**
    * �������� �������� ������ � ������� �������, XYZ, �/�.
    */
    real3_t velocity;

    /**
    * ���������� ������.
    */
    real_t luminosity;

} characteristicStar_t;




/**
* ��������� ������ �� ������ ������.
*/
typedef characteristicStar_t  todayStar_t;




/**
* �������, ���������� ������� �� 1 �����.
*
* # �������� �������� �� ������, ����� ����� ���� ����� ��������������
*   ��������� �� OpenCL.
*/
typedef eventTwo_t  emitterEventStar_t[ EMIT_EVENT_STAR_COUNT ];








#ifndef PORTULAN_AS_OPEN_CL_STRUCT

/**
* ����� ��� ������ �� �������.
*
* # ������������� � ���������� ������� - ������ ����� ������.
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
