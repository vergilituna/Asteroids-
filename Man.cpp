#include "Man.h"
#include "GLstuff.h"
#include <math.h>


 Man::Man()
 {
   x=0.03;
   y=-0.175;
   z=0.2;
   rot=0;
   }



void Man::drawMan()
{
  
  glColor3f(1.0f, 1.0f, 1.0f);

  glPushMatrix();
  
  glTranslatef(x,y,z);
  glRotatef(90,1,0,0);
  glRotatef(rot,0,1,0);
  glRotatef(0,0,0,1);
  
  
  // Draw Body	
  //  glTranslatef(1.0 ,1.0, 1.0);
  glutSolidSphere(0.30f,20,20);
  
  // Draw Head
  glTranslatef(0.0f, 0.30f+0.15f, 0.0f);
  glutSolidSphere(0.15f,20,20);
  
  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.03f, 0.12f, 0.08f);
  glutSolidSphere(0.03f,10,10);
  glTranslatef(-0.06f, 0.0f, 0.0f);
  glutSolidSphere(0.03f,10,10);
  glPopMatrix();
  
  // Draw Nose
  glColor3f(1.0f, 0.5f , 0.5f);
  glRotatef(0.0f,1.0f, 0.0f, 0.0f);
  glutSolidCone(0.06f,0.3f,10,2);
  glPopMatrix();
  
}


void Man::move()
{
  static float s=0;

  rot += 1.5;

  if(rot>360) rot = 0;

  // bouncing man
  s+=0.02;
  z = 0.3*sin(s);
  if (s>3.14) {s=0;}
}
