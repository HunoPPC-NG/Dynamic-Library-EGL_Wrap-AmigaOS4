//* Ported to GLUes minimal EGL_wrap lib for OpenglES AmigaOS4 by HunoPPC 7 November 2016
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EGL/egl.h"
#include "EGL/glues.h"


typedef struct {
    // Handle to a program object
    GLuint programObject;

    // Attribute locations
    GLint  positionLoc;
    GLint  texCoordLoc;

    // Sampler location
    GLint samplerLoc;

    // Texture handle
    GLuint textureId;

    GLuint vertexObject, indexObject;
} UserData;

static UserData _UserData;


//
// Initialize the shader and program object
//
static int Init (ESContext *esContext)
{
    UserData *userData = &_UserData;
    char vShaderStr[] =
        "attribute vec4 a_position;   \n"
        "attribute vec2 a_texCoord;   \n"
        "varying vec2 v_texCoord;     \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = a_position; \n"
        "   v_texCoord = a_texCoord;  \n"
        "}                            \n";

    char fShaderStr[] =
        "precision mediump float;                            \n"
        "varying vec2 v_texCoord;                            \n"
        "uniform sampler2D s_texture;                        \n"
        "void main()                                         \n"
        "{                                                   \n"
        "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
        "}                                                   \n";

    memset(&_UserData, 0, sizeof(_UserData));

    // Load the shaders and get a linked program object
    userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

    // Get the attribute locations
    userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
    userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );

    // Get the sampler location
    userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );

    // Load the texture
    userData->textureId = esLoadTGA("LogoTS256.tga");


    glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
    return GL_TRUE;
}

static void test_idle(ESContext *esContext) {
}

void Reshape(ESContext *esContext, int width, int height) {
    /* glutLogMessage("I/Reshape: %d, %d",width,height); */
    // Set the viewport
    glViewport ( 0, 0, width, height );
}

//
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext)
{
    UserData *userData = &_UserData;

        // Setup the vertex data
        GLfloat vVertices[] = { -0.5,  0.5, 0.0,1.0,  // Position 0
                                0.0,  1.0,       // TexCoord 0
                                -0.5, -0.5, 0.0,1.0,  // Position 1
                                0.0,  0.0,       // TexCoord 1
                                0.5, -0.5, 0.0,1.0,  // Position 2
                                1.0,  0.0,       // TexCoord 2
                                0.5,  0.5, 0.0,1.0,  // Position 3
                                1.0,  1.0        // TexCoord 3
        };
        GLushort indices[] = { 0, 1, 2, 0, 2, 3};

        glGenBuffers(1, &userData->vertexObject);
        glBindBuffer(GL_ARRAY_BUFFER, userData->vertexObject );
        glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW );

        glGenBuffers(1, &userData->indexObject);
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->indexObject );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Use the program object
    glUseProgram ( userData->programObject );

    // Load the vertex position
    glBindBuffer (GL_ARRAY_BUFFER, userData->vertexObject );
    glVertexAttribPointer ( userData->positionLoc, 4, GL_FLOAT,
                            GL_FALSE, 6 * 4, 0 );
    // Load the texture coordinate
    glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT,
                            GL_FALSE, 6 * 4,
                            (void*)(4 * 4) );

    glEnableVertexAttribArray ( userData->positionLoc );
    glEnableVertexAttribArray ( userData->texCoordLoc );

    // Bind the texture
    glActiveTexture ( GL_TEXTURE0 );
    glBindTexture ( GL_TEXTURE_2D, userData->textureId );

    // Set the sampler texture unit to 0
    glUniform1i ( userData->samplerLoc, 0 );

    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->indexObject );
    glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 );

    glutSwapBuffers();
}


/**
 * Handles special glut events.
 *
 * @param special the event to handle.
 */
static void
keys_special(ESContext *esContext, int special, int crap, int morecrap)
{
   switch (special) {
      case GLUT_KEY_1:
         esActivateFPS(1);
         break;
      case GLUT_KEY_0:
         esActivateFPS(0);
         break;
      case GLUT_KEY_ESCAPE:
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
       esShutdown(esContext);
	   break;
   }

}


int main ( int argc, char *argv[] )
{

    ESContext esContext;
    glutInit(&esContext, &argc,argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    if (!glutCreateWindow(&esContext, "File_Texture2D GLUes with lib EGL for Opengl-ES AmigaOS4")) {
        glutLogMessage("E/ Can't create window !");
        return -1;
    }

    glutIdleFunc(&esContext, test_idle);
    glutSpecialFunc(&esContext, keys_special);
    glutReshapeFunc(&esContext, Reshape);
    glutDisplayFunc(&esContext, Draw);

    if (!Init(&esContext)) {
        glutLogMessage("E/ Can't initialize test !");
        return -1;
    }

    glutMainLoop(&esContext);

    return 0;
}
