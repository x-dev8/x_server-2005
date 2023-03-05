#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <set>

#pragma warning ( push, 0 )

//设置第三方库freeType路径
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/fttrigon.h>

#include "validate.h"
#include "packet_interface.h"
//#include "Launcher/DataLauncher.h"
#ifdef _DEBUG
#pragma comment(lib, "freetype2311_D.lib")
#else 
#pragma comment(lib, "freetype2311.lib")
#endif

//#pragma warning(disable: 4996)
//#pragma warning(disable: 4099)
//#pragma warning(disable: 4101)

#ifndef M_PI
#define M_PI (float)3.14159265358979323846
#endif

#define round(a) ((int)((a)+0.5))
#define clamp(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define radians(ang)	(float)(((ang)*M_PI) / 180)
#define random(x) (rand() % (x))
#define rangeRandom(x,y) ((x) + rand()%((y+1)-(x))) 

time_t time(time_t *time);

int validate(const int& number, const char* backgroundPath, const char* numberPath, unsigned char* bitstream)
{
	char backgroundFilename[255], numFilename[255];

	unsigned char *background, *numberBuf, temp;

	long int backgroundLen, numberLen;

	f_Handle *backgroundFile, *numberFile;

	int backgroundNum, lineNumber, xa, xb, ya, yb, dx, dy, steps, k, xDist, yDist, dist, i, j, idx, theta, m, n;

	float xIncrement, yIncrement, x, y, sine, cosine;

	// srand((int)time(0));

	backgroundNum = random(10);

	_snprintf(backgroundFilename, sizeof(backgroundFilename), "%s%d.raw", backgroundPath, backgroundNum);

	backgroundFile = packet_namespace::w_fopen(backgroundFilename, "rb");

	if (!backgroundFile)
	{
		printf("Can't find the background file => %s !.\n", backgroundFilename);
		return false;
	}

	packet_namespace::w_fseek(backgroundFile, 0, SEEK_END);
	backgroundLen = packet_namespace::w_ftell(backgroundFile);
	packet_namespace::w_fseek(backgroundFile, 0, SEEK_SET);

	background = (unsigned char*)malloc(backgroundLen*sizeof(char));
	if (background == NULL)
	{
		background = (unsigned char*)malloc(backgroundLen*sizeof(char));
		if (background == NULL)
		{
			packet_namespace::w_fclose(backgroundFile);
			return false;
		}
	}
	packet_namespace::w_fread(background, sizeof(char), backgroundLen, backgroundFile);

	packet_namespace::w_fclose(backgroundFile);

	lineNumber = rangeRandom(1, 3);

// 	for (i = 0; i < lineNumber; ++i)
// 	{
// 		xa = random(160);
// 		xb = random(160);
// 		ya = random(48);
// 		yb = random(48);
// 
// 		dx = xb - xa;
// 		dy = yb - ya;
// 
// 		x = xa;
// 		y = ya;
// 
// 		if (abs(dx) > abs(dy))
// 		{
// 			steps = abs(dx);
// 
// 		}else
// 		{
// 			steps = abs(dy);
// 		}
// 
// 		xIncrement = dx / (float)steps;
// 		yIncrement = dy / (float)steps;
// 
// 		background[160*round(y) + round(x)] ^= 255; 
// 
// 		for (k = 0; k < steps; ++k)
// 		{
// 			x += xIncrement;
// 			y += yIncrement;
// 
// 			background[160*round(y) + round(x)] ^= 255;
// 		}
// 
// 	}

	for (i = 0; i < 200; ++i)
	{
		xDist = rangeRandom(1, 158);
		yDist = rangeRandom(1, 46);
		background[160*yDist + xDist] ^= 255;

		dist = rand() % 3 - 1;
		background[160*(yDist+dist) + (xDist+dist)] ^= 255;

		dist = rand() % 3 - 1;
		background[160*(yDist+dist) + (xDist+dist)] ^= 255;

		dist = rand() % 3 - 1;
		background[160*(yDist+dist) + (xDist+dist)] ^= 255;
	}

	numberBuf = (unsigned char*)malloc(768 * sizeof(char));	
	memset(numberBuf, 0, 768);

	char numBuffer[16];
	_snprintf(numBuffer, sizeof(numBuffer), "%04d\0", number);
	for (idx = 0; idx < strlen(numBuffer); ++idx)
	{
		temp = numBuffer[idx] - 0x30;
		_snprintf(numFilename, sizeof(numFilename), "%s%d.raw", numberPath, temp);

		numberFile = packet_namespace::w_fopen(numFilename, "rb");

		if (!numberFile)
		{
			printf("Can't find the number file => %s !", numFilename);
			return false;
		}

		packet_namespace::w_fseek(numberFile, 0, SEEK_END);
		numberLen = packet_namespace::w_ftell(numberFile);
		packet_namespace::w_fseek(numberFile, 0, SEEK_SET);

		packet_namespace::w_fread(numberBuf, sizeof(char), numberLen, numberFile);

		theta = rangeRandom(-30, 30);	
		sine = sinf(radians(theta));
		cosine = cosf(radians(theta));

		m = rangeRandom(-3, 3);
		n = rangeRandom(-7, 7);

		for (i = 0; i < 24; ++i)
		{
			for (j = 0; j < 32; ++j)
			{        
				xDist = (int)( (i-12)*cosine + (j-16)*sine + 20) + m;
				xDist = clamp(xDist, 0, 159);
				yDist = (int)(-(i-12)*sine + (j-16)*cosine + 24) + n;
				yDist = clamp(yDist, 0, 47);

				background[160*yDist + (xDist+idx*40)] ^= numberBuf[24*j + i];            
			}
		}
		packet_namespace::w_fclose(numberFile);
		numberFile = NULL;
	}
	free(numberBuf);
	numberBuf = NULL;

	memset(bitstream, 0, 960);
	for (i = 0; i < 960; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			if (background[i*8+j])
			{
				bitstream[i] |= 1 << (7-j);
			}
		}
	}
	free (background);
	background = NULL;

	return true;
}

int validateGlyph(const char* backgroundPath, const int& index, unsigned char* bitstream, char* glyphstream)
{
	char backgroundFilename[255];
	unsigned char *background;

	f_Handle *backgroundFile;

	int backgourndNum = random(10);

	_snprintf(backgroundFilename, sizeof(backgroundFilename), "%s%d.raw", backgroundPath, backgourndNum);

	backgroundFile = packet_namespace::w_fopen(backgroundFilename, "rb");

	if (!backgroundFile)
	{
		fprintf(stderr, "Can't find the background file => %s !\n", backgroundFilename);
		return false;
	}

	packet_namespace::w_fseek(backgroundFile, 0, SEEK_END);
	size_t backgroundLen = packet_namespace::w_ftell(backgroundFile);
	packet_namespace::w_fseek(backgroundFile, 0, SEEK_SET);

	background = new unsigned char[backgroundLen];
	packet_namespace::w_fread(background, sizeof(char), backgroundLen, backgroundFile);

	packet_namespace::w_fclose(backgroundFile);

	int lineNumber = rangeRandom(1, 3);

// 	for (int i = 0; i < lineNumber; ++i)
// 	{
// 		int xa = random(160);
// 		int xb = random(160);
// 		int ya = random(48);
// 		int yb = random(48);
// 
// 		int dx = xb - xa, dy = yb - ya, steps, k;
// 
// 		float xIncrement, yIncrement, x = xa, y = ya;
// 
// 		if (abs(dx) > abs(dy))
// 		{
// 			steps = abs(dx);
// 
// 		}else
// 		{
// 			steps = abs(dy);
// 		}
// 
// 		xIncrement = dx / (float)steps;
// 		yIncrement = dy / (float)steps;
// 
// 		background[160*round(y) + round(x)] ^= 255;
// 
// 		for (k = 0; k < steps; ++k)
// 		{
// 			x += xIncrement;
// 			y += yIncrement;
// 
// 			background[160*round(y) + round(x)] ^= 255;
// 		}
// 	}

	for (int i = 0; i < 200; ++i)
	{
		int x, y, dist;
		x = rangeRandom(1, 158);
		y = rangeRandom(1, 46);

		dist = rangeRandom(-1, 1);
		background[160*(y+dist) + (x+dist)] ^= 255;

		dist = rangeRandom(-1, 1);
		background[160*(y+dist) + (x+dist)] ^= 255;

		dist = rangeRandom(-1, 1);
		background[160*(y+dist) + (x+dist)] ^= 255;
	}

	wchar_t *unicodeIndex = new wchar_t[3755];
	f_Handle *fp_index;
    
	char unicodeIndexFilename[255];
	_snprintf(unicodeIndexFilename, sizeof(unicodeIndexFilename), "%s\\%s", backgroundPath, "unicodeIndex.raw");
	fp_index = packet_namespace::w_fopen(unicodeIndexFilename, "rb");

	if (!fp_index)
	{
		fprintf(stderr, "Can't find the unicodeIndex.raw file!\n");
		return false;
	}

	packet_namespace::w_fseek(fp_index, 0, SEEK_END);
	size_t len = packet_namespace::w_ftell(fp_index);
	packet_namespace::w_fseek(fp_index, 0, SEEK_SET);

	if (!packet_namespace::w_fread(unicodeIndex, sizeof(wchar_t), 3755, fp_index))
	{
		fprintf(stderr, "Can't read the data from the unicodeIndex.raw file!\n");
		return false;
	}

    if ( fp_index )
    { packet_namespace::w_fclose( fp_index ); }
    
	int idx;
	wchar_t glyphIndex;
	std::set<wchar_t> glyphMask;
	while (glyphMask.size() != 24)
	{
		idx = random(3756);
		glyphIndex = unicodeIndex[idx];
		glyphMask.insert(glyphIndex);
	}

	wchar_t glyphWchar[25];
	memset(glyphWchar, 0, sizeof(glyphWchar));

	idx = 0;
	std::set<wchar_t>::iterator iteratorGlyph;
	for (iteratorGlyph = glyphMask.begin(); iteratorGlyph != glyphMask.end(); ++iteratorGlyph)
	{
		glyphWchar[idx] = *iteratorGlyph;
		++idx;
	}
		
	idx = 0;
	for (size_t i = 0; i < wcslen(glyphWchar); ++i)
	{
		*(glyphstream+idx) = glyphWchar[i] >> 8;
		++idx;
		*(glyphstream+idx) = glyphWchar[i];
		++idx;
	}

	FT_Library library;
	FT_Error error;

	error = FT_Init_FreeType(&library);
	if (error)
	{
		fprintf(stderr, "Can't load the FreeType library!\n");
		return false;
	}

    
    char fontname[255] = {0};
	_snprintf(fontname, sizeof(fontname), "%s\\%s", backgroundPath, "SIMLI.ttf");
	FT_Face face;
	error = FT_New_Face(library, fontname, 0, &face);
	if (error)
	{
		FT_Done_FreeType(library);
		fprintf(stderr, "Can't load font => %s!\n", fontname);
		return false;
	}

	int nImgW = 36, nImgH = 48; 
	error = FT_Set_Pixel_Sizes(face, nImgW, nImgH);
	if (error)
	{
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		fprintf(stderr, "Can't set pixel size for FreeType!\n");
		return false;
	}

	unsigned char *glyphArray = new unsigned char[nImgW*nImgH];
	memset(glyphArray, 0, nImgW*nImgH);

	for (int idx = 0; idx < 4; ++idx)
	{
		FT_Int32 nflags = FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_MONO;
		error = FT_Load_Char(face, glyphWchar[index*4+idx], nflags);
		if (error)
		{
			FT_Done_Face(face);
			FT_Done_FreeType(library);
			fprintf(stderr, "Can't load the char.\n");
			return false;
		}

		FT_Glyph glyph;
		error = FT_Get_Glyph(face->glyph, &glyph);
		if (error)
		{
			FT_Done_Face(face);
			FT_Done_FreeType(library);
			fprintf(stderr, "Can't get the glyph!\n");
			return false;
		}

		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		FT_Bitmap &bitmap = bitmap_glyph->bitmap;

		int width = bitmap.width;
		int height = bitmap.rows;

		if (width > nImgW || height > nImgH)
		{
			width = clamp(width, 0, nImgW);
			height = clamp(height, 0, nImgH);
		}
		
		memset(glyphArray, 0, nImgW*nImgH);

		int nIndx = 0;
		for(int h = 0; h  < height ; ++h)
		{
			const unsigned char* src = bitmap.buffer + (h * bitmap.pitch);
			for(int w = 0; w < width; ++w)
			{
				if(src [w/8] & (0x80 >> (w & 7)))
				{
					nIndx = (w + h * nImgW);
					glyphArray[nIndx] = 255;
				}
			}
		}

		int theta, m, n;
		float sine, cosine;

		int judge = random(3);

		if (judge)
		{
			theta = rangeRandom(-30, 30);
			m = rangeRandom(-3, 3);
			n = rangeRandom(-7, 7);

		}
		else
		{
			theta = 0, m = 0, n = 0;
		}

		sine = sinf(radians(theta));
		cosine = cosf(radians(theta));

		for (int i = 0; i < nImgW; ++i)
		{
			for (int j = 0; j < nImgH; ++j)
			{
				int x, y;
				x = (int)( (i-(nImgW/2))*cosine + (j-(nImgH/2))*sine + 20) + m;
				x = clamp(x, 0, 159);
				y = (int)(-(i-(nImgW/2))*sine + (j-(nImgH/2))*cosine + 32) + n;
				y = clamp(y, 0, 47);

				background[160*y + (x+idx*40)] ^= glyphArray[nImgW*j + i];
			}
		}	
	}
	delete [] glyphArray;
	glyphArray = NULL;

	//compress
	memset(bitstream, 0, 960);
	for (int i = 0; i < 960; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (background[i*8+j])
			{
				bitstream[i] |= 1 << (7-j);
			}
		}
	}
	delete [] background;

	return true;
}

void uncompress(const unsigned char* bitstream, unsigned char* background)
{
	unsigned char charTable[256][8];

	f_Handle *tableFile;
	long int tableLen;
	int i, dist = 0;

	memset(charTable, 0, 8*256);

	tableFile = packet_namespace::w_fopen("charTable.raw", "rb");
	if (!tableFile)
	{
		printf("Can't find the charTable file!\n");
		return ;
	}

	packet_namespace::w_fseek(tableFile, 0, SEEK_END);
	tableLen = packet_namespace::w_ftell(tableFile);
	packet_namespace::w_fseek(tableFile, 0, SEEK_SET);

	packet_namespace::w_fread(charTable, sizeof(char), tableLen, tableFile);

	packet_namespace::w_fclose(tableFile);
	tableFile = NULL;

	for (i = 0; i < 960; ++i)
	{ 
		memcpy(background + dist, charTable[bitstream[i]], 8*sizeof(char)); 
		dist += 8;
	}  		
}

#pragma warning ( pop )
