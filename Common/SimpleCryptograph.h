#pragma once

#include "Cipher/cipher_factory.h"
#include "Cipher/cipher_interface.h"
#include <vector>

class CSimpleCryptograph
{
public:
	CSimpleCryptograph(void);
	~CSimpleCryptograph(void);

	static CSimpleCryptograph& Instance()
	{
		static CSimpleCryptograph csc;
		return csc;
	}

	bool Encode(const char* _input,unsigned short input_length,char* _output);
	bool Decode(const char* _input,unsigned short input_length,char* _output);

	bool OutputResult(unsigned char buff[],unsigned long length,char* _output);
private:
	Cipher::EncoderInterface* _encoder;
	Cipher::DecoderInterface* _decoder;

	std::vector<unsigned char> vecInput;
};

#define  theSimpleCtyp CSimpleCryptograph::Instance()
