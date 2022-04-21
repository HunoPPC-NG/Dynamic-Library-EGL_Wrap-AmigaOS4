#include <stdlib.h>
#include <stdio.h>
#include <EGL/egl.h>

EGLDisplay display;
EGLint major, minor;
EGLint num_config;
EGLConfig config;

int main(int argc, char *argv[])
{



	static EGLint const config_attrs[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_DEPTH_SIZE, 8,
		EGL_NONE
	};


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

   	if ( config == 0 )
	{
		printf("Could not get config for EGL display\n");
		return false;
	}

    printf("config:%p num_config:%d\n", config, num_config);

	return 0;
}
