//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// MipMap2D.c
//
//    This is a simple example that demonstrates generating a mipmap chain
//    and rendering with it
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "EGL/egl.h"

    // Handle to a program object
    GLuint programObject;

    // Attribute locations
    GLint positionLoc;
    GLint texCoordLoc;

    // Sampler location
    GLint samplerLoc;

    // Offset location
    GLint offsetLoc;

    // Texture handle
    GLuint textureId;


//
//  From an RGB8 source image, generate the next level mipmap
//
GLboolean GenMipMap2D(GLubyte *src, GLubyte **dst, int srcWidth, int srcHeight, int *dstWidth, int *dstHeight)
{
 int x, y;
    int texelSize = 4;

    *dstWidth = srcWidth / 2;
    if (*dstWidth <= 0)
        *dstWidth = 1;

    *dstHeight = srcHeight / 2;
    if (*dstHeight <= 0)
        *dstHeight = 1;

    *dst = (GLubyte*)malloc(sizeof(GLubyte) * texelSize * (*dstWidth) * (*dstHeight));
    if (*dst == NULL)
        return GL_FALSE;

    for (y = 0; y < *dstHeight; y++)
    {
        for (x = 0; x < *dstWidth; x++)
        {
            int srcIndex[4];
            float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
            int sample;

            // Compute the offsets for 2x2 grid of pixels in previous
            // image to perform box filter
            srcIndex[0] = (((y * 2) * srcWidth) + (x * 2)) * texelSize;
            srcIndex[1] = (((y * 2) * srcWidth) + (x * 2 + 1)) * texelSize;
            srcIndex[2] = ((((y * 2) + 1) * srcWidth) + (x * 2)) * texelSize;
            srcIndex[3] = ((((y * 2) + 1) * srcWidth) + (x * 2 + 1)) * texelSize;

            // Sum all pixels
            for (sample = 0; sample < 4; sample++)
            {
                r += src[srcIndex[sample]];
                g += src[srcIndex[sample] + 1];
                b += src[srcIndex[sample] + 2];
                a += src[srcIndex[sample] + 3];
            }

            // Average results
            r /= 4.0;
            g /= 4.0;
            b /= 4.0;
            a /= 4.0f;

            // Store resulting pixels
            (*dst)[(y * (*dstWidth) + x) * texelSize] = (GLubyte)(r);
            (*dst)[(y * (*dstWidth) + x) * texelSize + 1] = (GLubyte)(g);
            (*dst)[(y * (*dstWidth) + x) * texelSize + 2] = (GLubyte)(b);
            (*dst)[(y * (*dstWidth) + x) * texelSize + 3] = (GLubyte)(a);
        }
    }
    return GL_TRUE;
}

//
//  Generate an RGB8 checkerboard image
//
GLubyte* GenCheckImage(int width, int height, int checkSize)
{
    int x, y;
    GLubyte *pixels = (GLubyte *)malloc(width * height * 4);

    if (pixels == NULL)
        return NULL;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            GLubyte rColor = 0;
            GLubyte bColor = 0;

            if ((x / checkSize) % 2 == 0)
            {
                rColor = 255 * ((y / checkSize) % 2);
                bColor = 255 * (1 - ((y / checkSize) % 2));
            }
            else
            {
                bColor = 255 * ((y / checkSize) % 2);
                rColor = 255 * (1 - ((y / checkSize) % 2));
            }

            pixels[(y * height + x) * 4] = rColor;
            pixels[(y * height + x) * 4 + 1] = 0;
            pixels[(y * height + x) * 4 + 2] = bColor;
            pixels[(y * height + x) * 4 + 3] = 0;
        }
    }

    return pixels;
}

//
// Create a mipmapped 2D texture image
//
GLuint CreateMipMappedTexture2D()
{
    // Texture object handle
    GLuint textureId;
    int width = 256, height = 256;
    int level;
    GLubyte *pixels;
    GLubyte *prevImage;
    GLubyte *newImage = NULL;

    pixels = GenCheckImage(width, height, 8);
    if (pixels == NULL)
        return 0;

    // Generate a texture object
    glGenTextures(1, &textureId);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Load mipmap level 0
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    level = 1;
    prevImage = &pixels[0];

    while (width > 1 && height > 1)
    {
        int newWidth, newHeight;

        // Generate the next mipmap level
        GenMipMap2D(prevImage, &newImage, width, height, &newWidth, &newHeight);

        // Load the mipmap level
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, newWidth, newHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, newImage);

        // Free the previous image
        free(prevImage);

        // Set the previous image for the next iteration
        prevImage = newImage;
        level++;

        // Half the width and height
        width = newWidth;
        height = newHeight;
    }

    free(newImage);

    // Set the filtering mode
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
             glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
              glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
              glGenerateMipmap(GL_TEXTURE_2D);

    return textureId;
}


//
// Initialize the shader and program object
//
int Init(ESContext *esContext)
{
   // UserData *userData = esContext->userData;
    GLchar vShaderStr[] =
        "uniform float u_offset;      \n"
        "attribute vec4 a_position;   \n"
        "attribute vec2 a_texCoord;   \n"
        "varying vec2 v_texCoord;     \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = a_position; \n"
        "   gl_Position.x += u_offset;\n"
        "   v_texCoord = a_texCoord;  \n"
        "}                            \n";

    GLchar fShaderStr[] =
        "precision mediump float;                            \n"
        "varying vec2 v_texCoord;                            \n"
        "uniform sampler2D s_texture;                        \n"
        "void main()                                         \n"
        "{                                                   \n"
        "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
        "}                                                   \n";

    // Load the shaders and get a linked program object
    programObject = esLoadProgram(vShaderStr, fShaderStr);

    // Get the attribute locations
    positionLoc = glGetAttribLocation(programObject, "a_position");
    texCoordLoc = glGetAttribLocation(programObject, "a_texCoord");

    // Get the sampler location
    samplerLoc = glGetUniformLocation(programObject, "s_texture");

    // Get the offset location
    offsetLoc = glGetUniformLocation(programObject, "u_offset");

    /* Important Link the program object. */
    glLinkProgram ( programObject );

    // Load the texture
    textureId = CreateMipMappedTexture2D();

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    return TRUE;
}

//
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext)
{
   // UserData *userData = esContext->userData;
    GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f, 1.5f,  // Position 0
                            0.0f,  0.0f,              // TexCoord 0
                           -0.5f, -0.5f, 0.0f, 0.75f, // Position 1
                            0.0f,  1.0f,              // TexCoord 1
                            0.5f, -0.5f, 0.0f, 0.75f, // Position 2
                            1.0f,  1.0f,              // TexCoord 2
                            0.5f,  0.5f, 0.0f, 1.5f,  // Position 3
                            1.0f,  0.0f               // TexCoord 3
                         };
    GLushort indices[] =
    { 0, 1, 2, 0, 2, 3 };

    // Set the viewport
   glViewport(0, 0, esContext->width, esContext->height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(programObject);

    // Load the vertex position
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &vVertices[4]);

    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set the sampler texture unit to 0
    glUniform1i(samplerLoc, 0);

    // Draw quad with nearest sampling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glUniform1f(offsetLoc, -0.6f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    // Draw quad with trilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glUniform1f(offsetLoc, 0.6f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    //eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}


//
// Cleanup
//
void ShutDown(ESContext *esContext)
{

    // Delete texture object
    glDeleteTextures(1, &textureId);

    // Delete program object
    glDeleteProgram(programObject);
}

void Key ( ESContext *esContext, unsigned char key, int x, int y)
{
    //here add your action keyboard on your program
   switch ( key )
   {
   case 'm':
      printf( "Saw an 'm'\n" );
      break;

   case 'a':
      printf( "Saw an 'a'\n" );
      break;

   case '1':
      printf( "FPS Activated now !!\n" );
      // Activate FPS counter
    esActivateFPS(1);
      break;

   case '2':
      printf( "FPS disabled now !!\n" );
      // Disable FPS counter
    esActivateFPS(0);
      break;

   case 033: // ASCII Escape Key
    printf( "Saw an 'Escape' \n" );
    //cleanup your program
    ShutDown(esContext);
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
    esShutdown(esContext);
	   break;
   }
}


int main(int argc, char *argv[])
{
    ESContext esContext;
 //   UserData userData;

  //activate FPS
    esActivateFPS(1);

    esInitContext(&esContext);
    //esContext.userData = &userData;

    esCreateWindow(&esContext, "MipMap 2D lib EGL for Opengl-ES AmigaOS4", 1024, 600, ES_WINDOW_RGB);

    if (!Init(&esContext))
        return 0;

     // Draw function
     esRegisterDrawFunc(&esContext, Draw);

           //keyboard joystick
    esRegisterKeyFunc( &esContext, Key );

   esMainLoop ( &esContext);

    return 0;
}
