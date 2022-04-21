#include "EGL/gl.h"
#include "EGL/glues.h"


GLfloat mat_specular[] = {1.0, 1.0,1.0,1.0};
GLfloat mat_shininess[] = {50.0};
GLfloat light_position[] = {1.0,1.0,1.0,0.0};
 
void display(ESContext *esContext)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glColor3f(1.0,1.0,1.0);
	glLoadIdentity();
	gluLookAt(0.0,1.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);    // This has to be light not material
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glTranslatef(0.5,0,0);
	glutSolidSphere(0.5,100,100);
	glTranslatef(-1.0,0,0);
	glutSolidSphere(0.5,100,100);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
 
void resize(ESContext *esContext, int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0,2.0,-2.0*h/w,2.0*h/w,-10.0,10.0);
    else
        glOrtho(-2.0*w/h,2.0*w/h,-2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}

static void
key_special(ESContext *esContext, int special, int crap, int morecrap)
{
   switch (special) {
      case GLUT_KEY_ESCAPE:
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
       esShutdown(esContext);
	   break;
   }

}
 
int main(int argc, char **argv)
{
    ESContext esContext;
    glutInit(&esContext, &argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(&esContext,"Spheres");
	glutReshapeFunc(&esContext,resize);
    glutDisplayFunc(&esContext,display);
	glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(&esContext, key_special);
    glutMainLoop(&esContext);
}
