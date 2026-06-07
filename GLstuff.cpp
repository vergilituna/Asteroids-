
 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <stdlib.h>

#include "GLstuff.h"


void OnKeyboardDown(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'q':
    case ESC:     exit(1);  
    case 'a': /* do something */ ; break;
   
    }		
}




void init_GL_stuff()
{


  //Creacion y definicion de la ventana
    
  glutInitWindowSize(ANCHO,ALTO);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Ejemplo GLUT");

  //Habilitar las luces, la renderizacion y el color de los materiales
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
	
  //definir la proyeccion
  glMatrixMode(GL_PROJECTION);
  gluPerspective( 40.0, ANCHO/ALTO, 0.1, 50);

  
  // color del fondo
  glClearColor(0.5f, 0.91f, 0.9f, 0.5f);    
	
  // Define el punto de vista
  glMatrixMode(GL_MODELVIEW);	
  
 
}


GLuint LoadTexture( int width, int height, const char * filename )
{

  GLuint texture;


  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;

  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

  for(int i = 0; i < width * height ; ++i)
    {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];
      
      data[index] = R;
      data[index+2] = B;
      
    }
  
  
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
  
  
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );
  
  return texture;
}


void displaytext(GLuint Thetexture)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, Thetexture);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 5.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 5.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -5.0, 0.0);

   glEnd();
   glFlush();
   glDisable(GL_TEXTURE_2D);
}
 
 
 

 
