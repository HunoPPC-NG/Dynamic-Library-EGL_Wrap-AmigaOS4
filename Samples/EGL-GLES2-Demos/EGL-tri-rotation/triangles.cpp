/*
 * Book:      OpenGL(R) ES 2.0 Programming Guide
 * Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
 * ISBN-10:   0321502795
 * ISBN-13:   9780321502797
 * Publisher: Addison-Wesley Professional
 * URLs:      http: *safari.informit.com/9780321563835
 *            http: *www.opengles-book.com
 */

/*
 * triangles.c
 *
 * This is a simple example that draws a single triangle with a
 * minimal vertex/fragment shader.  The purpose of this example is to
 * demonstrate the basic concepts of OpenGL ES 2.0 rendering.
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "EGL/egl.h"

    /* Handle to a program object. */
    GLuint programObject;

    /* Angle of rotation. */
    float rotationAngle;

  /* Create and load a rotation matrix uniform. */
   ESMatrix rotationMatrix;
  // Attribute locations
   GLint  positionLoc;
   GLint  texCoordLoc;

   // Uniform locations
   GLint  rotateLoc;

unsigned int frame_counter=0;

/* Initialize the shader and program object. */
int init(ESContext *esContext)
{

    const char *vShaderStr =
        "uniform mat4 u_mvpMatrix;    \n"
        "attribute vec4 a_position;   \n"
        "attribute vec4 a_color;      \n"
        "varying vec4 v_color;        \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = u_mvpMatrix * a_position; \n"
        "   v_color = a_color;        \n"
        "}                            \n";
   
    const char *fShaderStr =
        "precision mediump float;                     \n"
        "varying vec4 v_color;                        \n"
        "void main()                                  \n"
        "{                                            \n"
        "  gl_FragColor = v_color;                    \n"
        "}                                            \n";

    // Load the shaders and get a linked program object
    programObject = esLoadProgram ( vShaderStr, fShaderStr );

    /* Bind artributes. */
    positionLoc = glGetAttribLocation(programObject, "a_position");
    texCoordLoc = glGetAttribLocation(programObject, "a_color");
    rotateLoc = glGetUniformLocation( programObject, "u_mvpMatrix" );

    // Starting rotation angle for the triangle
    rotationAngle =  0.0f;

    /* Important Link the program object. */
    glLinkProgram ( programObject );

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    return GL_TRUE;
}

/* Update the state. */
void update(ESContext *esContext, float deltaTime)
{
    rotationAngle += (32.0 * M_PI * deltaTime);
    if( rotationAngle >= 360.0f )
      rotationAngle -= 360.0f;
    
    esMatrixLoadIdentity(&rotationMatrix);
    	if(frame_counter & 2048) {
     //2
  	esRotate(&rotationMatrix, rotationAngle, 0.0f, 0.0f, 1.0f);
  } else if(frame_counter & 4096) {
    //3
  	esRotate(&rotationMatrix, rotationAngle, 1.0f, 0.0f, 0.0f);
  } else if(frame_counter & 16384) {
    //4
  	esRotate(&rotationMatrix, rotationAngle, 1.0f, 0.0f, 1.0f);
  }else if(frame_counter & 32768){
    //5
    esRotate(&rotationMatrix, rotationAngle, 0.0f, 1.0f, 1.0f);
  }else if(frame_counter & 65536){
    //6
    esRotate(&rotationMatrix, rotationAngle, 1.0f, 1.0f, 1.0f);
  }else if(frame_counter & 131072){
  //reset counter
    frame_counter = 0;
  }else{
  //1
   esRotate(&rotationMatrix, rotationAngle, 0.0f, 1.0f, 0.0f);
  }
++frame_counter;
}

///
// Cleanup
//
void ShutDown ( ESContext *esContext )
{

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
   case 'm':
      //printf( "Saw an 'm'\n" );
      break;

   case 'a':
      //printf( "Saw an 'a'\n" );
      break;

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


/* Draw a triangle using the shader pair created in Init() */
void draw(ESContext *esContext)
{
    static GLfloat vertices[] = {0.0f,  0.5f, 0.0f,1.0f,
                                 -0.5f, -0.5f, 0.0f, 1.0f,
                                 0.5f, -0.5f, 0.0f, 1.0f};

    static GLfloat colors[] = {1.0f, 0.0f, 0.0f, 1.0f,
                               0.0f, 1.0f, 0.0f, 1.0f, 
                               0.0f, 0.0f, 1.0f, 1.0f};
   
    /* Clear the color buffer. */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Use the program object. */
    glUseProgram(programObject);

    /* Load the vertex and color data. */
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(texCoordLoc, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(texCoordLoc);


    glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, (GLfloat*) &rotationMatrix.m[0]);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char *argv[])
{
    ESContext esContext;

    //activate FPS
    esActivateFPS(1);

    esInitContext(&esContext);

    esCreateWindow(&esContext, "Hello Triangle powered by EGL_WRAP for OpenglES AOS4", 800, 600, ES_WINDOW_ALPHA);

    if (!init(&esContext)) {
        return EXIT_FAILURE;
    }

       // Draw function
    esRegisterDrawFunc(&esContext, draw);

    //update function
    esRegisterUpdateFunc(&esContext, update);

    //keyboard joystick
    esRegisterKeyFunc( &esContext, Key );

    //main loop
    esMainLoop(&esContext);

    return EXIT_SUCCESS;
}
