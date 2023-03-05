#ifndef __MORE_CIPHER_CIPHER_FACTORY_H__
#define __MORE_CIPHER_CIPHER_FACTORY_H__

#include "cipher_interface.h"

#include <string>


namespace Cipher
{

const std::string CIPHERTYPE_XOR      = "xor";
const std::string CIPHERTYPE_BLOWFISH = "blowfish";
const std::string CIPHERTYPE_TEA      = "tea";
const std::string CIPHERTYPE_BASE64   = "base64";
const std::string CIPHERTYPE_3DES     = "3des";
const std::string CIPHERTYPE_RSA      = "rsa";
const std::string CIPHERTYPE_ECC      = "ecc";

/**
 * @brief Cipher factory class.
 */
class CipherFactory
{
// Constructor and destructor.
private:
    CipherFactory() {};
    ~CipherFactory() {};

// Method.
public:
    /// Instantiation CipherFactory object.
    static CipherFactory& Instance()
    {
        static CipherFactory factory;
        return factory;
    }

    EncoderInterface* CreateEncoder( std::string cipherType = CIPHERTYPE_XOR, const unsigned char key[] = NULL, unsigned long length = 0 );
    void ReleaseEncoder( EncoderInterface** encoder );

    DecoderInterface* CreateDecoder( std::string cipherType = CIPHERTYPE_XOR, const unsigned char key[] = NULL, unsigned long length = 0 );
    void ReleaseDecoder( DecoderInterface** decoder );

	//static FILE*				OpenCipherFile(const char* pszFilename);
};

extern EncoderInterface* g_Encoder ;
extern DecoderInterface* g_Decoder ;
namespace XOR
{
	extern unsigned char DEFAULT_KEY[];

};
}; // namespace Cipher.

#endif // __MORE_CIPHER_CIPHER_FACTORY_H__
