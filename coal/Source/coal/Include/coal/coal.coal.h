/*************************************************************************
*
*   coal
*__________________
*
* coal.coal.h
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
struct  coal_t
{
    /* primary container holding the cstr */
    const char s[N];

    /* utility functions */
    constexpr operator const char*() const { return s; }
    constexpr char  operator[]( int i )                         const { return s[i]; }
    constexpr bool  operator==( const coal_t& other )           const { return streq( s, other.s ); }
    constexpr const char*   data()                              const { return s; }
    constexpr int           size()                              const { return N; }
    constexpr int           length()                            const { return N; }
    constexpr int           toInt()                             const { return stoi( s ); }
    constexpr bool          isInt()                             const { return is_number( s ); }
    constexpr uint32_t      hash()                              const { return COAL_CRC32_STR( s ); }
    constexpr int           indexOf( const char* w, int f=0 )   const { return indexof( w, s, f ); }

    /* split */
    constexpr int querySplitNum( const char* sep )  const { int count = 0; for( int ind = 0; ind >= 0; ind = indexOf( sep, ind + 1 ) ) ++count; return  count; }
    constexpr int querySplitWordSize( const char* sep, int wordIndex )  const
    {
        int charIndex = 0;
        for( int count = 0; count <= wordIndex - 1; charIndex = indexOf( sep, charIndex + 1 ) )
            ++count;
        int nextIndex = indexOf( sep, charIndex + 1 );
        if( wordIndex == 0 )    return  nextIndex;
        if( nextIndex == -1 )   return  N - charIndex - 2;
        return  nextIndex - charIndex - 1;
    }

    constexpr int querySplitWordStart( const char* sep, int wordIndex )  const
    {
        int charIndex = 0;
        for( int count = 0; count <= wordIndex - 1; charIndex = indexOf( sep, charIndex + 1 ) )
            ++count;
        if( wordIndex == 0 )  return  0;
        return  charIndex + 1;
    }

    /* substring */
    static constexpr const char coal_impl_getchar_substring( const char* str, int start, int num ) { return str[num+start]; }
    template< int L, typename T, T... Nums > static constexpr const coal_t< L > make_coal_substring_impl(  const char* str, int start, std::integer_sequence< T, Nums... > ) { return { coal_impl_getchar_substring( str, start, Nums ) ..., '\0' }; }
    template< int L > static constexpr const coal_t< L > make_coal_substring( const char* str, int start = 0 ) { return make_coal_substring_impl< L >( str, start, std::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const coal_t< L + 1 > substring( int start = 0 ) const { return make_coal_substring< L + 1 >( s, start );}

    /* append */
    static constexpr const char coal_impl_getchar_append( const char* strA, const char* strB, int lenA, int num ) { return num < lenA ? strA[num] : strB[num-lenA]; }
    template< int L, typename T, T... Nums > static constexpr const coal_t< L > make_coal_append_impl(  const char* strA, const char* strB, std::integer_sequence< T, Nums... > ) { return { coal_impl_getchar_append( strA, strB, strlen( strA ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const coal_t< L > make_coal_append( const char* strA, const char* strB ) { return make_coal_append_impl< L >( strA, strB, std::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const coal_t< N + L - 1 > append( const char (&str)[L] ) const { return make_coal_append< N + L - 1 >( s, str ); }
    template< int L > constexpr const coal_t< N + L - 1 > append( const coal_t< L >& i ) const { return  append( i.s ); }

    /* prepend */
    static constexpr const char coal_impl_getchar_prepend( const char* strA, const char* strB, int lenB, int num ) { return num < lenB ? strB[num] : strA[num-lenB]; }
    template< int L, typename T, T... Nums > static constexpr const coal_t< L > make_coal_prepend_impl(  const char* strA, const char* strB, std::integer_sequence< T, Nums... > ) { return { coal_impl_getchar_prepend( strA, strB, strlen( strB ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const coal_t< L > make_coal_prepend( const char* strA, const char* strB ) { return make_coal_prepend_impl< L >( strA, strB, std::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const coal_t< N + L - 1 > prepend( const char (&str)[L] ) const { return make_coal_prepend< N + L - 1 >( s, str ); }
    template< int L > constexpr const coal_t< N + L - 1 > prepend( const coal_t< L >& i ) const { return  prepend( i.s ); }

    /* copy */
    constexpr const coal_t< N > copy() const { return  *this; }
};


/////////////////////////////////////////////////////
// coal makers
/* construction for coal, from string */
template< int N, typename T, T... Nums >
constexpr coal_t< N >
make_coal_from_string_impl( const char* str, std::integer_sequence< T, Nums... > )
{
    return { str[Nums] ... };
}


template< int N >
constexpr coal_t< N >
make_coal_from_string( const char (&str)[N] )
{
    return make_coal_from_string_impl< N >( str, std::make_integer_sequence< int, N >() );
}


constexpr int
make_coal_from_int_compute_length( int n )
{
    int i = 0;
    for( i = 0; n > 0; ++i )
        n /= 10;

    return  i == 0 ? 1 : i;
}


/* construction for coal, from int */
constexpr int
make_coal_from_int_reduce( int i, int num )
{
    if( num == 0 ) return  i;

    int result = i;
    int reduction = make_coal_from_int_compute_length( i ) - 1;
    for( int i = 0; i < reduction; ++i )
        result /= 10;
    for( int i = 0; i < reduction; ++i )
        result *= 10;
    result = i - result;
    return  make_coal_from_int_reduce( result, num - 1 );
}

constexpr const char
make_coal_from_int_impl_getchar( int i, int num )
{
    int result = make_coal_from_int_reduce( i, num );
    int reduction = make_coal_from_int_compute_length( result ) - 1;
    for( int i = 0; i < reduction; ++i )
        result /= 10;

    return  result + '0';
}

template< int N, typename T, T... Nums >
constexpr coal_t< N >
make_coal_from_int_impl( int i, std::integer_sequence< T, Nums... > )
{
    return { make_coal_from_int_impl_getchar( i, Nums ) ... };
}


template< int N >
constexpr coal_t< N >
make_coal_from_int( int i )
{
    return make_coal_from_int_impl< N >( i, std::make_integer_sequence< int, N - 1 >() );
}


/////////////////////////////////////////////////////
// coal operators
template< int N, int L >
constexpr coal_t< N + L - 1>
operator+( const coal_t< N >& A, const coal_t< L >& B )
{
    return  A.append( B );
}


template< int N, int L >
constexpr coal_t< N + L - 1>
operator+( const coal_t< N >& A, const char (&B)[L] )
{
    auto C = make_coal_from_string( B );
    return  A.append( C );
}


template< int N, int L >
constexpr coal_t< N + L - 1>
operator+( const char (&A)[N], const coal_t< L >& B )
{
    auto C = make_coal_from_string( A );
    return  B.prepend( C );
}


/////////////////////////////////////////////////////
// coal utility macro
/* utility shortcut for construction of coal */
#define coal                constexpr  auto
#define coalFromString(i)   ::__coal__::make_coal_from_string( i )
#define coalFromInt(i)      ::__coal__::make_coal_from_int< ::__coal__::make_coal_from_int_compute_length( i ) + 1 >( i )

#define coalFunc_RetVal( iRetType, iName )  template< int N > static constexpr const iRetType iName( const ::__coal__::coal_t<N> iCoal )
#define coal_split( obj, sep, ind )         obj.substring< obj.querySplitWordSize( sep, ind ) >( obj.querySplitWordStart( sep, ind ) )

} // namespace __coal__

