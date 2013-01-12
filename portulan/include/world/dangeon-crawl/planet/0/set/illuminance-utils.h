#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "illuminance.h"


/**
* ”тилиты дл€ работы с освещением.
*
* @see illuminance.h
*/


// # »з-за того, что утилиты используют структуры из 'portulan', лучше их
//   хранить в пространстве имЄн портулана, а не движка.
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif



/**
* ќсвещЄнность в области планеты от одной звезды.
*
* @param u  ячейка в области планеты, дл€ которой считаетс€ свет от звезды.
*
*   # ячейка карты освещЄнности обнулена (значени€ накапливаютс€).
*   # ”читываем радиус планеты.
*/
// @todo fine OpenCL требует объ€влени€ этого метода в biome.hcl. –азобратьс€,
//       почему нельз€ объ€вить только здесь и как 'inline'.
void starIlluminancePlanet(
    __global sourceIlluminance_t*  u,
    const cl_int ix, const cl_int iy, const cl_int iz,
    // планета
    const cl_float  radius,
    const cl_float  coord[ 3 ],
    const cl_float  omega[ 3 ],
    // звезда
    const __global aboutIlluminanceStar_t*  ais
) {
    // # „тобы сохранить похожесть с другими структурами, освещЄнность
    //   хранитс€ в наборе с кол-вом €чеек = 1.

    const cl_float di =
        sqrt( ( cl_float )( ix * ix + iy * iy + iz * iz ) );
#if 1
    // исключим €чейки, не принадлежащие планете
    {
        const cl_float IG_SCALE =
            2.0f * radius / ( cl_float )( ILLUMINANCE_GRID );
        if ((IG_SCALE * di) > (radius * 1.1f)) {
            return;
        }
    }
#endif

    // # ѕланета - шар; свет падает на сторону, повЄрнутую к звезде.

    // вектор, направленный от звезды к центру планеты
    const cl_float spx = coord[ 0 ] - ais->coord[ 0 ];
    const cl_float spy = coord[ 1 ] - ais->coord[ 1 ];
    const cl_float spz = coord[ 2 ] - ais->coord[ 2 ];
    const cl_float distanceSquare = spx * spx + spy * spy + spz * spz;
    const cl_float distance = sqrt( distanceSquare );

    // вектор, направленный от центра планеты к €чейке, дл€ которой
    // считаем освещЄнность = (ix, iy, iz)
    // учитываем, что планета может быть развЄрнута относительно XYZ
    const cl_float o[ 3 ] = {
        omega[ 0 ] * 3.1416f / 180.0f,
        omega[ 1 ] * 3.1416f / 180.0f,
        omega[ 2 ] * 3.1416f / 180.0f
    };
    // @todo –азобратьс€, почему поворачиваетс€ больше, чем необходимо.
    const cl_float a = asin( -spx / distance ) + o[ 0 ];
    const cl_float b = asin( -spy / distance ) + o[ 1 ];
    const cl_float c = asin( -spz / distance ) + o[ 2 ];
    /* - @test
    const cl_float a = o[ 0 ];
    const cl_float b = o[ 1 ];
    const cl_float c = o[ 2 ];
    */
    // используем матрицу поворота
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

    // смотрим положение векторов относительно друг друга
    const cl_float cross = spx * px + spy * py + spz * pz;
    if (cross > 0.0f) {
        // €чейка находитс€ на неосвещЄнной стороне планеты
        // # ячейка обнулена перед началом рассчЄта вне метода.
        return;
    }


    // угловые размеры планеты и звезды
    // считаем как радиусы
    //const real_t arPlanet = atan( radius / distance );
    //const cl_float arStar   = atan( ais->radius / distance );

    // # ”читываем угол падени€ на сферу со стороны точечного источника света.
    // @todo угловой размер звезды вли€ет на угол падени€ света
    const cl_float angle = 0.0;
    
    const cl_float e =
        ais->luminosity / distanceSquare * cos( angle );
    u[ 0 ].star += e;
}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
