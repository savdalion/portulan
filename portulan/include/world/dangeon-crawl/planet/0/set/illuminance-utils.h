#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "illuminance.h"


/**
* ������� ��� ������ � ����������.
*
* @see illuminance.h
*/


// ����� ��� OpenCL
#ifndef __global
#define __global /*nothing*/
#endif


// # ��-�� ����, ��� ������� ���������� ��������� �� 'portulan', ����� ��
//   ������� � ������������ ��� ���������, � �� ������.
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif



/**
* ��������� ��� ������ ���� �� ������������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������ ������, �.
    */
    cl_float radius;

    /**
    * ������� �����������, �.
    */
    cl_float temperature;

    /**
    * ���� �����, ��.
    *
    * @source http://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D0%BB%D0%B0_%D1%81%D0%B2%D0%B5%D1%82%D0%B0
    */
    cl_float luminousIntensity;

    /**
    * ���������� ������ � ������� �������, XYZ, �.
    */
    cl_float coord[ 3 ];

} aboutIlluminanceStar_t;


typedef struct __attribute__ ((packed)) {
    aboutIlluminanceStar_t  star[ ILLUMINANCE_STAR_COUNT ];
    // @todo sattelite, planet
} aboutIlluminanceSource_t;


typedef struct {
    // ��������� ���������
    illuminanceContent_t  result;
    // ����, ������� ��������
    cl_float  radius;
    cl_float  coord[ 3 ];
    cl_float  omega[ 3 ];
    // ��������� ���������
    aboutIlluminanceSource_t  source;
} illuminanceBody_t;





/**
* ������������ � ������� ������� �� ����� ������.
*
* @param u  ������ � ������� �������, ��� ������� ��������� ���� �� ������.
*
*   # ������ ����� ������������ �������� (�������� �������������).
*   # ��������� ������ �������.
*/
// @todo fine OpenCL ������� ���������� ����� ������ � biome.hcl. �����������,
//       ������ ������ �������� ������ ����� � ��� 'inline'.
void starIlluminance(
    __global illuminanceCell_t  u,
    const cl_int ix, const cl_int iy, const cl_int iz,
    // �������
    const cl_float  radius,
    const cl_float  coord[ 3 ],
    const cl_float  omega[ 3 ],
    // ������
    const aboutIlluminanceStar_t&  ais
) {
    // # ����� ��������� ��������� � ������� �����������, ������������
    //   �������� � ������ � ���-��� ����� = 1.

    const cl_float di =
        sqrt( static_cast< cl_float >( ix * ix + iy * iy + iz * iz ) );
#if 1
    // �������� ������, �� ������������� �������
    // @todo optimize ��������� ��������, �� ��� �� ������������ ���� ������
    //       ������������������.
    {
        const cl_float SCALE =
            2.0f * radius / static_cast< cl_float >( ILLUMINANCE_GRID );
        if ((SCALE * di) > (radius * 1.1f)) {
            return;
        }
    }
#endif


    // # ������� - ���; ���� ������ �� �������, ��������� � ������.

    // ������, ������������ �� ������ � ������ �������
    const cl_float spx = coord[ 0 ] - ais.coord[ 0 ];
    const cl_float spy = coord[ 1 ] - ais.coord[ 1 ];
    const cl_float spz = coord[ 2 ] - ais.coord[ 2 ];
    const cl_float distanceSquare = spx * spx + spy * spy + spz * spz;
    const cl_float distance = sqrt( distanceSquare );

    // ������, ������������ �� ������ ������� � ������, ��� �������
    // ������� ������������ = (ix, iy, iz)
    // ���������, ��� ������� ����� ���� ��������� ������������ XYZ
    const cl_float or[ 3 ] = {
        omega[ 0 ] * 3.1416f / 180.0f,
        omega[ 1 ] * 3.1416f / 180.0f,
        omega[ 2 ] * 3.1416f / 180.0f
    };
    // @todo �����������, ������ �������������� ������, ��� ����������.
    const cl_float a = asin( -spx / distance ) + or[ 0 ];
    const cl_float b = asin( -spy / distance ) + or[ 1 ];
    const cl_float c = asin( -spz / distance ) + or[ 2 ];
    /* - @test
    const cl_float a = or[ 0 ];
    const cl_float b = or[ 1 ];
    const cl_float c = or[ 2 ];
    */
    // ���������� ������� ��������
    /* - ��������. ��. ����.
    const cl_float px =
        ( cos( a ) * cos( c ) - sin( a ) * cos( b ) * sin( c ) ) * static_cast< cl_float >( ix ) +
        (-cos( a ) * sin( c ) - sin( a ) * cos( b ) * cos( c ) ) * static_cast< cl_float >( iy ) +
        ( sin( a ) * sin( b )                                  ) * static_cast< cl_float >( iz );
    const cl_float py =
        ( sin( a ) * cos( c ) + cos( a ) * cos( b ) * sin( c ) ) * static_cast< cl_float >( ix ) +
        (-sin( a ) * sin( c ) + cos( a ) * cos( b ) * cos( c ) ) * static_cast< cl_float >( iy ) +
        (-cos( a ) * sin( b )                                  ) * static_cast< cl_float >( iz );
    const cl_float pz =
        ( sin( b ) * sin( c ) ) * static_cast< cl_float >( ix ) +
        ( sin( b ) * cos( c ) ) * static_cast< cl_float >( iy ) +
        ( cos( b )            ) * static_cast< cl_float >( iz );
    */
    cl_float px = static_cast< cl_float >( ix );
    cl_float py = static_cast< cl_float >( iy );
    cl_float pz = static_cast< cl_float >( iz );
    // YZ
    py =  py * cos( a ) - pz * sin( a );
    pz =  py * sin( a ) + pz * cos( a );
    // XZ
    px =  px * cos( b ) + pz * sin( b );
    pz = -px * sin( b ) + pz * cos( b );
    // XY
    px = px * cos( c ) - py * sin( c );
    py = px * sin( c ) + py * cos( c );

    // ������� ��������� �������� ������������ ���� �����
    const cl_float cross = spx * px + spy * py + spz * pz;
    if (cross > 0.0f) {
        // ������ ��������� �� ������������ ������� �������
        return;
    }


    // ������� ������� ������� � ������
    // ������� ��� �������
    //const real_t arPlanet = atan( radius / distance );
    //const cl_float arStar   = atan( ais.radius / distance );

    // # ��������� ���� ������� �� ����� �� ������� ��������� ��������� �����.
    // @todo ������� ������ ������ ������ �� ���� ������� �����
    const cl_float angle = 0.0;
    
    const cl_float e = ais.luminousIntensity / distanceSquare * cos( angle );
    u[ 0 ].star += e;
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
