/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.CompileTime.ConstStr.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <utility>
#include "coal/coal.char.h"
#include "coal/coal.crc32.h"


namespace __coal__ {


/////////////////////////////////////////////////////
// coal Constexpr cpp0x compliant string manipulation operations
template< int N >
struct  coal
{
    /* primary container holding the cstr */
    const char s[N];

    /* utility functions */
    constexpr operator const char*() const { return s; }
    constexpr char  operator[]( int i )                         const { return s[i]; }
    constexpr bool  operator==( const coal& other )             const { return streq( s, other.s ); }
    constexpr const char*   data()                              const { return s; }
    constexpr int           size()                              const { return N; }
    constexpr int           toInt()                             const { return stoi( s ); }
    constexpr bool          isNumber()                          const { return is_number( s ); }
    constexpr uint32_t      hash()                              const { return COAL_CRC32_STR( s ); }
    constexpr int           IndexOf( const char* w, int f=0 )   const { return indexof( w, s, f ); }

    /* substring */
    static constexpr const char coal_impl_getchar_substring( const char* str, int start, int num ) { return str[num+start]; }
    template< int L, typename T, T... Nums > static constexpr const coal< L > make_coal_substring_impl(  const char* str, int start, std::integer_sequence< T, Nums... > ) { return { coal_impl_getchar_substring( str, start, Nums ) ..., '\0' }; }
    template< int L > static constexpr const coal< L > make_coal_substring( const char* str, int start = 0 ) { return make_coal_substring_impl< L >( str, start, std::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const coal< L + 1 > substring( int start = 0 ) const { return make_coal_substring< L + 1 >( s, start );}

    /* append */
    static constexpr const char coal_impl_getchar_append( const char* strA, const char* strB, int lenA, int num ) { return num < lenA ? strA[num] : strB[num-lenA]; }
    template< int L, typename T, T... Nums > static constexpr const coal< L > make_coal_append_impl(  const char* strA, const char* strB, std::integer_sequence< T, Nums... > ) { return { coal_impl_getchar_append( strA, strB, strlen( strA ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const coal< L > make_coal_append( const char* strA, const char* strB ) { return make_coal_append_impl< L >( strA, strB, std::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const coal< N + L - 1 > append( const char (&str)[L] ) const { return make_coal_append< N + L - 1 >( s, str ); }
    template< int L > constexpr const coal< N + L - 1 > append( const coal< L >& i ) const { return  append( i.s ); }

    /* prepend */
    static constexpr const char coal_impl_getchar_prepend( const char* strA, const char* strB, int lenB, int num ) { return num < lenB ? strB[num] : strA[num-lenB]; }
    template< int L, typename T, T... Nums > static constexpr const coal< L > make_coal_prepend_impl(  const char* strA, const char* strB, std::integer_sequence< T, Nums... > ) { return { coal_impl_getchar_prepend( strA, strB, strlen( strB ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const coal< L > make_coal_prepend( const char* strA, const char* strB ) { return make_coal_prepend_impl< L >( strA, strB, std::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const coal< N + L - 1 > prepend( const char (&str)[L] ) const { return make_coal_prepend< N + L - 1 >( s, str ); }
    template< int L > constexpr const coal< N + L - 1 > prepend( const coal< L >& i ) const { return  prepend( i.s ); }

    /* copy */
    constexpr const coal< N > copy() const { return  *this; }
};


/////////////////////////////////////////////////////
// coal makers
/* construction for coal, implementation from integer sequence */
template< int N, typename T, T... Nums >
constexpr coal< N >
make_coal_impl( const char* str, std::integer_sequence< T, Nums... > )
{
    return { str[Nums] ... };
}

/* construction for coal */
template< int N >
constexpr coal< N >
make_coal( const char (&str)[N] )
{
    return make_coal_impl< N >( str, std::make_integer_sequence< int, N >() );
}


/////////////////////////////////////////////////////
// coal utility macro
/* utility shortcut for construction of coal */
#define coal            constexpr  auto
#define coalFromString(i)    ::__coal__::make_coal( i )


} // namespace __coal__

