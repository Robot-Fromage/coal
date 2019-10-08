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
#include <coal_core>
#include <tuple>
#include <assert.h>
#include <bitset>


struct FInfo
{
    const  int       m1;
    const  int       m2;
    const  int       m3;
    const  int       m4;
    const  int       m5;
};

template< typename X >
constexpr  FInfo
ParseInfo( X )
{
    coal el = X::value();

    constexpr int sizeofsep = coalMakeFromString( "_MX:" ).count() - 1;
    constexpr int im1s = el.indexOf( "_M1:" ) + sizeofsep;
    constexpr int im2s = el.indexOf( "_M2:" ) + sizeofsep;
    constexpr int im3s = el.indexOf( "_M3:" ) + sizeofsep;
    constexpr int im4s = el.indexOf( "_M4:" ) + sizeofsep;
    constexpr int im5s = el.indexOf( "_M5:" ) + sizeofsep;

    constexpr int im1et = el.indexOf( "_", im1s + 1 );
    constexpr int im2et = el.indexOf( "_", im2s + 1 );
    constexpr int im3et = el.indexOf( "_", im3s + 1 );
    constexpr int im4et = el.indexOf( "_", im4s + 1 );
    constexpr int im5et = el.indexOf( "_", im5s + 1 );

    constexpr int im1er = im1et == -1 ? el.count() : im1et;
    constexpr int im2er = im2et == -1 ? el.count() : im2et;
    constexpr int im3er = im3et == -1 ? el.count() : im3et;
    constexpr int im4er = im4et == -1 ? el.count() : im4et;
    constexpr int im5er = im5et == -1 ? el.count() : im5et;

    constexpr int im1d = im1er - im1s;
    constexpr int im2d = im2er - im2s;
    constexpr int im3d = im3er - im3s;
    constexpr int im4d = im4er - im4s;
    constexpr int im5d = im5er - im5s;

    coal m1 = coalSubstring( el, im1s, im1d );
    coal m2 = coalSubstring( el, im2s, im2d );
    coal m3 = coalSubstring( el, im3s, im3d );
    coal m4 = coalSubstring( el, im4s, im4d );
    coal m5 = coalSubstring( el, im5s, im5d );

    constexpr int im1 = m1.toInt();
    constexpr int im2 = m2.toInt();
    constexpr int im3 = m3.toInt();
    constexpr int im4 = m4.toInt();
    constexpr int im5 = m5.toInt();

    return  { im1, im2, im3, im4, im5 };
}

constexpr int m1 = 111;
constexpr int m2 = 222;
constexpr int m3 = 333;
constexpr int m4 = 444;
constexpr int m5 = 555;
coal M1 = coalMakeFromString( "_M1:" ) + coalMakeFromInt( m1 );
coal M2 = coalMakeFromString( "_M2:" ) + coalMakeFromInt( m2 );
coal M3 = coalMakeFromString( "_M3:" ) + coalMakeFromInt( m3 );
coal M4 = coalMakeFromString( "_M4:" ) + coalMakeFromInt( m4 );
coal M5 = coalMakeFromString( "_M5:" ) + coalMakeFromInt( m5 );
coal mangled = M5 + M4 + M2 + M3 + M1;
static_assert( mangled == coalMakeFromString( "_M5:555_M4:444_M2:222_M3:333_M1:111" ), "..." );

coalMakeConstexprArg( const_mangled, mangled );
constexpr FInfo info = ParseInfo( const_mangled{} );

static_assert( info.m1 == m1, "..." );
static_assert( info.m2 == m2, "..." );
static_assert( info.m3 == m3, "..." );
static_assert( info.m4 == m4, "..." );
static_assert( info.m5 == m5, "..." );

int main()
{
    constexpr unsigned int ref = 2044517703U;
    constexpr unsigned int hashcrc32 = __coal__::crc32b( "ok" );
    static_assert( ref == hashcrc32, "..." );
    uint32_t a = 564653;
    uint32_t b = static_cast< unsigned int >( -( (int)a) );;

    std::bitset<32> xa(a);
    std::bitset<32> xb(b);
    std::cout << xa << std::endl;
    std::cout << xb << std::endl;

    constexpr const char* testvar = "Hello World";
    coal testcoal0 = coalMakeFromString( "Hello World" );
    coal testcoal1 = coalMakeFromCstr( testvar );
    static_assert( testcoal0 == testcoal1, "..." );
    return 0;
}

