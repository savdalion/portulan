#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "illuminance.h"


/**
* ������� ��� ������ � ����������.
*
* @see illuminance.h
*/


// # ��-�� ����, ��� ������� ���������� ��������� �� 'portulan', ����� ��
//   ������� � ������������ ��� ���������, � �� ������.
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif



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
void starIlluminancePlanet(
    __global sourceIlluminance_t*  u,
    const cl_int ix, const cl_int iy, const cl_int iz,
    // �������
    const cl_float  radius,
    const cl_float  coord[ 3 ],
    const cl_float  omega[ 3 ],
    // ������
    const __global aboutIlluminanceStar_t*  ais
) {
    // # ����� ��������� ��������� � ������� �����������, ������������
    //   �������� � ������ � ���-��� ����� = 1.

    const cl_float di =
        sqrt( ( cl_float )( ix * ix + iy * iy + iz * iz ) );
#if 1
    // �������� ������, �� ������������� �������
    {
        const cl_float IG_SCALE =
            2.0f * radius / ( cl_float )( ILLUMINANCE_GRID );
        if ((IG_SCALE * di) > (radius * 1.1f)) {
            return;
        }
    }
#endif

    // # ������� - ���; ���� ������ �� �������, ��������� � ������.

    // ������, ������������ �� ������ � ������ �������
    const cl_float spx = coord[ 0 ] - ais->coord[ 0 ];
    const cl_float spy = coord[ 1 ] - ais->coord[ 1 ];
    const cl_float spz = coord[ 2 ] - ais->coord[ 2 ];
    const cl_float distanceSquare = spx * spx + spy * spy + spz * spz;
    const cl_float distance = sqrt( distanceSquare );

    // ������, ������������ �� ������ ������� � ������, ��� �������
    // ������� ������������ = (ix, iy, iz)
    // ���������, ��� ������� ����� ���� ��������� ������������ XYZ
    const cl_float o[ 3 ] = {
        omega[ 0 ] * 3.1416f / 180.0f,
        omega[ 1 ] * 3.1416f / 180.0f,
        omega[ 2 ] * 3.1416f / 180.0f
    };
    // @todo �����������, ������ �������������� ������, ��� ����������.
    const cl_float a = asin( -spx / distance ) + o[ 0 ];
    const cl_float b = asin( -spy / distance ) + o[ 1 ];
    const cl_float c = asin( -spz / distance ) + o[ 2 ];
    /* - @test
    const cl_float a = o[ 0 ];
    const cl_float b = o[ 1 ];
    const cl_float c = o[ 2 ];
    */
    // ���������� ������� ��������
    cl_float px = ( cl_float )( ix );
    cl_float py = ( cl_float )( iy );
    cl_float pz = ( cl_float )( iz );
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
        // # ������ �������� ����� ������� �������� ��� ������.
        return;
    }


    // ������� ������� ������� � ������
    // ������� ��� �������
    //const real_t arPlanet = atan( radius / distance );
    //const cl_float arStar   = atan( ais->radius / distance );

    // # ��������� ���� ������� �� ����� �� ������� ��������� ��������� �����.
    // @todo ������� ������ ������ ������ �� ���� ������� �����
    const cl_float angle = 0.0;
    
    const cl_float e = ais->luminousIntensity / distanceSquare * cos( angle );
    u[ 0 ].star += e;
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
