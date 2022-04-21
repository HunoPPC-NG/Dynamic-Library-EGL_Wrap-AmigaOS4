//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Hello_TriangleColour.c
//
//    This is a simple example that draws a single triangle with
//    a minimal vertex/fragment shader.  The purpose of this 
//    example is to demonstrate the basic concepts of 
//    OpenGL ES 2.0 rendering.
//HunoPPC 2018
#include <stdlib.h>
#include <stdio.h>
#include "EGL/egl.h"


   // Handle to a program object
   GLuint programObject;


//
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint LoadShader ( GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;
   
   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderSrc, NULL );
   
   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled ) 
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog = (char*)malloc (sizeof(char) * infoLen );

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         printf ( "Error compiling shader:\n%s\n", infoLog );
         
         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}

//
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
  // esContext->userData = malloc(sizeof(UserData));

   //UserData *userData = esContext->userData;
   GLchar vShaderStr[] =
      "attribute vec4 vPosition;    \n"
      "attribute vec4 vColour;      \n"
      "varying vec4 vFragmentColour;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = vPosition;  \n"
      "   vFragmentColour = vColour;\n"
      "}                            \n";
   
   GLchar fShaderStr[] =
      "precision mediump float;\n"
      "varying vec4 vFragmentColour;     \n"
      "void main()                                  \n"
      "{                                            \n"
      "  gl_FragColor = vFragmentColour;\n"
      "}                                            \n";

   GLuint vertexShader;
   GLuint fragmentShader;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
   fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );

   // Create the program object
   programObject = glCreateProgram ( );
   
   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

   // Bind vPosition to attribute 0   
   glBindAttribLocation ( programObject, 0, "vPosition" );

   // Bind vColour to attribute 1
   glBindAttribLocation ( programObject, 1, "vColour" );

   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked ) 
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog = (char*)malloc (sizeof(char) * infoLen );

         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         printf ( "Error linking program:\n%s\n", infoLog );
         
         free ( infoLog );
      }

      glDeleteProgram ( programObject );
      return GL_FALSE;
   }

   //important!! Store the program object
    glUseProgram(programObject);

   glClearColor ( 0.5f, 0.5f, 0.5f, 0.5f );
   return GL_TRUE;
}

//
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
       GLfloat vVertices[] =
//here by default one error
//{ 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f }; //ORIGINAL
  { 0.0f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 1.0f }; // FIX: this was an array of vec3 (three). But your shader wants a vec4 (four)!!!
   GLfloat vColours[] = {1.0f, 0.0f, 0.0f, 1.0f,
			 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f, 1.0f};
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( programObject );

   // Load the vertex data
   glVertexAttribPointer ( 0, 4, GL_FLOAT, GL_FALSE, 0, vVertices );
   glEnableVertexAttribArray ( 0 );
   glVertexAttribPointer ( 1, 4, GL_FLOAT, GL_FALSE, 0, vColours );
   glEnableVertexAttribArray ( 1 );

   glDrawArrays ( GL_TRIANGLES, 0, 3 );
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
     // printf( "FPS disabled now !!\n" );
      // Disable FPS counter
    esActivateFPS(0);
      break;

   case 033: // ASCII Escape Key
   // printf( "Saw an 'Escape' \n" );
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
    esShutdown(esContext);
	   break;
   }
}


int main ( int argc, char *argv[] )
{
   ESContext esContext;

   //activate FPS
    esActivateFPS(1);

   esInitContext ( &esContext );

   esCreateWindow ( &esContext, "Hello Triangle color lib EGL for Opengl-ES AmigaOS4", 1024, 600, ES_WINDOW_ALPHA );

   if ( !Init ( &esContext ) )
      return 0;

   // Draw function
   esRegisterDrawFunc ( &esContext, Draw );

   //keyboard joystick
    esRegisterKeyFunc( &esContext, Key );

   //on a main loop
   esMainLoop ( &esContext);

   return 0;
}
