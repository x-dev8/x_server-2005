/**
 * @file    tea_cipher.h
 * @brief   Interface of the Encoder and Decoder class.
 * @date    2006-11-22 21:57:02
 * @author  
 * 
 *          
 * 
 *          Compiles with Visual C++-8.0 on Windows-XP-SP2.
 *          Compiles with GCC-3.2.3 on Linux-2.6.9-5.
 */

#ifndef __MORE_CIPHER_TEA_CIPHER_H__
#define __MORE_CIPHER_TEA_CIPHER_H__

#include "cipher/cipher_interface.h"


namespace Cipher
{

/**
 * @brief Tea encoder class.
 */
class TeaEncoder : public EncoderInterface
{
// Constructor and destructor.
public:
    TeaEncoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~TeaEncoder();

// Implementation.
public:
    virtual void SetKey( const unsigned char key[], unsigned long length );

    virtual unsigned long GetOutputLength( unsigned long inputLength );

    virtual unsigned long Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength );

// Attribute.
private:
    long key_[4];
};


/**
 * @brief Tea decoder class.
 */
class TeaDecoder : public DecoderInterface
{
// Constructor and destructor.
public:
    TeaDecoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~TeaDecoder();

// Implementation.
public:

    virtual unsigned long GetOutputLength( unsigned long inputLength );

	virtual unsigned long Decode(const unsigned char key[], unsigned long keylength, unsigned char output[], const unsigned char input[], unsigned long inputLength ) {return 0;}

// Attribute.
private:
	virtual void SetKey( const unsigned char key[], unsigned long length );
	virtual unsigned long Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength );
    long key_[4];
};

}; // namespace Cipher.

#endif // __MORE_CIPHER_TEA_CIPHER_H__
