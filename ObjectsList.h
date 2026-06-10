#ifndef OBJECTSLIST_H
#define OBJECTSLIST_H

#include "commonstuff.h" 


class Shape;
class Asteroid;
class Ship;
class Bullet;

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