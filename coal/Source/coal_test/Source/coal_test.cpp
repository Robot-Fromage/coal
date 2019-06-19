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

struct FInfo
{
    const  int       m1; // 1
    const  int       m2; // 2
    const  int       m3; // 3
    const  int       m4; // 4
    const  int       m5; // 5
};


template< typename X, typename T, T... Nums >
constexpr  auto
GenStartSeq_Imp( X, std::integer_sequence< T, Nums... > )
{
    return  std::integer_sequence< int, X::value().querySplitWordStart( ",", Nums ) ... >();
}

template< typename X >
constexpr  auto
GenStartSeq( X )
{
    using forwardConstexprArg0 = coalConstexprWrapper( X::value() );
    return  GenStartSeq_Imp( forwardConstexprArg0{}, std::make_integer_sequence< int, X::value().querySplitNum( "," ) >() );
}


coal str = coalMakeFromString( "654,5141,21132,478,45,2888" );


int main()
{
    constexpr int num1 = coalSplitElem( str, ",", 0 ).toInt();
    constexpr int num2 = coalSplitElem( str, ",", 1 ).toInt();
    constexpr int num3 = coalSplitElem( str, ",", 2 ).toInt();
    //...
    //constexpr auto jeeee = std::integer_sequence< int, str.querySplitWordStart( ",", 0 ), str.querySplitWordStart( ",", 1 ) >();
    using forwardConstexprArg0 = coalConstexprWrapper( str );
    coal jajo1 = GenStartSeq( forwardConstexprArg0{} );
    coal test = coalMakeFromInt( 569 );

    return 0;
}

