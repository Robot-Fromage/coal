/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <iostream>
#include <assert.h>
#include <coal_core>


int main()
{
    coal a = coalFromString( "Salut123" );
    coal b = coalFromString( "Mec" );
    coal c = a.append( b.s );
    coal d = a.append( b );
    coal lel = coalFromString( "Jambon" ).prepend( "ok" );
    coal z = a.copy();
    coal jeje = a + b + c + d + lel + z;

    constexpr int e = a.substring< 3 >( 5 ).toInt();

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << jeje << std::endl;

    return 0;
}

