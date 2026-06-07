#include "Cube.h"
#include <math.h>
#include "GLstuff.h"


 Cube::Cube()
 {
   x=0.03;
   y=-0.175;
   z=0.2;
   rotx=0;
   roty=0;
   rotz=0;
   }

Cube:: Cube(float xx, float yy, float zz, float rx, float ry, float rz)
{
   x=xx;
   y=yy;
   z=zz;
   rotx=rx;
   roty=ry;
   rotz=rz;
}


void Cube::draw()
{
  
  glColor3f(1.0f, 0.0f, 0.0f);

  glPushMatrix();
  
  glTranslatef(x,y,z);
  glRotatef(rotx,1,0,0);
  glRotatef(roty,0,1,0);
  glRotatef(rotz,0,0,1);
  
  
  // Draw a Cube	
  glutSolidCube(0.9f);
  
    glPopMatrix();

}


void Cube::move()
{
  rotx += 1.5;   if(rotx>360) rotx = 0;
  roty += 1.5;   if(roty>360) roty = 0;

}
