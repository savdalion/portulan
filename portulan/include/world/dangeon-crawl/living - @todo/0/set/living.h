#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ������ ����� ���������� - ��������, �������� - �� ������ ����
* ���� Dungeon Crawl.
*
* # ����� ��������� ������� �� ������.
* # �� ��������� ����� �� ������, �����, ����� � �.�. - ����������� ���������,
*   ��������� ������������ � ���� ����� ������, ���. ���������� �
*   ���� �������, ������������ ����������.
* # �������� - ��� ������������ ������.
*
* @see http://crawl.chaosforge.org
* @see living::Topology
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace living {
                namespace physics {
#endif



typedef cl_int  uid_t;



/**
* �������, ����������� ������ ����.
*/
enum FUNCTION {
    // �� ������� ��� �� ����������
    F_NONE = 0,

    // ������ ��������� (������ �����������)
    // @example ���� ����� ����������� �������� ��� ���. ���. �������.
    // ����� ���������� ����������, ���������� �����.
    F_STORE_COMPONENT,

    // ������ ������ ����� (���������, ������ �����������)
    // @example ������ ����� �������� �����, ������� �������, �����, �����.
    // ���� ����������� � ��������.
    // �����, ���, ��� ��������� ������� ������.
    // �����������, ���� ����������� � ����.
    F_STORE_PART,

    // ������ ����������
    // ���������� � �������������� �������� ����
    F_STORE_LOCATION_INFO,
    // ���������� �� ��������� � ��������: �������� / ���
    F_STORE_LIKE_INFO,
    // ����� ����������� (������: ��� ��� Dungeon Crawl)
    F_STORE_PRESENCE_INFO,
    // ���������� � ������ (��������)
    F_STORE_SMELL_INFO,
    // ���������� � �����
    F_STORE_SOUND_INFO,
    // ���������� � ���������� �������� (��������)
    F_STORE_TACTIL_INFO,
    // ���������� � �����
    F_STORE_TASTE_INFO,
    // ���������� �� ������
    F_STORE_VISION_INFO,

    // ��������� ������ ����� ��� ��������� � ����� ���� ��� ������� �����
    // @example ����� ��������� ��������, �����. ���, �����, ����, ����.
    // ������� ������� ������� �������.
    // ˸���� ��������� ����� ����������.
    F_TRANSFER,

    // ���������� ��������� ��� ������ ����� �� ��. ���������� / �����
    // @see ���������� > http://ru.wikipedia.org/wiki/%D0%9A%D0%B0%D1%82%D0%B0%D0%B1%D0%BE%D0%BB%D0%B8%D0%B7%D0%BC
    // @example ������� �������������� ���� ��� ���������� (��������� �� �����,
    // ����, ��������, ������������).
    F_FISSION,
    F_CATABOLISM = F_FISSION,

    // �������� �� ����������� ��� ������ ������ ��. ���������� / �����
    // @see ��������� > http://ru.wikipedia.org/wiki/%D0%90%D0%BD%D0%B0%D0%B1%D0%BE%D0%BB%D0%B8%D0%B7%D0%BC
    // @example �������� ����������� �� ����� �������. ���. �� �����������
    // ���� � ����.
    // �������� ��������� ����������� ����� �� �����������.
    F_FUSSION,
    F_ANABOLISM = F_FUSSION,

    // ���������
    F_last
};



typedef struct {
    /**
    * ����� ��������� ����� �������.
    */
    uid_t   whose;

    /**
    * � ����� ����������.
    * # ���������� ����������� ��� ����� �� ������.
    */
    cl_float  how;

} contentWhoseHow_t;


typedef struct {
    contentWhoseHow_t  content[ 10 ];
} storeComponentFunction_t;


typedef struct {
    contentWhoseHow_t  content[ 10 ];
} storePartFunction_t;



typedef struct {
    /**
    * ������� ������ ���� ����� �������.
    */
    cl_uint   size;

} storeInfoFunction_t;




typedef struct {
    uid_t     whose[ 10 ];

    /**
    * �������� - ����������, ����� ����� 'whose' ����� ����� ����������.
    * @example ����� ��������� ���� ���� ������ ����� (�������� = 1.0).
    */
    cl_float  power;

} transferFunction_t;



typedef struct {
    storeComponentFunction_t  storeComponent;
    storePartFunction_t       storePart;

    storeInfoFunction_t  storeLocationInfo;
    storeInfoFunction_t  storeLikeInfo;
    storeInfoFunction_t  storePresenceInfo;
    storeInfoFunction_t  storeSmellInfo;
    storeInfoFunction_t  storeSoundInfo;
    storeInfoFunction_t  storeTactilInfo;
    storeInfoFunction_t  storeTasteInfo;
    storeInfoFunction_t  storeVisionInfo;

    transferFunction_t  transferComponent;
    transferFunction_t  transferPart;

} function_t;



/**
* ����� ���������.
*/
typedef struct {
    /**
    * ���������� ID �����.
    * # UID �����, ����� ����� ���� ���������� ���������� � ������.
    * # ������������� UID �����. enum CODE_ORGANISM.
    * # ������������� UID ������������ ��� ���������� ����� ������.
    */
    uid_t  uid;


    /**
    * ����� ����� ���������, ����� ������� �����������.
    *
    * @example ������ �� ����� �. ��� �����.
    * ���� �� ����� �. ��� �����.
    * ���� ����� ������� ��� ���������� ������ ��� ��������� �������.
    * �������� ����� ������� ��� ����������� �����.
    */


    /**
    * ����� ������� ���������.
    *
    * @example ������ ��������� ����� � ������ ����� ����.
    * ����� ��������� ��������.
    * ������� ������� ������� �������.
    */
    function_t function;

} part_t;




typedef part_t  organ_t;

typedef part_t  creature_t;







#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // planet
        } // dungeoncrawl
    } // world
} // portulan
#endif
