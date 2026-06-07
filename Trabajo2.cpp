

#include <stdio.h> 
#include <stdlib.h>
#include <stdlib.h>

#include "GLstuff.h"

#include "Man.h"
#include "Cube.h"

// Prototipos de funciones 

//Callbacks de logica del programa
void myLogic();

//Callback de dibujo
void OnDibuja(void);	

//Callback de gestión del teclado
void OnKeyboardDown(unsigned char key, int x, int y);

  

// Variables globales


// Texture datas tructure
GLuint KLtexture;

Man theMan;
Cube *theCube;



int main(int argc,char* argv[])
{
  // Inicializaciones openGL


  // Inicialización GLUT
  glutInit(&argc, argv);

  // Inicializaciones openGL (ver GLstuff.c)
  init_GL_stuff();
  

  // Definición call backs de GLUT
  glutDisplayFunc(OnDibuja);
	
  glutIdleFunc(myLogic);

  glutKeyboardFunc(OnKeyboardDown);
 
  // posicciona el punto de vista 
  gluLookAt(0,-10,10,           // posicion del  ojo  
	    0.0, 0, 0.0,	// hacia que punto mira  
	    0.0, 1.0, 0.0);     // vector "UP"  (vertical positivo)


  // Carga la textura
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  KLtexture= LoadTexture(1400,1120, "LOGO_UPM.bmp" ); 
  glBindTexture (GL_TEXTURE_2D, KLtexture);


  // Crea el cubo

  theCube = new Cube(4, 2, 1 );
  
  // bucle del programa
  glutMainLoop();
  
  return 0;   

  /**************************************************************/}
 


void myLogic()
{
  theMan.move();  

  // es bueno comprobar el puntero antes de mandar mensajes !
  if(theCube)
    theCube->move();  
}

/**************************************************************/
/**************************************************************/
/**************************************************************/
/**************************************************************/

void OnDibuja(void)
{ 
  int i;

  //Borrado de la pantalla	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // proyeccion de las figuras


  displaytext(KLtexture);

  theMan.drawMan();

  // es bueno comprobar el puntero antes de mandar mensajes !
  if(theCube)
    theCube->draw();   
  
  glLoadIdentity();

  // posicciona el punto de vista 
  gluLookAt(0,-10,10,  // posicion del  ojo  
	    0.0, 0, 0.0,		        // hacia que punto mira  
	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)
  
  
  
  //Al final, cambiar el buffer
  glutSwapBuffers();
  glutPostRedisplay();//se le indica que redibuje la pantalla
  /**************************************************************/
}

 
 
