#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <EGL/gl.h>                                      // Header File For The OpenGL32 Library
#include <EGL/glues.h>                                     // Header File For The GLu32 Library

#include "EGLSDL/SDL.h"

#define SCREEN_WIDTH 800                                // We want our screen width 800 pixels
#define SCREEN_HEIGHT 600                               // We want our screen height 600 pixels
#define SCREEN_DEPTH 16                                 // We want 16 bits per pixel

using namespace std;

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

// We added a bunch of functionality to our CVector3 class.  Now we
// can have operator overloading, which will cut down the uglyness of
// our code when doing operations on and with vectors.  It also shortens
// our code.  We added a constructor, +/- operations between vectors,
// as well as * and / operations between scalers (single numbers).
//
// This is our basic 3D point/vector class
struct CVector3
{
public:
    
    // A default constructor
    CVector3() {}

    // This is our constructor that allows us to initialize our data upon creating an instance
    CVector3(float X, float Y, float Z) 
    { 
        x = X; y = Y; z = Z;
    }

    // Here we overload the + operator so we can add vectors together 
    CVector3 operator+(CVector3 vVector)
    {
        // Return the added vectors result.
        return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
    }

    // Here we overload the - operator so we can subtract vectors 
    CVector3 operator-(CVector3 vVector)
    {
        // Return the subtracted vectors result
        return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
    }
    
    // Here we overload the * operator so we can multiply by scalars
    CVector3 operator*(float num)
    {
        // Return the scaled vector
        return CVector3(x * num, y * num, z * num);
    }

    // Here we overload the / operator so we can divide by a scalar
    CVector3 operator/(float num)
    {
        // Return the scale vector
        return CVector3(x / num, y / num, z / num);
    }

    float x, y, z;                        
};

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


// This is our camera class
class CCamera {

public:

    CVector3 m_vPosition;                        // The camera's position
    CVector3 m_vView;                            // The camera's View
    CVector3 m_vUpVector;                        // The camera's UpVector
    
    // Our camera constructor
    CCamera();    

    // This changes the position, view, and up vector of the camera. (Used for initialization)
    void PositionCamera(float positionX, float positionY, float positionZ,
                         float viewX,     float viewY,     float viewZ,
                        float upVectorX, float upVectorY, float upVectorZ);

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

    // If we don't want use the keyboard to look around, this will use the mouse.
    // This type of viewing is used in most first person games.  
    void SetViewByMouse();

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

    // This rotates the camera's view around the position using axis-angle rotation
    void RotateView(float angle, float x, float y, float z);

    // This will move the camera forward or backward depending on the speed
    void MoveCamera(float speed);

};

// Extern our global variables so other source files can use them
extern CCamera    g_Camera;                             // This will be our global camera data

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


extern int VideoFlags;                                  // The Pixel Format flags
extern SDL_Surface * MainWindow;                        // Our Drawable portion of the window

// This Controls our MainLoop
void MainLoop(void);

// This toggles between the Full Screen mode and the windowed mode
void ToggleFullScreen(void);

// This allows us to configure our window for OpenGL and backbuffered
void SetupPixelFormat(void);

// This is our own function that makes creating a window modular and easy
void CreateMyWindow(const char *strWindowName, int width, int height, int VideoFlags);

// This inits our screen translations and projections
void SizeOpenGLScreen(int width, int height);

// This sets up OpenGL
void InitializeGL(int width, int height);

// This initializes the whole program
void Init();

// This handles the keypress events generated when the user presses a key
void HandleKeyPressEvent(SDL_keysym * keysym);

// This moves the camera
void CheckForMovement();

// This handles the keyrelease events generated when the user releases a key
void HandleKeyReleaseEvent(SDL_keysym * keysym);

// This draws everything to the screen
void RenderScene();

// This shuts down SDL and quits program
void Quit(int ret_val);

#endif  // _MAIN_H_

/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// In this tutorial, we added the CVector and CCamera class to this header file.
// You might be noticing that this header file is getting a bit cluttered.  Soon
// we will make another header file the split the rest of this stuff up.
//
// We also added a global instance of the class CCamera, called gCamera.  Now any
// source file can access the camera's current view and position.
// 
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//
