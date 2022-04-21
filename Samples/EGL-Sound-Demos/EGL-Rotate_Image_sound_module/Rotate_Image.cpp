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
//Ported to EGL_wrap lib for OpenglES AmigaOS4 by HunoPPC 11 November 2018
//
#include <stdlib.h>
#include <stdio.h>
#include "EGL/egl.h"

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

unsigned int frame_counter=0;

//
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
   // UserData *userData = esContext->userData;
    GLchar vShaderStr[] = 
      "uniform mat4 u_rotateMx;  \n" 
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = u_rotateMx * a_position; \n"
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
   rotateLoc = glGetUniformLocation( programObject, "u_rotateMx" );
   // Starting rotation angle for the square
   angle = 0.0f;
   
   // Get the sampler location
   samplerLoc = glGetUniformLocation ( programObject, "s_texture" );

   /* Important Link the program object. */
    glLinkProgram ( programObject );

   glClearColor ( 0.3f, 0.5f, 0.5f, 0.5f );

   // Load the texture	
   textureId=esLoadPNG("texturemap.png");

   return GL_TRUE;
}

//
// Update rotate matrix based on time
//
void Update ( ESContext *esContext, float deltaTime )
{
   
   // Compute a rotation angle based on time to rotate the image
   angle += ( deltaTime * 40.0f );
   if( angle >= 360.0f )
      angle -= 360.0f;

   // Generate an identity matrix before rotating the square
   esMatrixLoadIdentity(  &rotateMx );

	if(frame_counter & 2048*2) {
     //2
  	// Rotate the square
   esRotate(  &rotateMx, angle, 3.0, 0.0, 1.0 );
  } else if(frame_counter & 4096*2) {
    //3
  	// Rotate the square
   esRotate(  &rotateMx, angle, 3.0, 0.0, 1.0 );
  } else if(frame_counter & 16384*2) {
    //4
  	// Rotate the square
   esRotate(  &rotateMx, angle, 1.0, 0.0, 2.0 );
  }else if(frame_counter & 32768*2){
    //5
    // Rotate the square
   esRotate(  &rotateMx, angle, 1.0, 0.0, 2.0 );
  }else if(frame_counter & 65536*2){
    //6
    // Rotate the square
   esRotate(  &rotateMx, angle, 2.0, 0.0, 1.0 );
  }else if(frame_counter & 131072*2){
  //reset counter
    frame_counter = 0;
  }else{
  //1
   // Rotate the square
   esRotate(  &rotateMx, angle, 1.0, 2.0, 1.0 );
  }
++frame_counter;
}


///
// Cleanup
//
void ShutDown ( ESContext *esContext )
{

     // Delete texture object
   glDeleteTextures ( 1, &textureId );

   // Delete program object
   glDeleteProgram ( programObject );

   //Stop sound engine
   esStopSound_MOD_file("Hoffman_Drop_The_Panic.mod");

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

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, textureId );

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

   esCreateWindow ( &esContext, "Rotate Image PNG with internal Music Module, EGL for OpenglES AmigaOS4", 1024, 800, ES_WINDOW_ALPHA );

   if ( !Init ( &esContext ) )
      return 0;

   //Activate sound and load music MODULE
   esRunSound_MOD_file("Hoffman_Drop_The_Panic.mod");

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
