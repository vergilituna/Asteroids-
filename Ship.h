
#include "commonstuff.h"
#include "Shape.h"
#include "Bullet.h"

#ifndef __SHIP_H__
#define __SHIP_H__

class Ship: public Shape {
 private:
  int status;
  float spawnX;
  float spawnY;
  float spawnColor[3];
 public:
  Ship(float startX = 0, float startY = 0,
       float cr = 0.2f, float cg = 0.4f, float cb = 0.3f);
  void draw();
  void rotate(float,float,float);
  Bullet* fire();
  void thrust(float);
  void hyperjump();
  float getSize();
  void resetpos();
};

#endif
