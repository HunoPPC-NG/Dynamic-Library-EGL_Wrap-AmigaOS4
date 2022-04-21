/*
 * Mesa 3-D graphics library
 * Version:  3.0
 * Copyright (C) 1995-1998  Brian Paul
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * OpenGL ES 2.0 CM port of part of GLU by Mike Gorchak <mike@malva.ua>
 * GLU for EGL Wrapper lib for OpenGLES 2.0 and Warp3D-NOVA by Hugues "HunoPPC" Nouvel  2022
 */


#ifndef GLUES_MANGLE_H
#define GLUES_MANGLE_H

#define mgluLookAt gluLookAt
#define mgluOrtho2D mgluOrtho2D
#define mgluPerspective gluPerspective
#define mgluPickMatrix gluPickMatrix
#define mgluProject gluProject
#define mgluUnProject gluUnProject
#define mgluErrorString gluErrorString
#define mgluScaleImage gluScaleImage
#define mgluBuild1DMipmaps gluBuild1DMipmaps
#define mgluBuild2DMipmaps gluBuild2DMipmaps
#define mgluNewQuadric gluNewQuadric
#define mgluDeleteQuadric gluDeleteQuadric
#define mgluQuadricDrawStyle gluQuadricDrawStyle
#define mgluQuadricOrientation gluQuadricOrientation
#define mgluQuadricNormals gluQuadricNormals
#define mgluQuadricTexture gluQuadricTexture
#define mgluQuadricCallback gluQuadricCallback
#define mgluCylinder gluCylinder
#define mgluSphere gluSphere
#define mgluDisk gluDisk
#define mgluPartialDisk gluPartialDisk
#define mgluNewNurbsRenderer gluNewNurbsRenderer
#define mgluDeleteNurbsRenderer gluDeleteNurbsRenderer
#define mgluLoadSamplingMatrices gluLoadSamplingMatrices
#define mgluNurbsProperty gluNurbsProperty
#define mgluGetNurbsProperty gluGetNurbsProperty
#define mgluBeginCurve gluBeginCurve
#define mgluEndCurve gluEndCurve
#define mgluNurbsCurve gluNurbsCurve
#define mgluBeginSurface gluBeginSurface
#define mgluEndSurface gluEndSurface
#define mgluNurbsSurface gluNurbsSurface
#define mgluBeginTrim gluBeginTrim
#define mgluEndTrim gluEndTrim
#define mgluPwlCurve gluPwlCurve
#define mgluNurbsCallback gluNurbsCallback
#define mgluNewTess gluNewTess
#define mgluDeleteTess gluDeleteTess
#define mgluTessBeginPolygon gluTessBeginPolygon
#define mgluTessBeginContour gluTessBeginContour
#define mgluTessVertex gluTessVertex
#define mgluTessEndPolygon gluTessEndPolygon
#define mgluTessEndContour gluTessEndContour
#define mgluTessProperty gluTessProperty
#define mgluTessNormal gluTessNormal
#define mgluTessCallback gluTessCallback
#define mgluGetTessProperty gluGetTessProperty
#define mgluBeginPolygon gluBeginPolygon
#define mgluNextContour gluNextContour
#define mgluEndPolygon gluEndPolygon
#define mgluGetString gluGetString
#define mgluBuild1DMipmapLevels gluBuild1DMipmapLevels
#define mgluBuild2DMipmapLevels gluBuild2DMipmapLevels
#define mgluBuild3DMipmapLevels gluBuild3DMipmapLevels
#define mgluBuild3DMipmaps gluBuild3DMipmaps
#define mgluCheckExtension gluCheckExtension
#define mgluUnProject4 gluUnProject4
#define mgluNurbsCallbackData gluNurbsCallbackData
#define mgluNurbsCallbackDataEXT gluNurbsCallbackDataEXT

#endif
