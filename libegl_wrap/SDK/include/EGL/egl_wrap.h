/* EGL Wrapper lib for Opengl-ES-NOVA Written by Hugues 'HunoPPC' Nouvel 2022 Amiga French Team Power!!*/ 
#ifndef EGL_WRAP_H
#define EGL_WRAP_H

#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
/* EGL Types */
typedef int EGLint;
typedef unsigned int EGLBoolean;
typedef unsigned int EGLenum;
typedef void *EGLConfig;
typedef void *EGLContext;
typedef void *EGLDisplay;
typedef void *EGLNativeDisplayType;
typedef void *EGLNativePixmapType;
typedef void *EGLNativeWindowType; //Many EGL programs want it (Virtual)
typedef void *EGLSurface;
typedef void *EGLClientBuffer;
/*
 * EGL API macro definitions -- the display mode definitions
 */
// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1
// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2
// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

/* EGL Versioning */
#define EGL_VERSION_1_0			1
#define EGL_VERSION_1_1			1
#define EGL_VERSION_1_2			1
#define EGL_VERSION_1_3			1
#define EGL_VERSION_1_4	        1

/* EGL Enumerants. Bitmasks and other exceptional cases aside, most
 * enums are assigned unique values starting at 0x3000.
 */

/* EGL aliases */
#define EGL_FALSE			0
#define EGL_TRUE			1

/* Out-of-band handle values */
#define EGL_DEFAULT_DISPLAY		((EGLNativeDisplayType)0)
#define EGL_NO_CONTEXT			((EGLContext)0)
#define EGL_NO_DISPLAY			((EGLDisplay)0)
#define EGL_NO_SURFACE			((EGLSurface)0)

/* Out-of-band attribute value */
#define EGL_DONT_CARE			((EGLint)-1)

/* Errors / GetError return values */
#define EGL_SUCCESS			       0x3000
#define EGL_NOT_INITIALIZED		0x3001
#define EGL_BAD_ACCESS			0x3002
#define EGL_BAD_ALLOC			0x3003
#define EGL_BAD_ATTRIBUTE		0x3004
#define EGL_BAD_CONFIG			0x3005
#define EGL_BAD_CONTEXT			0x3006
#define EGL_BAD_CURRENT_SURFACE	0x3007
#define EGL_BAD_DISPLAY			0x3008
#define EGL_BAD_MATCH			0x3009
#define EGL_BAD_NATIVE_PIXMAP	0x300A
#define EGL_BAD_NATIVE_WINDOW	0x300B
#define EGL_BAD_PARAMETER		0x300C
#define EGL_BAD_SURFACE			0x300D
#define EGL_CONTEXT_LOST		       0x300E	/* EGL 1.1 - IMG_power_management */

/* Reserved 0x300F-0x301F for additional errors */

/* Config attributes */
#define EGL_BUFFER_SIZE			       0x3020
#define EGL_ALPHA_SIZE			       0x3021
#define EGL_BLUE_SIZE			       0x3022
#define EGL_GREEN_SIZE			       0x3023
#define EGL_RED_SIZE			       0x3024
#define EGL_DEPTH_SIZE			       0x3025
#define EGL_STENCIL_SIZE		       0x3026
#define EGL_CONFIG_CAVEAT		       0x3027
#define EGL_CONFIG_ID			       0x3028
#define EGL_LEVEL			           0x3029
#define EGL_MAX_PBUFFER_HEIGHT		   0x302A
#define EGL_MAX_PBUFFER_PIXELS		   0x302B
#define EGL_MAX_PBUFFER_WIDTH		   0x302C
#define EGL_NATIVE_RENDERABLE		   0x302D
#define EGL_NATIVE_VISUAL_ID		   0x302E
#define EGL_NATIVE_VISUAL_TYPE		   0x302F
#define EGL_PRESERVED_RESOURCES		   0x3030
#define EGL_SAMPLES			           0x3031
#define EGL_SAMPLE_BUFFERS		       0x3032
#define EGL_SURFACE_TYPE		       0x3033
#define EGL_TRANSPARENT_TYPE		   0x3034
#define EGL_TRANSPARENT_BLUE_VALUE	   0x3035
#define EGL_TRANSPARENT_GREEN_VALUE	   0x3036
#define EGL_TRANSPARENT_RED_VALUE	   0x3037
#define EGL_NONE			           0x3038	/* Attrib list terminator */
#define EGL_BIND_TO_TEXTURE_RGB		   0x3039
#define EGL_BIND_TO_TEXTURE_RGBA	   0x303A
#define EGL_MIN_SWAP_INTERVAL		   0x303B
#define EGL_MAX_SWAP_INTERVAL		   0x303C
#define EGL_LUMINANCE_SIZE		       0x303D
#define EGL_ALPHA_MASK_SIZE		       0x303E
#define EGL_COLOR_BUFFER_TYPE		   0x303F
#define EGL_RENDERABLE_TYPE		       0x3040
#define EGL_MATCH_NATIVE_PIXMAP		   0x3041	/* Pseudo-attribute (not queryable) */
#define EGL_CONFORMANT			       0x3042

/* Reserved 0x3041-0x304F for additional config attributes */

/* Config attribute values */
#define EGL_SLOW_CONFIG			       0x3050	/* EGL_CONFIG_CAVEAT value */
#define EGL_NON_CONFORMANT_CONFIG	   0x3051	/* EGL_CONFIG_CAVEAT value */
#define EGL_TRANSPARENT_RGB		       0x3052	/* EGL_TRANSPARENT_TYPE value */
#define EGL_RGB_BUFFER			       0x308E	/* EGL_COLOR_BUFFER_TYPE value */
#define EGL_LUMINANCE_BUFFER		   0x308F	/* EGL_COLOR_BUFFER_TYPE value */

/* More config attribute values, for EGL_TEXTURE_FORMAT */
#define EGL_NO_TEXTURE			      0x305C
#define EGL_TEXTURE_RGB			      0x305D
#define EGL_TEXTURE_RGBA		      0x305E
#define EGL_TEXTURE_2D			      0x305F

/* Config attribute mask bits */
#define EGL_PBUFFER_BIT			       0x0001	/* EGL_SURFACE_TYPE mask bits */
#define EGL_PIXMAP_BIT			       0x0002	/* EGL_SURFACE_TYPE mask bits */
#define EGL_WINDOW_BIT			       0x0004	/* EGL_SURFACE_TYPE mask bits */
#define EGL_VG_COLORSPACE_LINEAR_BIT   0x0020	/* EGL_SURFACE_TYPE mask bits */
#define EGL_VG_ALPHA_FORMAT_PRE_BIT	   0x0040	/* EGL_SURFACE_TYPE mask bits */

#define EGL_OPENGL_ES_BIT		       0x0001	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENVG_BIT			       0x0002	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_ES2_BIT		       0x0004	/* EGL_RENDERABLE_TYPE mask bits */

/* QueryString targets */
#define EGL_VENDOR			0x3053
#define EGL_VERSION			0x3054
#define EGL_EXTENSIONS		0x3055
#define EGL_CLIENT_APIS		0x308D

/* QuerySurface / CreatePbufferSurface targets */
#define EGL_HEIGHT			           0x3056
#define EGL_WIDTH			           0x3057
#define EGL_LARGEST_PBUFFER		       0x3058
#define EGL_TEXTURE_FORMAT		       0x3080
#define EGL_TEXTURE_TARGET		       0x3081
#define EGL_MIPMAP_TEXTURE		       0x3082
#define EGL_MIPMAP_LEVEL		       0x3083
#define EGL_RENDER_BUFFER		       0x3086
#define EGL_VG_COLORSPACE		       0x3087
#define EGL_VG_ALPHA_FORMAT		       0x3088
#define EGL_HORIZONTAL_RESOLUTION	   0x3090
#define EGL_VERTICAL_RESOLUTION		   0x3091
#define EGL_PIXEL_ASPECT_RATIO		   0x3092
#define EGL_SWAP_BEHAVIOR		       0x3093

/* EGL_RENDER_BUFFER values / BindTexImage / ReleaseTexImage buffer targets */
#define EGL_BACK_BUFFER			       0x3084
#define EGL_SINGLE_BUFFER		       0x3085

/* OpenVG color spaces */
#define EGL_VG_COLORSPACE_sRGB		0x3089	/* EGL_VG_COLORSPACE value */
#define EGL_VG_COLORSPACE_LINEAR	0x308A	/* EGL_VG_COLORSPACE value */

/* OpenVG alpha formats */
#define EGL_VG_ALPHA_FORMAT_NONPRE	0x308B	/* EGL_ALPHA_FORMAT value */
#define EGL_VG_ALPHA_FORMAT_PRE		0x308C	/* EGL_ALPHA_FORMAT value */

/* Constant scale factor by which fractional display resolutions &
 * aspect ratio are scaled when queried as integer values.
 */
#define EGL_DISPLAY_SCALING		10000

/* Unknown display resolution/aspect ratio */
#define EGL_UNKNOWN			((EGLint)-1)

/* Back buffer swap behaviors */
#define EGL_BUFFER_PRESERVED		0x3094	/* EGL_SWAP_BEHAVIOR value */
#define EGL_BUFFER_DESTROYED		0x3095	/* EGL_SWAP_BEHAVIOR value */

/* CreatePbufferFromClientBuffer buffer types */
#define EGL_OPENVG_IMAGE		    0x3096

/* QueryContext targets */
#define EGL_CONTEXT_CLIENT_TYPE		0x3097

/* CreateContext attributes */
#define EGL_CONTEXT_CLIENT_VERSION	0x3098

/* BindAPI/QueryAPI targets */
#define EGL_OPENGL_ES_API		    0x30A0
#define EGL_OPENVG_API			    0x30A1

/* GetCurrentSurface targets */
#define EGL_DRAW			0x3059
#define EGL_READ			0x305A

/* WaitNative engines */
#define EGL_CORE_NATIVE_ENGINE		0x305B

/* EGL 1.2 tokens renamed for consistency in EGL 1.3 */
#define EGL_COLORSPACE			EGL_VG_COLORSPACE
#define EGL_ALPHA_FORMAT		EGL_VG_ALPHA_FORMAT
#define EGL_COLORSPACE_sRGB		EGL_VG_COLORSPACE_sRGB
#define EGL_COLORSPACE_LINEAR   EGL_VG_COLORSPACE_LINEAR
#define EGL_ALPHA_FORMAT_NONPRE	EGL_VG_ALPHA_FORMAT_NONPRE
#define EGL_ALPHA_FORMAT_PRE	EGL_VG_ALPHA_FORMAT_PRE

#define  EGL_ELAPSED_TIME                  0x02BC

#ifndef EGL_EXT_create_context_robustness
#define EGL_EXT_create_context_robustness 1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT               0x30BF
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#define EGL_NO_RESET_NOTIFICATION_EXT		               0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_EXT		               0x31BF
#endif

// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1
// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2
// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

/* Joysticks */
struct gamejoystick{
char up,down,left,right,up2,down2,left2,right2,b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,num,pad,pad2,pad3;
};
extern struct gamejoystick joystick;

#define    GLES_JOY_LEFT               2
#define    GLES_JOY_UP                 8
#define    GLES_JOY_RIGHT              5
#define    GLES_JOY_DOWN               4
#define    GLES_JOY_B0                 joystick.b0
#define    GLES_JOY_B1                 joystick.b1
#define    GLES_JOY_B2                 joystick.b2
#define    GLES_JOY_B3                 joystick.b3
#define    GLES_JOY_B4                 joystick.b4
#define    GLES_JOY_B5                 joystick.b5
#define    GLES_JOY_B6                 joystick.b6

//left mouse button is active
extern BOOL esLeftMouseButtonActivated;
//right mouse button is active
extern BOOL esRightMouseButtonActivated;
//middle mouse button is active
extern BOOL esMiddleMouseButtonActivated;

// new width of window resized on real time
extern GLint esNewWidthMainLoopOnRealTime;
// new height of window resized on real time
extern GLint esNewHeightMainLoopOnRealTime;

#ifdef __cplusplus

extern "C" {
#endif

    //
    //  Macros
    //
    #define ESUTIL_API
    #define ESCALLBACK


typedef struct
{
   // Put platform specific data here
   void       *platformData;

   // Put your user data here...
   void       *userData;

  // Put other user data here...
   void       *user_data;

   // Window width
   GLint       width;

   // Window height
   GLint       height;

   // Window handle
   struct Window    *hWnd;

   // display native handle
   EGLNativeDisplayType  eglNativeDisplay;

   // window native handle
   EGLNativeWindowType  eglNativeWindow;

   // EGL display
   EGLDisplay  eglDisplay;

   // EGL context
   EGLContext  eglContext;

   // EGL surface
   EGLSurface eglSurface;

    // Callbacks EGL new function by HunoPPC
   void (ESCALLBACK *ReshapeFunc) ( void*,int, int );
   void (ESCALLBACK *drawFunc) ( void* );
   void (ESCALLBACK *shutdownFunc ) ( void* );
   void (ESCALLBACK *keyFunc) ( void*, unsigned char, int, int );
   void (ESCALLBACK *KeyUpFunc)(void*, unsigned char, int, int );
   void (ESCALLBACK *updateFunc) ( void*, float deltaTime );
   void (ESCALLBACK *DeinitFunc) ( void* );
   void (ESCALLBACK *JoysticksFunc)(void*, unsigned char, int, int);
   void (ESCALLBACK *MouseFunc)(void*, int, int, int, int );
   void (ESCALLBACK *MouseWheelFunc)(void*, int, int, int );
   void (ESCALLBACK *MotionFunc)(void*, int, int );
   void (ESCALLBACK *PassiveMotionFunc)(void*, int, int );
   void (ESCALLBACK *TimerFunc)(void*, int);

   // Callbacks GLUES new function by HunoPPC
   void (ESCALLBACK *gluReshapeFunc) ( void*,int, int );
   void (ESCALLBACK *gluDisplayFunc ) ( void* );
   void (ESCALLBACK *gluKeyboardFunc)(void*, unsigned char, int, int);
   void (ESCALLBACK *gluKeyboardUpFunc)(void*, unsigned char, int, int );
   void (ESCALLBACK *gluSpecialFunc)(void*, int, int, int );
   void (ESCALLBACK *gluSpecialUpFunc)(void*, int, int, int );
   void (ESCALLBACK *gluMouseFunc)(void*, int, int, int, int );
   void (ESCALLBACK *gluMouseWheelFunc)(void*, int, int, int );
   void (ESCALLBACK *gluMotionFunc)(void*, int, int );
   void (ESCALLBACK *gluPassiveMotionFunc)(void*, int, int );
   void (ESCALLBACK *gluIdleFunc ) ( void* );
   void (ESCALLBACK *gluJoysticksFunc)(void*, unsigned char, int, int);
   void (ESCALLBACK *gluTimerFunc)(void*, int);
   void (ESCALLBACK *gluWindowStatusFunc)(void*, int);
   void (ESCALLBACK *gluVisibilityFunc)(void*, int);
   void (ESCALLBACK *gluEntryFunc)(void*, int);
   void (ESCALLBACK *gluCloseFunc ) ( void* );

} ESContext;

//new function for compiled all projects on EGL RPI

typedef uint32_t DISPMANX_DISPLAY_HANDLE_T;
typedef uint32_t DISPMANX_UPDATE_HANDLE_T;
typedef uint32_t DISPMANX_ELEMENT_HANDLE_T;
typedef uint32_t DISPMANX_RESOURCE_HANDLE_T;
typedef uint32_t DISPMANX_PROTECTION_T;
typedef uint32_t DISPMANX_PROTECTION_NONE;
typedef uint32_t DISPLAY_INPUT_FORMAT_T;

#define DISPMANX_NO_HANDLE 0

#define DISPMANX_PROTECTION_MAX   0x0f
#define DISPMANX_PROTECTION_NONE  0
#define DISPMANX_PROTECTION_HDCP  11   // Derived from the WM DRM levels, 101-300

typedef enum {
  /* Bottom 2 bits sets the orientation */
  DISPMANX_NO_ROTATE = 0,
  DISPMANX_ROTATE_90 = 1,
  DISPMANX_ROTATE_180 = 2,
  DISPMANX_ROTATE_270 = 3,

  DISPMANX_FLIP_HRIZ = 1 << 16,
  DISPMANX_FLIP_VERT = 1 << 17,

  /* invert left/right images */
  DISPMANX_STEREOSCOPIC_INVERT =  1 << 19,
  /* extra flags for controlling 3d duplication behaviour */
  DISPMANX_STEREOSCOPIC_NONE   =  0 << 20,
  DISPMANX_STEREOSCOPIC_MONO   =  1 << 20,
  DISPMANX_STEREOSCOPIC_SBS    =  2 << 20,
  DISPMANX_STEREOSCOPIC_TB     =  3 << 20,
  DISPMANX_STEREOSCOPIC_MASK   = 15 << 20,

  /* extra flags for controlling snapshot behaviour */
  DISPMANX_SNAPSHOT_NO_YUV = 1 << 24,
  DISPMANX_SNAPSHOT_NO_RGB = 1 << 25,
  DISPMANX_SNAPSHOT_FILL = 1 << 26,
  DISPMANX_SNAPSHOT_SWAP_RED_BLUE = 1 << 27,
  DISPMANX_SNAPSHOT_PACK = 1 << 28
} DISPMANX_TRANSFORM_T;

typedef enum {
  /* Bottom 2 bits sets the alpha mode */
  DISPMANX_FLAGS_ALPHA_FROM_SOURCE = 0,
  DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS = 1,
  DISPMANX_FLAGS_ALPHA_FIXED_NON_ZERO = 2,
  DISPMANX_FLAGS_ALPHA_FIXED_EXCEED_0X07 = 3,

  DISPMANX_FLAGS_ALPHA_PREMULT = 1 << 16,
  DISPMANX_FLAGS_ALPHA_MIX = 1 << 17
} DISPMANX_FLAGS_ALPHA_T;

typedef struct {
  DISPMANX_FLAGS_ALPHA_T flags;
  uint32_t opacity;
//  VC_IMAGE_T *mask;
} DISPMANX_ALPHA_T;

typedef struct {
  DISPMANX_FLAGS_ALPHA_T flags;
  uint32_t opacity;
  DISPMANX_RESOURCE_HANDLE_T mask;
} VC_DISPMANX_ALPHA_T;  /* for use with vmcs_host */

typedef enum {
  DISPMANX_FLAGS_CLAMP_NONE = 0,
  DISPMANX_FLAGS_CLAMP_LUMA_TRANSPARENT = 1,
#if __VCCOREVER__ >= 0x04000000
  DISPMANX_FLAGS_CLAMP_TRANSPARENT = 2,
  DISPMANX_FLAGS_CLAMP_REPLACE = 3
#else
  DISPMANX_FLAGS_CLAMP_CHROMA_TRANSPARENT = 2,
  DISPMANX_FLAGS_CLAMP_TRANSPARENT = 3
#endif
} DISPMANX_FLAGS_CLAMP_T;

typedef enum {
  DISPMANX_FLAGS_KEYMASK_OVERRIDE = 1,
  DISPMANX_FLAGS_KEYMASK_SMOOTH = 1 << 1,
  DISPMANX_FLAGS_KEYMASK_CR_INV = 1 << 2,
  DISPMANX_FLAGS_KEYMASK_CB_INV = 1 << 3,
  DISPMANX_FLAGS_KEYMASK_YY_INV = 1 << 4
} DISPMANX_FLAGS_KEYMASK_T;

typedef union {
  struct {
    uint8_t yy_upper;
    uint8_t yy_lower;
    uint8_t cr_upper;
    uint8_t cr_lower;
    uint8_t cb_upper;
    uint8_t cb_lower;
  } yuv;
  struct {
    uint8_t red_upper;
    uint8_t red_lower;
    uint8_t blue_upper;
    uint8_t blue_lower;
    uint8_t green_upper;
    uint8_t green_lower;
  } rgb;
} DISPMANX_CLAMP_KEYS_T;

typedef struct {
  DISPMANX_FLAGS_CLAMP_T mode;
  DISPMANX_FLAGS_KEYMASK_T key_mask;
  DISPMANX_CLAMP_KEYS_T key_value;
  uint32_t replace_value;
} DISPMANX_CLAMP_T;

typedef struct {
  int32_t width;
  int32_t height;
  DISPMANX_TRANSFORM_T transform;
  DISPLAY_INPUT_FORMAT_T input_format;
  uint32_t display_num;
} DISPMANX_MODEINFO_T;
//--------

typedef struct {
   DISPMANX_ELEMENT_HANDLE_T element;
   uint32_t width;
   uint32_t height;
} EGL_DISPMANX_WINDOW_T;

typedef struct tag_VC_RECT_T {
int32_t x;
int32_t y;
int32_t width;
int32_t height;
} VC_RECT_T;

typedef struct  CUBE_STATE_T
{
   
   // Put platform specific data here
   void       *platformData;

   // Put your user data here...
   void       *userData;

   // Put other user data here...
   void       *user_data;


   // Window width
   uint32_t       width;

   // Window height
   uint32_t       height;

   // Window handle
   struct Window    *hWnd;

   // Virtual Native Window handle
   EGL_DISPMANX_WINDOW_T nativewindow;

   // EGL display
   EGLDisplay  eglDisplay;

   // Other EGL display
   EGLDisplay  display;

   // EGL context
   EGLContext  eglContext;

   // Other EGL context
   EGLContext context;

   // EGL surface
   EGLSurface eglSurface;

   // Other EGL surface
   EGLSurface surface;

    // Callbacks EGL new function by HunoPPC
   void (ESCALLBACK *ReshapeFunc) ( void*,int, int );
   void (ESCALLBACK *drawFunc) ( void* );
   void (ESCALLBACK *shutdownFunc ) ( void* );
   void (ESCALLBACK *keyFunc) ( void*, unsigned char, int, int );
   void (ESCALLBACK *KeyUpFunc)(void*, unsigned char, int, int );
   void (ESCALLBACK *updateFunc) ( void*, float deltaTime );
   void (ESCALLBACK *DeinitFunc) ( void* );
   void (ESCALLBACK *JoysticksFunc)(void*, unsigned char, int, int);
   void (ESCALLBACK *MouseFunc)(void*, int, int, int, int );
   void (ESCALLBACK *MouseWheelFunc)(void*, int, int, int );
   void (ESCALLBACK *MotionFunc)(void*, int, int );
   void (ESCALLBACK *PassiveMotionFunc)(void*, int, int );
   void (ESCALLBACK *TimerFunc)(void*, int);

   // Callbacks GLUES new function by HunoPPC
   void (ESCALLBACK *gluReshapeFunc) ( void*,int, int );
   void (ESCALLBACK *gluDisplayFunc ) ( void* );
   void (ESCALLBACK *gluKeyboardFunc)(void*, unsigned char, int, int);
   void (ESCALLBACK *gluKeyboardUpFunc)(void*, unsigned char, int, int );
   void (ESCALLBACK *gluSpecialFunc)(void*, int, int, int );
   void (ESCALLBACK *gluSpecialUpFunc)(void*, int, int, int );
   void (ESCALLBACK *gluMouseFunc)(void*, int, int, int, int );
   void (ESCALLBACK *gluMouseWheelFunc)(void*, int, int, int );
   void (ESCALLBACK *gluMotionFunc)(void*, int, int );
   void (ESCALLBACK *gluPassiveMotionFunc)(void*, int, int );
   void (ESCALLBACK *gluIdleFunc ) ( void* );
   void (ESCALLBACK *gluJoysticksFunc)(void*, unsigned char, int, int);
   void (ESCALLBACK *gluTimerFunc)(void*, int);
   void (ESCALLBACK *gluWindowStatusFunc)(void*, int);
   void (ESCALLBACK *gluVisibilityFunc)(void*, int);

   void (ESCALLBACK *draw_func) (struct CUBE_STATE_T* ); 
   
} CUBE_STATE_T;

void ESUTIL_API bcm_host_init(void);
void ESUTIL_API bcm_host_deinit(void);
GLuint ESUTIL_API vc_dispmanx_display_open( uint32_t device );
void ESUTIL_API vc_dispmanx_display_open_mode( uint32_t device, uint32_t mode );
GLuint ESUTIL_API vc_dispmanx_update_start( int32_t priority );
GLuint  ESUTIL_API vc_dispmanx_element_add ( DISPMANX_UPDATE_HANDLE_T update,DISPMANX_DISPLAY_HANDLE_T display, int32_t layer,
                                                                                                                                       const VC_RECT_T *dest_rect,
                                                                                                                           DISPMANX_RESOURCE_HANDLE_T src,
                                                                                                                                         const VC_RECT_T *src_rect,
                                                                                                                           DISPMANX_PROTECTION_T protection,
                                                                                                                                    VC_DISPMANX_ALPHA_T *alpha,
                                                                                                                                        DISPMANX_CLAMP_T *clamp,
                                                                                                                          DISPMANX_TRANSFORM_T transform );
void ESUTIL_API vc_dispmanx_update_submit_sync( DISPMANX_UPDATE_HANDLE_T update );
int32_t ESUTIL_API graphics_get_display_size( const uint16_t display_number, uint32_t *width, uint32_t *height);
//end RPI project

typedef struct
{
    GLfloat   m[4][4];
} ESMatrix;

void ESUTIL_API glEnableClientState(GLenum cap);
void ESUTIL_API glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * ptr);
void ESUTIL_API glDisableClientState(GLenum cap);
void ESUTIL_API glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);

void Resize(int w,int h);

void ESUTIL_API esInitContext ( ESContext *esContext );
EGLSurface ESUTIL_API eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
				  EGLNativeWindowType win,
				  const EGLint *attrib_list);

EGLContext ESUTIL_API eglCreateContext(EGLDisplay dpy, EGLConfig config,
			    EGLContext share_context,
			    const EGLint *attrib_list);

GLboolean  ESUTIL_API eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
			  EGLSurface read, EGLContext ctx);

GLboolean ESUTIL_API esCreateWindow ( ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags );

GLboolean ESUTIL_API showMouse(GLboolean showmouse);

void ESUTIL_API esMainLoop (ESContext *esContext);
void ESUTIL_API glutMainLoop(ESContext *esContext);
/* return current time (in seconds) */
double ESUTIL_API esNow(void);
int ESUTIL_API eglGet(GLenum query);

void ESUTIL_API esReshapeFunc(ESContext *esContext, void(ESCALLBACK *ReshapeFunc)(ESContext *esContext, int, int y));
void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void (ESCALLBACK *drawFunc) (ESContext *esContext ) );
void ESUTIL_API esRegisterUpdateFunc(ESContext *esContext, void(ESCALLBACK *updateFunc)(ESContext *esContext, float));
void ESUTIL_API esRegisterKeyFunc(ESContext *esContext, void(ESCALLBACK *keyFunc)(ESContext *esContext, unsigned char, int, int));
void ESUTIL_API esRegisterKeyUpFunc(ESContext *esContext, void(ESCALLBACK *keyUpFunc)(ESContext *esContext, unsigned char, int, int));
void ESUTIL_API esRegisterShutdownFunc ( ESContext *esContext, void ( ESCALLBACK *shutdownFunc ) ( ESContext * ) );
void ESUTIL_API esRegisterDeinitFunc ( ESContext *esContext, void (ESCALLBACK *DeinitFunc) (ESContext * ) );
void ESUTIL_API esRegisterJoysticksFunc(ESContext *esContext, void(ESCALLBACK *JoysticksFunc)(ESContext *esContext, unsigned char, int, int y));
void ESUTIL_API esRegisterMouseFunc(ESContext *esContext, void (ESCALLBACK *MouseFunc)(ESContext *esContext, int, int, int, int ) );
void ESUTIL_API esRegisterMouseWheelFunc(ESContext *esContext, void (ESCALLBACK *MouseWheelFunc)(ESContext *esContext, int, int, int ) );
void ESUTIL_API esRegisterMotionFunc(ESContext *esContext, void (ESCALLBACK *MotionFunc)(ESContext *esContext, int, int ) );
void ESUTIL_API esRegisterPassiveMotionFunc(ESContext *esContext, void (ESCALLBACK *PassiveMotionFunc)(ESContext *esContext, int, int ) );

GLuint ESUTIL_API esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc );
GLuint ESUTIL_API esLoadShader ( GLenum type, const char *shaderSrc );
GLuint ESUTIL_API loadShadersFiles(const char *vertFileName, const char *fragFileName);
GLboolean  ESUTIL_API eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
EGLBoolean ESUTIL_API CreateEGLContext(struct Window *hWnd, EGLDisplay* eglDisplay, EGLContext* eglContext, EGLSurface* eglSurface, EGLint attribList[]);
		
void ESUTIL_API esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB);
void ESUTIL_API esMatrixLoadIdentity(ESMatrix *result);
void ESUTIL_API esMatrixLookAt ( ESMatrix *result,
                 float posX,    float posY,    float posZ,
                 float lookAtX, float lookAtY, float lookAtZ,
                 float upX,     float upY,     float upZ );
void ESUTIL_API esMatrixInverse3x3(ESMatrix *result, ESMatrix *input);
void ESUTIL_API esMatrixTranspose(ESMatrix *result, ESMatrix *input);
void ESUTIL_API esScale(ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);
void ESUTIL_API esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
void ESUTIL_API esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void ESUTIL_API esFrustum(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void ESUTIL_API esPerspective(ESMatrix *result, float fovy, float aspect, float nearZ, float farZ);
void ESUTIL_API esOrtho(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);

void ESUTIL_API esLogMessage(const char *formatStr, ...);
void ESUTIL_API esActivateFPS(int FPSactivated);
void ESUTIL_API eglRenderBpp(GLint bpp);
void ESUTIL_API eglStencilBpp(GLint bpp);
void ESUTIL_API esShutdown(ESContext *esContext);
void ESUTIL_API eglVsyncActivated(GLint VsyncActivated);
void ESUTIL_API eglFullScreenActivated(GLint FullScreenActivated);
EGLint ESUTIL_API eglGetError(void);
EGLDisplay ESUTIL_API eglGetDisplay(EGLNativeDisplayType display_id);
EGLBoolean ESUTIL_API eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLBoolean ESUTIL_API eglTerminate(EGLDisplay dpy);
const char * ESUTIL_API eglQueryString(EGLDisplay dpy, EGLint name);
EGLBoolean ESUTIL_API eglGetConfigs(EGLDisplay dpy, EGLConfig *configs,
			 EGLint config_size, EGLint *num_config);
EGLBoolean ESUTIL_API eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list,
			   EGLConfig *configs, EGLint config_size,
			   EGLint *num_config);
EGLBoolean ESUTIL_API eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config,
			      EGLint attribute, EGLint *value);
EGLSurface ESUTIL_API eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config,
				   const EGLint *attrib_list);
EGLSurface ESUTIL_API eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config,
				  EGLNativePixmapType pixmap,
				  const EGLint *attrib_list);
EGLBoolean ESUTIL_API eglDestroySurface(EGLDisplay dpy, EGLSurface surface);
EGLBoolean ESUTIL_API eglQuerySurface(EGLDisplay dpy, EGLSurface surface,
			   EGLint attribute, EGLint *value);
EGLBoolean ESUTIL_API eglBindAPI(EGLenum api);
EGLenum ESUTIL_API eglQueryAPI(void);
EGLBoolean ESUTIL_API eglWaitClient(void);
EGLBoolean ESUTIL_API eglReleaseThread(void);
EGLSurface ESUTIL_API eglCreatePbufferFromClientBuffer(
	      EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer,
	      EGLConfig config, const EGLint *attrib_list);
EGLBoolean ESUTIL_API eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface,
			    EGLint attribute, EGLint value);
EGLBoolean ESUTIL_API eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
EGLBoolean ESUTIL_API eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
EGLBoolean ESUTIL_API eglSwapInterval(EGLDisplay dpy, EGLint interval);
EGLBoolean ESUTIL_API eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
EGLContext ESUTIL_API eglGetCurrentContext(void);
EGLSurface ESUTIL_API eglGetCurrentSurface(EGLint readdraw);
EGLDisplay ESUTIL_API eglGetCurrentDisplay(void);
EGLBoolean ESUTIL_API eglQueryContext(EGLDisplay dpy, EGLContext ctx,
			   EGLint attribute, EGLint *value);
EGLBoolean ESUTIL_API eglWaitGL(void);
EGLBoolean ESUTIL_API eglWaitNative(EGLint engine);
EGLBoolean ESUTIL_API eglCopyBuffers(EGLDisplay dpy, EGLSurface surface,
			  EGLNativePixmapType target);
void ESUTIL_API *eglGetProcAddress(const char* name);
void ESUTIL_API esInitContextVersion(int major, int minor);
void ESUTIL_API esRepeatingTimerFunc(int millis);
void ESUTIL_API esTimerFunc(ESContext *esContext, int millis, void(ESCALLBACK *TimerFunc)(int), int arg);
void ESUTIL_API eschecktimers();
void ESUTIL_API esPostRedisplay(ESContext *esContext);
int ESUTIL_API setEglFPS(int fps);
GLuint ESUTIL_API esCreate_VBO(const GLsizeiptr size, const void* data, const GLenum usage);
void ESUTIL_API esRequesterInit(ESContext *esContext, GLint requesterActive, GLint width, GLint height, GLint SDLgl4esActive);

//load PNG image and return "(char *)pixels"
char* ESUTIL_API esLoad_PNG(const char *name, int *width, int *height);
//return texture ID of PNG image
GLuint ESUTIL_API esLoadPNG(const char *filename);
//Load TGA image and return texture ID of TGA image
GLuint ESUTIL_API esLoadTGA(const char *filename);
//Load BMP image and return texture ID of BMP image
GLuint ESUTIL_API esLoadBMP(const char *filename);
//Load JPEG image and return texture ID of JPEG image
GLuint ESUTIL_API esLoadJPEG(const char *filename);


int ESUTIL_API esGenSphere ( int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
                             GLfloat **texCoords, GLushort **indices );

int ESUTIL_API esGenCube ( float scale, GLfloat **vertices, GLfloat **normals,
                           GLfloat **texCoords, GLushort **indices );

int ESUTIL_API esGenSquareGrid ( int size, GLfloat **vertices, GLushort **indices );


//Audio esSound
int ESUTIL_API esRunSound_MOD_file(const char* modulefile);
int ESUTIL_API esStopSound_MOD_file(const char* modulefile);

//Get Processor Type string
const char * ESUTIL_API AmigaSys_GetProcessorString(void);

#ifdef __cplusplus
}
#endif
#endif //EGL_WRAP
