#pragma once


namespace portulan {
    namespace command {


template< typename T >
inline elevationMap< T >::elevationMap(
    const std::string& sign,
    const std::string& source,
    double scaleXY, double hMin, double hMax
) :
    sign( sign ),
    source( source),
    scaleXY( scaleXY ),
    hMin( hMin ),
    hMax( hMax )
{
}




template< typename T >
inline void elevationMap< T >::operator()( T& map ) const {

    std::cout << "ok! " << this->sign << std::endl;


    auto& topology = map.topology();
    // @todo ...

}



    } // command
} // portulan
