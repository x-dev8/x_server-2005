#include "tea_cipher.h"

#include "tea/tea.h"


namespace Cipher
{

// Anonymous namespace.
namespace
{
    const long DEFAULT_KEY[] = { 0xfb25bdf3, 0x638cf3b2, 0x136be7d2, 0x4b76ac25 }; 
};

TeaEncoder::TeaEncoder( const unsigned char key[], unsigned long length )
{
    if ( key != NULL && length > 0 )
        SetKey( key, length );
    else
        SetKey( (const unsigned char*)DEFAULT_KEY, sizeof( DEFAULT_KEY ) );
}

TeaEncoder::~TeaEncoder()
{
}

void TeaEncoder::SetKey( const unsigned char key[], unsigned long length )
{
    if ( length > 0 )
    {
        key_[0] = key[0];

        for ( unsigned long i = 0; i < length / Tea::KEY_LENGTH - 1; ++i )
            key_[ i + 1 ] = key[ sizeof(long) * ( i + 1 ) ];
    }
}

unsigned long TeaEncoder::GetOutputLength( unsigned long inputLength )
{
    return Tea::GetOutputLength( inputLength );
}

unsigned long TeaEncoder::Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength ) 
{
    if ( NULL == input ) throw EncodeException( "input buffer is NULL" );
    if ( NULL == output ) throw EncodeException( "output buffer is NULL" );

    Tea::Encode( output, input, inputLength, key_ );

    return GetOutputLength( inputLength );
}


TeaDecoder::TeaDecoder( const unsigned char key[], unsigned long length )
{
    if ( key != NULL && length > 0 )
        SetKey( key, length );
    else
        SetKey( (const unsigned char*)DEFAULT_KEY, sizeof( DEFAULT_KEY ) );
}

TeaDecoder::~TeaDecoder()
{
}

void TeaDecoder::SetKey( const unsigned char key[], unsigned long length )
{
    if ( length > 0 )
    {
        key_[0] = key[0];

        for ( unsigned long i = 0; i < length / Tea::KEY_LENGTH - 1; ++i )
            key_[ i + 1 ] = key[ sizeof(long) * ( i + 1 ) ];
    }
}

unsigned long TeaDecoder::GetOutputLength( unsigned long inputLength )
{
    return Tea::GetOutputLength( inputLength );
}

unsigned long TeaDecoder::Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength )
{
    if ( NULL == input ) throw DecodeException( "input buffer is NULL" );
    if ( NULL == output ) throw DecodeException( "output buffer is NULL" );

    Tea::Decode( output, input, inputLength, key_ );

    return GetOutputLength( inputLength );
}

}; // namespace Cipher.
