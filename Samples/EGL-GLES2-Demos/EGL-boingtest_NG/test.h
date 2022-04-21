//---------------------------------------------------------------------------
#ifndef TextureH
#define TextureH
//---------------------------------------------------------------------------
#include "EGL/egl.h"
//---------------------------------------------------------------------------
void SaveTGA(const char *p_file_name,unsigned int width,unsigned int height,unsigned int *p_rgba);
int Init(ESContext *esContext);
void RenderFrame(ESContext *esContext);
void UnInit(ESContext *esContext);
void update(ESContext *esContext, float deltaTime);

extern int ball_key_x;
extern int ball_key_y;

const unsigned int num_balls_x=ball_key_x;
const unsigned int num_balls_y=ball_key_y;
//---------------------------------------------------------------------------
#endif
