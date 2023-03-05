#include "blowfish_cipher.h"

#include "blowfish/blowfish.h"

#include <sstream>


namespace Cipher
{

namespace 
{
    const unsigned char DEFAULT_KEY[] = "(vmYemmVBIUYew$#^%!LKJV_3hfJli9)*($#%Af987A*&S^";
};


BlowfishEncoder::BlowfishEncoder( const unsigned char key[], unsigned long length )
{
    if ( key != NULL && length > 0 )
        SetKey( key, length );
    else
        SetKey( DEFAULT_KEY, (unsigned long)strlen( (char*)DEFAULT_KEY ) );
}

BlowfishEncoder::~BlowfishEncoder()
{
}

void BlowfishEncoder::SetKey( const unsigned char key[], unsigned long length )
{
    Blowfish::GenSubkeys( PArray_, SBoxes_, key, length );
}

unsigned long BlowfishEncoder::GetOutputLength( unsigned long inputLength ) 
{
    return Blowfish::GetOutputLength( inputLength );
}

unsigned long BlowfishEncoder::Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength ) 
{
    if ( NULL == input ) throw EncodeException( "input buffer is NULL" );
    if ( NULL == output ) throw EncodeException( "output buffer is NULL" );
    if ( output != input ) memcpy( output, input, inputLength );

    Blowfish::Encode( output, input, inputLength, PArray_, SBoxes_ );

    return GetOutputLength( inputLength );
}

BlowfishDecoder::BlowfishDecoder( const unsigned char key[], unsigned long length  ) 
{
    if ( key != NULL && length > 0 )
        SetKey( key, length );
    else
        SetKey( DEFAULT_KEY, (unsigned long)strlen( (char*)DEFAULT_KEY ) );
}

BlowfishDecoder::~BlowfishDecoder()
{
}

void BlowfishDecoder::SetKey( const unsigned char key[], unsigned long length )
{
    Blowfish::GenSubkeys( PArray_, SBoxes_, key, length );
}

unsigned long BlowfishDecoder::GetOutputLength( unsigned long inputLength ) 
{
    return Blowfish::GetOutputLength( inputLength );
}

unsigned long BlowfishDecoder::Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength )
{
    if ( NULL == input ) throw DecodeException( "input buffer is NULL" );
    if ( NULL == output ) throw DecodeException( "output buffer is NULL" );

    Blowfish::Decode( output, input, inputLength, PArray_, SBoxes_ );

    return GetOutputLength( inputLength );
}

}; // namespace Cipher.
