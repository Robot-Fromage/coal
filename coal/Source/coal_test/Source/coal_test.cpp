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
    coal akk = coalFromInt( 99999991 );

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << char( '0' + 9 ) << std::endl;
    std::cout << int( '0' ) << std::endl;
    std::cout << int( '9' ) << std::endl;
    std::cout << jeje << std::endl;

    return 0;
}

