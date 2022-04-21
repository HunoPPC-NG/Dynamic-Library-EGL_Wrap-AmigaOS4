/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Septembre 2008                               */
/* OpenGL et GLUt                               */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "EGL/gl.h"
#include "EGL/glues.h"

/* Variables et constantes globales             */

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,0.5F };
static const float jaune[] = { 1.0F,1.0F,0.0F,0.5F };
static float rx = -50.0F;
static float r1 = 0.0F;
static float r2 = 0.0F;
static float dr1 = 0.31F;
static float dr2 = 1.81F;
static int anim = 1;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

void init(ESContext *esContext) {
  const GLfloat mat_shininess[] = { 50.0 };
  glMaterialfv(GL_FRONT,GL_SPECULAR,blanc);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,blanc);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,blanc);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,blanc);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_CULL_FACE);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

/* Scene dessinee                               */

void scene(ESContext *esContext) {
  glPushMatrix();
  glRotatef(r1,0.0F,0.0F,1.0F);
  glTranslatef(10.0F,0.0F,0.0F);
  glPushMatrix();
  glRotatef(r2,0.0F,1.0F,0.0F);
  glTranslatef(0.15F,0.0F,0.0F);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,blanc);
  glutSolidSphere(0.1F,36,36);
  glPopMatrix();
  glPushMatrix();
  glRotatef(r2+120.0F,0.0F,1.0F,0.0F);
  glTranslatef(0.15F,0.0F,0.0F);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,vert);
  glutSolidSphere(0.1F,36,36);
  glPopMatrix();
  glPushMatrix();
  glRotatef(r2+240.0F,0.0F,1.0F,0.0F);
  glTranslatef(0.15F,0.0F,0.0F);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,bleu);
  glutSolidSphere(0.1F,36,36);
  glPopMatrix();
  glPopMatrix();
  glMaterialfv(GL_FRONT,GL_DIFFUSE,rouge);
  glutSolidTorus(0.3,10.0,36,180);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,jaune);
  glPushMatrix();
  for( int i = 0 ; i < 10 ; i++ ) {
    glPushMatrix();
    glRotatef(36.0F*i,0.0F,0.0F,1.0F);
    glTranslatef(10.0F,0.0F,0.0F);
    glutSolidCube(1.0F);
    glPopMatrix(); }
  glPopMatrix();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

void idle(ESContext *esContext) {
  r1 += dr1;
  r2 += dr2;
  glutPostRedisplay(esContext);
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

void display(ESContext *esContext) {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  const GLfloat light0_position[] = { 1.0,1.0,1.0,0.0 };
  const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
  const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
  glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
  glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
  glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
  glPushMatrix();
  glRotatef(rx,1.0F,0.0F,0.0F);
  scene(esContext);
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
    printf("Attention, erreur OpenGL %d\n",error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

void reshape(ESContext *esContext,int x,int y) {
  glViewport(0,0,x,y); 
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  gluPerspective(30.0F,(float) x/y,1.0,50.0) ;
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
  gluLookAt(0.0,-7.0,25.0,0.0,-2.0,0.0,0.0,1.0,0.0);
}

/* Fonction executee lors de l'appui            */
/* d'une touche du clavier                      */

void keyboard(ESContext *esContext,unsigned char c,int x,int y) {
  switch (c) {
    case 43 :
      dr1 *= 1.01F;
      break;
    case 45 :
      dr1 /= 1.01F;
      break;
    case 0x1B :
      exit(0);
      break;
    case 0x0D :
      dr1 = -dr1;
      break;
    case 0x20 :
      anim = !anim;
      glutIdleFunc(esContext,(anim) ? idle : NULL);
      break; }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier             */

void special(ESContext *esContext,int c,int x,int y) {
  switch (c) {
    case GLUT_KEY_UP :
      rx += 1.0F;
      glutPostRedisplay(esContext);
      break;
    case GLUT_KEY_DOWN :
      rx -= 1.0F;
      glutPostRedisplay(esContext);
      break;
    case GLUT_KEY_ESCAPE:
    //New function for Unload context and shutdown a lib EGL for Opengl-ES AOS4
       esShutdown(esContext);
	   break;
    }
}

/* Fonction executee lors de l'appui            */
/* d'une touche de la souris                    */

void mouse(ESContext *esContext,int bouton,int etat,int x,int y) {
  if ( bouton == GLUT_LEFT_BUTTON ) {
    dr1 = -dr1; }
  if ( ( bouton == GLUT_RIGHT_BUTTON ) && ( etat == GLUT_UP ) ) {
    dr1 = -dr1; }
}

/* Fonction principale                          */

int main(int argc,char **argv) {
    ESContext esContext;
  /* Initialisation de l'affichage              */
  glutInit(&esContext,&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(450,250); 
  glutInitWindowPosition(50,50);
  glutCreateWindow(&esContext,"EGL_Wrap GLUt test");
  /* Initialisation d'un certain nombre         */
  /* de parametres d'OpenGL                     */
  init(&esContext);
  /* Specification des fonctions de gestion     */
  /* evenementielle                             */
  glutIdleFunc(&esContext,idle);
  glutKeyboardFunc(&esContext,keyboard);
  glutSpecialFunc(&esContext,special);
  glutReshapeFunc(&esContext,reshape);
  glutMouseFunc(&esContext,mouse);
  glutDisplayFunc(&esContext,display);
  /* Boucle principale d'affichage              */
  /* et de gestion des evenements               */
  glutMainLoop(&esContext);
  return(0);
}
