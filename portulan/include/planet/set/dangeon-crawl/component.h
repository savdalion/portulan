#pragma once

#include "structure.h"


/**
* ������ ����������� ��� ������������� ������� �� ������
* ���� ���� Dungeon Crawl.
*
* @see http://crawl.chaosforge.org
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace component {

/**
* ������������ ����� � ������ �����������
* GROUP_ELEMENT::GE_COMPONENT.
*/
#undef CC_NONE
enum CODE_COMPONENT {
    // ��������� ����������� ��� ����������
    CC_NONE = 0,

    // �������
    CC_VACUUM = 1,

    // ������ (�������� + ����)
    CC_AIR,

    // �����
    //   - ���������� �����
    CC_BAREN_SOIL,
    //   - �����
    CC_BOULDER,
    //   - ����������� �����
    CC_RICH_SOIL,
    //   - �������� ������
    CC_PEBBLE,
    //   - ������� ������
    CC_ROCK,
    //   - �����
    CC_SAND,

    // ����������� �������� ��� ���������� ������
    //   - ��������
    CC_CARBOHYDRATE,
    //   - ���������� ���
    CC_CARBON_ACID,
    //   - ����
    CC_FAT,
    //   - �����
    CC_PROTEIN,

    // ������, �����
    CC_BONE,

    // ������ ���������� ����������������� ������ (�����������)
    //   - ���
    CC_FECES,
    //   - ����
    CC_URINE,

    // ����
    CC_WATER,

    // ������ ��������
    CC_SPARSE
};





/**
* ��� ���������� � �������� ���� � ����� �������� ���
* ���������� ����������.
* ������ portionEnergy_t.
*
* ��������: ����� = 0.2, ���� = 0.1, �������� = 0.7.
* ��������: ����� = 6e6, ���� = 3e3, �������� = 4e4.
*/
typedef struct {
    CODE_COMPONENT code;
    cl_float count;
} portionComponent_t;





/**
* ������������ ����� � ������ �����������
* GROUP_ELEMENT::GE_ENERGY.
*/
enum CODE_ENERGY {
    // ������� ����������� ��� ������������
    CE_NONE = 0,

    // �������� (��������� ������� �������)
    CE_RADIATION,

    // ������� ���� (��������� � ������� ������������� ����� ���������)
    CE_NORMAL_LIGHT,

    // ����� �����. �����
    CE_HEAT,

    // �������������
    CE_ELECTRICITY
};




/**
* ��� ������� � �������� ���� � ����� ������ ������� �������� ���
* ���������� �������.
* ������ portionComponent_t.
*/
typedef struct {
    CODE_ENERGY code;
    cl_float count;
} portionEnergy_t;







/**
* ���������� � ����������.
*
* @see portulan::command::planet::aoc()
*/
typedef struct {
    /**
    * ���������, �� / �3.
    */
    cl_float density;

    /**
    * ����������� ���������, �.
    */
    cl_float meltingPoint;

    /**
    * ����������� �������, �.
    */
    cl_float boilingPoint;

    /**
    * ������� ��������� ��� ������������� (��������� ���������), �� / ��.
    */
    cl_float enthalpyFusion;

    /**
    * ������� ��������� ��� ���������������, �� / ��.
    */
    cl_float enthalpyVaporization;

    /**
    * �����������, �� / (�� * �).
    */
    cl_float heatCapacity;

    /**
    * @todo extend ������� �������� http://ru.wikipedia.org/wiki/%D0%A1%D0%BA%D1%80%D1%8B%D1%82%D0%B0%D1%8F_%D1%82%D0%B5%D0%BF%D0%BB%D0%BE%D1%82%D0%B0_%D1%81%D0%B3%D0%BE%D1%80%D0%B0%D0%BD%D0%B8%D1%8F
    */

} aboutOneComponent_t;



/**
* ���������� � �����������.
*/
typedef aboutOneComponent_t  aboutComponent_t[ COMPONENT_COUNT ];



/**
* ����. ���-�� ����������� � ��������� ������ �� ������, ������� ���������
* � ������� ������� (� ���������). ��� ������ ������������ ��� ������������
* �������� ��������� � �������.
*/
typedef portionComponent_t  componentAll_t[ COMPONENT_COUNT ];



/**
* ����. ���-�� ����������� � ��������� ������ �� ������, ������� �����
* *������������* ��������� � 1-� ������ ���������.
*/
typedef portionComponent_t  componentCell_t[ COMPONENT_CELL ];




                } // component
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
