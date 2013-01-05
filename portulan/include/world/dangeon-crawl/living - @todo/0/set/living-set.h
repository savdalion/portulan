#pragma once

#include "living.h"
#include <typelib/typelib.h>


/**
* ������ ����� ���������� - ��������, �������� - ��� ������������� �������
* �� ������ ���� ���� Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {

namespace tc = typelib::constant::physics;



/**
* ������������ ������ ���������, ���. �����������, ���������.
* �������� ����� ������������ ������ ��� UID ����� ���������.
*/
enum CODE_LIVING {
    // �� �������� ��� �� ������������
    CL_NONE,
    CL_EMPTY= CL_NONE,

    // �����
    CL_BONE,

    // �����
    CL_BLOOD,

    // ���������� �����
    CL_BLOOD_VESSEL,

    // �����
    CL_LYMPH,

    // ������������� �����
    CL_LYMPHATIC_VESSEL,

    // ���� (������������� �����)
    CL_SKIN,

    // ����� (�������� �����)
    CL_MUSCLE,

    // ���� (������� �����)
    CL_NERVOUS,

    // @todo ������ ���� �������������� �����
    // ������
    // ���������
    // ����
    // ������

    // ��������
    CL_OXYGEN,

    // ���������� ���
    CL_CO2,

    // ����
    CL_NITROGEN,

    // ������
    // = ���� + �������� + ���������� ���
    CL_AIR,


    // ����
    CL_LIGHT,

    // �����
    CL_HEAT,


    // ���������
    CL_last
};





static const aboutLiving_t aboutLiving[ LIVING_COUNT ] = {
/**
* ������ �����.
* ������������ ��� ������������ �������� ������ �� CODE_LIVING.
*/
#if 1
{
},
#endif




/**
* ����� �������������.
* @base ����� ��������.
* @source http://xumuk.ru/biologhim/257.html
* @source http://potomy.ru/human/800.html
* @source �����������, �������������� > http://medicinskaya-biofizika.ru/teploemkost-krovi
*/
#if 1
{
    // uid
    CL_BLOOD,

    // �������
    // fasten / store
    {
        // whose, how %
        { CL_H2O,     0.75 },
        { CL_OXYGEN,  0.20 },
        { CL_CO2,     0.05 },
        { CL_HEAT },
    },

    // transfer
    // # ������� ����� ����������� ������� �� ����������� ������������
    //   ����� �����������.
    {
        // whose
        { CL_H2O, CL_OXYGEN, CL_CO2, CL_HEAT },
        // power
        1.0
    },

    // �� ���� �������

},
#endif




/**
* �����.
* @base ����� ��������.
* @source http://xumuk.ru/biologhim/257.html
* @source http://potomy.ru/human/800.html
* @source �����������, �������������� > http://medicinskaya-biofizika.ru/teploemkost-krovi
*/
#if 1
{
    // uid
    CL_BLOOD,

    // �������

    // fasten / store
    {
        // whose, how %
        { CL_H2O,     0.75 },
        { CL_OXYGEN,  0.20 },
        { CL_CO2,     0.05 },
        { CL_HEAT },
    },

    // transfer
    // # ������� ����� ����������� ������� �� ����������� ������������
    //   ����� �����������.
    {
        // whose
        { CL_H2O, CL_OXYGEN, CL_CO2, CL_HEAT },
        // power
        1.0
    },

    // �� ���� �������

},
#endif




/**
* ������� �������.
*
* @prototype http://crawl.chaosforge.org/index.php?title=Worker_ant
*
* @see http://koti.welho.com/jarmoki/crawl/crawl_ss_monsters_by_name.html#MONS_WORKER_ANT
*/
#if 1

// ������� �������
#if 1
{
    // uid
    CL_WORKER_ANT,

    // �� ���� �������, ��������� �����
    // # ������������� �����, ����������� ������������ ��. �����.
    // # ������������ - ������ ������, ��������� XY.
    {
        // ������
        { CL_HEAD_WORKER_ANT,   D_NONE, D_NORTH },
        // ����� (������� ����� ����)
        { CL_BREAST_WORKER_ANT, D_NONE, D_NONE  },
        // ������ (������ ����� ����)
        { CL_BELLY_WORKER_ANT,  D_NONE, D_SOUTH },
    },

    // �������
    // fasten / store
    {},
    // transfer
    {},
},
#endif

// ������ �������� �������
#if 1
{
    // uid
    CL_HEAD_WORKER_ANT,

    // �� ���� �������, ��������� �����
    // # ������������: �������� ��������� ������� (��. ����).
    {
        // ������ ����
        { CL_EYE_WORKER_ANT,      D_EAST, D_NONE },
        // ����� ����
        { CL_EYE_WORKER_ANT,      D_WEST, D_NONE },
        // ������ ����
        { CL_FEELER_WORKER_ANT,   D_EAST, D_NORTH },
        // ����� ����
        { CL_FEELER_WORKER_ANT,   D_WEST, D_NORTH },
        // �����
        { CL_MANDIBLE_WORKER_ANT, D_NONE, D_NORTH },
        // ����
        { CL_BRAIN_WORKER_ANT,    D_NONE, D_SOURTH },
    },

    // �������
    // fasten / store
    {},
    // transfer
    {},
},
#endif

// ���� �������� �������
#if 1
{
    // uid
    CL_HEAD_WORKER_ANT,

    // �� ���� �������, ��������� �����
    {},

    // �������, function_t
    {
        // storeComponent
        // whose, how
        {
            { CL_BLOOD, 0.2 },
        },

        // storePart
        {},

        // storeLocationInfo
        // �������� ������� ���� � ���������:
        // # ����� �������� �������� ������ ������ �� ����� ������������
        //   ���������� �� ��������� � ����: �����, ���������� ����� � �.�..
        { F_STORE_LOCATION_INFO, 10 },

        // storeLikeInfo
        { F_STORE_LIKE_INFO, 50 }

        // storePresenceInfo
        {},

        // storeSmellInfo
        // # ����� ������� ������, �� �� ������� �����, ��� �� ������.
        { F_STORE_SMELL_INFO, 20 },

        // storeSoundInfo
        {},

        // storeTactilInfo
        {},

        // storeTasteInfo
        {},

        // storeVisionInfo
        {},

        // transferComponent
        {},

        // transferPart
        {},
    }
},
#endif

#endif




/**
* ���������� �����.
* �����������.
* ������������ �� �������� � � �����.
*
* @prototype http://dfwk.ru/Grama
* @prototype http://ru.wikipedia.org/wiki/%D0%9E%D0%B2%D1%81%D1%8F%D0%BD%D0%B8%D1%86%D0%B0_%D0%BB%D1%83%D0%B3%D0%BE%D0%B2%D0%B0%D1%8F
*
* @see ����������� �������� > http://big-fermer.ru/zelenyi-korm
* @see ������������� ����� > http://furazh.ru/dictoth/?data=18453
* @see ����� ����� > http://prasemena.ru/blog/skolko_semian_v_odnom_gramme
* @see ������� �������� > http://floragrow.ru/blog/pischa/13.html
*/
#if 1
{
},
#endif

};


                } // physics
            } // living
        } // dungeoncrawl
    } // world
} // portulan
