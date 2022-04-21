//
//	IMAGE.h
//	Image class declaration
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	9th November 2002	-	Corrected stride for TGA textures
//									-	Split up .cpp files
//									-	Added support for paletted textures
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//

#ifndef IMAGE_H
#define IMAGE_H


#ifndef __WIN32

#include "EGLSDL/SDL.h"

typedef int LONG2;
typedef uint32_t DWORD;
typedef unsigned short WORD2;

typedef struct tagBITMAPFILEHEADER
{
    WORD2    bfType; 
    DWORD   bfSize; 
    WORD2    bfReserved1; 
    WORD2    bfReserved2; 
    DWORD   bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    DWORD    biSize;
    LONG2     biWidth;
    LONG2     biHeight;
    WORD2     biPlanes;
    WORD2     biBitCount;
    DWORD    biCompress;
    DWORD    biSizeImage;
    LONG2     biXPelsPerMeter;
    LONG2     biYPelsPerMeter;
    DWORD    biClrUsed;
    DWORD    biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;

#endif



class IMAGE
{
public:
	IMAGE()	:	data(NULL), bpp(0), width(0), height(0), stride(0),
				paletted(false), paletteBpp(0), palette(NULL)
	{}

	~IMAGE()
	{
		if(data)
			delete [] data;
		data=NULL;

		if(palette)
			delete [] palette;
		palette=NULL;
	}

	//Load image
	bool Load(char * filename);

	//Use the color indices from a paletted image as the alpha channel for this image
	bool LoadAlpha(const IMAGE & alphaImage);

protected:
	//Load BMPs
	bool LoadBMP(char * filename);
	bool Load8BitBMP(char * filename);
	bool Load24BitBMP(char * filename);

	//Load TGAs
	bool LoadTGA(char * filename);
	bool LoadUncompressed8BitTGA(char * filename);
	bool LoadUncompressedTrueColorTGA(char * filename);
	bool LoadCompressedTrueColorTGA(char * filename);

	//Calculate the number of bytes in a row, including padding bytes
	unsigned int CalculateStride(unsigned int testBpp=-1, unsigned int testWidth=-1);
	//Do not pass values to use class members

public:
	//Alter the image
	void FlipVertically(void);
	void MirrorHorizontally(void);
	void ExpandPalette(void);		//convert a paletted image into a non-paletted one
	
	unsigned int bpp;				//bits per pixel
	unsigned int width, height;		//size
	unsigned int stride;			//bytes per row, including padding bytes
	GLuint format;					//format (eg GL_RGBA)

	//Data
	GLubyte * data;
	
	//palette data (256 entries)
	bool paletted;

	unsigned int paletteBpp;
	GLuint paletteFormat;
	GLubyte * palette;
};

//Bitmap ID
const DWORD bitmapID=0x4D42;

#endif	//IMAGE_H


	


