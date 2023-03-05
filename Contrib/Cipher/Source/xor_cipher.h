#ifndef __MORE_CIPHER_DEFAULT_CIPHER_H__
#define __MORE_CIPHER_DEFAULT_CIPHER_H__

#include "cipher/cipher_interface.h"

#include <vector>
#include <Windows.h>


namespace Cipher
{

/**
 * @brief Default encoder class.
 */
class XorEncoder : public EncoderInterface
{
// Constructor and destructor.
public:
    XorEncoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~XorEncoder();

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
 * @brief Default decoder class.
 */
class XorDecoder : public DecoderInterface
{
// Constructor and destructor.
public:
    XorDecoder( const unsigned char key[] = NULL, unsigned long length = 0 );
    virtual ~XorDecoder();


	virtual unsigned long GetOutputLength( unsigned long inputLength );
// Implementation.
	virtual unsigned long Decode(const unsigned char key[], unsigned long keylength, unsigned char output[], const unsigned char input[], unsigned long inputLength );//这个可以用于多线程

// Attribute.
private://这两个接口不能用于多线程加载
	virtual void SetKey( const unsigned char key[], unsigned long length );

	virtual unsigned long Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength );
    std::vector<unsigned char> key_;
	CRITICAL_SECTION cipher_section;
};

}; // namespace Cipher.

#endif // __MORE_CIPHER_DEFAULT_CIPHER_H__
