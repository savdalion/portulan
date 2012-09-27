#ifndef PORTULAN_AS_OPEN_CL_STRUCT

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
#endif



/**
* ������������ ����� � ������ �����������
* GROUP_ELEMENT::GE_COMPONENT.
*
*   #! ��������� ����������� ������ �����. ������� � ������ aboutComponent_t.
*/
#undef CC_NONE
enum CODE_COMPONENT {
    // ��������� ����������� ��� �� ��������
    CC_NONE = 0,

    // �������
    CC_VACUUM = CC_NONE,

    // ������ (�������� + ����, #! ��� CARBON_ACID)
    CC_AIR = 1,

    // �����
    //   - ���������� �����
    CC_BARREN_SOIL,
    //   - ����������� �����
    CC_RICH_SOIL,

    // �����
    CC_BOULDER,
    // ������� ������
    CC_ROCK,

    // �����
    CC_SAND,

    // ����������� �������� ��� ���������� ������
    //   - �������� ( # ��������� - �� �� �������� )
    CC_CARBOHYDRATE,
    //   - ���������� ���, CO2
    CC_CARBON_ACID,
    //   - ����
    CC_FAT,
    //   - �����
    CC_PROTEIN,

    // ������, �����
    CC_BONE,
    // ������� ���������� ���������� �����
    CC_DETRITUS,

    // ������ ���������� ����������������� ������ (�����������)
    //   - ���
    CC_FECES,
    //   - ����
    CC_URINE,

    // ����
    CC_WATER,

    // ������ ��������
    CC_SPARSE,

    // ���������
    CC_last
};





/**
* ��� ���������� � �������� ���� � ����� �������� ���
* ���������� ����������.
* ������ portionEnergy_t.
*
* ��������: ����� = 0.2, ���� = 0.1, �������� = 0.7.
* ��������: ����� = 6e6, ���� = 3e3, �������� = 4e4.
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_COMPONENT code;
    cl_float count;
} portionComponent_t;





/**
* ������������ ����� � ������ �������
* GROUP_ELEMENT::GE_ENERGY.
*/
enum CODE_ENERGY {
    // ������� ����������� ��� ������������
    CE_NONE = 0,

    // �������������
    CE_ELECTRICITY,

    // ����� �����. �����
    CE_HEAT,

    // ������� ���� (��������� � ������� ������������� ����� ���������)
    CE_NORMAL_LIGHT,

    // �������� (��������� ������� �������)
    CE_RADIATION,

    // ���������
    CE_last
};




/**
* ��� ������� � �������� ���� � ����� ������ ������� �������� ���
* ���������� �������.
* ������ portionComponent_t.
*   # ���������� ������� ����������� ����� ������� � ������ / ����.
*     ��. http://ru.wikipedia.org/wiki/%D0%9B%D1%8E%D0%BA%D1%81
*     ������� �����������
        10?5 	    ���� �������, �������� ������ ������� ����
        0,0003 	    ��������� ������� ����
        0,01 	    �������� ����
        0,27 	    ���������� � ����� ����
        1 	        ���������� � ��������
        �� 20 	    � ���� �� ������� ~50 �
        50 	        ����� �������
        80 	        �������/������
        100 	    ����� ��������� ����
        320-500     ������� �������
        350�150     ������ ��� ����� �� ������
        400 	    ������ ��� ����� � ����� ����
        1000 	    ��������� ����, ��������� � ����������
        1-3 ���. 	������� �� ������
        4-5 ���. 	������� � ������� � ������
        10-25 ���. 	����� ��������� ���� (� ����)
        32-130 ���. ��� ������ �������
        135 ���. 	��� ��������� �� ������� ���������� ����� �� ������
*/
typedef struct __attribute__ ((packed)) {
    enum CODE_ENERGY code;
    cl_float count;
} portionEnergy_t;







/**
* ���������� � ����������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ��� ����������.
    */
    enum CODE_COMPONENT code;

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
    * �� / �� = �� / ���� ��������� �� �������� �����
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
*   #! � ���� ������ ������ ���������� �����. ���� ����������.
*/
typedef aboutOneComponent_t  aboutComponent_t[ COMPONENT_COUNT ];



/**
* ����. ���-�� ����������� � ��������� ������ �� ������, ������� �����
* *������������* ��������� � 1-� ������ ���������.
*/
typedef portionComponent_t  componentCell_t[ COMPONENT_CELL ];



/**
* ���������� �������. ����� ����� ������ �������� � 1-� ������ ���������.
*
*   # ������ ������� ������� ������ ��������� ������������ �� 100%.
*
* ��������: ������ 0.1, ����������� ����� 0.7, ���� 0.05, ������ 0.15.
*/
typedef componentCell_t*  componentContent_t;
typedef struct __attribute__ ((packed)) {
    /**
    * ���������� � ������ (�� ������).
    * ����������� � ���� ������ (% / 100) ������������ �����������.
    * ����� ���� = 1.0.
    */
    /* - �������� �� ��������� ������ � ����, �.�. OpenCL ��� ������� �������
         ����� �� ����������������.
    typedef componentCell_t content_t[ COMPONENT_GRID * COMPONENT_GRID * COMPONENT_GRID ];
    */
    componentContent_t content;

} component_t;



#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
