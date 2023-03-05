#ifndef __MORE_CIPHER_BASE64_CIPHER_H__
#define __MORE_CIPHER_BASE64_CIPHER_H__

#include "cipher/cipher_interface.h"

#include <vector>


namespace Cipher
{

/**
 * @brief Base64 encoder class.
 */
class Base64Encoder : public EncoderInterface
{
// Constructor and destructor.
public:
    Base64Encoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~Base64Encoder();

// Implementation.
public:
    virtual void SetKey( const unsigned char key[], unsigned long length );

    virtual unsigned long GetOutputLength( unsigned long inputLength );

    virtual unsigned long Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength );

// Attribute.
private:
    std::vector<unsigned char> key_;
};


/**
 * @brief Base64 decoder class.
 */
class Base64Decoder : public DecoderInterface
{
// Constructor and destructor.
public:
    Base64Decoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~Base64Decoder();

// Implementation.
public:

    virtual unsigned long GetOutputLength( unsigned long inputLength );


	virtual unsigned long Decode(const unsigned char key[], unsigned long keylength, unsigned char output[], const unsigned char input[], unsigned long inputLength ) {return 0;}
// Attribute.
private:
	virtual void SetKey( const unsigned char key[], unsigned long length );
	virtual unsigned long Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength );
    std::vector<unsigned char> key_;
};

}; // namespace Cipher.

#endif // __MORE_CIPHER_BASE64_CIPHER_H__
