#ifndef __MORE_CIPHER_BASE64_H__
#define __MORE_CIPHER_BASE64_H__

#include <cctype>


namespace Base64
{

    const std::string BASE64_STRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const unsigned int CIPHER_SIZE  = 3;

    inline unsigned long GetEncodeOutputLength( unsigned long inputLength ) 
    {
        unsigned long mod = inputLength % CIPHER_SIZE;

        return ( ( mod != 0 ) ? ( inputLength + CIPHER_SIZE - mod ) * 4 / 3 : inputLength * 4 / 3 );
    }

    inline unsigned long GetDecodeOutputLength( unsigned long inputLength ) 
    {
        return inputLength / 4 * 3;
    }
    
    bool IsBase64( char ch )
    {
        return ( isalnum( ch ) || ( '+' == ch ) || ( '/' == ch ) );
    }

    inline void Encode( unsigned char output[], const unsigned char input[], unsigned long length )
    {
        int i = 0, j = 0;
        unsigned char charArray3[3], charArray4[4];

        while ( length-- )
        {
            charArray3[ i++ ] = *input++;

            if ( i == 3 )
            {
                charArray4[0] = ( charArray3[0] & 0xfc ) >> 2;
                charArray4[1] = ( ( charArray3[0] & 0x03 ) << 4 ) + ( ( charArray3[1] & 0xf0 ) >> 4 );
                charArray4[2] = ( ( charArray3[1] & 0x0f ) << 2 ) + ( ( charArray3[2] & 0xc0 ) >> 6 );
                charArray4[3] = charArray3[2] & 0x3f;

                for ( i = 0; i < 4; ++i )
                    *output++ = BASE64_STRING[ charArray4 [ i ] ];

                i = 0;
            }
        }

        if ( i > 0 )
        {
            for ( j = i; j < 3; ++j )
                charArray3[ j ] = '\0';

            charArray4[0] = ( charArray3[0] & 0xfc ) >> 2;
            charArray4[1] = ( ( charArray3[0] & 0x03 ) << 4 ) + ( ( charArray3[1] & 0xf0 ) >> 4 );
            charArray4[2] = ( ( charArray3[1] & 0x0f ) << 2 ) + ( ( charArray3[2] & 0xc0 ) >> 6 );
            charArray4[3] = charArray3[2] & 0x3f;

            for ( j = 0; j < i + 1; ++j )
                *output++ = BASE64_STRING[ charArray4[ j ] ];

            while ( i++ < 3 )
                *output++ = '=';
        }
    }

    inline void Decode( unsigned char output[], const unsigned char input[], unsigned long length )
    {
        int i = 0, j = 0, count = 0;
        unsigned char charArray4[4], charArray3[3];

        while ( length-- && ( input[ count ] != '=' ) && IsBase64( input[ count ] ) )
        {
            charArray4[ i++ ] = input[ count ];
            ++count;

            if ( 4 == i )
            {
                for ( i = 0; i < 4; ++i )
                    charArray4[ i ] = (unsigned char)BASE64_STRING.find( charArray4[ i ] );

                charArray3[0] = ( charArray4[0] << 2 ) + ( ( charArray4[1] & 0x30 ) >> 4 );
                charArray3[1] = ( ( charArray4[1] & 0xf ) << 4 ) + ( ( charArray4[2] & 0x3c ) >> 2 );
                charArray3[2] = ( ( charArray4[2] & 0x3 ) << 6 ) + charArray4[3];

                for ( i = 0; i < 3; ++i )
                    *output++ = charArray3[ i ];

                i = 0;
            }
        }

        if ( i > 0 )
        {
            for ( j = i; j < 4; ++j )
                charArray4[ j ] = 0;

            for ( j = 0; j < 4; ++j )
                charArray4[ j ] = (unsigned char)BASE64_STRING.find( charArray4[ j ] );

            charArray3[0] = ( charArray4[0] << 2 ) + ( ( charArray4[1] & 0x30 ) >> 4 );
            charArray3[1] = ( ( charArray4[1] & 0xf ) << 4 ) + ( ( charArray4[2] & 0x3c ) >> 2 );
            charArray3[2] = ( ( charArray4[2] & 0x3 ) << 6 ) + charArray4[3];

            for ( j = 0; j < i - 1; ++j )
                *output++ = charArray3[ j ];
        }
    }


}; // namespace Base64.

#endif // __MORE_CIPHER_BASE64_H__
