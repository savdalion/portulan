#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"
#include "component.h"


/**
* �������� (�������������� ��������) ��� ������������� �������
* �� ������ ���� ���� Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* �������� ������������.
* ������������ ����� ��������� (���)��������� �� ������
* GROUP_ELEMENT::GE_ELEMENT_LANDSCAPE.
*
* @todo ����� ������� > http://ru.wikipedia.org/wiki/%D0%A4%D0%BE%D1%80%D0%BC%D0%B0_%D1%80%D0%B5%D0%BB%D1%8C%D0%B5%D1%84%D0%B0
*/
enum CODE_ELEMENT_LANDSCAPE {
    // ����������� ��� �� ��������
    CEL_NONE = 0,

    // �����
    CEL_ANY = CEL_NONE,

    // �������, �����
    CEL_FLAT,

    // ����, ����
    // ����� �������������
    // �������� ������ �������
    CEL_MOUNTAIN,

    // ���������
    // ����� ����������
    CEL_BASIN,

    // ������
    CEL_RANGE,

    // �������, ������, ������, �����
    CEL_RAVINE,

    // �����, ����, ����, �����
    // ����������� ������ ����������� ����������
    CEL_LAKE,
    CEL_SEA   = CEL_LAKE,
    CEL_POND  = CEL_LAKE,
    CEL_OCEAN = CEL_LAKE,

    // ����
    // �������������� �� ���������� ������ ���������
    CEL_RIVER,

    // �������
    // �������� � ������ ������ ���������
    CEL_CASCADE,

    // ������
    // ����� ������ ����������� �� �����������, ����� �������
    // ����� ������������
    CEL_ROAD,

    // ������
    CEL_CAVE,

    // ���������
    CEL_last
};





/**
* ������ �����������, ����������� ���������� �������������
* ��������� �������� ���������.
*   # ��� ������� �������� ��������� �������� ���������� ���������
*     � ��������� Landscape_t.
*   # ��� ��������� ������������ � ����������� ��� ������������ ��������
*     � �������� ������� � ���������� �� ��������.
*   # �.�. ������� ����� ���������� � ��������� �������� �����������,
*     ������������� "����������� ��������" - "scattering".
*/

typedef struct __attribute__ ((packed)) {

    cl_float height;

    /**
    * �������� �������, �������.
    * [0; 90]
    * @todo extend ����� �����: �������� �����.
    */
    cl_float slope;

} mountainLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float depth;

    /**
    * �������� �������, �������.
    * [0; 90]
    * @todo extend ����� �����: �������� �����.
    */
    cl_float slope;

} basinLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float height;

    /**
    * ������������, �.
    */
    cl_float length;

} rangeLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float depth;

    /**
    * ������������, �.
    */
    cl_float length;

} ravineLandscape_t;


typedef struct __attribute__ ((packed)) {

    cl_float depth;

    /**
    * ����� ����������� ���������.
    */
    enum CODE_COMPONENT component;

} lakeLandscape_t;


typedef struct __attribute__ ((packed)) {

    /**
    * ������� ����.
    * @todo ������ ����� ���������� � ����������.
    */
    cl_float depth;

    /**
    * ����� ��������� �����.
    */
    enum CODE_COMPONENT component;

    /**
    * �������� �������, �/�.
    */
    cl_float drift;

    /**
    * ����������� �������: �����, ��, ...
    */
    enum DIRECTION direction;

} riverLandscape_t;


// �������� ���������
typedef union __attribute__ ((packed)) {
    mountainLandscape_t  mountain;
    basinLandscape_t     basin;
    rangeLandscape_t     range;
    ravineLandscape_t    ravine;
    lakeLandscape_t      lake;
    riverLandscape_t     river;
    // @todo ...

    /**
    * ������� ��������� ����� ���������� � ������ ��������.
    * �������, ��������� ������ �� ������� 3x3x3 � ���������, � ����� �������
    * ������ ��������� ������ �����.
    * # D_NONE ��� 'partially' ��������, ��� ������� ��������� ���������
    *   ��������� � ������.
    */
    enum DIRECTION partially;

} aboutElementLandscape_t;







/**
* �������� �������� ���������.
*
* @see landscapeCell_t
*/
typedef struct __attribute__ ((packed)) {

    enum CODE_ELEMENT_LANDSCAPE  code;

    aboutElementLandscape_t  about;

    /**
    * ���������� ������� - ��. "scattering" - ��������� � �������� ������.
    */
    cl_float count;

    /**
    * ����������� �������� ���������� ��� ��������.
    * ������� - �� ��, ��� survivorLiving_t::adaptability.
    * �����, �.�. � 1-� ������ ����� ������� ���������� � ���������
    * �������� �����������.
    */
    cl_float scattering;

} elementLandscape_t;




/**
* �������� ���������.
* ������ ��������� � ����������� �� ��������� ���������.
* �.�. ���������� ������� - �������, �� ���� ������ ������������ �� ����� ��,
* ������� ������ ����� ��������� ��������� ����������.
*/
typedef elementLandscape_t  landscapeCell_t[ LANDSCAPE_CELL ];




/**
* �������� �������.
*/
typedef landscapeCell_t*  landscapeContent_t;
typedef struct __attribute__ ((packed)) {
    landscapeContent_t content;
} landscape_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
