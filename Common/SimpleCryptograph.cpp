#include "SimpleCryptograph.h"

const short key_max = 10;
const unsigned char key[key_max] = "t!o#l$e%z" ;

CSimpleCryptograph::CSimpleCryptograph(void)
{
	_decoder = Cipher::CipherFactory::Instance().CreateDecoder( Cipher::CIPHERTYPE_BASE64,key,key_max );
	_encoder = Cipher::CipherFactory::Instance().CreateEncoder( Cipher::CIPHERTYPE_BASE64,key,key_max );

	//if (_decoder)
	//{
	//	_decoder->SetKey(key,key_max);
	//}
	//if (_encoder)
	//{
	//	_encoder->SetKey(key,key_max);
	//}

	vecInput.clear();
}

CSimpleCryptograph::~CSimpleCryptograph(void)
{
	Cipher::CipherFactory::Instance().ReleaseEncoder( &_encoder );
	Cipher::CipherFactory::Instance().ReleaseDecoder( &_decoder );
}

bool CSimpleCryptograph::Encode(const char* _input,unsigned short input_length,char* _output)
{
	if (strlen(_input) == 0)
	{
		return false;
	}

	vecInput.clear();

	for (int loop = 0;loop < input_length;loop++)
	{
		vecInput.push_back(_input[loop]);
	}

	vecInput.resize( _encoder->GetOutputLength( (unsigned long)vecInput.size() ) );

	std::vector<unsigned char> output( _encoder->GetOutputLength( (unsigned long)vecInput.size() ) );

	unsigned long outputLength = 0;
	try
	{
		outputLength = _encoder->Encode( (unsigned char*)&output[0], (unsigned char*)&vecInput[0], (unsigned long)vecInput.size() );
	}
	catch( Cipher::EncoderInterface& reason )
	{
		return false;
	}

	//_output = (char*)&output[0];
	return OutputResult((unsigned char*)&output[0],outputLength,_output);
	//return true;
}

bool CSimpleCryptograph::Decode(const char* _input,unsigned short input_length,char* _output)
{
	if (strlen(_input) == 0)
	{
		return false;
	}

	vecInput.clear();

	for (int loop = 0;loop < input_length;loop++)
	{
		vecInput.push_back(_input[loop]);
	}

	vecInput.resize( _decoder->GetOutputLength( (unsigned long)vecInput.size() ) );

	std::vector<unsigned char> output( _decoder->GetOutputLength( (unsigned long)vecInput.size() ) );

	unsigned long outputLength = 0;
	try
	{
		outputLength = _decoder->Decode( (unsigned char*)&output[0], (unsigned char*)&vecInput[0], (unsigned long)vecInput.size() );
	}
	catch( Cipher::DecodeException& reason )
	{
		return false;
	}
	return OutputResult((unsigned char*)&output[0],outputLength,_output);
	/*return (char*)&output[0];*/
}

bool CSimpleCryptograph::OutputResult(unsigned char buff[],unsigned long length,char* _output)
{
	if (length == 0)
	{
		return false;
	}
	memcpy(_output,buff,sizeof(unsigned char)*length);
	return true;
}