#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "asteroid.h"
#include "planet.h"
#include "star.h"


/**
* ���������� � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ���������� � ���������� ����.
* ��������� ��� ������ ������� ��� �������� ���. ��������������.
*/
typedef struct __attribute__ ((packed)) {
    real_t mass;
    real_t coord[ 3 ];
    real_t rotation[ 3 ];
} aboutBody_t;




/**
* ���������� � ���. ����, ��� ������������ �����.
* ��������� ��� ������ ������� ��� �������� ���. ��������������.
*/
#ifdef PORTULAN_AS_OPEN_CL_STRUCT
typedef struct __attribute__ ((packed)) {
    real_t  coord[ 3 ];
    real_t  velocity[ 3 ];
    real_t  lengthVelocity;
} point_t;

#else
typedef struct __attribute__ ((packed)) {
    typelib::CoordT< real_t >   coord;
    typelib::VectorT< real_t >  velocity;
    real_t                      lengthVelocity;
} point_t;


#endif




/**
* ���������� �� ��������� ������������� ��������� � �� ����������
* � �������. ��������� ��� ������ �������.
* ��������� ��������� ��������� ��� ����������� ������� ����� "����"
* � "�����" (������).
*/
typedef struct __attribute__ ((packed)) {
    aboutAsteroid_t about;
    int count;
} deltaAsteroid_t;

typedef struct __attribute__ ((packed)) {
    aboutPlanet_t about;
    int count;
} deltaPlanet_t;

typedef struct __attribute__ ((packed)) {
    aboutStar_t about;
    int count;
} deltaStar_t;

typedef struct __attribute__ ((packed)) {
    deltaAsteroid_t asteroid;
    deltaPlanet_t   planet;
    deltaStar_t     star;
} deltaElement_t;




/**
* ��������� ��� ����� ���������� � ������� �������.
* ����� �������������� �������� ��� ����������� ��������.
*
* # ������� � �������� �������� � �������� �������� 2:
*     0 �������
*     1 ��������
*/
typedef struct __attribute__ ((packed)) {
    real_t  distance[ 2 ];
    real_t  velocity[ 2 ];

    /**
    * ��������� ����� ��������� ���� ���.
    */
    real_t  estimateTimeApproaching[ 2 ];

} statistics_t;








#ifndef PORTULAN_AS_OPEN_CL_STRUCT

/**
* ����� ��� ������ � ����� ����������� � ������� �������.
*/
class AboutStarSystem :
    public Element
{
public:
    inline AboutStarSystem( const real3_t& size ) : mSize( size ) {
    }




private:
    /**
    * ������������ ������� �������, XYZ, �.
    */
    const real3_t mSize;
};


                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
