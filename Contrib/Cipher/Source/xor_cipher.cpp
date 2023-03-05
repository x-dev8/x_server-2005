#include "xor_cipher.h"
#include <Windows.h>


namespace Cipher
{

// Anonymous namespace.
namespace XOR
{
     unsigned char DEFAULT_KEY[] = "ABCDEFGHIJklmnopqrstuvwxyz0123456789";
};

XorEncoder::XorEncoder( const unsigned char key[], unsigned long length )
{
    SetKey( key, length );
}

XorEncoder::~XorEncoder()
{
}

void XorEncoder::SetKey( const unsigned char key[], unsigned long length )
{
	key_.clear();
    if ( key && length )
        for ( unsigned long i = 0; i < length; ++i )
            key_.push_back( key[ i ] );
    else
		for ( unsigned long i = 0; i < strlen( (char*)XOR::DEFAULT_KEY ); ++i )
            key_.push_back( XOR::DEFAULT_KEY[ i ] );
}

unsigned long XorEncoder::GetOutputLength( unsigned long inputLength )
{
    return inputLength;
}

unsigned long XorEncoder::Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength )
{
    if ( NULL == input ) throw DecodeException( "input buffer is NULL" );
    if ( NULL == output ) throw DecodeException( "output buffer is NULL" );
    if ( output != input ) memcpy( output, input, inputLength );

    for ( unsigned long i = 0; i < inputLength; ++i )
        for ( size_t j = 0; j < key_.size(); ++j )
            output[ i ] ^= key_[ j ];

    return GetOutputLength( inputLength );
}


XorDecoder::XorDecoder( const unsigned char key[], unsigned long length )
{
   SetKey( key, length );
   InitializeCriticalSection(&cipher_section);
}

XorDecoder::~XorDecoder()
{
	DeleteCriticalSection(&cipher_section);
}

void XorDecoder::SetKey( const unsigned char key[], unsigned long length )
{
	key_.clear();
    if ( key && length )
        for ( unsigned long i = 0; i < length; ++i )
            key_.push_back( key[ i ] );
    else
        for ( unsigned long i = 0; i < strlen( (char*)XOR::DEFAULT_KEY ); ++i )
            key_.push_back( XOR::DEFAULT_KEY[ i ] );
}

unsigned long XorDecoder::GetOutputLength( unsigned long inputLength )
{
    return inputLength;
}

unsigned long XorDecoder::Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength )
{
    if ( NULL == input ) throw DecodeException( "input buffer is NULL" );
    if ( NULL == output ) throw DecodeException( "output buffer is NULL" );
    if ( output != input ) memcpy( output, input, inputLength );

    for ( unsigned long i = 0; i < inputLength; ++i )
        for ( size_t j = 0; j < key_.size(); ++j )
            output[ i ] ^= key_[ j ];

    return GetOutputLength( inputLength );
}

unsigned long XorDecoder::Decode( const unsigned char key[], unsigned long keylength, unsigned char output[], const unsigned char input[], unsigned long inputLength )
{
	EnterCriticalSection(&cipher_section);
	SetKey(key,keylength);
	Decode(output,input,inputLength);
	LeaveCriticalSection(&cipher_section);
	return 0;
}
}; // namespace Cipher.
