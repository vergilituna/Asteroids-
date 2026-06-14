#define _CRT_SECURE_NO_WARNINGS




//***********************
// Asteroids Open GL
// Claudio Rossi, Universidad Polit�cnica de Madrid 
// (C) 2015 
//***********************



#include "commonstuff.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>

#include "Shape.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Ship.h"
#include "ObjectsList.h"
#include "Flame.h"
#include "Ovni.h"


//***********************
// Prototipos de funciones 
//***********************

// Callback de la logica del juego
void myLogic();

//Callback de dibujo
void OnDibuja(void);	

//Callbacks para teclado y raton
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseBtn(int button, int state,int x, int y);
void OnMouseMoveBtn(int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);


void printdata();
void gameover(int score);
void tryFire(Ship* ship, Bullet*& bullet);
void handleCollisionResult(int res, Ship* ship, Bullet*& bullet, int& shotTime, int& nShips, int& n_otherShip);

  
//***********************
// Variables globales
//***********************

// Posici�n y step de la camara
float cam_pos[6]={0, 0, 27};

// posici�n de la explosi�n
float expl_pos[2]={-1000,-1000};

// Modo del Mouse
int MODE=NONE;

// Objetos globales
ObjectsList worldobjects;
Ship *theShip1=NULL;
Ship *theShip2=NULL;
Bullet *theBullet1=NULL;
Bullet *theBullet2=NULL;
Flame *theFlame=NULL;

// Varias constantes usadas en el programa
int shotTime1=0;
int shotTime2=0;
int nShips1=3;
int nShips2=3;
int score=0;
int FlameTime=0;
int FT=20;


//***  VELOCIDAD

//***********************
// Programa principal
//***********************


int main(int argc,char* argv[])
{

  // inicializaciones

  //Creacion y definicion de la ventana
  glutInit(&argc, argv);
  glutInitWindowSize(WINX,WINY);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Asteroids GL");

  //Habilita las luces, la renderizacion y el color de los materiales
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    
	
  //Define la proyeccion
  glMatrixMode(GL_PROJECTION);
  gluPerspective( 40.0, WINX/WINY, 0.1, 50);

  //Para definir el punto de vista
  glMatrixMode(GL_MODELVIEW);	

  // Define call backs te GLUT

  // Display function: contiene las instrucciones de dibujo
  glutDisplayFunc(OnDibuja);
    // Idle function: contiene la logica del juego
  glutIdleFunc(myLogic);
  
  // Callbacks de teclado y rat�n
  glutKeyboardFunc(OnKeyboardDown);
  glutSpecialFunc(OnSpecKeyboardDown);
  glutMotionFunc(OnMouseMoveBtn);
  glutMouseFunc(OnMouseBtn);

  
  // Posicciona el punto de vista (c�mara)
  gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
	    0.0, 0.0, 0.0,		        // hacia que punto mira  
	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)


  
  // Creacci�n de los objetos iniciales
  theShip1 = worldobjects.getShip(0);
  theShip2 = worldobjects.getShip(1);

  // WORLDOBJECTS es declarada est�tica, se inicializa "automaticamente" - contiene los asteroides  //***
  
  // bucle infinito de Open GL
  glutMainLoop();

  // Esto solo sirve para que el compilador no proteste, nunca se llegar� aqu�
  return 0;   

}

/************************** FIN DEL MAIN ************************************/





//***********************
// Callbacks
//***********************


// Imprime puntuacci�n y num. de naves
void printdata()
{
  int i,l;
  char buffer[50];
  
  glPushMatrix();

  sprintf(buffer,"P1: %d   P2: %d   Score: %d",nShips1,nShips2,score);
  l=strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i=0; i < l; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
    }
  glEnable(GL_LIGHTING);

  glPopMatrix();

}


//no usada
void gameover(int score)
{
  int i,l;
  char buffer[30];
  
  glPushMatrix();

    sprintf(buffer,"GAME OVER! Points: %d",score);

  l=strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i=0; i < l; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
    }
  glEnable(GL_LIGHTING);

  glPopMatrix();

}


void tryFire(Ship* ship, Bullet*& bullet)
{
  if (ship && !bullet)
    {
      bullet = ship->fire();
      worldobjects.add(bullet);
    }
}


void handleCollisionResult(int res, Ship* ship, Bullet*& bullet, int& shotTime, int& nShips, int& other_nShip)
{
  if (res == 1)
    {
      nShips--;
      if (nShips1 == 0 && nShips2 == 0)
	exit(1);
      if (nShips > 0)
	{
	  ship->resetpos();
	  worldobjects.reposition(ship);
	}
      else { //caso donde un juguador pierde y el otro sobrevive
          worldobjects.remove(ship);
      }
    }

  if (res >= 2)
    {
      worldobjects.remove(bullet);
      bullet = NULL;
      shotTime = 0;
      if (res <= 4)
	score += 100*(res-1);
      else if (res <= 7)
	score += 100*(res-4);
    }
}


// Logica del juego: mueve los objeto mandando el mensaje "move"
void myLogic()
{
  int res1, res2;

  if(shotTime1++>MAXSHOTTIME)
    {
      worldobjects.remove(theBullet1);
      theBullet1 = NULL;
      shotTime1 = 0;
    }

  if(shotTime2++>MAXSHOTTIME)
    {
      worldobjects.remove(theBullet2);
      theBullet2 = NULL;
      shotTime2 = 0;
    }

  static int ovniSpawnTimer = 0;
  if (!worldobjects.hasOvni()) {
    ovniSpawnTimer++;
    if (ovniSpawnTimer > 500) {
      worldobjects.add(new Ovni());
      ovniSpawnTimer = 0;
    }
  }

  // Pide al mudo que mueve los objetos
  worldobjects.move();

  // Pide si ha habido colisi�n, pasa referencia a proyectil y nave, retorna tipo de colisi�n y posici�n de la colisi�n
  // res==0:  No ha colisic�n
  // res==1:  Asteroide/Nave
  // res>=2:  Asteroide/Proyectil, depende del tipo de asteroide (grande/mediano/peque�o)
  res1 = worldobjects.collisions(theBullet1, nShips1 > 0 ? theShip1 : NULL, expl_pos);
  res2 = worldobjects.collisions(theBullet2, nShips2 > 0 ? theShip2 : NULL, expl_pos);

  int res = (res1 > 0) ? res1 : res2;

  // Explosion
  if(res>0 || FlameTime>0)
    {
      FlameTime++;
      if(!theFlame)
	{
	  theFlame = new Flame(expl_pos);
	  worldobjects.add(theFlame);
	}
      else
	if(FlameTime>FT)
	  {
	    worldobjects.remove(theFlame);
	    theFlame=NULL;
	    FlameTime = 0;
	  }
    }
  
  handleCollisionResult(res1, theShip1, theBullet1, shotTime1, nShips1, nShips2);
  handleCollisionResult(res2, theShip2, theBullet2, shotTime2, nShips2, nShips1);
}
 
/**************************************************************/ 

void OnDibuja(void)
{ 
  //Borrado de la pantalla	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Manda el mensaje "draw" al mundo
  worldobjects.draw();    

  // imprime datos
  printdata();
 
  //Al final, cambiar el buffer
  glutSwapBuffers();
  glutPostRedisplay();//se le indica que redibuje la pantalla
  /**************************************************************/}



   


void OnKeyboardDown(unsigned char key, int x, int y)
{ 
  switch(key)
    {
    case 'q':
    case 'Q':
    case ESC:
      exit(1);
    case ' ':
      if (nShips1 > 0)
	tryFire(theShip1, theBullet1);
      break;
    case 'w':
      if (nShips1 > 0)
	theShip1->thrust(SHIPSPEED);
      break;
    case 's':
      if (nShips1 > 0)
	theShip1->thrust(-SHIPSPEED);
      break;
    case 'a':
      if (nShips1 > 0)
	theShip1->rotate(0, -5, 0);
      break;
    case 'd':
      if (nShips1 > 0)
	theShip1->rotate(0, 5, 0);
      break;
    case '\r':
        if (nShips2 > 0)
            tryFire(theShip2, theBullet2);
        break;
    }		

}


void OnSpecKeyboardDown(int key, int x, int y)
{ 
  switch(key)
    {
    case GLUT_KEY_DOWN:
      if (nShips2 > 0)
	theShip2->thrust(-SHIPSPEED);
      break;
    case GLUT_KEY_UP:
      if (nShips2 > 0)
	theShip2->thrust(SHIPSPEED);
      break;
    case GLUT_KEY_LEFT:
      if (nShips2 > 0)
	theShip2->rotate(0, -5, 0);
      break;
    case GLUT_KEY_RIGHT:
      if (nShips2 > 0)
	theShip2->rotate(0, 5, 0);
      break;
    }		

}

// No usada
void OnMouseBtn(int button, int state,int x, int y)
{
  if(state==GLUT_DOWN)
    if(button==GLUT_LEFT_BUTTON)
      MODE=TRANS;
    else
      if(button==GLUT_RIGHT_BUTTON)
        MODE=ROT;
      else
        MODE=NONE;
    printf("MOUSE!\n");
}

 
// No usada
void  OnMouseMoveBtn  (int x, int y)
{

  //  printf("MOUSE MOVES!\n");
    
  if(MODE==TRANS)
    {
     
    }
  else
    {
     
    }

 
 
}
