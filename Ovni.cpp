
#include "commonstuff.h"
#include "Ovni.h"

Ovni::Ovni()
{
  size = RAND_DOM(SMALL, BIG);
  phase = RAND_FRAC() * 6.28318f;
  amplitude = 0.08f + RAND_FRAC() * 0.12f;

  pos[Y] = RAND_DOMF(-SIZEY2 + 1.0f, SIZEY2 - 1.0f);
  pos[Z] = 0;

  rot[X] = 0;
  rot[Y] = 0;
  rot[Z] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  if (RAND_BIT()) {
    pos[X] = -SIZEX2;
    tspeed[X] = OVNI_SPEED;
  }
  else {
    pos[X] = SIZEX2;
    tspeed[X] = -OVNI_SPEED;
  }

  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.2f;
  color[G] = 0.9f;
  color[B] = 0.3f;
}


void Ovni::move()
{
  pos[X] += tspeed[X];

  phase += 0.15f + RAND_FRAC() * 0.05f;
  tspeed[Y] += (float)((RAND_FRAC() - 0.5) * 0.008);
  if (tspeed[Y] > 0.06f) tspeed[Y] = 0.06f;
  if (tspeed[Y] < -0.06f) tspeed[Y] = -0.06f;

  pos[Y] += amplitude * (float)sin(phase) + tspeed[Y];

  if (pos[Y] > SIZEY2) {
    pos[Y] = SIZEY2;
    tspeed[Y] = -fabs(tspeed[Y]);
  }
  if (pos[Y] < -SIZEY2) {
    pos[Y] = -SIZEY2;
    tspeed[Y] = fabs(tspeed[Y]);
  }
}


void Ovni::draw()
{
  predraw();
  glColor3f(1.0f, 1.0f, 1.0f);
  glutSolidSphere(size * 0.2f, 9, 8);
  postdraw();
}


float Ovni::getSize()
{
  return 0.25f * size;
}


bool Ovni::isOffScreen()
{
  return (pos[X] < -SIZEX2 - 1.0f || pos[X] > SIZEX2 + 1.0f);
}


int Ovni::getScoreCode()
{
  if (size == SMALL) return 1500;
  if (size == MEDIUM) return 1000;
  return 500;
}


float Ovni::operator+(Shape* s)
{
  if (!s) return 0.0f;
  float s_pos[3];
  s->getPos(s_pos);
  return mydistance(pos[X], pos[Y], s_pos[X], s_pos[Y]);
}
