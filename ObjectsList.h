#ifndef OBJECTSLIST_H
#define OBJECTSLIST_H

#include "Shape.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Bullet.h"
#include "commonstuff.h"

struct Node {
    Shape* object;
    Node* next;
};


class ObjectsList {
private:
    Node* list_head; 

public:
    ObjectsList();
    ~ObjectsList();
    void add(Shape* obj);
    void remove(Shape* obj);
    void move();
    void draw();
    void reposition(Ship* ship);
    Ship* getShip();
    int collisions(Bullet* bullet, Ship* ship, float* expl_pos);
};

#endif