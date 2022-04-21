//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// MultiTexture.c
//
//    This is an example that draws a quad with a basemap and
//    lightmap to demonstrate multitexturing.
//
//HunoPPC 2018
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EGL/egl.h"
    // Handle to a program object
    GLuint programObject;

    // Attribute locations
    GLint positionLoc;
    GLint texCoordLoc;

    // Sampler locations
    GLint baseMapLoc;
    GLint lightMapLoc;

    // Texture handle
    GLuint baseMapTexId;
    GLuint lightMapTexId;


#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif


//
// Initialize the shader and program object
//
int Init(ESContext *esContext)
{
   // UserData *userData = esContext->userData;
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
        "uniform sampler2D s_baseMap;                        \n"
        "uniform sampler2D s_lightMap;                       \n"
        "void main()                                         \n"
        "{                                                   \n"
        "  vec4 baseColor;                                   \n"
        "  vec4 lightColor;                                  \n"
        "                                                    \n"
        "  baseColor = texture2D( s_baseMap, v_texCoord );   \n"
        "  lightColor = texture2D( s_lightMap, v_texCoord ); \n"
        "  gl_FragColor = baseColor * (lightColor + 0.25);   \n"
        "}                                                   \n";

    // Load the shaders and get a linked program object
    programObject = esLoadProgram(vShaderStr, fShaderStr);

    // Get the attribute locations
    positionLoc = glGetAttribLocation(programObject, "a_position");
    texCoordLoc = glGetAttribLocation(programObject, "a_texCoord");

    // Get the sampler location
    baseMapLoc = glGetUniformLocation(programObject, "s_baseMap");
    lightMapLoc = glGetUniformLocation(programObject, "s_lightMap");

    // Load the textures
    baseMapTexId = esLoadTGA("basemap.tga");
   lightMapTexId = esLoadTGA("lightmap.tga");

    if (baseMapTexId == 0 || lightMapTexId == 0)
        return FALSE;

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    return TRUE;
}

//
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext)
{
    //UserData *userData = esContext->userData;
    GLfloat vVertices[] = {
            -0.5f, 0.5f, 0.0f, 1.0f, // Position 0
             0.0f, 0.0f,        // TexCoord 0
            -0.5f, -0.5f, 0.0f, 1.0f, // Position 1
             0.0f, 1.0f,        // TexCoord 1
             0.5f, -0.5f, 0.0f, 1.0f, // Position 2
             1.0f, 1.0f,        // TexCoord 2
             0.5f, 0.5f, 0.0f, 1.0f,  // Position 3
             1.0f, 0.0f         // TexCoord 3
            };
    GLushort indices[] =
    { 0, 1, 2, 0, 2, 3 };

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

    // Bind the base map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, baseMapTexId);

    // Set the base map sampler to texture unit to 0
    glUniform1i(baseMapLoc, 0);

    // Bind the light map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, lightMapTexId);

    // Set the light map sampler to texture unit 1
    glUniform1i(lightMapLoc, 1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
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
     // printf( "FPS Activated now !!\n" );
      // Activate FPS counter
    esActivateFPS(1);
      break;

   case '2':
    //  printf( "FPS disabled now !!\n" );
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

//
// Cleanup
//
void ShutDown(ESContext *esContext)
{

    // Delete texture object
    glDeleteTextures(1, &baseMapTexId);
    glDeleteTextures(1, &lightMapTexId);

    // Delete program object
    glDeleteProgram(programObject);

   //shutdown context opengl-es AOS4
   esShutdown(esContext);
}

int main(int argc, char *argv[])
{
    ESContext esContext;

     // Activate FPS counter
    esActivateFPS(1);

    //Init context opengles
    esInitContext(&esContext);

    esCreateWindow(&esContext, "MultiTextures lib EGL for Opengl-ES AmigaOS4", 1024, 600, ES_WINDOW_ALPHA);

    if (!Init(&esContext))
        return 0;

    //Draw function
    esRegisterDrawFunc(&esContext, Draw);

    //keyboard joystick
    esRegisterKeyFunc( &esContext, Key );

    //main loop
    esMainLoop(&esContext);

    return 0;
}
