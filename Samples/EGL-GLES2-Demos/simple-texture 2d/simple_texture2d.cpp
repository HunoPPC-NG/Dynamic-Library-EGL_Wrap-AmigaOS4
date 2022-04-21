//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//
// Simple_Texture2D.c
//
//    This is a simple example that draws a quad with a 2D
//    texture image. The purpose of this example is to demonstrate 
//    the basics of 2D texturing
//
//HunoPPC 2018
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "EGL/egl.h"
//---------------------------------------------------------------------------
   // Handle to a program object
   GLuint programObject;
   // Attribute locations
   GLint  positionLoc;
   GLint  texCoordLoc;
   // Sampler location
   GLint samplerLoc;
   // Texture handle
   GLuint textureId;

//
// Create a simple 2x2 texture image with four different colors
//
GLuint CreateSimpleTexture2D( )
{
   // Texture object handle
   GLuint textureId;
   
   // 2x2 Image, 3 bytes per pixel (R, G, B)
   GLubyte pixels[4 * 4] =
   {
      255,   0,   0, 255, // Red
        0, 255,   0, 255, // Green
        0,   0, 255, 255,// Blue
      255, 255,   0,  255// Yellow
   };
   // Use tightly packed data
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
   // Generate a texture object
   glGenTextures ( 1, &textureId );
   // Bind the texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );
   // Load the texture
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
   // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
   return textureId;
}
//
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
   //UserData *userData = esContext->userData;
   GLchar vShaderStr[] =
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
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
   programObject = esLoadProgram ( vShaderStr, fShaderStr );
   // Get the attribute locations
   positionLoc = glGetAttribLocation ( programObject, "a_position" );
   texCoordLoc = glGetAttribLocation ( programObject, "a_texCoord" );
   
   // Get the sampler location
   samplerLoc = glGetUniformLocation ( programObject, "s_texture" );
   // Load the texture
   textureId = CreateSimpleTexture2D ();
    //important!! Store the program object
    glUseProgram(programObject);
   glClearColor ( 0.5f, 0.5f, 0.5f, 0.5f );
   return TRUE;
}

//
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
   //UserData *userData = esContext->userData;
   GLfloat vVertices[] = {-0.5f,  0.5f, 0.0f, 1.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0
                           -0.5f, -0.5f, 0.0f, 1.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            0.5f, -0.5f, 0.0f, 1.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            0.5f,  0.5f, 0.0f, 1.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
};
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );
   // Use the program object
   glUseProgram ( programObject );
   // Load the vertex position
   glVertexAttribPointer ( positionLoc, 4, GL_FLOAT,
                           GL_FALSE, 6 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 6 * sizeof(GLfloat), &vVertices[4] );
   glEnableVertexAttribArray ( positionLoc );
   glEnableVertexAttribArray ( texCoordLoc );
   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, textureId );
   // Set the sampler texture unit to 0
   glUniform1i ( samplerLoc, 0 );
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
 //  eglSwapBuffers ( NULL, NULL );
}

//
// Cleanup
//
void ShutDown ( ESContext *esContext )
{
   // Delete texture object
   glDeleteTextures ( 1, &textureId );
   // Delete program object
   glDeleteProgram ( programObject );

   //shutdown context opengl-es AOS4
   esShutdown(esContext);
}

void Key ( ESContext *esContext, unsigned char key, int x, int y)
{
    //here add your action keyboard on your program
   switch ( key )
   {
   case '1':
    //  printf( "FPS Activated now !!\n" );
      // Activate FPS counter
    esActivateFPS(1);
      break;

   case '2':
     // printf( "FPS disabled now !!\n" );
      // Disable FPS counter
    esActivateFPS(0);
      break;

   case 033: // ASCII Escape Key
    //printf( "Saw an 'Escape' \n" );
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
    ShutDown(esContext);
	   break;
   }
}


int main ( int argc, char *argv[] )
{
   ESContext esContext;
  
   //activate FPS
    esActivateFPS(1);

   esInitContext (&esContext );
   
   esCreateWindow (&esContext, ("Simple Texture 2D lib EGL for Opengl-ES AmigaOS4"), 1024, 600, ES_WINDOW_ALPHA );
   
   if ( !Init (&esContext ) )
   return 0;

   // Draw function
   esRegisterDrawFunc(&esContext, Draw);

    //keyboard joystick
    esRegisterKeyFunc( &esContext, Key );

   //on a main loop
   esMainLoop ( &esContext);

   return 0;
}

