#ifndef __MORE_CIPHER_BLOWFISH_H__
#define __MORE_CIPHER_BLOWFISH_H__


namespace Blowfish
{
    const unsigned long NUM_SUBKEYS = 18;
    const unsigned long NUM_S_BOXES = 4;
    const unsigned long NUM_ENTRIES = 256;
    const unsigned long CIPHER_SIZE = 8;

    void GenSubkeys( unsigned long PArray[ NUM_SUBKEYS ],
        unsigned long SBoxes[ NUM_S_BOXES ][ NUM_ENTRIES ],
        const unsigned char key[], unsigned long length );

    void Encode( unsigned char output[], const unsigned char input[], unsigned long inputLength,
        unsigned long PArray[ NUM_SUBKEYS ], unsigned long SBoxes[ NUM_S_BOXES ][ NUM_ENTRIES ] );

    void Decode( unsigned char output[], const unsigned char input[], unsigned long inputLength,
        unsigned long PArray[ NUM_SUBKEYS ], unsigned long SBoxes[ NUM_S_BOXES ][ NUM_ENTRIES ] );

    inline unsigned long GetOutputLength( unsigned long inputLength )
    {
        unsigned long mod = inputLength % CIPHER_SIZE;

        return ( ( mod != 0 ) ? ( inputLength + CIPHER_SIZE - mod ) : inputLength );
    }
}; // namespace Blowfish.

#endif //__MORE_CIPHER_BLOWFISH_H__
