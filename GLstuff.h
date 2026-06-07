
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
 

//#ifdef linux
#ifdef __APPLE__
#include "GLUT/glut.h"
#include <stdlib.h>
#endif

#ifdef linux
#include <GL/glut.h>
#endif
 
#define  ANCHO 800
#define ALTO 800

#define ESC 27

// Prototipos de funciones
GLuint LoadTexture(int, int, const char * filename );

void displaytext(GLuint Thetexture);

void init_GL_stuff();
 

