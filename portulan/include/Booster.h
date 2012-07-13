#pragma once

namespace portulan {

class Booster;

}


namespace portulan {


/**
* ����� ��� ����������� ��������� ������ �� ������������� �����������
* (OpenCL, Cuda).
* ������-������� ���� ������ ���������� ������ ��� ������ ����� ������
* � "������������ �����������".
*
* # �������� ���������� ��������� ��������� ������ ���� "booster_t".
*/
class Booster {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Booster >  Ptr;
    typedef std::unique_ptr< Booster >  UPtr;



public:
    /**
    * ����� ��� ������ ������ "����������� �������" � �������������.
    */
    virtual void toBooster() = 0;


    /**
    * ����� ��� ������ ������ �� ������������� � "���������� ������".
    */
    virtual void fromBooster() = 0;

};



} // portulan

