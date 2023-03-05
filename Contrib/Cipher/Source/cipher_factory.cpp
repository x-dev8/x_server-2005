#include "cipher/cipher_factory.h"

#include "xor_cipher.h"
#include "blowfish_cipher.h"
#include "tea_cipher.h"
#include "base64_cipher.h"

#include <cctype>
#include "vector"
#include "Launcher/DataLauncher.h"


namespace
{

bool StringCompare( const std::string& first, const std::string& second )
{ 
    for ( std::string::const_iterator firstIt = first.begin(), secondIt = second.begin(); 
        firstIt != first.end() && secondIt != second.end(); ++firstIt, ++secondIt )
	{
		char chTemp1 = toupper( *firstIt );
		char chTemp2 = toupper( *secondIt );		
		if (chTemp1 != chTemp2)
			return false;
	}
    return true;
}

}; // Anonymous namespace.


namespace Cipher
{

EncoderInterface* CipherFactory::CreateEncoder( std::string cipherType, const unsigned char key[], unsigned long length )
{
    if ( !cipherType.empty() )
        if ( StringCompare( cipherType, CIPHERTYPE_BLOWFISH ) )
            return new BlowfishEncoder( key, length );
        else if ( StringCompare( cipherType, CIPHERTYPE_TEA ) )
            return new TeaEncoder( key, length );
        else if ( StringCompare( cipherType, CIPHERTYPE_BASE64 ) )
            return new Base64Encoder( key, length );
        else if ( StringCompare( cipherType, CIPHERTYPE_XOR ) )
            return new XorEncoder( key, length );

    return new XorEncoder( key, length );
}

void CipherFactory::ReleaseEncoder( EncoderInterface** encoder )
{
    if ( *encoder != NULL )
    {
        delete *encoder;
        *encoder = NULL;
    };
}

DecoderInterface* CipherFactory::CreateDecoder( std::string cipherType, const unsigned char key[], unsigned long length )
{
    if ( !cipherType.empty() )
        if ( StringCompare( cipherType, CIPHERTYPE_BLOWFISH ) )
            return new BlowfishDecoder( key, length );
        else if ( StringCompare( cipherType, CIPHERTYPE_TEA ) )
            return new TeaDecoder( key, length );
        else if ( StringCompare( cipherType, CIPHERTYPE_BASE64 ) )
            return new Base64Decoder( key, length );
        else if ( StringCompare( cipherType, CIPHERTYPE_XOR ) )
            return new XorDecoder( key, length );

    return new XorDecoder( key, length );
}

void CipherFactory::ReleaseDecoder( DecoderInterface** decoder )
{
    if ( *decoder != NULL )
    {
        delete *decoder;
        *decoder = NULL;
    }
}
#define _IOYOURBUF 0x0100
//FILE* CipherFactory::OpenCipherFile( const char* pszFilename )
//{
//	FILE* fp = NULL;
//	std::string CipherFileName(pszFilename);
//	CipherFileName += 'c';
//// 	struct _stat st;
//// 	if( ::_stat( CipherFileName.c_str(), &st ) != -1 )
//	{
//		FILE*cipherFp  = NULL;
//		fopen_s(&cipherFp,CipherFileName.c_str(),"rbT");
//		if (!cipherFp)
//		{
//			return NULL;
//		}
//		fseek ( cipherFp, 0, SEEK_END );
//		long nSize = ftell( cipherFp );
//		rewind( cipherFp );
//		unsigned char* buffer = NULL;
//#ifdef DATA_LAUNCHER
//		if (g_DirectReadInPackage && (cipherFp->_flag & (_IOYOURBUF)))
//		{
//			buffer = (unsigned char*)cipherFp->_base;
//		}
//		else
//#endif
//		{
//			buffer = new unsigned char[nSize];
//			fread(buffer,sizeof(unsigned char),nSize,cipherFp);
//		}
//// 		char temp[1024];
//// 		strcpy(temp,pszFilename);
//// 		strlwr(temp);
//// 		std::string key = temp;
//// 		int nBaseFileNameBegin = key.rfind('\\');
//// 		int nSlashPos = key.rfind("/");
//// 		if (nBaseFileNameBegin < nSlashPos)
//// 		{
//// 			nBaseFileNameBegin = nSlashPos;
//// 		}
//// 		key = &key.c_str()[nBaseFileNameBegin + 1];
//// 		key += (char*)XOR::DEFAULT_KEY;
//// 		g_Decoder->SetKey();
//
//
//		char* fileName = _tempnam("./",NULL);
//#ifdef fopen_s
//#undef fopen_s
//#endif
//		fopen_s(&fp,fileName,"wb+D");
//		free(fileName);
//		if (!fp)
//		{
//			return NULL;
//		}
//		{
//			unsigned long outputLength =  Cipher::g_Decoder->GetOutputLength( (unsigned long)nSize );
//			unsigned char* pBuffer = new unsigned char[outputLength + 1];
//// 			Cipher::g_Decoder->Decode((const unsigned char*)key.c_str(),key.length(), (unsigned char*)pBuffer, (unsigned char*)buffer, (unsigned long)nSize );
//			Cipher::g_Decoder->Decode((const unsigned char*)"M",1, (unsigned char*)pBuffer, (unsigned char*)buffer, (unsigned long)nSize );
//			pBuffer[outputLength] = '\0';
//// #ifdef DATA_LAUNCHER
////  			if (g_DirectReadInPackage)
//// 			{
//// 				fwrite(&output[0],sizeof(unsigned char),outputLength,fp);
//// 				fseek(fp,0, SEEK_SET );
//// 			}
//// 			else
//// #endif
//			{
//				setvbuf(fp,(char*)pBuffer,_IOFBF,outputLength + 1);
//				fp->_cnt = outputLength;
////  				fwrite(&output[0],sizeof(unsigned char),outputLength,fp);
//				fp->_ptr = fp->_base;
//				fseek(fp,0, SEEK_SET );
//				fp->_cnt = outputLength;
//			}
//		}
//		fclose(cipherFp);
//
//#ifdef DATA_LAUNCHER
//		if (g_DirectReadInPackage)
//		{
//		}
//		else
//#endif
//		{
//			delete [] buffer;
//		}
//		return fp;
//	}
//	return NULL;
//
//}
EncoderInterface* g_Encoder = CipherFactory::Instance().CreateEncoder(CIPHERTYPE_XOR);
DecoderInterface* g_Decoder = CipherFactory::Instance().CreateDecoder(CIPHERTYPE_XOR);
// EncoderInterface* g_Encoder = NULL;
// DecoderInterface* g_Decoder = NULL;
}; // namespace Cipher.
