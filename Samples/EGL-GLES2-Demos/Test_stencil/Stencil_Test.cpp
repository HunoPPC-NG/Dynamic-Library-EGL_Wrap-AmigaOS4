//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Stencil_Test.c
//
//    This example shows various stencil buffer
//    operations.
//
#include <stdlib.h>
#include <stdio.h>
#include "EGL/egl.h" 

   // Handle to a program object
   GLuint programObject;

   // Attribute locations
   GLint  positionLoc;

   // Uniform locations
   GLint  colorLoc;


///
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
   GLchar vShaderStr[] =  
      "attribute vec4 a_position;   \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "}                            \n";
   
   GLchar fShaderStr[] =  
      "precision mediump float;  \n"
      "uniform vec4  u_color;    \n"
      "void main()               \n"
      "{                         \n"
      "  gl_FragColor = u_color; \n"
      "}                         \n";

   // Load the shaders and get a linked program object
   programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   positionLoc = glGetAttribLocation ( programObject, "a_position" );
   
   // Get the sampler location
   colorLoc = glGetUniformLocation ( programObject, "u_color" );

   // Set the clear color
   glClearColor ( 0.5f, 0.5f, 0.5f, 0.5f );
   
   // Set the stencil clear value
   glClearStencil ( 0x1 );

   // Set the depth clear value
   glClearDepthf( 0.75f );

   // Enable the depth and stencil tests
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_STENCIL_TEST );


   return TRUE;
}

///
// Initialize the stencil buffer values, and then use those
//   values to control rendering
//
void Draw ( ESContext *esContext )
{
   int  i;

   GLfloat vVertices[] = { 
       -0.75f,  0.25f,  0.50f, 1.0f,// Quad #0
       -0.25f,  0.25f,  0.50f, 1.0f,
       -0.25f,  0.75f,  0.50f, 1.0f,
       -0.75f,  0.75f,  0.50f, 1.0f,
	    0.25f,  0.25f,  0.90f, 1.0f,// Quad #1
		0.75f,  0.25f,  0.90f, 1.0f,
		0.75f,  0.75f,  0.90f, 1.0f,
		0.25f,  0.75f,  0.90f, 1.0f,
	   -0.75f, -0.75f,  0.50f, 1.0f,// Quad #2
       -0.25f, -0.75f,  0.50f, 1.0f,
       -0.25f, -0.25f,  0.50f, 1.0f,
       -0.75f, -0.25f,  0.50f, 1.0f,
        0.25f, -0.75f,  0.50f, 1.0f,// Quad #3
        0.75f, -0.75f,  0.50f, 1.0f,
        0.75f, -0.25f,  0.50f, 1.0f,
        0.25f, -0.25f,  0.50f, 1.0f,
       -1.00f, -1.00f,  0.00f, 1.0f,// Big Quad
        1.00f, -1.00f,  0.00f, 1.0f,
        1.00f,  1.00f,  0.00f, 1.0f,
       -1.00f,  1.00f,  0.00f,  1.0f,
   };

   GLubyte indices[][6] = { 
       {  0,  1,  2,  0,  2,  3 }, // Quad #0
       {  4,  5,  6,  4,  6,  7 }, // Quad #1
       {  8,  9, 10,  8, 10, 11 }, // Quad #2
       { 12, 13, 14, 12, 14, 15 }, // Quad #3
       { 16, 17, 18, 16, 18, 19 }  // Big Quad
   };
   
#define NumTests  4
   GLfloat  colors[NumTests][4] = { 
       { 1.0f, 0.0f, 0.0f, 1.0f },
       { 0.0f, 1.0f, 0.0f, 1.0f },
       { 0.0f, 0.0f, 1.0f, 1.0f },
       { 1.0f, 1.0f, 0.0f, 0.0f }
   };

   GLint   numStencilBits;
   GLuint  stencilValues[NumTests] = { 
      0x7, // Result of test 0
      0x0, // Result of test 1
      0x2, // Result of test 2
      0xff // Result of test 3.  We need to fill this
           //  value in a run-time
   };
   
   // Clear the color, depth, and stencil buffers.  At this
   //   point, the stencil buffer will be 0x1 for all pixels
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

   // Use the program object
   glUseProgram ( programObject );

   // Load the vertex position
   glVertexAttribPointer ( positionLoc, 4, GL_FLOAT,
                           GL_FALSE, 0, vVertices );
  
   glEnableVertexAttribArray ( positionLoc );

   // Test 0:
   //
   // Initialize upper-left region.  In this case, the
   //   stencil-buffer values will be replaced because the
   //   stencil test for the rendered pixels will fail the
   //   stencil test, which is
   //
   //        ref   mask   stencil  mask
   //      ( 0x7 & 0x3 ) < ( 0x1 & 0x7 )
   //
   //   The value in the stencil buffer for these pixels will
   //   be 0x7.
   //
   glStencilFunc( GL_LESS, 0x7, 0x3 );
   glStencilOp( GL_REPLACE, GL_DECR, GL_DECR );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[0] );
 
   // Test 1:
   //
   // Initialize the upper-right region.  Here, we'll decrement
   //   the stencil-buffer values where the stencil test passes
   //   but the depth test fails.  The stencil test is
   //
   //        ref  mask    stencil  mask
   //      ( 0x3 & 0x3 ) > ( 0x1 & 0x3 )
   //
   //    but where the geometry fails the depth test.  The
   //    stencil values for these pixels will be 0x0.
   //
   glStencilFunc( GL_GREATER, 0x3, 0x3 );
   glStencilOp( GL_KEEP, GL_DECR, GL_KEEP );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[1] );

   // Test 2:
   //
   // Initialize the lower-left region.  Here we'll increment 
   //   (with saturation) the stencil value where both the
   //   stencil and depth tests pass.  The stencil test for
   //   these pixels will be
   //
   //        ref  mask     stencil  mask
   //      ( 0x1 & 0x3 ) == ( 0x1 & 0x3 )
   //
   //   The stencil values for these pixels will be 0x2.
   //
   glStencilFunc( GL_EQUAL, 0x1, 0x3 );
   glStencilOp( GL_KEEP, GL_INCR, GL_INCR );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[2] );

   // Test 3:
   //
   // Finally, initialize the lower-right region.  We'll invert
   //   the stencil value where the stencil tests fails.  The
   //   stencil test for these pixels will be
   //
   //        ref   mask    stencil  mask
   //      ( 0x2 & 0x1 ) == ( 0x1 & 0x1 )
   //
   //   The stencil value here will be set to ~((2^s-1) & 0x1),
   //   (with the 0x1 being from the stencil clear value),
   //   where 's' is the number of bits in the stencil buffer
   //
   glStencilFunc( GL_EQUAL, 0x2, 0x1 );
   glStencilOp( GL_INVERT, GL_KEEP, GL_KEEP );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[3] );
   
   // Since we don't know at compile time how many stecil bits are present,
   //   we'll query, and update the value correct value in the
   //   stencilValues arrays for the fourth tests.  We'll use this value
   //   later in rendering.
   glGetIntegerv( GL_STENCIL_BITS, &numStencilBits );
   
   stencilValues[3] = ~(((1 << numStencilBits) - 1) & 0x1) & 0xff;

     // Save stencil mask
    GLint stencilMask;
    glGetIntegerv(GL_STENCIL_WRITEMASK, &stencilMask);

   // Use the stencil buffer for controlling where rendering will
   //   occur.  We diable writing to the stencil buffer so we
   //   can test against them without modifying the values we
   //   generated.
   glStencilMask( 0x0 );
   
   for ( i = 0; i < NumTests; ++i )
   {
      glStencilFunc( GL_EQUAL, stencilValues[i], 0xff );
      glUniform4fv( colorLoc, 1, colors[i] );
      glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[4] );
   }

 // Restore stencil mask
    glStencilMask(stencilMask);

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
   switch ( key )
   {
   case '1':
     // printf( "FPS Activated now !!\n" );
      // Activate FPS counter
    esActivateFPS(1);
      break;

   case '2':
     // printf( "FPS disabled now !!\n" );
      // Disable FPS counter
    esActivateFPS(0);
      break;

   case 033: // ASCII Escape Key
       //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
	   ShutDown( esContext );
	   break;
   }
}



int main ( int argc, char *argv[] )
{
   ESContext esContext;
   
   //activate FPS
   esActivateFPS(1);

   esInitContext ( &esContext );

   esCreateWindow ( &esContext, "Stencil Test lib EGL for OpenGL-ES AmigaOS4", 800, 600,
                    ES_WINDOW_ALPHA | ES_WINDOW_DEPTH | ES_WINDOW_STENCIL );
   
   if ( !Init ( &esContext ) )
      return 0;

   // Draw function
   esRegisterDrawFunc ( &esContext, Draw );
   //keyboard joystick
   esRegisterKeyFunc( &esContext, Key );
   //on a main loop
   esMainLoop ( &esContext );

   return 0;
}
