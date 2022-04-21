//first egl demo with lib egl_wrap by HunoPPC 2017
#include <stdio.h>
#include <string.h>
#include "texture.h"
//---------------------------------------------------------------------------
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
//---------------------------------------------------------------------------
extern OGLES2IFace *IOGLES2;
//---------------------------------------------------------------------------
void SaveTGA(const char *p_file_name,unsigned int width,unsigned int height,unsigned int *tex_data)
{
  // save to TGA
	const unsigned char	static_header[12]={1,0,2,0,0,0,0,0,0,0,0,0};
  struct dyn_header {
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char padding1;
    unsigned char padding2;
    unsigned char padding3;
  };
  dyn_header header;
  header.width=((width>>8) | (width<<8));
  header.height=((height>>8) | (height<<8));
  header.bpp=32;
  header.padding1=0;
  header.padding2=0;
  const unsigned int l_file_size=sizeof(static_header)+7+(width*height)*4;
  unsigned char *tga=new unsigned char[l_file_size];
  memcpy(&tga[0],static_header,sizeof(static_header));
  memcpy(&tga[sizeof(static_header)],&header,7);
  unsigned char *dst=&tga[sizeof(static_header)+7];
  for(unsigned int y=0;y<height;++y) {
    const unsigned char *src=(const unsigned char*)&tex_data[y*width]; // no need to turn upside down, glRead already delivers it upside down
    for(unsigned int x=0;x<width;++x) {
      dst[0]=src[2];
      dst[1]=src[1];
      dst[2]=src[0];
      dst[3]=src[3];
      dst+=4;
      src+=4;
    }
  }
	FILE *fp=fopen(p_file_name,"wb");
	if(fp) {
    fwrite(tga,l_file_size,1,fp);
		fclose(fp);
	}
	delete[] tga;
}
//---------------------------------------------------------------------------
