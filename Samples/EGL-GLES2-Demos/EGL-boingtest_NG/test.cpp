//first egl demo with lib egl_wrap by HunoPPC 2017
#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "EGL/egl.h"

BOOL debug = FALSE;
extern float  speedRot;
extern float changeRot;
extern float changeZoom;
extern float changeProj;

//32 by default
int ball_key_x=32;
int ball_key_y=32;

//
// Handle keyboard input
//
void Key ( ESContext *esContext, unsigned char key, int x, int y)
{
    //here add your action keyboard on your program
   switch ( key )
   {
   case '1':
                if(debug) printf( "FPS Activated now on window mode!!\n" );
                // Activate FPS counter
                esActivateFPS(1);
                break;

   case '2':
               if(debug) printf( "FPS disabled now on window mode!!\n" );
               // Disable FPS counter
               esActivateFPS(0);
               break;

   case 033: // ASCII Escape Key
               if(debug) printf( "Saw an 'Escape' \n" );
             // cleanup your program
               UnInit (esContext);
             //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
               esShutdown(esContext);
	           break;

   default: break;
   }
}

/**
 * Handles standard joystick
 */
static void
ball_joystick(ESContext *esContext, unsigned char joy, int crap, int morecrap)
{
  char newbutton[255];


         if (joy) {
         if (joy & GLES_JOY_DOWN){
         speedRot-=5.0f;
         if(debug)sprintf((char*)newbutton, "GLES_JOY_DOWN");
         if(debug)esLogMessage("Joystick button: %s (%d)", newbutton, joy);
         }else if (joy & GLES_JOY_UP){
         speedRot+=5.0f;
         if(debug)sprintf((char*)newbutton, "GLES_JOY_UP");
         if(debug)esLogMessage("Joystick button: %s (%d)", newbutton, joy);}
         if (joy & GLES_JOY_LEFT){
         changeRot=-1.0f;
         if(debug)sprintf((char*)newbutton, "GLES_JOY_LEFT");
         if(debug)esLogMessage("Joystick button: %s (%d)", newbutton, joy);
         }else if (joy & GLES_JOY_RIGHT){
         changeRot=1.0f;
         if(debug)sprintf((char*)newbutton, "GLES_JOY_RIGHT");
         if(debug)esLogMessage("Joystick button: %s (%d)", newbutton, joy);}
           }
}

BOOL debugZOOM = FALSE;
BOOL debugROT = FALSE;
BOOL debugSPEED = FALSE;

/**
 * Handle mouse move
 */
static void
mouse_move(ESContext *esContext, int x, int y) {

    if(esLeftMouseButtonActivated || esRightMouseButtonActivated){
    int changex, changey;
    changex = x - esNewWidthMainLoopOnRealTime/2;
    changey = y - esNewHeightMainLoopOnRealTime/2;
   if(debug)esLogMessage("window resized: %d, %d\n", esNewWidthMainLoopOnRealTime, esNewHeightMainLoopOnRealTime);
   if(esLeftMouseButtonActivated){
  //keep camera from rotating beyond vertically up/down
   if(changeZoom>=-30 && changey < 0){
   changeZoom-=0.08f;
   if(debugZOOM)esLogMessage("changeZoom NEGATIVE\n");
   }else if(changeZoom<=-1.0 && changey > 0){
   changeZoom+=0.08f;
   if(debugZOOM)esLogMessage("changeZoom POSITIVE\n");
   }
   //keep camera from projection beyond vertically left/right
   if(changeProj>=-4.0 && changex < 0){
   changeProj+=0.01f;
   }else if(changeProj<=4.0 && changex > 0){
   changeProj-=0.01f;
   }
   }
   if(esRightMouseButtonActivated){
   //keep camera from rotating beyond vertically left/right
   if(changeRot>=-90 && changex < 0){
   changeRot=-1.0f;
   if(debugROT)esLogMessage("changeROT NEGATIVE\n");
   }else if(changeRot<=90 && changex > 0){
   changeRot=1.0f;
   if(debugROT)esLogMessage("changeROT POSITIVE\n");
   }
   //keep speed rotation beyond vertically up/down
   if(speedRot>=-90 && changey < 0){
   speedRot-=1.0f;
   if(debugSPEED)esLogMessage("changeSPEED NEGATIVE\n");
   }else if(speedRot<=90 && changey > 0){
   speedRot+=1.0f;
   if(debugSPEED)esLogMessage("changeSPEED POSITIVE\n");
   }
   }
   }



if(debug)esLogMessage("esLeftMouseButtonActivated: %d\n", esLeftMouseButtonActivated);
if(debug)esLogMessage("esRightMouseButtonActivated: %d\n", esRightMouseButtonActivated);
if(debug)esLogMessage("MouseMove: %d, %d\n", x, y);

}

/**
 * Handle passive mouse move
 */
static void
passive_mouse_move(ESContext *esContext, int x, int y) {
    if(debug)esLogMessage("PassiveMouseMove: %d, %d", x, y);
}

/**
 * Handle mouse button
 */
static void
mouse_button(ESContext *esContext, int button, int state, int x, int y) {
    if(debug)esLogMessage("MouseButton: %d, isUp: %d, %d, %d", button, state, x, y);
}



int main(int argc, char** argv)
{
        ESContext esContext;

    //setEglFPS(60);

    //Init context on EGL lib
    esInitContext(&esContext);


    if (!esCreateWindow(&esContext, "BoingTest with EGL Lib for Opengl-ES AmigaOS4", 640, 480, ES_WINDOW_ALPHA))
        return 0;

    if (!Init(&esContext))
        return 0;
    //Draw function activated
    esRegisterDrawFunc(&esContext, RenderFrame);
    //keyboard
    esRegisterKeyFunc( &esContext, Key );
    //joystick
    esRegisterJoysticksFunc(&esContext,ball_joystick);
    //mouse motion
    esRegisterMotionFunc(&esContext, mouse_move);
    //mouse passive motion
    esRegisterPassiveMotionFunc(&esContext, passive_mouse_move);
    //mouse button
    esRegisterMouseFunc(&esContext, mouse_button);
    //update loop
    esRegisterUpdateFunc(&esContext, update);
    //on a main loop
    esMainLoop(&esContext);

    return 0;
}
//---------------------------------------------------------------------------
