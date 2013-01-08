#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* ���������� � ����������� � ������� �������.
*
* # ����������� � ���� ������ ����.
* # ����������� �� ��������������� � ���������� ����.
* # ������ ����������� - ����������� ������� ����� ����� � ����� �����������,
*   ����� ����� ������ ��������������� ��� ����������� (�������) � ���������
*   ������ ������� ���������� ����������.
*
* #i �������� ����������� ��������� ������������ ��������� ������� ���
*    ����������� (������) ��������� *����������* �� ������ ����������. �������
*    ��� ����������� �������� ������������� ���������� (��������, OpenCL).
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* ������ ����������� � �������� � ����� �����������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������ ("�����" - ��. ���� 'SpaceChem') ��� ������ �������� �������.
    * [0; *_EVENT_TWO_COUNT - 1]
    *
    * # ��������� ���� �������������, ����� �������� ������ � ���.
    */
    cl_int  waldo;

    eventTwo_t  content[ OBSERVER_EVENT_TWO_COUNT ];
    
} observerMemoryEventTwo_t;




/**
* ���������� � ����������� ������� �������.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * ������� � ����� �����������, ����������� ������������.
    * @see #���������� � 'event_t'.
    */
    observerMemoryEventTwo_t memoryEventTwo;

} observer_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
