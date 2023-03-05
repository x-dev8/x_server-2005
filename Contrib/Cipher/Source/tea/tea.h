#ifndef __MORE_CIPHER_TEA_H__
#define __MORE_CIPHER_TEA_H__

#pragma warning( push )
#pragma warning( disable: 4307 )

namespace Tea
{
    const unsigned int CIPHER_SIZE = 8;

    const unsigned int KEY_LENGTH = 4;

    const unsigned int CYCLES = 16;

    const unsigned long DELTA = 0x9e3779b9;

    const unsigned long SUM = 0xc6ef3720;

    inline void SetKey( long buffer[], long key[ KEY_LENGTH ] )
    {
        key[0] ^= buffer[1];
        key[1] ^= buffer[0];
        key[2] ^= buffer[1];
        key[3] ^= buffer[0];
    }

    inline unsigned long GetOutputLength( unsigned long inputLength ) 
    {
        unsigned long mod = inputLength % CIPHER_SIZE;

        return ( ( mod != 0 ) ? ( inputLength + CIPHER_SIZE - mod ) : inputLength );
    }

    inline void Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength, long key[ KEY_LENGTH ] )
    {
        unsigned long outputLength = GetOutputLength( inputLength );

        if ( output != input ) memcpy( output, input, outputLength );

        long* outputBuffer = (long*)output;

        for ( unsigned long count = outputLength / Tea::CIPHER_SIZE; count > 0; --count )
        {
            unsigned long sum = 0;

            for ( unsigned long cycles = 0; cycles < CYCLES; ++cycles )
            {
                sum += DELTA;

                outputBuffer[0] += ( outputBuffer[1] << 4 ) + key[0] ^ outputBuffer[1] + sum ^ ( outputBuffer[1] >> 5 ) + key[1];
                outputBuffer[1] += ( outputBuffer[0] << 4 ) + key[2] ^ outputBuffer[0] + sum ^ ( outputBuffer[0] >> 5 ) + key[3];
            }

            Tea::SetKey( outputBuffer, key );

            outputBuffer += 2;
        }
    }

    inline void Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength, long key[ KEY_LENGTH ] )
    {
        unsigned long outputLength = GetOutputLength( inputLength );

        if ( output != input ) memcpy( output, input, outputLength );

        long* outputBuffer = (long*)output;

        for ( unsigned long count = outputLength / Tea::CIPHER_SIZE; count > 0; --count )
        {
            unsigned long sum = DELTA * CYCLES;
            long tmpkey[ KEY_LENGTH ] = { key[0], key[1], key[2], key[3] };
            SetKey( outputBuffer , key );

            for ( unsigned long cycles = 0; cycles < CYCLES; ++cycles )
            {
                outputBuffer[1] -= ( outputBuffer[0] << 4 ) + tmpkey[2] ^ outputBuffer[0] + sum ^ ( outputBuffer[0] >> 5 ) + tmpkey[3];
                outputBuffer[0] -= ( outputBuffer[1] << 4 ) + tmpkey[0] ^ outputBuffer[1] + sum ^ ( outputBuffer[1] >> 5 ) + tmpkey[1];

                sum -= DELTA;
            }

            outputBuffer += 2;
        }
    }
};

#pragma warning( pop )

#endif // __MORE_CIPHER_TEA_H__
