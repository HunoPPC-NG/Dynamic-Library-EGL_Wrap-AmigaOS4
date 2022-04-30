Beta Beta Beta Work In Progress please update immediately your all games/API after this new release

LibEGL_wrap Version 0.7.19 2022

Minimal required:
Warp3DNova.library Version 54 revision 16
ogles2.library Version 3 revision 3
 

EGL can be implemented on multiple operating systems and now on native AmigaOS4.
Implementations may also choose to allow rendering into specific types of EGL surfaces via other supported native rendering APIs (here OpenglES 2.0 for AmigaOS4.x).
Mechanisms for creating rendering surfaces (windows, pbuffers, pixmaps) onto which client APIs can draw and share.
Methods to create and manage graphics contexts for client APIs.
Ways to synchronize drawing by client APIs as well as native platform rendering APIs.
The EGLStreams extension provides a powerful but easily programmed API to control how a stream of images flow between AmigaOS4 OpenglES 2.0 APIs to enable advanced applications such as Augmented Reality with full hardware acceleration.
Include ow GL4es created by PtitSeb (https://github.com/ptitSeb/gl4es), image decoder PNG/JPEG/BMP/TGA by HunoPPC, sound engine by HunoPPC, AmigaInput lowlevel by HunoPPC,GUI by HunoPPC,SDL1, SDL2 and SDL_image by HunoPPC, GLUes and other small stuffs by HunoPPC.
 
Documentation not completed Work In Progress for porting your work or all games in the web ;-)

Please use a new Prefs GUI on your SYS:Prefs/ for configure your EGL_wrap and GL4es libraries
Please use ans test all samples on this folder for mecanism of my EGL_library.
Other games using the GL4es library can take advantage of my Prefs GUI, use a GL4es part on GUI and enjoy!!

Install library and Prefs:
Just launch script Install "LIB_EGL to SYS and Prefs" on libegl_wrap and enjoy!!
For SDK launch script "copy LIB_EGL to SDK"

/*---------------------------------------------SDL1-----------------------------------------------------------*/

For Projects GLUES SDL GL (no native, use gl4es) please link with this .h:

#include <EGLSDL/SDL.h>
#include <EGLSDL/SDL_opengl.h>

Or

#include "EGLSDL/SDL.h"
#include "EGLSDL/SDL_opengl.h"


If you use GLUES on SDL add this:

#include "EGLSDL/SDL.h"
#include "EGLSDL/SDL_opengl.h"
#include "EGL/glues.h"

Linked by: -lSDLegl_wrap -use-dynld -legl_wrap -lauto

IMPORTANT: do not use #include "SDL/SDL_opengl.h" (is for minigl) use #include "EGLSDL/SDL_opengl.h" and for the others originals headers no problems, use this.
                  Do not use `sdl-config --cflags`option please on your makefile
				  Use `eglsdl-config --cflags`option on your makefile

/*---------------------------------------------SDL2-----------------------------------------------------------*/
For Projects GLUES SDL2 GL (no native, use gl4es) please link with this .h:

#include <EGLSDL2/SDL.h>
#include <EGLSDL2/SDL_opengl.h>

Or

#include "EGLSDL2/SDL.h"
#include "EGLSDL2/SDL_opengl.h"


If you use GLUES on SDL2 add this:

#include "EGLSDL2/SDL.h"
#include "EGLSDL2/SDL_opengl.h"
#include "EGL/glues.h"

Linked by: -lSDL2egl_wrap -use-dynld -legl_wrap -lauto

IMPORTANT: do not use #include "SDL2/SDL_opengl.h" (is for minigl) use #include "EGLSDL2/SDL_opengl.h" and for the others originals headers no problems, use this.
                  Do not use `sdl2-config --cflags`option please on your makefile
				  Use `egl2sdl-config --cflags`option on your makefile

/*--------------------------------------------Native------------------------------------------------------------*/

For Projects EGL GLUES OPENGLES (native, use opengles 2.0) please link with this .h:

#include "EGL/egl.h"
#include "EGL/glues.h"

Linked by: -use-dynld -legl_wrap -lauto

/*-------------------------------------------Releases-----------------------------------------------------------*/
Version 0.7.19:
* Updated Gl4ES
* Updated GUI
* Added new icons into the GUI
* Added new Prefs on the GUI for Gl4ES
* Added SDL1 SDLegl_image.a fixed for fast loading all images supported by this library
* Fixed problem on AHI with new SDK


Version 0.7.18:
* Updated Gl4ES
* Added SDL1 EGL includes and package for SDK
* Added SDL2 EGL includes and package for SDK
* Added option BLITFULLSCREEN on GL4ES parts

Version 0.7.17:
* Updated Gl4ES
* Fixed SDL1 Fullscreen render 
* Added SDL2 EGL (beta)



Version 0.7.16:
* Updated Gl4ES
* Added new Prefs on the GUI for Gl4ES
* Fixed free surface on Glues render
* Added new functions on Glues
                - glutGameModeString
                - glutEnterGameMode
                - glutLeaveGameMode
                - glutGameModeGet
                - glutIgnoreKeyRepeat
                - glutSetKeyRepeat
                - glutSimulateButton
                - glutPostWindowRedisplay
                - glutCloseFunc
                - glutWindowStatusFunc
                - glutForceJoystickFunc
* Fixed glutKeyboardFunc, keyboard working fine now!!             
 

Version 0.7.15:
* Updated Gl4ES
* Fix Prefs file on the GUI           


Version 0.7.14:
* Fixed problem on texture filter
* Updated Gl4ES
* Fixed loading texture on Glues no native Projects
* Modification of all header's .h (please install a new SDK of EGL_wrapper)
* Added all samples SDL_egl_wrap with code
* Added library SDLegl_wrap.a 1.2.15 on EGL SDK
* Added headers of SDLegl_wrap.a 1.2.15 on EGL SDK "EGLSDL/"
PROBLEM: No free surface correctly on Glues render, W.I.P (please reboot your Amiga after use Glues projects)
 

Version 0.7.13:
* Fixed crash music module on Update Effect.
* Updated Gl4ES
* Add new options environment ENVARC
* Fix mkdir (unix), now native AOS4 functions
* Add new function GLU and GLUT for all mix demos code
* Glues and Glut lights effects working fine now
* Fog effects working fine now
* Colors effects working fine now

 
 Version 0.7.12:
* Internal Shaders working (limited actually W.I.P)
* Small speedup on renderer HD
* New update of GL4ES include

 
Problems:
* ALPHA problem on games engine (example: IOQUAKE and RTCW)
* Internal GAMMA
* Endianness problems
* On SDLegl_wrap, Option: SDL_RESIZABLE not working fine

In the future:
* Loading external Shader on GL 1.X
* Fix colors and lights effects
* Add new functions
* Speed increase
* Add new options on Prefs GUI
* And other stuffs for your pleasure... 

 

Thanks go to:
My children "Matthis" and "Sorhënn" for allowing me some time to develop
Hyperion Entertainment - For the development of Amiga OS 4.0 and 4.1
Relec for my X1000 NEMO and my X5000
George Sakianos for my new cool web site 
Lio, Samo79, K-L, zzd10h, Javier de las Rivas, Pseudaxos, Salternaos, Elwood, Alain Thellier, Sinisrus, Ölrick, Alex, Corto, Daytona, PtitSeb, Kas1e, Xray, A-eon and all my betatesters on my site
My All My Donators ;o)
And of course the whole AMIGA community

 
For lib GL4es donate to PtitSeb at https://github.com/ptitSeb/gl4es

 
Bug reports for AmigaOS 4x at
NOUVEL (HunoPPC) Hugues
Mail and donate to: hunoppc(AT)gmail.com
http://hunoppc.amiga-projects.net/
