//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Rotate_image.c
//
//    This is a simple example that draws a quad with a 2D
//    texture image. The purpose of this example is to demonstrate 
//    the basics of 2D texturing
//Ported to EGL_wrap lib for OpenglES AmigaOS4 by HunoPPC 11 November 2016
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "EGL/egl.h"

BOOL debug = FALSE;




   // Handle to a program object
   GLuint programObject;

   // Attribute locations
   GLint  positionLoc;
   GLint  texCoordLoc;

   // Uniform locations
   GLint  rotateLoc;

   // Sampler location
   GLint samplerLoc;

   // Texture handle
   GLuint textureId;

   GLubyte *image;
    int width, height;

   // Rotation angle
   GLfloat   angle;

   // rotate matrix
   ESMatrix  rotateMx;


//
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
   // Load the shaders and get a linked program object
   programObject = loadShadersFiles("shaderVertex_normal.vert", "shaderFragment_normal.frag");

   // Get the attribute locations
   positionLoc = glGetAttribLocation ( programObject, "a_position" );
   texCoordLoc = glGetAttribLocation ( programObject, "a_texCoord" );
   rotateLoc = glGetUniformLocation( programObject, "u_rotateMx" );
   // Starting rotation angle for the square
   angle = 0.0f;
   
   // Get the sampler location Normal
   samplerLoc = glGetUniformLocation ( programObject, "s_texture" );

   /* Important Link the program object. */
    glLinkProgram ( programObject );

   glClearColor ( 0.2f, 0.2f, 0.5f, 0.2f );

   // Load the texture	
   textureId=esLoadPNG("1102_d.png");

   return GL_TRUE;
}

//
// Update rotate matrix based on time
//
void Update ( ESContext *esContext, float deltaTime )
{
   
   // Compute a rotation angle based on time to rotate the cube
   angle += ( deltaTime * 40.0f );
   if( angle >= 360.0f )
      angle -= 360.0f;

   // Generate an identity matrix before rotating the square
   esMatrixLoadIdentity(  &rotateMx );

   // Rotate the square
  esRotate(  &rotateMx, angle, 1.0, 0.0, 1.0 );
}


///
// Cleanup
//
void ShutDown ( ESContext *esContext )
{

     // Delete texture object Normal
   glDeleteTextures ( 1, &textureId );

   // Delete program object
   glDeleteProgram ( programObject );

   //shutdown context opengl-es AOS4
   esShutdown(esContext);
}

//
// Handle keyboard input
//
void Key ( ESContext *esContext, unsigned char key, int x, int y)
{
    //here add your action keyboard on your program
   switch ( key )
   {
   case '1':
      //printf( "FPS Activated now !!\n" );
      // Activate FPS counter
    esActivateFPS(1);
      break;

   case '2':
      //printf( "FPS disabled now !!\n" );
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

//
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
   GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f,1.0f,  // Position 0
                            0.0f,  1.0f,        // TexCoord 0
                           -0.5f, -0.5f, 0.0f,1.0f,  // Position 1
                            0.0f,  0.0f,        // TexCoord 1
                            0.5f, -0.5f, 0.0f,1.0f,  // Position 2
                            1.0f,  0.0f,        // TexCoord 2
                            0.5f,  0.5f, 0.0f,1.0f,  // Position 3
                            1.0f,  1.0f         // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
   
   glEnable(GL_CULL_FACE);

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

   // Load the rotate matrix
   glUniformMatrix4fv( rotateLoc, // userData->mvpLoc,
		       1, GL_FALSE, (GLfloat*) &rotateMx.m[0][0] );

   // Bind the texture NORMAL
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, textureId );
   glDisable(GL_TEXTURE_2D);

   // Set the sampler texture unit to 0
   glUniform1i ( samplerLoc, 0 );

   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

}


int main ( int argc, char *argv[] )
{
   ESContext esContext;

   // Activate FPS counter
    esActivateFPS(1);

   //Init context opengles
   esInitContext ( &esContext );

   esCreateWindow ( &esContext, "Rotate Image PNG lib EGL for OpenglES AmigaOS4", 1024, 800, ES_WINDOW_ALPHA );

   if ( !Init ( &esContext ) )
      return 0;

   //Draw function
   esRegisterDrawFunc ( &esContext, Draw );

   //update function
   esRegisterUpdateFunc ( &esContext, Update );

   //keyboard joystick
   esRegisterKeyFunc( &esContext, Key );

   //main loop
   esMainLoop ( &esContext);

   return 0;
}
