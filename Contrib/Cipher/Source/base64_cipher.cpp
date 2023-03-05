#include "base64_cipher.h"

#include "base64/base64.h"


namespace Cipher
{

Base64Encoder::Base64Encoder( const unsigned char /*key*/[], unsigned long /*length*/ )
{
}

Base64Encoder::~Base64Encoder()
{
}

void Base64Encoder::SetKey( const unsigned char /*key*/[], unsigned long /*length*/ )
{
}

unsigned long Base64Encoder::GetOutputLength( unsigned long inputLength )
{
    return Base64::GetEncodeOutputLength( inputLength );
}

unsigned long Base64Encoder::Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength ) 
{
    if ( NULL == input ) throw EncodeException( "input buffer is NULL" );
    if ( NULL == output ) throw EncodeException( "output buffer is NULL" );
    if ( input == output ) throw EncodeException( "input == output" );

    Base64::Encode( output, input, inputLength );

    return GetOutputLength( inputLength );
}


Base64Decoder::Base64Decoder( const unsigned char /*key*/[], unsigned long /*length*/ )
{
}

Base64Decoder::~Base64Decoder()
{
}

void Base64Decoder::SetKey( const unsigned char /*key*/[], unsigned long /*length*/ )
{
}

unsigned long Base64Decoder::GetOutputLength( unsigned long inputLength )
{
    return Base64::GetDecodeOutputLength( inputLength );
}

unsigned long Base64Decoder::Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength )
{
    if ( NULL == input ) throw DecodeException( "input buffer is NULL" );
    if ( NULL == output ) throw DecodeException( "output buffer is NULL" );
    if ( input == output ) throw EncodeException( "input == output" );

    Base64::Decode( output, input, inputLength );

    return GetOutputLength( inputLength );
}

}; // namespace Cipher.
