#ifndef __MORE_CIPHER_BLOWFISH_CIPHER_H__
#define __MORE_CIPHER_BLOWFISH_CIPHER_H__

#include "cipher/cipher_interface.h"


namespace Cipher
{

/**
 * @brief Blowfish encoder class.
 */
class BlowfishEncoder : public EncoderInterface
{
// Constructor and destructor.
public:
    BlowfishEncoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~BlowfishEncoder();

// Implementation.
public:
    virtual void SetKey( const unsigned char key[], unsigned long length );

    virtual unsigned long GetOutputLength( unsigned long inputLength );

    virtual unsigned long Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength );

// Attribute.
private:
    unsigned long PArray_[18];
    unsigned long SBoxes_[4][256];
};


/**
 * @brief Blowfish decoder class.
 */
class BlowfishDecoder : public DecoderInterface
{
// Constructor and destructor.
public:
    BlowfishDecoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~BlowfishDecoder();

// Implementation.
public:

    virtual unsigned long GetOutputLength( unsigned long inputLength );

	virtual unsigned long Decode(const unsigned char key[], unsigned long keylength, unsigned char output[], const unsigned char input[], unsigned long inputLength ) {return 0;}

// Attribute.
private:
	virtual void SetKey( const unsigned char key[], unsigned long length );
	virtual unsigned long Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength );
    unsigned long PArray_[18];
    unsigned long SBoxes_[4][256];
};

}; // namespace Cipher.

#endif // __MORE_CIPHER_BLOWFISH_CIPHER_H__
