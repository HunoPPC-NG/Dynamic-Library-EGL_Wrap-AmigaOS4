/* SDL_oglblit - An OpenGL blitter for SDL
 * 
 * See doc/license.txt for license information (GPLv3)
 * 
 * Authors: 
 * 	Fredrik Hultin, noname@ the domain two lines below, 2008
 *
 * http://nurd.se/~noname/sdl_oglblit
 */

/* SDL_oglblit.h
 *
 * This file contains all declarations needed to write an application using SDL_oglblit.
 * See the SDL_oglblit documentation for better descriptions of the functions.
 * */

#ifndef SDL_OGLBLIT_H
#define SDL_OGLBLIT_H

#include <EGLSDL/SDL.h>
#include <EGLSDL/SDL_opengl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The OGL_Texture structure */
typedef struct
{
	GLuint name;		/* OpenGL texture name (texture id) */
	GLenum format;		/* The color format of the texture */
	int w, h;		/* The width and height of the original surface */
	int wTex, hTex;		/* The actual size of the OpenGL texture (it might differ, power of two etc.) */
} OGL_Texture;

/* Initializes SDL with OpenGL with the given width, height, color depth and flags */
int OGL_Init(int w, int h, int bpp, Uint32 flags);

/* Frees a OGL_Texture structure created with OGL_FromSurface */
void OGL_FreeTexture(OGL_Texture* texture);

/* Flips the OpenGL buffers, updates the screen */
void OGL_Flip();

/* Clears the screen */
void OGL_Clear();

/* Blits an OGL_Texture to the screen */
void OGL_Blit(OGL_Texture* texture, SDL_Rect* clipping, int x, int y, GLfloat vZoom, GLfloat hZoom, GLfloat rotation);

/* Creates an OGL_Texture from an SDL_Surface */
OGL_Texture* OGL_FromSurface(SDL_Surface* surface);

/* Creates an OGL_Texture from an SDL_Surface and frees the SDL_Surface*/
OGL_Texture* OGL_FromSurfaceFree(SDL_Surface* surface);

#ifdef __cplusplus
}
#endif

#endif
