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

struct FInfo
{
    const  int       m1; // 1
    const  int       m2; // 2
    const  int       m3; // 3
    const  int       m4; // 4
    const  int       m5; // 5
};


coal str = coalMakeFromString( "654,5141,21132,478,45,2888" );


template< typename X, typename T, T... Nums >
constexpr  auto
GenStartSeq_Imp( std::integer_sequence< T, Nums... > )
{
    return  std::integer_sequence< int, X::value().querySplitWordStart( ",", Nums ) ... >();
}

template< typename X >
constexpr  auto
GenStartSeq( X )
{
    return  GenStartSeq_Imp< X >( std::make_integer_sequence< int, X::value().querySplitNum( "," ) >() );
}


template< typename X, typename Y, typename T, T... Nums >
constexpr  auto
SplitIntoTuple_Imp( std::integer_sequence< T, Nums... > )
{
    //return  std::make_tuple( X::value().substring< X::value().querySplitWordSize( Y::value(), Nums ) >( X::value().querySplitWordStart( Y::value(), Nums ) ) ... );
    return  std::make_tuple( coalSplitElem( X::value(), Y::value(), Nums ) ... );
}


template< typename X, typename Y >
constexpr  auto
SplitIntoTuple( X, Y )
{
    return  SplitIntoTuple_Imp< X, Y >( std::make_integer_sequence< int, X::value().querySplitNum( Y::value() ) >() );
}


constexpr int coal_test_str()
{
    return 0;
}


constexpr int coal_test_int()
{
    return 0;
}


constexpr int coal_test_list()
{
    return 0;
}


int main()
{
    coal num1 = coalSplitElem( str, ",", 0 );
    coal num2 = coalSplitElem( str, ",", 1 );
    coal num3 = coalSplitElem( str, ",", 2 );
    //...
    //constexpr auto jeeee = std::integer_sequence< int, str.querySplitWordStart( ",", 0 ), str.querySplitWordStart( ",", 1 ) >();
    using forwardConstexprArg0 = coalConstexprWrapper( str );
    coal jajo1 = GenStartSeq( forwardConstexprArg0{} );
    coal test = coalMakeFromInt( 569 );

    coal list = std::make_tuple( coalSplitElem( str, ",", 0 ), coalSplitElem( str, ",", 1 ), coalSplitElem( str, ",", 2 ) );
    coal e0 = std::get< 0 >( list );
    static_assert( e0 == num1, " .... " );
    constexpr char ok1 = num1[0];
    constexpr char ok2 = e0[0];
    static_assert( '6' == ok2, "ok" );

    coal sep = coalMakeFromString( "," );
    using forwardConstexprArg1 = coalConstexprWrapper( "," );
    constexpr auto list2 = SplitIntoTuple( forwardConstexprArg0{}, forwardConstexprArg1{} );
    static_assert( std::get< 0 >( list2 ) == num1, "nop" );

    return 0;
}

