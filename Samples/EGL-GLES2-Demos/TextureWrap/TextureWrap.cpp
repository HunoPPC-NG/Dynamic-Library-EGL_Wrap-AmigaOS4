//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// TextureWrap.c
//
//    This is an example that demonstrates the three texture
//    wrap modes available on 2D textures
//
//HunoPPC 2018
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

///
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

///
// Create a mipmapped 2D texture image
//
GLuint CreateTexture2D()
{
    // Texture object handle
    GLuint textureId;
    int width = 256, height = 256;
    GLubyte *pixels;

    pixels = GenCheckImage(width, height, 64);
    if (pixels == NULL)
        return 0;

    // Generate a texture object
    glGenTextures(1, &textureId);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Load mipmap level 0
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureId;
}


///
// Initialize the shader and program object
//
int Init(ESContext *esContext)
{
    //UserData *userData = esContext->userData;
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

    // Load the texture
    textureId = CreateTexture2D();

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext)
{
    GLfloat vVertices[] = { -0.3f,  0.3f, 0.0f, 1.0f,  // Position 0
                           -1.0f,  -1.0f,              // TexCoord 0
                           -0.3f, -0.3f, 0.0f, 1.0f, // Position 1
                           -1.0f,  2.0f,              // TexCoord 1
                            0.3f, -0.3f, 0.0f, 1.0f, // Position 2
                            2.0f,  2.0f,              // TexCoord 2
                            0.3f,  0.3f, 0.0f, 1.0f,  // Position 3
                            2.0f,  -1.0f               // TexCoord 3
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

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set the sampler texture unit to 0
    glUniform1i(samplerLoc, 0);

    // Draw quad with repeat wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glUniform1f(offsetLoc, -0.7f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    // Draw quad with clamp to edge wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glUniform1f(offsetLoc, 0.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    // Draw quad with mirrored repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glUniform1f(offsetLoc, 0.7f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

}

///
// Cleanup
//
void ShutDown(ESContext *esContext)
{

    // Delete texture object
    glDeleteTextures(1, &textureId);

    // Delete program object
    glDeleteProgram(programObject);

    //shutdown context opengl-es AOS4
   esShutdown(esContext);
}

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
     // printf( "FPS disabled now !!\n" );
      // Disable FPS counter
    esActivateFPS(0);
      break;

   case 033: // ASCII Escape Key
    //printf( "Saw an 'Escape' \n" );
    //cleanup your program
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
    ShutDown(esContext);
	   break;
   }
}

int main(int argc, char *argv[])
{
    ESContext esContext;

    //activate FPS
    esActivateFPS(1);

    esInitContext(&esContext);

    esCreateWindow(&esContext, "MipMap 2D lib EGL for Opengl-ES AmigaOS4", 1024, 600, ES_WINDOW_ALPHA);

    if (!Init(&esContext))
        return 0;

    // Draw function
    esRegisterDrawFunc(&esContext, Draw);

        //keyboard joystick
    esRegisterKeyFunc( &esContext, Key );

    //on a main loop
    esMainLoop(&esContext);


    return 0;
}
