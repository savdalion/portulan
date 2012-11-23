#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "biome.h"
#include "biome-set.h"
#include "landscape.h"


/**
* Утилиты для работы с биомами.
*
* @see biome.h
*/


// нужно для OpenCL
#ifndef __global
#define __global /*nothing*/
#endif


namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace planet {
                namespace l0 {
#endif




/**
* Биомы, наиболее близкие заданной местности (местность определяется
* температурой, осадками, ...), заполняют 'pb'.
*
* @param randomValue @todo Значение используется для выбора, когда обнаружено
*        несколько подходящих заданной местности биомов.
*
* #! Метод может не компилироваться в ядре OpenCL при большом BIOME_COUNT.
*/
// @todo fine OpenCL требует объявления этого метода в biome.hcl. Разобраться,
//       почему нельзя объявить только здесь и как 'inline'.
void likeBiome(
    __global biomeCell_t bc,
    const cl_float temperature,
    const cl_float rainfall,
    const cl_float drainage,
    __global const landscapeCell_t landscapeCell,
    const cl_uint randomValue
) {
    // @todo Протестировать.

    // просмотрим биомы, заданные в 'aboutBiome'
    // выберем наиболее подходящий биом

    // определим "степень соответствия" каждого биома из 'aboutBiome'
    // заданной местности
    // @see biome-set.h
    cl_float like[ BIOME_COUNT ] = {};
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
#if 1
        //__constant aboutOneBiome_t* ab = aboutBiome[ i ];
        // набор не обязательно содержит именно BIOME_COUNT биомов
        // @see Завершение заполнения biome-set.h / aboutBiome
        if (aboutBiome[ i ]->temperature.min == INFINITYf) {
            break;
        }

        // температура
        {
            const cl_float average = (
                aboutBiome[ i ]->temperature.min +
                aboutBiome[ i ]->temperature.max
            ) / 2.0f;
            // учитываем важность характеристики
            const cl_float delta = average * ( cl_float )( CRITERIA_D );
            if ( (temperature >= aboutBiome[ i ]->temperature.min)
              && (temperature <= aboutBiome[ i ]->temperature.max)
            ) {
                like[ i ] += delta;
            } else {
                like[ i ] -= delta;
            }
        }

        // атм. осадки
        {
            const cl_float average = (
                aboutBiome[ i ]->rainfall.min +
                aboutBiome[ i ]->rainfall.max
            ) / 2.0f;
            const cl_float delta = average * ( cl_float )( CRITERIA_C );
            if ( (rainfall >= aboutBiome[ i ]->rainfall.min)
              && (rainfall <= aboutBiome[ i ]->rainfall.max)
            ) {
                like[ i ] += delta;
            } else {
                like[ i ] -= delta;
            }
        }

        // дренаж
        {
            const cl_float average = (
                aboutBiome[ i ]->drainage.min +
                aboutBiome[ i ]->drainage.max
            ) / 2.0f;
            const cl_float delta = average * ( cl_float )( CRITERIA_C );
            if ( (drainage >= aboutBiome[ i ]->drainage.min)
              && (drainage <= aboutBiome[ i ]->drainage.max)
            ) {
                like[ i ] += delta;
            } else {
                like[ i ] -= delta;
            }
        }

        // ландшафт
        {
            // просматриваем возможные для этого биома ландшафты
            // считаем подходящие и нет ландшафты для биома
            cl_uint yes = 0;
            cl_uint no = 0;
            for (cl_uint l = 0; l < LANDSCAPE_BIOME_COUNT; ++l) {
                const enum CODE_ELEMENT_LANDSCAPE thisLanscape = 
                    aboutBiome[ i ]->landscape[ l ].code;
                if (thisLanscape == CEL_NONE) {
                    // список ландшафтов для этого биома завершён
                    break;
                }
                // сравниваем с ландшафтами заданной местности
                for (cl_uint e = 0; e < LANDSCAPE_CELL; ++e) {
                    if (thisLanscape == landscapeCell[ e ].code) {
                        ++yes;
                        // ландшафты повторяются с разными модификациями (см.
                        // инициализацию в landscape.hcl) - продолжаем поиск
                    } else {
                        ++no;
                    }
                }

            } // for (cl_uint l = 0; l < LANDSCAPE_BIOME_COUNT; ++l)

            // ландшафт найден?
            const bool present = (yes > 0);
            if ( present ) {
                const cl_float delta =
                    ( cl_float )( yes ) *
                    ( cl_float )( CRITERIA_B ) /
                    ( cl_float )( no );
                like[ i ] += delta;
            } else {
                // отсутствие ландшафта уменьшает "подходящесть"
                // биома заданной местности
                like[ i ] /= 2.0f;
            }
        }
#endif
    } // for (cl_uint i = 1; i < BIOME_COUNT; ++i)


    // выберем биом с наибольшей степенью соответствия 'aboutBiome'
    enum CODE_BIOME code = CB_NONE;
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
        if (like[ i ] > like[ code ]) {
            code = ( enum CODE_BIOME )( i );
        }
    }

    // возможно, что заданная местность не подходит ни одному биому...
    // ...этот случай фильтруется ниже

    // оставим значения 'like' для биомов, которые близки к выбранному биому
    const cl_float selectedLike = like[ code ];
    cl_uint nearCount = 0;
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
        if ( (like[ i ] < selectedLike * 0.9f)
          || (like[ i ] > selectedLike * 1.1f)
        ) {
            like[ i ] = 0.0f;
        } else {
            ++nearCount;
        }
    }

    // заполняем подходящие биомы
    cl_uint k = 0;
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
        if (like[ i ] != 0.0f) {
            bc[ k ].code = ( enum CODE_BIOME )( i );
            ++k;
            if (k >= BIOME_CELL) {
                // @todo fine extend Могут пропасть биомы, идущие в конце
                //       списка 'aboutBiome'. Регулировать это передаваемым
                //       в параметрах случ. числом 'randomValue'.
                break;
            }
        }
    }

    // дозаполняем пустотой
    for ( ; k < BIOME_CELL; ++k) {
        bc[ k ].code  = CB_NONE;
    }

}




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
