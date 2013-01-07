#pragma once


namespace portulan {


/*
* ���������� ��� ������ � ��������
*   # ��� ������������ enum ������������� ��������� ���� SHORT_last,
*     ��� SHORT - ����������� �������� ������������.
*   # ��. ��. ����������, ���������� �������� "#" � ���� �������.
*/




/**
* ������������ ���� ������ �� ���������� OpenCL.
* (!) �� ��� ������ ������� ����� �������� ��� ���������� ���� ����������.
*/
#define OPENCL_PORTULAN


/**
* ����� ��� (����� ��������) ������������.
*/
#define DUNGEON_CRAWL_WORLD_PORTULAN




/**
* ��������� ������������ ��� 'double' � ����������.
* ��� ���� ��������� ������ ��������� ����������� � 'float'.
* 
* #! �� ��� ���������� ������������ 'double' ��� OpenCL.
*
* @see typedef real_t
* @see porte::PERMIT_DOUBLE_ENGINE_PORTE
*/
#define PERMIT_DOUBLE_ENGINE_PORTULAN




/**
* ������ ������ (���������� �������-�������) ��� ������� ���������� ���������.
*
* @see world::*::Portulan::statistics_t
*/
static const size_t STATISTICS_BUFFER_COUNT = 200000;


} // portulan
