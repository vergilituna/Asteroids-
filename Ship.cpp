
#include "commonstuff.h"
#include "Ship.h"
#include "Bullet.h"


Ship::Ship(float startX, float startY, float cr, float cg, float cb)
{
  spawnX = startX;
  spawnY = startY;
  spawnColor[R] = cr;
  spawnColor[G] = cg;
  spawnColor[B] = cb;

  pos[X] = startX;
  pos[Y] = startY;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = -90;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = 0;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = cr;
  color[G] = cg;
  color[B] = cb;
}

void Ship::rotate(float rx, float ry, float rz)
{
  rot[X] += rx;  rot[Y] += ry;  rot[Z] += rz;
}

 Bullet* Ship::fire()
 {
   Bullet *tmp;

   tmp = new Bullet(pos[X],pos[Y],BULLETSPEED*sin(D2R*rot[Y]),BULLETSPEED*cos(D2R*rot[Y]));

   return tmp;
 }

 void Ship::thrust(float howmuch)
 {
   tspeed[X] += howmuch*sin(D2R*rot[Y]);
   tspeed[Y] += howmuch*cos(D2R*rot[Y]);
}


void Ship::hyperjump()
{
  pos[X] = RAND_DOM(0,(SIZEX-2))-SIZEX2;
  pos[Y] = RAND_DOM(0,(SIZEY-2))-SIZEY2;

  //printf("ship @ %f %f\n",pos[X],pos[Y]);
  //rot[Y] =  RAND_DOM(0,359);
}


void Ship::draw()
{
  predraw();
  glutSolidCone(0.25,1,10,10);	
  postdraw();
}
  

float Ship::getSize()
{
  return (0.25);
}

void Ship::resetpos()
{
  pos[X] = spawnX;
  pos[Y] = spawnY;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = -90;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = 0;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = spawnColor[R];
  color[G] = spawnColor[G];
  color[B] = spawnColor[B];
}
