#ifndef __Validate_H__
#define __Validate_H__

int validate(const int& number, const char* backgroundPath, const char* numberPath, unsigned char* bitstream);

int validateGlyph(const char* backgroundPath, const int& index, unsigned char* bitstream, char* glyphstream);

void uncompress(const unsigned char* bitstream, unsigned char* background);


#endif

