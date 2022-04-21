//first egl demo with lib egl_wrap by HunoPPC 2017
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "EGL/egl.h"
#include <math.h>
//----------------------------------------------------------------------------
#define DBG_LINE printf("DBG %u\n",__LINE__);
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
float  speedRot = 20.0f;//default
float changeRot = 1.0f;//default
float changeZoom = -3.0f;//default max in = -40  max out = -1.0
float changeProj = 0.0f; //
static GLuint bufferVBOvertices=0;//new function create VBO lib eglwrap
static GLuint bufferVBOindices=0;//new function create VBO lib eglwrap

typedef struct
{

    /* Angle of rotation. */
    float rotationAngle;

    /* Handle to a program object. */
    GLuint programObject;

} UserData;

class Ball {
		struct Vertex {
			float pos[3];
			float uv[2];
			float normal[3];
		};
	private:
		static Vertex *vertex_data;
		static Vertex *vertex_data_alt;
		static unsigned short *index_data;
		static unsigned int vertex_count;
		static unsigned int index_count;
		static unsigned short *half_sphere_index_start;
	public:
		float position[3];
		float anim;
	public:
		Ball(void);
		~Ball(void);
		static void ActivateRenderVBO(GLuint pos_index,GLuint uv_index,GLuint normal_index);
		static void ActivateRenderArrays(GLuint pos_index,GLuint uv_index,GLuint normal_index);
		static void DeactivateRendering(GLuint pos_index,GLuint uv_index,GLuint normal_index);
		void Render(GLint pos_location);
		static void ManipulateVertexData(int p_variant);
};
//----------------------------------------------------------------------------
Ball::Vertex *Ball::vertex_data=0;
Ball::Vertex *Ball::vertex_data_alt=0;
unsigned short *Ball::index_data=0;
unsigned int Ball::vertex_count=0;
unsigned int Ball::index_count=0;
unsigned short *Ball::half_sphere_index_start=0;
unsigned int frame_counter=0;
//----------------------------------------------------------------------------
Ball::Ball(void)
{
	anim=2.0f*((float)rand()/(float)RAND_MAX);
	if(!bufferVBOvertices) {
		const unsigned int y_res=20;
		const unsigned int x_res=20;
		// create the vertex data
		const float radius=0.1f;
		vertex_count=x_res*y_res;
		vertex_data=new Vertex[vertex_count];
		vertex_data_alt=new Vertex[vertex_count];
		for(unsigned int y=0,i=0;y<y_res;++y) {
			float ty=(((float)y)/((float)(y_res-1)));
			float a=ty*M_PI;
			
			float py=cos(a)*radius;
			float rx=sin(a)*radius;
			for(unsigned int x=0;x<x_res;++x) {
				Vertex &vtx_alt=vertex_data_alt[i];
				Vertex &vtx=vertex_data[i++];
				float tx=(((float)x)/((float)(x_res-1)));
				float ax=tx*2.0f*M_PI;
				vtx.pos[0]=cos(ax)*rx;
				vtx.pos[2]=sin(ax)*rx;
				vtx.pos[1]=py;
				vtx.uv[0]=tx;
				vtx.uv[1]=ty;
				vtx.normal[0]=vtx.pos[0]/radius;
				vtx.normal[1]=vtx.pos[1]/radius;
				vtx.normal[2]=vtx.pos[2]/radius;
				vtx_alt=vtx;
				vtx_alt.pos[1]*=0.5f;
				vtx_alt.pos[0]*=2.0f;
			}
		}
		// store that vertex data in the VBO with new function on my lib
        bufferVBOvertices = esCreate_VBO(vertex_count*sizeof(Vertex),vertex_data,GL_STATIC_DRAW);
		
		// create an index array for all balls
		index_count=(x_res*2+2)*(y_res-1);
		index_data=new unsigned short[index_count];
		unsigned short *idx=index_data;
		unsigned short strip_top=0;
		half_sphere_index_start=(unsigned short*)((2*x_res+2)*(y_res/2)*sizeof(unsigned short));
		for(unsigned int y=1;y<y_res;++y) {
			for(unsigned int x=0;x<x_res;++x) {
				idx[0]=strip_top;
				idx[1]=strip_top+x_res;
				++strip_top;
				idx+=2;
			}
			// add degen tri
      idx[0]=idx[-1];
      idx[1]=strip_top;
			idx+=2;
		}
		index_count-=2; // forget the last degen again
        // store that vertex data in the VBO with new function on my lib
        bufferVBOindices = esCreate_VBO(index_count*sizeof(unsigned short),index_data,GL_STATIC_DRAW);
	}
}
//----------------------------------------------------------------------------
Ball::~Ball(void)
{
	if(bufferVBOindices) {
		glDeleteBuffers(1,&bufferVBOindices);
		bufferVBOindices=0;
	}
	if(bufferVBOvertices) {
		glDeleteBuffers(1,&bufferVBOvertices);
		bufferVBOvertices=0;
	}
	if(vertex_data_alt) {
		delete[] vertex_data_alt;
		vertex_data_alt=0;
	}
	if(vertex_data) {
		delete[] vertex_data;
		vertex_data=0;
	}
	if(index_data) {
		delete[] index_data;
		index_data=0;
	}
}
//----------------------------------------------------------------------------
void Ball::ActivateRenderVBO(GLuint pos_index,GLuint uv_index,GLuint normal_index)
{
	glBindBuffer(GL_ARRAY_BUFFER,bufferVBOvertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bufferVBOindices);
  glVertexAttribPointer(pos_index,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)0);
  glVertexAttribPointer(uv_index,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)(sizeof(float)*3));
  glVertexAttribPointer(normal_index,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)(sizeof(float)*5));
  glEnableVertexAttribArray(pos_index);
  glEnableVertexAttribArray(uv_index);
  glEnableVertexAttribArray(normal_index);
}
//----------------------------------------------------------------------------
void Ball::ActivateRenderArrays(GLuint pos_index,GLuint uv_index,GLuint normal_index)
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glVertexAttribPointer(pos_index,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),&vertex_data[0].pos[0]);
  glVertexAttribPointer(uv_index,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),&vertex_data[0].uv[0]);
  glVertexAttribPointer(normal_index,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),&vertex_data[0].normal[0]);
  glEnableVertexAttribArray(pos_index);
  glEnableVertexAttribArray(uv_index);
  glEnableVertexAttribArray(normal_index);
}
//----------------------------------------------------------------------------
void Ball::DeactivateRendering(GLuint pos_index,GLuint uv_index,GLuint normal_index)
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glDisableVertexAttribArray(pos_index);
  glDisableVertexAttribArray(uv_index);
  glDisableVertexAttribArray(normal_index);
}
//----------------------------------------------------------------------------
void Ball::Render(GLint pos_location)
{
	glUniform3fv(pos_location,1,position);
	GLint bound_element_buffer;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING,&bound_element_buffer);
	glDrawElements(GL_TRIANGLE_STRIP,index_count,GL_UNSIGNED_SHORT,bound_element_buffer ? (GLvoid*)0 : index_data);
}
//----------------------------------------------------------------------------
void Ball::ManipulateVertexData(int p_variant)
{
	glBindBuffer(GL_ARRAY_BUFFER,bufferVBOvertices);
	switch(p_variant) {
		case 0:
			glBufferSubData(GL_ARRAY_BUFFER,0,vertex_count*sizeof(Vertex),vertex_data_alt);
			break;
		default:
			glBufferSubData(GL_ARRAY_BUFFER,0,vertex_count*sizeof(Vertex),vertex_data);
			break;
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
GLuint programObject;
GLuint texture_id[2];
Ball *balls;
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//
// Initialize the shader and program object
//
int Init(ESContext *esContext)
{

      esContext->userData = malloc(sizeof(UserData));

    UserData *userData = (UserData*)esContext->userData;

   char vShaderStr[] =
      "#version 310 es           \n"
      "in layout(location=2) vec3 vPosition;  \n"
      "in layout(location=1) vec2 vTexCoord;  \n"
      "in layout(location=0) vec3 vNormal;  \n"
      "uniform layout(location = 0)  mat4 mp;\n"
      "uniform layout(location = 1)  vec3 pos; \n"
      "uniform layout(location = 2)  vec4 unicol; \n"
      "out vec4 col;  \n"
      "out vec2 uv;  \n"
      "void main()                              \n"
      "{                                        \n"
      "		vec3 p=pos;          \n"
      "   float squeeze=1.5-3.0*abs(p.y);   \n"
      "   vec3 spos=vPosition*vec3(squeeze,2.0-squeeze,squeeze);  \n"
      "   vec4 final_pos=mp*vec4(p+spos,1.0);  \n"
      "   gl_Position = final_pos;              \n"
      "   uv = vTexCoord;              \n"
      "   vec3 L=normalize(vec3(0.2,1.0,0.2));  \n"
			"   float diffuse = max(dot(normalize(spos),L)*1.0,0.25);   \n"
      "   col = unicol*(diffuse*max(1.0-abs(final_pos.z)*0.12,0.0));              \n"
      "}";

   char fShaderStr[] =
	  "uniform sampler2D tex; \n"
      "varying vec4 col;                          \n"
      "varying vec2 uv;                          \n"
      "void main()                                  \n"
      "{                                            \n"
      "   gl_FragColor = col*(texture2D(tex,uv));  \n"
      "}                                            \n";

   GLuint programObject;
   // Load the shaders and get a linked program object
  programObject = esLoadProgram ( vShaderStr, fShaderStr );

   //   /*
  glBindAttribLocation(programObject,0,"vPosition");
  glBindAttribLocation(programObject,1,"vTexCoord");
  glBindAttribLocation(programObject,2,"vNormal");
   //  */

    /* Important Link the program object. */
    glLinkProgram ( programObject );


    /* Store the program object. */
    userData->programObject = programObject;

//DBG_LINE
   if ( programObject == 0 )
   {
DBG_LINE
      return 0;
   }

   glClearColor ( 0.5f, 0.5f, 1.0f, 1.0f );
   glActiveTexture(GL_TEXTURE0);
     texture_id[0]=esLoadPNG("PROGDIR:boingtex.png");
   glActiveTexture(GL_TEXTURE1);
     texture_id[1]=esLoadPNG("PROGDIR:boingtex2.png");
	balls=new Ball[num_balls_x*num_balls_y];

	const GLint tex_location=glGetUniformLocation(userData->programObject,"tex");
	glGetError();
	
	// testing getting / changing uniform-sampler value.
	GLint tex_idx;
	//printf("tex-loc : %d\n",tex_location);
	glGetUniformiv(userData->programObject,tex_location,&tex_idx);
	//printf("tex-idx orig : %d\n",tex_idx);
	
	glUniform1i(tex_location,0); 
	glGetUniformiv(userData->programObject,tex_location,&tex_idx);
	//printf("tex-idx new : %d\n",tex_idx);

    /* Important Link the program object. */
    glLinkProgram ( userData->programObject );

	      /* Use the program object. */
    glUseProgram(userData->programObject);
	
   return TRUE;
}

ESMatrix  modelviewMatrix;

/* Update the state. */
void update(ESContext *esContext, float deltaTime)
{
    UserData *userData = (UserData*)esContext->userData;
    static float rot=0.0f;
	rot+=(1.0f/60.0f)*speedRot;
    
    esMatrixLoadIdentity(&modelviewMatrix);
    esTranslate(&modelviewMatrix, 0.0f,0.0f,changeZoom);
    esRotate(&modelviewMatrix, -30.0f,1.0f,0.0f,changeProj);
    esRotate(&modelviewMatrix, rot,0.0f,changeRot,0.0f);
}

//
// Draw a triangle using the shader pair created in Init()
//
void RenderFrame(ESContext *esContext)
{
   UserData *userData = (UserData*)esContext->userData;

    float aspect = (float) esNewHeightMainLoopOnRealTime / esNewWidthMainLoopOnRealTime;

    ESMatrix projectionFinal;
    esMatrixLoadIdentity(&projectionFinal);
    esFrustum(&projectionFinal, -1.0, +1.0, -1.0 * aspect, +1.0 * aspect, 1.0, 30.0);


    ESMatrix modelviewprojection;
	esMatrixLoadIdentity(&modelviewprojection);
    esMatrixMultiply( &modelviewprojection, &modelviewMatrix, &projectionFinal );

	if(frame_counter & 64) {
  	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
  } else {
  	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
  }


	const GLint tex_location=glGetUniformLocation(userData->programObject,"tex");
	GLint val=0;
	glGetUniformiv(userData->programObject,tex_location,&val);

	if(frame_counter & 64) {
		if(val!=0) {
			glUniform1i(tex_location,0);
			Ball::ManipulateVertexData(0);
		}
  } else {
		if(val!=1) {
			glUniform1i(tex_location,1);
			Ball::ManipulateVertexData(1);
		}
  }

/*
	if(frame_counter==2) {
		const uint32 w=64;
		const uint32 h=64;
		glBindTexture(GL_TEXTURE_2D,texture_id);
		glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,w,h,0);
//		glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,100,w,h);
	   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	}
*/


	
	const GLint mpv_location=glGetUniformLocation(userData->programObject,"mp");
  glUseProgram ( userData->programObject );
//	  glUniformMatrix4fv(mpv_location,1,GL_FALSE,modelview.m);
    glUniformMatrix4fv(mpv_location,1,GL_FALSE,&modelviewprojection.m[0][0]/*modelview.m*/);
	const GLint unicol_location=glGetUniformLocation(userData->programObject,"unicol");
	glUniform4f(unicol_location,1.0f,1.0f,1.0f,1.0f);
	const GLint pos_location=glGetUniformLocation(userData->programObject,"pos");
	glUniform3f(pos_location,0.0f,0.0f,0.0f);
	
	
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	GLint attrib_loc_pos=0;//glGetAttribLocation(programObject,"vPosition");
	GLint attrib_loc_uv=1;//glGetAttribLocation(programObject,"vTexCoord");
	GLint attrib_loc_norm=2;//glGetAttribLocation(programObject,"vNormal");
	
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CW);

    #ifdef USEVBO
	Ball::ActivateRenderVBO(attrib_loc_pos,attrib_loc_uv,attrib_loc_norm);
    #else
    Ball::ActivateRenderArrays(attrib_loc_pos,attrib_loc_uv,attrib_loc_norm);
    #endif
	const float anim_step=(1.0f/60.0f)*6.0f;
	const float dist=0.3f;
	const float start=-0.5f*(((float)num_balls_y)*dist);
	float py=start;
	for(unsigned int y=0,t=0;y<num_balls_y;++y) {
		py+=dist;
		float px=start;
		for(unsigned int x=0;x<num_balls_x;++x) {
			balls[t].anim+=anim_step;
			balls[t].position[0]=px;
			balls[t].position[1]=fabsf(cosf(balls[t].anim)*0.3f);
			balls[t].position[2]=py;
			balls[t].Render(pos_location);
			px+=dist;
			++t;
		}
	}
	Ball::DeactivateRendering(attrib_loc_pos,attrib_loc_uv,attrib_loc_norm);
	++frame_counter;
}

void UnInit (ESContext *esContext)
{

    UserData *userData = (UserData*)esContext->userData;
	// save a screenshot to test readpixels
	GLint dim[4];
	glGetIntegerv(GL_VIEWPORT,dim);
	unsigned int *l_data=new unsigned int[dim[2]*dim[3]];
	glReadPixels(0,0,dim[2],dim[3],GL_RGBA,GL_UNSIGNED_BYTE,l_data);
	SaveTGA("RAM:screen.tga",dim[2],dim[3],l_data);
	delete[] l_data;
	// cleanup
//	delete[] balls;
  glDeleteProgram ( userData->programObject );
  glDeleteProgram ( programObject );
  glDeleteTextures (2,texture_id);
}

