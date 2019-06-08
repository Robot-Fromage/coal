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
    coal a = coal_make( "Salut123" );
    coal b = coal_make( "Mec" );
    coal c = a.Append( b.s );
    coal d = a.Append( b );
    constexpr int e = a.Substring< 3 >( 5 ).ToInt();

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    return 0;
}

