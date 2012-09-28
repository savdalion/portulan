#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� � ������� �� ������������ �������.
*
*   # ������������ ������ ������� ���� ����������� ����. �� @todo �����
*     ������������� ��� �� ��������� ��� ������� ������� � �������� �������.
*   # ��������� ��������� ��������� �� "rainfall".
*
* @see rainfall_t
* @see planet::Topology
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
#endif


/**
* ��������� ������� � 1-� ������ �� ����������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������� �������� �������, �� / ����.
    */
    cl_float average;

} behaviourDrainage_t;




/**
* ������ ��������� � ����������� � ����������� �� �����������.
*/
typedef behaviourDrainage_t  drainageCell_t[ 1 ];





/**
* ����������� �� ����������� �������.
*/
typedef drainageCell_t*  drainageContent_t;
typedef struct __attribute__ ((packed)) {
    drainageContent_t content;
} drainage_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
            } // dungeoncrawl
        } // set
    } // planet
} // portulan
#endif
