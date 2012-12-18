#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "illuminance.h"


/**
* Утилиты для работы с освещением.
*
* @see illuminance.h
*/


// нужно для OpenCL
#ifndef __global
#define __global /*nothing*/
#endif


// # Из-за того, что утилиты используют структуры из 'portulan', лучше их
//   хранить в пространстве имён портулана, а не движка.
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif



/**
* Структуры для обмена инфо об освещённости.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Радиус звезды, м.
    */
    cl_float radius;

    /**
    * Средняя температура, К.
    */
    cl_float temperature;

    /**
    * Сила света, кд.
    *
    * @source http://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D0%BB%D0%B0_%D1%81%D0%B2%D0%B5%D1%82%D0%B0
    */
    cl_float luminousIntensity;

    /**
    * Координаты звезды в звёздной системе, XYZ, м.
    */
    cl_float coord[ 3 ];

} aboutIlluminanceStar_t;


typedef struct __attribute__ ((packed)) {
    aboutIlluminanceStar_t  star[ ILLUMINANCE_STAR_COUNT ];
    // @todo sattelite, planet
} aboutIlluminanceSource_t;


typedef struct {
    // результат освещения
    illuminanceContent_t  result;
    // тело, которое освещают
    cl_float  radius;
    cl_float  coord[ 3 ];
    cl_float  omega[ 3 ];
    // источники освещения
    aboutIlluminanceSource_t  source;
} illuminanceBody_t;





/**
* Освещённость в области планеты от одной звезды.
*
* @param u  Ячейка в области планеты, для которой считается свет от звезды.
*
*   # Ячейка карты освещённости обнулена (значения накапливаются).
*   # Учитываем радиус планеты.
*/
// @todo fine OpenCL требует объявления этого метода в biome.hcl. Разобраться,
//       почему нельзя объявить только здесь и как 'inline'.
void starIlluminance(
    __global illuminanceCell_t  u,
    const cl_int ix, const cl_int iy, const cl_int iz,
    // планета
    const cl_float  radius,
    const cl_float  coord[ 3 ],
    const cl_float  omega[ 3 ],
    // звезда
    const aboutIlluminanceStar_t&  ais
) {
    // # Чтобы сохранить похожесть с другими структурами, освещённость
    //   хранится в наборе с кол-вом ячеек = 1.

    const cl_float di =
        sqrt( static_cast< cl_float >( ix * ix + iy * iy + iz * iz ) );
#if 1
    // исключим ячейки, не принадлежащие планете
    // @todo optimize Наглядная картинка, но вся не используется плюс потеря
    //       производительности.
    {
        const cl_float SCALE =
            2.0f * radius / static_cast< cl_float >( ILLUMINANCE_GRID );
        if ((SCALE * di) > (radius * 1.1f)) {
            return;
        }
    }
#endif


    // # Планета - шар; свет падает на сторону, повёрнутую к звезде.

    // вектор, направленный от звезды к центру планеты
    const cl_float spx = coord[ 0 ] - ais.coord[ 0 ];
    const cl_float spy = coord[ 1 ] - ais.coord[ 1 ];
    const cl_float spz = coord[ 2 ] - ais.coord[ 2 ];
    const cl_float distanceSquare = spx * spx + spy * spy + spz * spz;
    const cl_float distance = sqrt( distanceSquare );

    // вектор, направленный от центра планеты к ячейке, для которой
    // считаем освещённость = (ix, iy, iz)
    // учитываем, что планета может быть развёрнута относительно XYZ
    const cl_float or[ 3 ] = {
        omega[ 0 ] * 3.1416f / 180.0f,
        omega[ 1 ] * 3.1416f / 180.0f,
        omega[ 2 ] * 3.1416f / 180.0f
    };
    // @todo Разобраться, почему поворачивается больше, чем необходимо.
    const cl_float a = asin( -spx / distance ) + or[ 0 ];
    const cl_float b = asin( -spy / distance ) + or[ 1 ];
    const cl_float c = asin( -spz / distance ) + or[ 2 ];
    /* - @test
    const cl_float a = or[ 0 ];
    const cl_float b = or[ 1 ];
    const cl_float c = or[ 2 ];
    */
    // используем матрицу поворота
    /* - Заменено. См. ниже.
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

    // смотрим положение векторов относительно друг друга
    const cl_float cross = spx * px + spy * py + spz * pz;
    if (cross > 0.0f) {
        // ячейка находится на неосвещённой стороне планеты
        return;
    }


    // угловые размеры планеты и звезды
    // считаем как радиусы
    //const real_t arPlanet = atan( radius / distance );
    //const cl_float arStar   = atan( ais.radius / distance );

    // # Учитываем угол падения на сферу со стороны точечного источника света.
    // @todo угловой размер звезды влияет на угол падения света
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
