/*************************************************************************
*
*   coal
*__________________
*
* coal.char.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once


namespace __coal__ {
/////////////////////////////////////////////////////
// c++14 compliant Constexpr Functions
constexpr int
strlen( const char* s )
{
    for( int i = 0;; ++i ) if( !s[i] ) return  i;
}


constexpr bool
streq( char const * a, char const * b )
{
    int lena = strlen( a );
    int lenb = strlen( b );
    if( lena != lenb ) return  false;

    for( int i = 0; i < lena; ++i )
        if( a[i] != b[i] )
            return  false;

    return  true;
}


constexpr bool
is_digit( char c )
{
    return  c >= '0' && c <= '9';
}


constexpr bool
is_number( const char* s )
{
    for( int i = 0; i < strlen( s ); ++i )
        if( !is_digit( s[i] ) )
            return  false;

    return  true;
}


constexpr int
stoi( const char* s )
{
    int r = 0;
    int l = strlen( s );
    for( int i = 0; i < strlen( s ); ++i )
        r = r * 10 + int( s[i] - '0' );
    return  r;
}


constexpr int
indexof( const char* word, const char* str, int from = 0 )
{
    int ls = strlen( str );
    int lw = strlen( word );

    for( int i = from; i < ls; ++i )
    {
        for( int j = 0; j < lw; ++j )
        {
            if( str[i+j] != word[j] )
                break;

            if( j == lw - 1 )
            {
                return  i;
            }
        }
    }

    return  -1;
}
} // namespace __coal__


//constexpr const int ct_char_index_without_digits ( char c, const char* s ) { int cind = 0; int lpos = 0; while(1) { if( s[cind] == c ) { break; } if( !is_digit( s[cind] ) ) { ++lpos; } ++cind; } return lpos; }

