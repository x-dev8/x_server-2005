#ifndef __MORE_CIPHER_CIPHER_INTERFACE_H__
#define __MORE_CIPHER_CIPHER_INTERFACE_H__

#include <stdexcept>
#include <string>


namespace Cipher
{

	/**
	* @brief Exception class for encryption.
	*/
	class EncodeException : public std::runtime_error
	{
		// Constructor and destructor.
	public:
		/**
		* @brief Constructor.
		* @param reason String containing the description of the exception.
		*/
		EncodeException::EncodeException( const std::string& reason ) : std::runtime_error( reason ) {}
	};


	/**
	* @brief Exception class for decryption.
	*/
	class DecodeException : public std::runtime_error
	{
		// Constructor and destructor.
	public:
		/**
		* @brief Constructor.
		* @param reason String containing the description of the exception.
		*/
		DecodeException::DecodeException( const std::string& reason ) : std::runtime_error( reason ) {}
	};


	/**
	* @brief Encoder abstract interface class.
	*/
	class EncoderInterface
	{
		// Constructor and destructor.
	public:
		EncoderInterface() {}
		virtual ~EncoderInterface() {}

		// Copy constructor and operator.
	private:
		EncoderInterface( const EncoderInterface& );
		EncoderInterface& operator=( const EncoderInterface& );

		// Interface.
	public:
		virtual void SetKey( const unsigned char key[], unsigned long length ) = 0;

		virtual unsigned long GetOutputLength( unsigned long inputLength ) = 0;

		virtual unsigned long Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength ) = 0;
	};


	/**
	* @brief Decoder abstract interface class.
	*/
	class DecoderInterface
	{
		// Constructor and destructor.
	public:
		DecoderInterface() {}
		virtual ~DecoderInterface() {}

		// Copy constructor and operator.
	private:
		DecoderInterface( const DecoderInterface& );
		DecoderInterface& operator=( const DecoderInterface& );

		// Interface.
	public:
		virtual unsigned long Decode(const unsigned char key[], unsigned long keylength, unsigned char output[], const unsigned char input[], unsigned long inputLength ) = 0;//这个可以用于多线程

		virtual unsigned long GetOutputLength( unsigned long inputLength ) = 0;

		virtual void SetKey( const unsigned char key[], unsigned long length ) = 0;

		virtual unsigned long Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength ) = 0;
	private:	

	};

}; // namespace Cipher.

#endif // __MORE_CIPHER_CIPHER_INTERFACE_H__
