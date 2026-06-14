
#include "commonstuff.h"
#include "Shape.h"

#ifndef __OVNI_H__
#define __OVNI_H__

class Ovni : public Shape {
 private:
  int size;
  float phase;
  float amplitude;
 public:
  Ovni();
  void move();
  void draw();
  float getSize();
  bool isOffScreen();
  int getScoreCode();
  float operator+(Shape* s);
};

#endif
