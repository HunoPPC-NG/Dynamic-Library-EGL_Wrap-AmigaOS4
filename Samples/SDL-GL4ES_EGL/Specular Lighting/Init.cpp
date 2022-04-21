//***********************************************************************//
//                                                                       //
//        - "Talk to me like I'm a 3 year old!" Programming Lessons -    //
//                                                                       //
//        $Author:        DigiBen        digiben@gametutorials.com       //
//                                                                       //
//        $Program:        Specular Lighting                             //
//                                                                       //
//        $Description:    Demonstrates specular lighting                //
//                                                                       //
//        $Date:            9/22/01                                      //
//                                                                       //
//***********************************************************************//

#include "main.h"                                       // includes our function protoypes and globals                        

int VideoFlags = 0;                                     // Video Flags for the Create Window function
SDL_Surface * MainWindow = NULL;                        // drawing surface on the SDL window

bool FullscreenOn;


/////////////////////////////////// TOGGLE FULL SCREEN \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function TOGGLES between FULLSCREEN and WINDOWED mode
/////
/////////////////////////////////// TOGGLE FULL SCREEN \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ToggleFullScreen(void)
{
SDL_WM_ToggleFullScreen( MainWindow );
}


///////////////////////////////   CREATE MY WINDOW   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////  This function CREATES our WINDOW for drawing the GL stuff
/////
///////////////////////////////   CREATE MY WINDOW   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CreateMyWindow(const char * strWindowName, int width, int height, int VideoFlags)
{
    MainWindow = SDL_SetVideoMode(width, height, SCREEN_DEPTH, VideoFlags);     // SCREEN_DEPTH is macro for bits per pixel

    if( MainWindow == NULL )                            // if window creation failed
    {
        cerr << "Failed to Create Window : " << SDL_GetError() << endl;         // report error 
        Quit(0);
    }

    SDL_WM_SetCaption(strWindowName, "GameTutorials");  // set the window caption (first argument) and icon caption (2nd arg)
}


/////////////////////////////   SETUP PIXEL FORMAT   \\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////  Sets the pixel format for openGL and video flags for SDL
/////
/////////////////////////////   SETUP PIXEL FORMAT   \\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void SetupPixelFormat(void)
{
    //////// SURFACE IS THE DRAWABLE PORTION OF AN SDL WINDOW \\\\\\\\*
    
    /////////////  we set the common flags here
    VideoFlags    = SDL_OPENGL;                         // it's an openGL window
    VideoFlags   |= SDL_HWPALETTE;                      // exclusive access to hardware colour palette
    VideoFlags   |= SDL_RESIZABLE;                      // the window must be resizeable

    const SDL_VideoInfo * VideoInfo = SDL_GetVideoInfo();     // query SDL for information about our video hardware

    if(VideoInfo == NULL)                                     // if this query fails
    {
        cerr << "Failed getting Video Info : " << SDL_GetError() << endl;          // report error
        Quit(0);
    }

    ///////////// we set the system dependant flags here
    if(VideoInfo -> hw_available)                      // is it a hardware surface
        VideoFlags |= SDL_HWSURFACE;
    else
        VideoFlags |= SDL_SWSURFACE;

    // Blitting is fast copying / moving /swapping of contiguous sections of memory
    // for more about blitting check out : http://www.csc.liv.ac.uk/~fish/HTML/blitzman/bm_blitter.html
    if(VideoInfo -> blit_hw)                            // is hardware blitting available
        VideoFlags |= SDL_HWACCEL;

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );      // tell SDL that the GL drawing is going to be double buffered
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,   SCREEN_DEPTH);         // size of depth buffer 
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 0);       // we aren't going to use the stencil buffer
    SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0);     // this and the next three lines set the bits allocated per pixel -
    SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0);   // - for the accumulation buffer to 0
    SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0);
}



//////////////////////////// RESIZE OPENGL SCREEN \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////    This function resizes the viewport for OpenGL.
/////
//////////////////////////// RESIZE OPENGL SCREEN \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void SizeOpenGLScreen(int width, int height)            // Initialize The GL Window
{
    if (height==0)                                        // Prevent A Divide By Zero error
    {
        height=1;                                        // Make the Height Equal One
    }

    glViewport(0,0,width,height);                        // Make our viewport the whole window
                                                        // We could make the view smaller inside
                                                        // Our window if we wanted too.
                                                        // The glViewport takes (x, y, width, height)
                                                        // This basically means, what our our drawing boundries

    glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
    glLoadIdentity();                                    // Reset The Projection Matrix

                                                        // Calculate The Aspect Ratio Of The Window
                                                        // The parameters are:
                                                        // (view angle, aspect ration of the width to the height, 
                                                        //  The closest distance to the camera before it clips, 
                  // FOV        // Ratio                //  The farthest distance before it stops drawing)
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, .5f ,150.0f);

    glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
    glLoadIdentity();                                    // Reset The Modelview Matrix
}


/////////////////////////////////   INITIALIZE OPENGL  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////         This function handles all the initialization for openGL
/////
/////////////////////////////////   INITIALIZE OPENGL  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void InitializeOpenGL(int width, int height)
{
    glEnable( GL_DEPTH_TEST );                             // Enables Depth Test i.e enables use of depth buffer for drawing
    glEnable( GL_TEXTURE_2D );
    SizeOpenGLScreen(width, height);                       // Setup the screen translations and viewport
}


////////////////////////////////      MAIN      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
//////
//////     create the window and calling the initialization functions
//////
////////////////////////////////      MAIN      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int main(void)
{
    // print user instructions
    cout << " Hit the F1 key to Toggle between Fullscreen and windowed mode" << endl;
    cout << " Hit ESC to quit" << endl;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )                      // try to initialize SDL video module
    {
        cerr << "Failed initializing SDL Video : " << SDL_GetError() << endl;      // report error if it fails
        return 1;                                             // we use this instead of Quit because SDL isn't yet initialized
    }

    // Set up the format for the pixels of the OpenGL drawing surface
    SetupPixelFormat();
    // Create our window, we pass caption for the window, the width, height and video flags required
    CreateMyWindow("www.GameTutorials.com - Specular Lighting", SCREEN_WIDTH, SCREEN_HEIGHT, VideoFlags);

    // Initializes our OpenGL drawing surface
    
    Init();

    // Run our message loop
    MainLoop();

    // quit main returning success
    return 0;
}


////////////////////////////////    QUIT    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
//////
//////      This will shutdown SDL and quit the program
//////
////////////////////////////////    QUIT    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Quit(int ret_val)
{
    SDL_Quit();                                            // shuts down SDL stuff

    exit(ret_val);                                         // quit the program
}

/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//    
// The only thing changed in this file from the Quadric tutorial is that the
// texture mapping information was taken out. 
// 
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
// 
//
