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
#include <cstring>
#include <coal_core>
#include <array>
#include <assert.h>

#define COAL_ASSERT( i ) static_assert( i, "" );
// Quick look MAX 96
// Actual MAX 357


template< int S >
struct kpm
{
    static  constexpr  int Size()  { return S; }
};

int main()
{
    //constexpr int a = coal::indexof( "i", "ooooooi" );
    //oooooooooo
    //kpm< a > m;
    //COAL_ASSERT( m.Size() == 357 )

    //oooooooooo
    //oooooooooooooooooooooooooooooooooooooooooooooooooo
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
    //constexpr int xx11 = coal::cpp11::indexof(      "k", "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooook" );
    constexpr int xx14 = coal::cpp14::indexof(      "k", "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooook" );
    //std::cout<< kpm< xx11 >::Size() << std::endl;
    //std::cout<< kpm< xx14 >::Size() << std::endl;
    std::cout<< kpm< xx14 >::Size() << std::endl;

    return 0;
}

