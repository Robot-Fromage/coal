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
#include <tuple>
#include <coal_core>

struct FInfo
{
    const  int       m1; // 1
    const  int       m2; // 2
    const  int       m3; // 3
    const  int       m4; // 4
    const  int       m5; // 5
};


/////////////////////////////////////////////////////
// ParseSpecStr
coalFunc_RetVal( FInfo, Parse )
{
    return  { 8 };
}


template< int H, int N >
static
constexpr
const
int
Rec( const ::__coal__::coal_t<N> iCoal )
{
    //return  iCoal.substring< iCoal.querySplitWordSize( ",", 0 ) >( iCoal.querySplitWordStart( ",", 0 ) )
    int val =  iCoal.substring< iCoal.querySplitWordSize( ",", 0 ) >( iCoal.querySplitWordStart( ",", 0 ) ).toInt();
    return  0;
}


int main()
{
    coal split_str      = coalFromString( "654,5141,21132,478,45" );
    coal kojok  = coal_split( split_str, ",", 0 );
    constexpr FInfo nfo = Parse( split_str );
    constexpr uint32_t je = split_str.hash();
    return 0;
}

