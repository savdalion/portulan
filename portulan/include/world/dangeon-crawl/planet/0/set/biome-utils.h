#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "biome.h"
#include "biome-set.h"
#include "landscape.h"


/**
* ������� ��� ������ � �������.
*
* @see biome.h
*/


// ����� ��� OpenCL
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
* �����, �������� ������� �������� ��������� (��������� ������������
* ������������, ��������, ...), ��������� 'pb'.
*
* @param randomValue @todo �������� ������������ ��� ������, ����� ����������
*        ��������� ���������� �������� ��������� ������.
*
* #! ����� ����� �� ��������������� � ���� OpenCL ��� ������� BIOME_COUNT.
*/
// @todo fine OpenCL ������� ���������� ����� ������ � biome.hcl. �����������,
//       ������ ������ �������� ������ ����� � ��� 'inline'.
void likeBiome(
    __global biomeCell_t bc,
    const cl_float temperature,
    const cl_float rainfall,
    const cl_float drainage,
    __global const landscapeCell_t landscapeCell,
    const cl_uint randomValue
) {
    // @todo ��������������.

    // ���������� �����, �������� � 'aboutBiome'
    // ������� �������� ���������� ����

    // ��������� "������� ������������" ������� ����� �� 'aboutBiome'
    // �������� ���������
    // @see biome-set.h
    cl_float like[ BIOME_COUNT ] = {};
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
#if 1
        //__constant aboutOneBiome_t* ab = aboutBiome[ i ];
        // ����� �� ����������� �������� ������ BIOME_COUNT ������
        // @see ���������� ���������� biome-set.h / aboutBiome
        if (aboutBiome[ i ]->temperature.min == INFINITYf) {
            break;
        }

        // �����������
        {
            const cl_float average = (
                aboutBiome[ i ]->temperature.min +
                aboutBiome[ i ]->temperature.max
            ) / 2.0f;
            // ��������� �������� ��������������
            const cl_float delta = average * ( cl_float )( CRITERIA_D );
            if ( (temperature >= aboutBiome[ i ]->temperature.min)
              && (temperature <= aboutBiome[ i ]->temperature.max)
            ) {
                like[ i ] += delta;
            } else {
                like[ i ] -= delta;
            }
        }

        // ���. ������
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

        // ������
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

        // ��������
        {
            // ������������� ��������� ��� ����� ����� ���������
            // ������� ���������� � ��� ��������� ��� �����
            cl_uint yes = 0;
            cl_uint no = 0;
            for (cl_uint l = 0; l < LANDSCAPE_BIOME_COUNT; ++l) {
                const enum CODE_ELEMENT_LANDSCAPE thisLanscape = 
                    aboutBiome[ i ]->landscape[ l ].code;
                if (thisLanscape == CEL_NONE) {
                    // ������ ���������� ��� ����� ����� ��������
                    break;
                }
                // ���������� � ����������� �������� ���������
                for (cl_uint e = 0; e < LANDSCAPE_CELL; ++e) {
                    if (thisLanscape == landscapeCell[ e ].code) {
                        ++yes;
                        // ��������� ����������� � ������� ������������� (��.
                        // ������������� � landscape.hcl) - ���������� �����
                    } else {
                        ++no;
                    }
                }

            } // for (cl_uint l = 0; l < LANDSCAPE_BIOME_COUNT; ++l)

            // �������� ������?
            const bool present = (yes > 0);
            if ( present ) {
                const cl_float delta =
                    ( cl_float )( yes ) *
                    ( cl_float )( CRITERIA_B ) /
                    ( cl_float )( no );
                like[ i ] += delta;
            } else {
                // ���������� ��������� ��������� "������������"
                // ����� �������� ���������
                like[ i ] /= 2.0f;
            }
        }
#endif
    } // for (cl_uint i = 1; i < BIOME_COUNT; ++i)


    // ������� ���� � ���������� �������� ������������ 'aboutBiome'
    enum CODE_BIOME code = CB_NONE;
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
        if (like[ i ] > like[ code ]) {
            code = ( enum CODE_BIOME )( i );
        }
    }

    // ��������, ��� �������� ��������� �� �������� �� ������ �����...
    // ...���� ������ ����������� ����

    // ������� �������� 'like' ��� ������, ������� ������ � ���������� �����
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

    // ��������� ���������� �����
    cl_uint k = 0;
    for (cl_uint i = 1; i < BIOME_COUNT; ++i) {
        if (like[ i ] != 0.0f) {
            bc[ k ].code = ( enum CODE_BIOME )( i );
            ++k;
            if (k >= BIOME_CELL) {
                // @todo fine extend ����� �������� �����, ������ � �����
                //       ������ 'aboutBiome'. ������������ ��� ������������
                //       � ���������� ����. ������ 'randomValue'.
                break;
            }
        }
    }

    // ����������� ��������
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
