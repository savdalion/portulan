#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� �� ���������� � ������� �������.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ������ ��������� � �������� � ������� �������.
*
* @see #���������� � 'event_t'.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������ ("�����" - ��. ���� 'SpaceChem') ��� ������ �������� �������.
    * [0; *_EVENT_COUNT - 1]
    *
    * # ��������� ���� �������������, ����� �������� ������ � ���.
    */
    cl_int   waldo;

    event_t  content[ ASTEROID_EVENT_COUNT ];
    
} asteroidMemoryEvent_t;




/**
* ���������� �� ��������� � ������� �������.
* ������� ����� �� �����������: ����� MapContent3D - ������� ��������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������������� ���������.
    */
    uid_t uid;

    /**
    * �������� ��������������� � ������� ���������� ������� �������.
    */
    bool live;

    /**
    * ����� ���������, ��.
    *
    * @see pns::massAsteroid()
    */
    mass_t mass;

    /**
    * ������� ��������� �� XYZ, �.
    */
    real_t size[ 3 ];

    /**
    * ���������� ��������� � ������� �������, XYZ, �.
    */
    real_t coord[ 3 ];

    /**
    * ������ ��������� �� XYZ.
    */
    real_t rotation[ 3 ];

    /**
    * ������ �������������� ���, ����������� �� ��������, �.
    * ����� ������ ����� �������.
    */
    real_t force[ 3 ];
    real_t absForce;

    /**
    * �������� �������� ��������� � ������� �������, XYZ, �/�.
    */
    real_t velocity[ 3 ];


    /**
    * ���������, �� / �3.
    */
    real_t density;


    /**
    * �����������, C.
    *
    * # ��������� � ��������, ����� ��������.
    * @todo optimize ����� ��������� ���������� �. � ��������.
    *
    * @copy ������ 'v3d', ���� struct.h.
    * @info ���������� ����������� ����� � ��������� ~ (0; 1.42e32) ���������.
    * @info ����������� ���������� ����� ~ 1 �.
    * @info ����������� ���������� �������� ~ 13 �.
    * @info ����������� ����������� ���� ~ 1 500 �.
    * @info ����������� �� ����������� ������ ~ 6 ���� �.
    * @info ����������� �� ����������� ������� � ~ 10 ���� �.
    * @info ����������� ��� ������� ����� ������ ~ 10 ���� �.
    * @info ����������� ��� ������� ���������� ������ ~ 10 ���� �.
    * @info ����������� ��� ������� ���������� ������ ~ 10 ���� �.
    * @info ����������� � ������ ������� ����� �������� ������ ~ 10 ���� �.
    * @info ����������� ������ ������� ������� � ������� �������� ���������� ~ 10 ��� (10^18) �.
    * @info ����������� ����� ������� � ���� �������� ��������� ~ 1 ���� (10^21) �.
    * @see more http://en.wikipedia.org/wiki/Orders_of_magnitude_%28temperature%29
    */
    real_t temperature;


    /**
    * �������������� �������.
    */
    real_t albedo;


    /**
    * ����������� ���������, �.
    */
    real_t meltingPoint;


    /**
    * ����������� �������, �.
    */
    real_t boilingPoint;


    /**
    * �������� �����������, �� / (�� * �).
    *
    * @see http://ru.wikipedia.org/wiki/%D0%A3%D0%B4%D0%B5%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D1%82%D0%B5%D0%BF%D0%BB%D0%BE%D1%91%D0%BC%D0%BA%D0%BE%D1%81%D1%82%D1%8C
    */
    real_t heatCapacity;


    /**
    * �������� ������� ���������, �� / ��.
    */
    real_t enthalpyFusion;


    /**
    * �������� ������� ��������� (���������������), �� / ��.
    */
    real_t enthalpyVaporization;


    /**
    * �������, ������� ��������� � ����������.
    *
    * @see #���������� � 'event_t'.
    */
    asteroidMemoryEvent_t memoryEvent;


    /**
    * ��������� ��������� �������� ��������, �/�.
    * ����� ������ ����� �������.
    */
    real_t deltaVelocity[ 3 ];
    real_t absDeltaVelocity;


    /**
    * ��������� ��������� ���������, �/�.
    * ����� ������ ����� �������.
    */
    real_t deltaCoord[ 3 ];
    real_t absDeltaCoord;

    /**
    * @see star.h
    */
    real_t tm[ 16 ];


    /**
    * �������� �����.
    */
    real_t test[ 5 ];

} aboutAsteroid_t;




/**
* ������������ ���� ���������� � ������� �������.
*
* # ���� ���� ����������� - ���������, ����� �� ������� ������� �������
*   � �.�. - ��� ����� = 0.
* # ������������� �������� - ������ ����� ������.
*/
typedef aboutAsteroid_t asteroidContent_t[ ASTEROID_COUNT ];




/**
* ��������� � ������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    asteroidContent_t content;
} asteroid_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
