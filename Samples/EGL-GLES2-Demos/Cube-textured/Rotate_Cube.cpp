//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Rotate_Cube_Textured.c
//
//    This is a simple example that draws a cube with texture
//    texture image. The purpose of this example is to demonstrate 
//    the basics of 2D texturing
//Ported to EGL_wrap lib for OpenglES AmigaOS4 by HunoPPC 2018
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

   GLuint vbo1;

   GLuint vbo2;


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

   glClearColor ( 0.6f, 0.5f, 0.5f, 0.5f );

   // Load the texture	
   textureId=esLoadPNG("text1.png");

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

     // Delete texture object
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
    int numVertices = 24;//24
    int numIndices = 36;//36

    GLfloat cubeVerts2[] =
    {
		//1
        -0.5f, -0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f,
		//2
        -0.5f,  0.5f, -0.5f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f,
		//3
        -0.5f, -0.5f, -0.5f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f,
		//4
        -0.5f, -0.5f, 0.5f, 1.0f,
        -0.5f,  0.5f, 0.5f, 1.0f,
        0.5f,  0.5f, 0.5f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f,
		//5
        -0.5f, -0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f,
		//6
        0.5f, -0.5f, -0.5f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f,
		// 24 VERTICES

    };

    GLfloat cubeNormals2[] =
    {
		//1
        0.0f, -1.0f, 0.0f, 1.0f,
        0.0f, -1.0f, 0.0f, 1.0f,
        0.0f, -1.0f, 0.0f, 1.0f,
        0.0f, -1.0f, 0.0f, 1.0f,
		//2
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        //3
		0.0f, 0.0f, -1.0f, 1.0f,
        0.0f, 0.0f, -1.0f, 1.0f,
        0.0f, 0.0f, -1.0f, 1.0f,
        0.0f, 0.0f, -1.0f, 1.0f,
        //4
		0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        //5
		-1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f, 1.0f,
        //6
		1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
		//24 VERTICES
    };

    GLfloat cubeTex2[] =
    {
		//1
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
		//2
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
		//3
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
		//4
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
		//5
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
		//6
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };

     GLushort cubeIndices[] =
        {
            0, 2, 1, //1
            0, 3, 2, //2
            4, 5, 6, //3
            4, 6, 7, //4
            8, 9, 10, //5
            8, 10, 11, //6
            12, 15, 14, //7
            12, 14, 13, //8
            16, 17, 18, //9
            16, 18, 19, //10
            20, 23, 22, //11
            20, 22, 21 //12
			//12 X 3 + + 36 INDICES
        };


    // Enable depth test
   glEnable(GL_DEPTH_TEST);

   // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

   // Clear the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Use the program object
   glUseProgram ( programObject );

  // vbo1 = esCreate_VBO(sizeof(cubeVerts2), cubeVerts2,GL_STATIC_DRAW);

 //  vbo2 = esCreate_VBO(sizeof(cubeIndices), cubeIndices,GL_STATIC_DRAW);

  

   // Load the vertex position
   glVertexAttribPointer ( positionLoc, 4, GL_FLOAT,
                           GL_FALSE, 4 * sizeof(GLfloat), cubeVerts2 );
   // Load the texture coordinate
   glVertexAttribPointer ( texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 2 * sizeof(GLfloat), cubeTex2 );

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

   glDrawArrays(GL_TRIANGLES, 0, numVertices);

  glDrawElements ( GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, cubeIndices );


}


int main ( int argc, char *argv[] )
{
   ESContext esContext;

   // Activate FPS counter
    esActivateFPS(1);

   //Init context opengles
   esInitContext ( &esContext );

   esCreateWindow ( &esContext, "Rotate Cube with texture PNG with lib EGL for OpenglES AmigaOS4", 800, 600, ES_WINDOW_ALPHA );

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
