/*
 * SGI FREE SOFTWARE LICENSE B (Version 2.0, Sept. 18, 2008)
 * Copyright (C) 1991-2000 Silicon Graphics, Inc. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice including the dates of first publication and
 * either this permission notice or a reference to
 * http://oss.sgi.com/projects/FreeB/
 * shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * SILICON GRAPHICS, INC. BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of Silicon Graphics, Inc.
 * shall not be used in advertising or otherwise to promote the sale, use or
 * other dealings in this Software without prior written authorization from
 * Silicon Graphics, Inc.
 *
 * OpenGL ES 2.0 CM port of part of GLU by Mike Gorchak <mike@malva.ua>
 * GLUes for EGL Wrapper lib for OpenGLES 2.0 and Warp3D-NOVA AmigaOS4 by Hugues "HunoPPC" Nouvel  2022
 */

#ifndef __glues_h__ 
#define __glues_h__

/*
 * The GLUT|ES, freeglut and GLUT API versions
 */
#define  GLUTES					1
#define  FREEGLUT				1
#define  GLUT_API_VERSION		4
#define  FREEGLUTES_VERSION_1_0	1
#define  FREEGLUT_VERSION_2_0	1

/* XXX Update these for each release! */
#define  VERSION_MAJOR 2
#define  VERSION_MINOR 5
#define  VERSION_PATCH 3

#include <EGL/egl_wrap.h>
#include <libraries/lowlevel.h>

typedef double	  GLdouble;	  /* double precision float */

#if defined(USE_MGL_NAMESPACE)
#include "glues_mangle.h"
#endif

#ifdef __cplusplus
   extern "C" {
#endif
/*************************************************************/
/*
 * GLUT API macro definitions -- windows and menu related definitions
 */
#define  GLUT_MENU_NOT_IN_USE                   0x0000
#define  GLUT_MENU_IN_USE                       0x0001
#define  GLUT_NOT_VISIBLE                       0x0000
#define  GLUT_VISIBLE                           0x0001
#define  GLUT_HIDDEN                            0x0000
#define  GLUT_FULLY_RETAINED                    0x0001
#define  GLUT_PARTIALLY_RETAINED                0x0002
#define  GLUT_FULLY_COVERED                     0x0003

#define  GLUT_RGBA		 (1L << 0)
#define  GLUT_RGB		 GLUT_RGBA
#define  GLUT_SINGLE	 0
#define  GLUT_DOUBLE	 (1L << 1)
#define  GLUT_DEPTH		 (1L << 2)
#define  GLUT_STENCIL	 (1L << 3)

/*
 * GLUT API macro definitions -- the special key codes:
 */
#define    GLUT_KEY_F1                 282
#define    GLUT_KEY_F2                 283
#define    GLUT_KEY_F3                 284
#define    GLUT_KEY_F4                 285
#define    GLUT_KEY_F5                 286
#define    GLUT_KEY_F6                 287
#define    GLUT_KEY_F7                 288
#define    GLUT_KEY_F8                 289
#define    GLUT_KEY_F9                 290
#define    GLUT_KEY_F10                291
#define    GLUT_KEY_F11                292
#define    GLUT_KEY_F12                293
#define    GLUT_KEY_LEFT               CURSORLEFT
#define    GLUT_KEY_UP                 CURSORUP
#define    GLUT_KEY_RIGHT              CURSORRIGHT
#define    GLUT_KEY_DOWN               CURSORDOWN
#define    GLUT_KEY_PAGE_UP            280
#define    GLUT_KEY_PAGE_DOWN          281
#define    GLUT_KEY_HOME               278
#define    GLUT_KEY_END                279
#define    GLUT_KEY_INSERT             277

#define    GLUT_UNKNOWN		           0
#define    GLUT_FIRST	               0
#define    GLUT_BACKSPACE	           8
#define    GLUT_TAB		               9
#define    GLUT_CLEAR	               12
#define    GLUT_RETURN	               13
#define    GLUT_PAUSE	               19
#define    GLUT_ESCAPE	               27
#define    GLUT_SPACE	               32
#define    GLUT_EXCLAIM		           33
#define    GLUT_QUOTEDBL	           34
#define    GLUT_HASH	               35
#define    GLUT_DOLLAR	               36
#define    GLUT_AMPERSAND	           38
#define    GLUT_QUOTE	               39
#define    GLUT_LEFTPAREN	           40
#define    GLUT_RIGHTPAREN	           41
#define    GLUT_ASTERISK	           42
#define    GLUT_PLUS	               43
#define    GLUT_COMMA	               44
#define    GLUT_MINUS	               45
#define    GLUT_PERIOD	               46
#define    GLUT_SLASH	               47
#define    GLUT_KEY_0		           48
#define	   GLUT_KEY_1		           49
#define	   GLUT_KEY_2		           50
#define	   GLUT_KEY_3		           51
#define	   GLUT_KEY_4		           52
#define	   GLUT_KEY_5		           53
#define	   GLUT_KEY_6		           54
#define	   GLUT_KEY_7		           55
#define	   GLUT_KEY_8		           56
#define	   GLUT_KEY_9		           57
#define    GLUT_KEY_LEFTBRACKET	       91
#define    GLUT_KEY_BACKSLASH	       92
#define    GLUT_KEY_RIGHTBRACKET       93
#define    GLUT_KEY_CARET	           94
#define    GLUT_KEY_UNDERSCORE	       95
#define    GLUT_KEY_BACKQUOTE	       96
#define    GLUT_KEY_a		           97
#define    GLUT_KEY_b		           98
#define    GLUT_KEY_c		           99
#define    GLUT_KEY_d		           100
#define    GLUT_KEY_e		           101
#define    GLUT_KEY_f		           102
#define    GLUT_KEY_g		           103
#define    GLUT_KEY_h		           104
#define    GLUT_KEY_i		           105
#define    GLUT_KEY_j		           106
#define    GLUT_KEY_k		           107
#define    GLUT_KEY_l		           108
#define    GLUT_KEY_m		           109
#define    GLUT_KEY_n		           110
#define    GLUT_KEY_o		           111
#define    GLUT_KEY_p		           112
#define    GLUT_KEY_q		           113
#define    GLUT_KEY_r		           114
#define    GLUT_KEY_s		           115
#define    GLUT_KEY_t		           116
#define    GLUT_KEY_u		           117
#define    GLUT_KEY_v		           118
#define    GLUT_KEY_w		           119
#define    GLUT_KEY_x		           120
#define    GLUT_KEY_y		           121
#define    GLUT_KEY_z		           122
#define    GLUT_KEY_DELETE	           127
#define    GLUT_KEY_DELETE             127
#define    GLUT_KEY_SHIFT_L            304
#define    GLUT_KEY_SHIFT_R            303
#define    GLUT_KEY_CTRL_L             306
#define    GLUT_KEY_CTRL_R             305
#define    GLUT_KEY_ALT_L              308
#define    GLUT_KEY_ALT_R              307

#define    GLUT_KEY_ESCAPE             033
#define    GLUT_KEY_SPACE              040

#define    GLUT_JOY_LEFT               2
#define    GLUT_JOY_UP                 8
#define    GLUT_JOY_RIGHT              5
#define    GLUT_JOY_DOWN               4
#define    GLUT_JOY_B0                 joystick.b0
#define    GLUT_JOY_B1                 joystick.b1
#define    GLUT_JOY_B2                 joystick.b2
#define    GLUT_JOY_B3                 joystick.b3
#define    GLUT_JOY_B4                 joystick.b4
#define    GLUT_JOY_B5                 joystick.b5
#define    GLUT_JOY_B6                 joystick.b6

/*
 * GLUT API macro definitions -- mouse state definitions
 */
#define    GLUT_LEFT_BUTTON           0x0000
#define    GLUT_MIDDLE_BUTTON         0x0001
#define    GLUT_RIGHT_BUTTON          0x0002
#define    GLUT_DOWN                  0x0000
#define    GLUT_UP                    0x0001
#define    GLUT_LEFT                  0x0000 
#define    GLUT_ENTERED               0x0001

/*
 * GLUT API macro definitions -- the glutGet parameters
 */
#define  GLUT_WINDOW_X                      0x0064
#define  GLUT_WINDOW_Y                      0x0065
#define  GLUT_WINDOW_WIDTH                  0x0066
#define  GLUT_WINDOW_HEIGHT                 0x0067
#define  GLUT_WINDOW_BUFFER_SIZE            0x0068
#define  GLUT_WINDOW_STENCIL_SIZE           0x0069
#define  GLUT_WINDOW_DEPTH_SIZE             0x006A
#define  GLUT_WINDOW_RED_SIZE               0x006B
#define  GLUT_WINDOW_GREEN_SIZE             0x006C
#define  GLUT_WINDOW_BLUE_SIZE              0x006D
#define  GLUT_WINDOW_ALPHA_SIZE             0x006E
#define  GLUT_WINDOW_ACCUM_RED_SIZE         0x006F
#define  GLUT_WINDOW_ACCUM_GREEN_SIZE       0x0070
#define  GLUT_WINDOW_ACCUM_BLUE_SIZE        0x0071
#define  GLUT_WINDOW_ACCUM_ALPHA_SIZE       0x0072
#define  GLUT_WINDOW_DOUBLEBUFFER           0x0073
#define  GLUT_WINDOW_RGBA                   0x0074
#define  GLUT_WINDOW_PARENT                 0x0075
#define  GLUT_WINDOW_NUM_CHILDREN           0x0076
#define  GLUT_WINDOW_COLORMAP_SIZE          0x0077
#define  GLUT_WINDOW_NUM_SAMPLES            0x0078
#define  GLUT_WINDOW_STEREO                 0x0079
#define  GLUT_WINDOW_CURSOR                 0x007A

#define  GLUT_SCREEN_WIDTH                  0x00C8
#define  GLUT_SCREEN_HEIGHT                 0x00C9
#define  GLUT_SCREEN_WIDTH_MM               0x00CA
#define  GLUT_SCREEN_HEIGHT_MM              0x00CB
#define  GLUT_MENU_NUM_ITEMS                0x012C
#define  GLUT_DISPLAY_MODE_POSSIBLE         0x0190
#define  GLUT_INIT_WINDOW_X                 0x01F4
#define  GLUT_INIT_WINDOW_Y                 0x01F5
#define  GLUT_INIT_WINDOW_WIDTH             0x01F6
#define  GLUT_INIT_WINDOW_HEIGHT            0x01F7
#define  GLUT_INIT_DISPLAY_MODE             0x01F8
#define  GLUT_ELAPSED_TIME                  0x02BC
#define  GLUT_WINDOW_FORMAT_ID              0x007B
#define  GLUT_INIT_STATE                    0x007C

/*
 * GLUT API macro definitions -- game mode definitions
 */
#define  GLUT_GAME_MODE_ACTIVE              0x0000
#define  GLUT_GAME_MODE_POSSIBLE            0x0001
#define  GLUT_GAME_MODE_WIDTH               0x0002
#define  GLUT_GAME_MODE_HEIGHT              0x0003
#define  GLUT_GAME_MODE_PIXEL_DEPTH         0x0004
#define  GLUT_GAME_MODE_REFRESH_RATE        0x0005
#define  GLUT_GAME_MODE_DISPLAY_CHANGED     0x0006

/*
 * GLUT API Extension macro definitions -- behaviour when the user clicks on an "x" to close a window
 */
#define GLUT_ACTION_EXIT                         0
#define GLUT_ACTION_GLUTMAINLOOP_RETURNS         1
#define GLUT_ACTION_CONTINUE_EXECUTION           2

/*
 * Create a new rendering context when the user opens a new window?
 */
#define GLUT_CREATE_NEW_CONTEXT                  0
#define GLUT_USE_CURRENT_CONTEXT                 1

/*
 * GLUT API Extension macro definitions -- the glutGet parameters
 */
#define  GLUT_ACTION_ON_WINDOW_CLOSE        0x01F9

#define  GLUT_WINDOW_BORDER_WIDTH           0x01FA
#define  GLUT_WINDOW_HEADER_HEIGHT          0x01FB

#define  GLUT_VERSION                       0x01FC

#define  GLUT_RENDERING_CONTEXT             0x01FD

/*************************************************************/


/*************************************************************/
/* Extensions */
#define GLU_EXT_object_space_tess          1
#define GLU_EXT_nurbs_tessellator          1

/* Boolean */
#define GLU_FALSE                          0
#define GLU_TRUE                           1

/* Version */
#define GLU_VERSION_1_1                    1
#define GLU_VERSION_1_2                    1
#define GLU_VERSION_1_3                    1

/* StringName */
#define GLU_VERSION                        100800
#define GLU_EXTENSIONS                     100801

/* ErrorCode */
#define GLU_INVALID_ENUM                   100900
#define GLU_INVALID_VALUE                  100901
#define GLU_OUT_OF_MEMORY                  100902
#define GLU_INCOMPATIBLE_GL_VERSION        100903
#define GLU_INVALID_OPERATION              100904

/* NurbsDisplay */
/*      GLU_FILL */
#define GLU_OUTLINE_POLYGON                100240
#define GLU_OUTLINE_PATCH                  100241

/* NurbsCallback */
#define GLU_NURBS_ERROR                    100103
#define GLU_ERROR                          100103
#define GLU_NURBS_BEGIN                    100164
#define GLU_NURBS_BEGIN_EXT                100164
#define GLU_NURBS_VERTEX                   100165
#define GLU_NURBS_VERTEX_EXT               100165
#define GLU_NURBS_NORMAL                   100166
#define GLU_NURBS_NORMAL_EXT               100166
#define GLU_NURBS_COLOR                    100167
#define GLU_NURBS_COLOR_EXT                100167
#define GLU_NURBS_TEXTURE_COORD            100168
#define GLU_NURBS_TEX_COORD_EXT            100168
#define GLU_NURBS_END                      100169
#define GLU_NURBS_END_EXT                  100169
#define GLU_NURBS_BEGIN_DATA               100170
#define GLU_NURBS_BEGIN_DATA_EXT           100170
#define GLU_NURBS_VERTEX_DATA              100171
#define GLU_NURBS_VERTEX_DATA_EXT          100171
#define GLU_NURBS_NORMAL_DATA              100172
#define GLU_NURBS_NORMAL_DATA_EXT          100172
#define GLU_NURBS_COLOR_DATA               100173
#define GLU_NURBS_COLOR_DATA_EXT           100173
#define GLU_NURBS_TEXTURE_COORD_DATA       100174
#define GLU_NURBS_TEX_COORD_DATA_EXT       100174
#define GLU_NURBS_END_DATA                 100175
#define GLU_NURBS_END_DATA_EXT             100175

/* NurbsError */
#define GLU_NURBS_ERROR1                   100251
#define GLU_NURBS_ERROR2                   100252
#define GLU_NURBS_ERROR3                   100253
#define GLU_NURBS_ERROR4                   100254
#define GLU_NURBS_ERROR5                   100255
#define GLU_NURBS_ERROR6                   100256
#define GLU_NURBS_ERROR7                   100257
#define GLU_NURBS_ERROR8                   100258
#define GLU_NURBS_ERROR9                   100259
#define GLU_NURBS_ERROR10                  100260
#define GLU_NURBS_ERROR11                  100261
#define GLU_NURBS_ERROR12                  100262
#define GLU_NURBS_ERROR13                  100263
#define GLU_NURBS_ERROR14                  100264
#define GLU_NURBS_ERROR15                  100265
#define GLU_NURBS_ERROR16                  100266
#define GLU_NURBS_ERROR17                  100267
#define GLU_NURBS_ERROR18                  100268
#define GLU_NURBS_ERROR19                  100269
#define GLU_NURBS_ERROR20                  100270
#define GLU_NURBS_ERROR21                  100271
#define GLU_NURBS_ERROR22                  100272
#define GLU_NURBS_ERROR23                  100273
#define GLU_NURBS_ERROR24                  100274
#define GLU_NURBS_ERROR25                  100275
#define GLU_NURBS_ERROR26                  100276
#define GLU_NURBS_ERROR27                  100277
#define GLU_NURBS_ERROR28                  100278
#define GLU_NURBS_ERROR29                  100279
#define GLU_NURBS_ERROR30                  100280
#define GLU_NURBS_ERROR31                  100281
#define GLU_NURBS_ERROR32                  100282
#define GLU_NURBS_ERROR33                  100283
#define GLU_NURBS_ERROR34                  100284
#define GLU_NURBS_ERROR35                  100285
#define GLU_NURBS_ERROR36                  100286
#define GLU_NURBS_ERROR37                  100287

/* NurbsProperty */
#define GLU_AUTO_LOAD_MATRIX               100200
#define GLU_CULLING                        100201
#define GLU_SAMPLING_TOLERANCE             100203
#define GLU_DISPLAY_MODE                   100204
#define GLU_PARAMETRIC_TOLERANCE           100202
#define GLU_SAMPLING_METHOD                100205
#define GLU_U_STEP                         100206
#define GLU_V_STEP                         100207
#define GLU_NURBS_MODE                     100160
#define GLU_NURBS_MODE_EXT                 100160
#define GLU_NURBS_TESSELLATOR              100161
#define GLU_NURBS_TESSELLATOR_EXT          100161
#define GLU_NURBS_RENDERER                 100162
#define GLU_NURBS_RENDERER_EXT             100162

/* NurbsSampling */
#define GLU_OBJECT_PARAMETRIC_ERROR        100208
#define GLU_OBJECT_PARAMETRIC_ERROR_EXT    100208
#define GLU_OBJECT_PATH_LENGTH             100209
#define GLU_OBJECT_PATH_LENGTH_EXT         100209
#define GLU_PATH_LENGTH                    100215
#define GLU_PARAMETRIC_ERROR               100216
#define GLU_DOMAIN_DISTANCE                100217

/* NurbsTrim */
#define GLU_MAP1_TRIM_2                    100210
#define GLU_MAP1_TRIM_3                    100211

/* QuadricDrawStyle */
#define GLU_POINT                          100010
#define GLU_LINE                           100011
#define GLU_FILL                           100012
#define GLU_SILHOUETTE                     100013

/* QuadricCallback */
/*      GLU_ERROR */

/* QuadricNormal */
#define GLU_SMOOTH                         100000
#define GLU_FLAT                           100001
#define GLU_NONE                           100002

/* QuadricOrientation */
#define GLU_OUTSIDE                        100020
#define GLU_INSIDE                         100021

/* TessCallback */
#define GLU_TESS_BEGIN                     100100
#define GLU_BEGIN                          100100
#define GLU_TESS_VERTEX                    100101
#define GLU_VERTEX                         100101
#define GLU_TESS_END                       100102
#define GLU_END                            100102
#define GLU_TESS_ERROR                     100103
#define GLU_TESS_EDGE_FLAG                 100104
#define GLU_EDGE_FLAG                      100104
#define GLU_TESS_COMBINE                   100105
#define GLU_TESS_BEGIN_DATA                100106
#define GLU_TESS_VERTEX_DATA               100107
#define GLU_TESS_END_DATA                  100108
#define GLU_TESS_ERROR_DATA                100109
#define GLU_TESS_EDGE_FLAG_DATA            100110
#define GLU_TESS_COMBINE_DATA              100111

/* TessContour */
#define GLU_CW                             100120
#define GLU_CCW                            100121
#define GLU_INTERIOR                       100122
#define GLU_EXTERIOR                       100123
#define GLU_UNKNOWN                        100124

/* TessProperty */
#define GLU_TESS_WINDING_RULE              100140
#define GLU_TESS_BOUNDARY_ONLY             100141
#define GLU_TESS_TOLERANCE                 100142

/* TessError */
#define GLU_TESS_ERROR1                    100151
#define GLU_TESS_ERROR2                    100152
#define GLU_TESS_ERROR3                    100153
#define GLU_TESS_ERROR4                    100154
#define GLU_TESS_ERROR5                    100155
#define GLU_TESS_ERROR6                    100156
#define GLU_TESS_ERROR7                    100157
#define GLU_TESS_ERROR8                    100158
#define GLU_TESS_MISSING_BEGIN_POLYGON     100151
#define GLU_TESS_MISSING_BEGIN_CONTOUR     100152
#define GLU_TESS_MISSING_END_POLYGON       100153
#define GLU_TESS_MISSING_END_CONTOUR       100154
#define GLU_TESS_COORD_TOO_LARGE           100155
#define GLU_TESS_NEED_COMBINE_CALLBACK     100156

/* TessWinding */
#define GLU_TESS_WINDING_ODD               100130
#define GLU_TESS_WINDING_NONZERO           100131
#define GLU_TESS_WINDING_POSITIVE          100132
#define GLU_TESS_WINDING_NEGATIVE          100133
#define GLU_TESS_WINDING_ABS_GEQ_TWO       100134

/*************************************************************/

#ifdef __cplusplus
class GLUnurbs;
class GLUquadric;
class GLUtesselator;
#else
typedef struct GLUnurbs GLUnurbs;
typedef struct GLUquadric GLUquadric;
typedef struct GLUtesselator GLUtesselator;
#endif

typedef GLUnurbs GLUnurbsObj;
typedef GLUquadric GLUquadricObj;
typedef GLUtesselator GLUtesselatorObj;
typedef GLUtesselator GLUtriangulatorObj;

#define GLU_TESS_MAX_COORD 1.0e150

/* Internal convenience typedefs */
typedef void (ESUTIL_API _GLUfuncptr)(void);

void  ESUTIL_API gluBeginCurve (GLUnurbs* nurb);
void  ESUTIL_API gluBeginPolygon (GLUtesselator* tess);
void  ESUTIL_API gluBeginSurface (GLUnurbs* nurb);
void  ESUTIL_API gluBeginTrim (GLUnurbs* nurb);
GLint ESUTIL_API gluBuild1DMipmapLevels (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data);
GLint ESUTIL_API gluBuild1DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data);
GLint ESUTIL_API gluBuild2DMipmapLevels (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data);
GLint ESUTIL_API gluBuild2DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data);
GLint ESUTIL_API gluBuild3DMipmapLevels (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data);
GLint ESUTIL_API gluBuild3DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
GLboolean ESUTIL_API gluCheckExtension (const GLubyte *extName, const GLubyte *extString);
void  ESUTIL_API gluCylinder (GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
void  ESUTIL_API gluDeleteNurbsRenderer (GLUnurbs* nurb);
void  ESUTIL_API gluDeleteQuadric (GLUquadric* quad);
void  ESUTIL_API gluDeleteTess (GLUtesselator* tess);
void  ESUTIL_API gluDisk (GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops);
void  ESUTIL_API gluEndCurve (GLUnurbs* nurb);
void  ESUTIL_API gluEndPolygon (GLUtesselator* tess);
void  ESUTIL_API gluEndSurface (GLUnurbs* nurb);
void  ESUTIL_API gluEndTrim (GLUnurbs* nurb);
const GLubyte * ESUTIL_API gluErrorString (GLenum error);
void  ESUTIL_API gluGetNurbsProperty (GLUnurbs* nurb, GLenum property, GLfloat* data);
const GLubyte * ESUTIL_API gluGetString (GLenum name);
void  ESUTIL_API gluGetTessProperty (GLUtesselator* tess, GLenum which, GLdouble* data);
void  ESUTIL_API gluLoadSamplingMatrices (GLUnurbs* nurb, const GLfloat *model, const GLfloat *perspective, const GLint *view);
void  ESUTIL_API gluLookAt (GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);
GLUnurbs* ESUTIL_API gluNewNurbsRenderer (void);
GLUquadric* ESUTIL_API gluNewQuadric (void);
GLUtesselator* ESUTIL_API gluNewTess (void);
void  ESUTIL_API gluNextContour (GLUtesselator* tess, GLenum type);
void  ESUTIL_API gluNurbsCallback (GLUnurbs* nurb, GLenum which, _GLUfuncptr CallBackFunc);
void  ESUTIL_API gluNurbsCallbackData (GLUnurbs* nurb, GLvoid* userData);
void  ESUTIL_API gluNurbsCallbackDataEXT (GLUnurbs* nurb, GLvoid* userData);
void  ESUTIL_API gluNurbsCurve (GLUnurbs* nurb, GLint knotCount, GLfloat *knots, GLint stride, GLfloat *control, GLint order, GLenum type);
void  ESUTIL_API gluNurbsProperty (GLUnurbs* nurb, GLenum property, GLfloat value);
void  ESUTIL_API gluNurbsSurface (GLUnurbs* nurb, GLint sKnotCount, GLfloat* sKnots, GLint tKnotCount, GLfloat* tKnots, GLint sStride, GLint tStride, GLfloat* control, GLint sOrder, GLint tOrder, GLenum type);
void  ESUTIL_API gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
void  ESUTIL_API gluPartialDisk (GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops, GLdouble start, GLdouble sweep);
void  ESUTIL_API gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
void  ESUTIL_API gluPickMatrix (GLdouble x, GLdouble y, GLdouble delX, GLdouble delY, GLint *viewport);
GLint ESUTIL_API gluProject (GLdouble objX, GLdouble objY, GLdouble objZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* winX, GLdouble* winY, GLdouble* winZ);
void  ESUTIL_API gluPwlCurve (GLUnurbs* nurb, GLint count, GLfloat* data, GLint stride, GLenum type);
void  ESUTIL_API gluQuadricCallback (GLUquadric* quad, GLenum which, _GLUfuncptr CallBackFunc);
void  ESUTIL_API gluQuadricDrawStyle (GLUquadric* quad, GLenum draw);
void  ESUTIL_API gluQuadricNormals (GLUquadric* quad, GLenum normal);
void  ESUTIL_API gluQuadricOrientation (GLUquadric* quad, GLenum orientation);
void  ESUTIL_API gluQuadricTexture (GLUquadric* quad, GLboolean texture);
GLint ESUTIL_API gluScaleImage (GLenum format, GLsizei wIn, GLsizei hIn, GLenum typeIn, const void *dataIn, GLsizei wOut, GLsizei hOut, GLenum typeOut, GLvoid* dataOut);
void  ESUTIL_API gluSphere (GLUquadric* quad, GLdouble radius, GLint slices, GLint stacks);
void  ESUTIL_API gluTessBeginContour (GLUtesselator* tess);
void  ESUTIL_API gluTessBeginPolygon (GLUtesselator* tess, GLvoid* data);
void  ESUTIL_API gluTessCallback (GLUtesselator* tess, GLenum which, _GLUfuncptr CallBackFunc);
void  ESUTIL_API gluTessEndContour (GLUtesselator* tess);
void  ESUTIL_API gluTessEndPolygon (GLUtesselator* tess);
void  ESUTIL_API gluTessNormal (GLUtesselator* tess, GLdouble valueX, GLdouble valueY, GLdouble valueZ);
void  ESUTIL_API gluTessProperty (GLUtesselator* tess, GLenum which, GLdouble data);
void  ESUTIL_API gluTessVertex (GLUtesselator* tess, GLdouble *location, GLvoid* data);
GLint ESUTIL_API gluUnProject (GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ);
GLint ESUTIL_API gluUnProject4 (GLdouble winX, GLdouble winY, GLdouble winZ, GLdouble clipW, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble nearVal, GLdouble farVal, GLdouble* objX, GLdouble* objY, GLdouble* objZ, GLdouble* objW);
/*
 * Colormap functions
 */
void ESUTIL_API glutSetColor( int color, GLfloat red, GLfloat green, GLfloat blue );
GLfloat ESUTIL_API glutGetColor( int color, int component );
void ESUTIL_API glutCopyColormap( int window );
/*
 * Game mode functions, see glutes_gamemode.c
 */
void ESUTIL_API glutGameModeString( const char* string );
int  ESUTIL_API glutEnterGameMode( void );
void ESUTIL_API glutLeaveGameMode( void );
int  ESUTIL_API glutGameModeGet( GLenum query );


//New functions glutes 2020 by HunoPPC
void ESUTIL_API glutWireCube( GLdouble dSize );
void ESUTIL_API glutSolidCube( GLdouble dSize );
void ESUTIL_API glutWireSphere( GLdouble radius, GLint slices, GLint stacks );
void ESUTIL_API glutSolidSphere( GLdouble radius, GLint slices, GLint stacks );
void ESUTIL_API glutWireCone( GLdouble base, GLdouble height, GLint slices, GLint stacks);
void ESUTIL_API glutSolidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks );
void ESUTIL_API glutWireTorus( GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings );
void ESUTIL_API glutSolidTorus( GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings );
void ESUTIL_API glutWireTeapot( GLdouble size );     
void ESUTIL_API glutSolidTeapot( GLdouble size ); 
void ESUTIL_API glutWireDodecahedron( void );  
void ESUTIL_API glutSolidDodecahedron( void ); 
void ESUTIL_API glutWireOctahedron( void ); 
void ESUTIL_API glutSolidOctahedron( void ); 
void ESUTIL_API glutWireTetrahedron( void ); 
void ESUTIL_API glutSolidTetrahedron( void ); 
void ESUTIL_API glutWireIcosahedron( void ); 
void ESUTIL_API glutSolidIcosahedron( void ); 
void ESUTIL_API glutWireRhombicDodecahedron( void );
void ESUTIL_API glutSolidRhombicDodecahedron( void );  
void ESUTIL_API glutWireSierpinskiSponge ( int num_levels, GLdouble offset[3], GLdouble scale );  
void ESUTIL_API glutSolidSierpinskiSponge ( int num_levels, GLdouble offset[3], GLdouble scale ); 


//not supported actually on AOS4 dummy functions
void ESUTIL_API gluEnable(GLenum cap);
void ESUTIL_API gluDisable(GLenum cap);
void ESUTIL_API gluGetFloatv(GLenum pname, GLfloat* params);
void ESUTIL_API gluGetIntegerv(GLenum pname, GLint* params);
void ESUTIL_API gluViewport(GLint x, GLint y, GLsizei width, GLsizei height);
int  ESUTIL_API glutCreateSubWindow( ESContext *esContext, int parentID, int x, int y, int width, int height );
void ESUTIL_API glutSetWindow(ESContext *esContext, int ID );
int  ESUTIL_API glutGetWindow(ESContext *esContext);
void ESUTIL_API glutShowWindow( ESContext *esContext );
void ESUTIL_API glutHideWindow( ESContext *esContext );
void ESUTIL_API glutIconifyWindow( ESContext *esContext );
void ESUTIL_API glutSetWindowTitle(ESContext *esContext, const char* title );
void ESUTIL_API glutSetIconTitle(ESContext *esContext, const char* title );
void ESUTIL_API glutDestroyWindow(ESContext *esContext, int windowID );
void ESUTIL_API glutPositionWindow(ESContext *esContext, int x, int y );
void ESUTIL_API glutReshapeWindow(ESContext *esContext, int width, int height );
void ESUTIL_API glutPopWindow( ESContext *esContext );
void ESUTIL_API glutPushWindow( ESContext *esContext );
void ESUTIL_API glutForceJoystickFunc( void );
//not supported on AOS4 dummy functions

/*
 * Initialization functions
 */
void ESUTIL_API glutInitDisplayString( const char* displayMode );
void ESUTIL_API glutInit(ESContext *esContext, int * pargc, char** argv);
void ESUTIL_API glutInitWindowPosition( int x, int y );
void ESUTIL_API glutInitWindowSize(int width, int height);
void ESUTIL_API glutInitDisplayMode(unsigned int displayMode);
void ESUTIL_API glutInitContextVersion(int major, int minor);

/*
 * Window management functions
 */
int  ESUTIL_API glutCreateWindow(ESContext *esContext, const char* title ); 
void ESUTIL_API glutLogMessage(const char *formatStr, ...);
void ESUTIL_API glutWarpPointer( int x, int y );
void ESUTIL_API glutSetCursor( int cursor );
void ESUTIL_API glutSwapBuffers(void);

/*
 * State setting and retrieval functions
 */
int ESUTIL_API glutGet(GLenum query);
int ESUTIL_API glutLayerGet( GLenum eWhat );
int ESUTIL_API glutDeviceGet( GLenum query );
int ESUTIL_API glutGetModifiers( void );

/*
 * Global callback functions
 */
void ESUTIL_API glutIdleFunc(ESContext *esContext, void (ESCALLBACK *gluIdleFunc) (ESContext *esContext ));
void ESUTIL_API glutTimerFunc(ESContext *esContext, int millis, void(ESCALLBACK *gluTimerFunc)(int) , int arg);

/*
 * Misc keyboard and joystick functions
 */
void ESUTIL_API glutIgnoreKeyRepeat( int ignore );
void ESUTIL_API glutSetKeyRepeat( int repeatMode );

/*
 * Misc functions
 */
int  ESUTIL_API glutExtensionSupported( const char* extension );
void ESUTIL_API glutReportErrors( void );
void ESUTIL_API glutSimulateButton(int button, int x, int y);

/*
 * Window management functions
 */
void ESUTIL_API glutPostWindowRedisplay( int window );
void ESUTIL_API glutFullScreen();
void ESUTIL_API glutPostRedisplay(ESContext *esContext);

/*
 * Window-specific callback functions
 */
void ESUTIL_API glutKeyboardFunc( ESContext *esContext, void(ESCALLBACK *gluKeyboardFunc)(ESContext *esContext, unsigned char, int, int));
void ESUTIL_API glutSpecialFunc(ESContext *esContext, void (ESCALLBACK *gluSpecialFunc)(ESContext *esContext, int, int, int));
void ESUTIL_API glutReshapeFunc(ESContext *esContext, void (ESCALLBACK *gluReshapeFunc)(ESContext *esContext, int, int y));
void ESUTIL_API glutVisibilityFunc(ESContext *esContext, void (ESCALLBACK * gluVisibilityFunc)(ESContext *esContext, int));
void ESUTIL_API glutDisplayFunc(ESContext *esContext, void (ESCALLBACK *gluDisplayFunc) (ESContext *esContext));
void ESUTIL_API glutMouseFunc(ESContext *esContext, void (ESCALLBACK *gluMouseFunc)(ESContext *esContext, int, int, int, int));
void ESUTIL_API glutMouseWheelFunc(ESContext *esContext, void (ESCALLBACK *gluMouseWheelFunc)(ESContext *esContext, int, int, int));
void ESUTIL_API glutMotionFunc(ESContext *esContext, void (ESCALLBACK *gluMotionFunc)(ESContext *esContext, int, int));
void ESUTIL_API glutPassiveMotionFunc(ESContext *esContext, void (ESCALLBACK *gluPassiveMotionFunc)(ESContext *esContext, int, int));
void ESUTIL_API glutEntryFunc(ESContext *esContext, void(ESCALLBACK *gluEntryFunc)(ESContext *esContext, int));
void ESUTIL_API glutKeyboardUpFunc( ESContext *esContext, void(ESCALLBACK *gluKeyboardUpFunc)(ESContext *esContext, unsigned char, int, int));
void ESUTIL_API glutSpecialUpFunc(ESContext *esContext, void (ESCALLBACK *gluSpecialUpFunc)(ESContext *esContext, int, int, int));
void ESUTIL_API glutJoysticksFunc( ESContext *esContext, void(ESCALLBACK *gluJoysticksFunc)(ESContext *esContext, unsigned char, int, int));
void ESUTIL_API glutWindowStatusFunc(ESContext *esContext, void (ESCALLBACK *gluWindowStatusFunc)(ESContext *esContext, int));
void ESUTIL_API glutCloseFunc(ESContext *esContext, void (ESCALLBACK *gluCloseFunc) (ESContext *esContext));


void ESUTIL_API glutRepeatingTimerFunc(int millis);
void ESUTIL_API checktimers();
int  ESUTIL_API setGluesFPS(int fps);
void ESUTIL_API glutSetOption( GLenum eWhat, int value );
int  ESUTIL_API GetStateKEYModifiers(ULONG rawkey);
void ESUTIL_API esGluLookAt(ESMatrix *result, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

/*
 * ****************************************************************************
 * The non-GLUT-compatible extensions to the GLUT|ES library include file
 * ****************************************************************************
 */

/*
 * GLUT API Extension macro definitions -- behaviour when the user clicks on an "x" to close a window
 */
#define GLUT_ACTION_EXIT                         0
#define GLUT_ACTION_GLUTMAINLOOP_RETURNS         1
#define GLUT_ACTION_CONTINUE_EXECUTION           2

/*
 * Create a new rendering context when the user opens a new window?
 */
#define GLUT_CREATE_NEW_CONTEXT                  0
#define GLUT_USE_CURRENT_CONTEXT                 1

/*
 * GLUT API Extension macro definitions -- the glutGet parameters
 */
#define  GLUT_ACTION_ON_WINDOW_CLOSE        0x01F9

#define  GLUT_WINDOW_BORDER_WIDTH           0x01FA
#define  GLUT_WINDOW_HEADER_HEIGHT          0x01FB

#define  GLUT_VERSION                       0x01FC

#define  GLUT_RENDERING_CONTEXT             0x01FD


#ifdef __cplusplus
}
#endif

#endif /* __glues_h__ */
