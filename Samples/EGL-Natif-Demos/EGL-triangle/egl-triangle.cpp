/*
 * Copyright (c) 2012, 2013 Erik Faye-Lund
 * Copyright (c) 2013 Avionic Design GmbH
 * Copyright (c) 2013 Thierry Reding
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include "EGL/egl.h"


 	EGLDisplay display;
    EGLSurface surface;

//
// Draw a triangle
//
void Draw(ESContext *esContext)
{
    static GLfloat vertices[] = {
		 0.0f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f,
	};

	static GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};

    printf("=== Calling glClear()\n");
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	printf("=== Calling glVertexAttribPointer(0)\n");
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	glFlush();
	printf("=== Calling glEnableVertexAttribArray(0)\n");
	glEnableVertexAttribArray(0);
	glFlush();
	printf("=== Calling glVertexAttribPointer(1)\n");
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glFlush();
	printf("=== Calling glEnableVertexAttribArray(1)\n");
	glEnableVertexAttribArray(1);
	glFlush();
	printf("=== Calling glDrawArrays(GL_TRIANGLES, 0, 3)\n");
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
	printf("=== Calling eglSwapBuffers()\n");
    eglSwapBuffers(display, surface);
    glFlush();

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
      // Activate FPS counter
    esActivateFPS(1);
      break;

   case '2':
      // Disable FPS counter
    esActivateFPS(0);
      break;

   case 033: // ASCII Escape Key
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
    esShutdown(esContext);
	   break;
   }
}

//
// Main
//
int main(int argc, char *argv[])
{
	GLuint vertex, fragment;
	EGLint major, minor;
	ESContext esContext;
    EGLContext context;
	EGLint num_config;
	EGLConfig config;
	GLuint program;
	GLint height;
	GLint width;


	static EGLint const config_attrs[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_DEPTH_SIZE, 8,
		EGL_NONE
	};

	static EGLint const context_attrs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	static EGLint const pbuffer_attrs[] = {
		EGL_WIDTH, 640,
		EGL_HEIGHT, 480,
		EGL_LARGEST_PBUFFER, EGL_TRUE,
		EGL_NONE
	};

    	static const char *vertex_source =
		"attribute vec4 position;\n"
		"attribute vec4 color;\n"
		"\n"
		"varying vec4 vcolor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_Position = position;\n"
		"  vcolor = color;\n"
		"}\n";

	static const char *fragment_source =
		"precision mediump float;\n"
		"varying vec4 vcolor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_FragColor = vcolor;\n"
		"}\n";



        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        fprintf(stderr, "no display found\n");
        return 1;
    }

    if (!eglInitialize(display, &major, &minor)) {
        fprintf(stderr, "failed to initialize EGL\n");
        return 1;
    }

    printf("EGL: %d.%d\n", major, minor);

   if (!eglChooseConfig(display, config_attrs, &config, 1, &num_config)) {
        fprintf(stderr, "failed to choose configuration\n");
       return 1;
   }

    printf("config:%p num_config:%d\n", config, num_config);

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrs);
    if (context == EGL_NO_CONTEXT) {
        fprintf(stderr, "failed to create context\n");
        return 1;
   }

    surface = eglCreatePbufferSurface(display, config, pbuffer_attrs);
    if (surface == EGL_NO_SURFACE) {
        fprintf(stderr, "failed to create surface\n");
        return 1;
    }

    surface = eglCreateWindowSurface(display, config, NULL, pbuffer_attrs);
    if (surface == EGL_NO_SURFACE) {
        fprintf(stderr, "failed to create surface\n");
        return 1;
    }


    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width)) {
       fprintf(stderr, "failed to query surface width\n");
        return 1;
    }

    if (!eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        fprintf(stderr, "failed to query surface height\n");
        return 1;
    }

    printf("PBuffer: %dx%d\n", width, height);

    if (!eglMakeCurrent(display, surface, surface, context)) {
        fprintf(stderr, "failed to activate context\n");
        return 1;
    }

    glFlush();
    //initContext EGL
    esInitContext ( &esContext );

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_source, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_source, NULL);
    glCompileShader(fragment);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");

	printf("=== Calling glLinkProgram()\n");
	glLinkProgram(program);
	glFlush();
	printf("=== Calling glUseProgram()\n");
	glUseProgram(program);
	glFlush();
	printf("=== Calling glClearColor()\n");
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glFlush();

     // Draw function
    printf("=== Calling esRegisterDrawFunc()\n");
    esRegisterDrawFunc ( &esContext, Draw );

    //keyboard joystick
    printf("=== Calling esRegisterKeyFunc()\n");
    esRegisterKeyFunc( &esContext, Key );

    //on a main loop
    printf("=== Calling esMainLoop()\n");
    esMainLoop ( &esContext);

    printf("=== Calling eglDestroySurface()\n");
    eglDestroySurface(display, surface);
    glFlush();
    printf("=== Calling eglTerminate()\n");
    eglTerminate(display);

	return 0;
}
