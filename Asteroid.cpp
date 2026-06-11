
#include "commonstuff.h"
#include "Asteroid.h"


Asteroid::Asteroid(int t)
{
  float tmp;

  size = BIG;
  type = t;

  pos[X] = RAND_DOM(0,SIZEX);
  pos[Y] = RAND_DOM(0,SIZEY);
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = RAND_FRAC()*0.5;
  rspeed[Y] = RAND_FRAC()*0.5;
  rspeed[Z] = RAND_FRAC()*0.5;

  tmp = RAND_FRAC();
  tspeed[X] = tmp*ASTEROID_SPEED;
  tspeed[Y] = (1-tmp)*ASTEROID_SPEED;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.2;
  color[B] = 0.1;

  //  printf("Mi no is %d",mynumber);
}


Asteroid::Asteroid(int t, int s, float px, float py)
{
  float tmp;

  size = s;
  type = t;

  pos[X] = px;
  pos[Y] = py;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = RAND_FRAC()*0.5;
  rspeed[Y] = RAND_FRAC()*0.5;
  rspeed[Z] = RAND_FRAC()*0.5;

  tmp = RAND_FRAC();
  tspeed[X] = tmp*ASTEROID_SPEED;
  tspeed[Y] = (1-tmp)*ASTEROID_SPEED;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.2;
  color[B] = 0.1;
}


void Asteroid::draw()
{
  predraw();
  glutSolidSphere(size*0.3,9,8);
  glTranslatef(0,size*0.3,0);	
  glutSolidSphere(size*0.25,7,9);
  
  postdraw();
}
 

Asteroid *Asteroid::split()
{
  Asteroid *tmp;

  tmp = new Asteroid(1,size-1,pos[X],pos[Y]);
  size--;

  return tmp;
}
 
float Asteroid::getSize()
{
  return (0.3*size);
}

void Asteroid::reposition()
{
  pos[X] += 1+3*RAND_FRAC();
  pos[Y] += 1+3*RAND_FRAC();

}

float Asteroid::operator+(Shape* s) {
  if (!s) return 0.0f;
  float s_pos[3];
  s->getPos(s_pos);
  return mydistance(pos[X], pos[Y], s_pos[X], s_pos[Y]);
}
