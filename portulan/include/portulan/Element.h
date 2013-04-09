#pragma once

#include <memory>


namespace portulan {


/**
* ����� ����� ��� ��������� ���������.
*/
class Element {
public:
    inline Element() {
    }




    inline virtual ~Element() {
    }




protected:
    /**
    * ����������� ����� ��� ��������� � ����.
    * �������������� ��������� ��������� ������.
    */
    template< class T, size_t N >
    inline static std::unique_ptr< T >
    createContent() {
        std::unique_ptr< T >  content( new T[ N ] );
        std::memset( content.get(),  0,  sizeof( T ) * N );

        return std::move( content );
    }

};


} // portulan
