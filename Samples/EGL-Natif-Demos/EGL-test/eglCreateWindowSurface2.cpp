#define __USE_INLINE__

#include <EGL/egl.h>
#include <stdio.h>
#include <proto/dos.h>

int main()
{

	typedef struct Window *EGLNativeWindowTypeMY;
	
	EGLDisplay display;	
	
	EGLint majorVersion;
	EGLint minorVersion;
	
	EGLint numConfigs;
	
	EGLint attribList[] =    {EGL_NONE};
	
	EGLConfig config = 0;
	
	EGLNativeWindowTypeMY window;
	EGLSurface surface;
	EGLContext context;

	
	EGLint OpenGLESVersion = 2; //2 for ogles2
	EGLint ContextAttribs[] =
	{
#ifdef EGL_VERSION_1_3
		EGL_CONTEXT_CLIENT_VERSION, OpenGLESVersion,
#endif
		EGL_NONE, 0
	};

	
// Obtain an EGL display object.
display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
if (display == EGL_NO_DISPLAY)
{
  printf("display == EGL_NO_DISPLAY\n");
  return 0;
}

printf("eglGetDisplay ok!\n");
Delay(30);

// Initialize the display
if (!eglInitialize(display, &majorVersion, &minorVersion))
{
  printf("can't eglInitialize");
  return 0;

}
printf("eglInitialize ok!\n");
Delay(30);


// Obtain the display configs
		if ( eglGetConfigs( display, NULL, 0, &numConfigs) == EGL_FALSE )
		{
			printf("find of number of available configs sucked !\n");			
			return 0;
		}

		if ( numConfigs <= 0 ) {
			printf("numConfigs is less that 0\n");
			return 0;
		}
		else {
			printf("numConfigs is > that 0, i.e. : %d\n", numConfigs);
			
		}	

printf("eglGetConfigs done!\n");
Delay(30);


// Choose the display config
if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
{
  printf("can't eglChooseConfig\n");
  return 0;

}

printf("eglChooseConfig done!\n");
Delay(30);


// Create a surface
surface = eglCreateWindowSurface(display, config, window, NULL);
if (surface == EGL_NO_SURFACE)
{
  printf("surface == EGL_NO_SURFACE\n");
  return 0;

}

printf("eglCreateWidowSurface done!\n");
Delay(30);



// Create a drawing context from the EGLDisplay
context = eglCreateContext(display, config, EGL_NO_CONTEXT, ContextAttribs);
if (context == EGL_NO_CONTEXT)
{
  printf("context == EGL_NO_CONTEXT\n");
  return 0;

}

printf("eglCreateContext done!\n");
Delay(30);



// Make the context current
if (!eglMakeCurrent(display, surface, surface, context))
{
  printf("can't eglMakeCurrent\n");
  return 0;

}

printf("eglMakeCurrent done!\n");
Delay(30);


//to show your drawing you swap the buffers like this
eglSwapBuffers(display, surface);


eglDestroySurface(display, surface);

printf("Full test egl is done now!\n");
 
//Terminating a display (release the window resources)
eglTerminate(display);


}

