#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <cstdlib>
#include "glut.h"
#include "ObjectsList.h"
#include "Shape.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Bullet.h"
#include "commonstuff.h"


ObjectsList::ObjectsList() {
    n = 0;
    list_head = nullptr;
    add(new Ship());
    for(int i = 0; i < NUMASTEROIDS; ++i) {
        add(new Asteroid(1));
    }
}


ObjectsList::~ObjectsList() {
    Node* current = list_head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current->object; 
        delete current;         
        current = nextNode;
    }
}


void ObjectsList::add(Shape* obj) {
    if (obj == nullptr) return;

    Node* newNode = new Node();
    newNode->object = obj;
    newNode->next = list_head;
    list_head = newNode;
    n++;
}


void ObjectsList::remove(Shape* obj) {
    if (obj == nullptr) return;

    Node* current = list_head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->object == obj) {
            if (prev == nullptr) {
                list_head = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current->object;
            delete current;
            n--;
            return;
        }
        prev = current;
        current = current->next;
    }
}


void ObjectsList::move() {
    Node* current = list_head;
    while (current != nullptr) {
        if (current->object != nullptr) {
            current->object->move();
        }
        current = current->next;
    }
}


void ObjectsList::draw() {
    Node* current = list_head;
    while (current != nullptr) {
        if (current->object != nullptr) {
            current->object->draw();
        }
        current = current->next;
    }
}


Ship* ObjectsList::getShip() {
    Node* current = list_head;
    while (current != nullptr) {
        Ship* ship = dynamic_cast<Ship*>(current->object);
        if (ship != nullptr) {
            return ship;
        }
        current = current->next;
    }
    return nullptr;
}


void ObjectsList::reposition(Ship* ship) {
    Node* current = list_head;
    while (current != nullptr) {
        Asteroid* ast = dynamic_cast<Asteroid*>(current->object);
        if (ast != nullptr) {
            float pos[3];
            ast->getPos(pos);
            float distanceToCenter = mydistance(pos[0], pos[1], 0.0f, 0.0f);
            if (distanceToCenter < 5.0f) {
                ast->reposition();
            }
        }
        current = current->next;
    }
    if (ship != nullptr) {
        ship->resetpos(); 
    }
}


int ObjectsList::collisions(Bullet* bullet, Ship* ship, float* expl_pos) {
    Node* current = list_head;
    while (current != nullptr) {
        Asteroid* ast = dynamic_cast<Asteroid*>(current->object);
        if (ast != nullptr) {

            float posAst[3];
            ast->getPos(posAst);

          
            if (ship != nullptr) {
                float distShip = (*ast) + ship;

                if (distShip < (ast->getSize() + ship->getSize())) {
                    this->remove(ship);
                    return 1;
                }
            }

            
            if (bullet != nullptr) {
                float distBullet = (*ast) + bullet;

                if (distBullet < (ast->getSize() + bullet->getSize())) {
                    this->remove(bullet);

                    if (ast->getSize() == SMALL) {
                        this->remove(ast);
                        return 4;
                    }
                    else {
                        Asteroid* newAst = ast->split();
                        if (newAst != nullptr) {
                            this->add(newAst);
                        }
                        return (ast->getSize() == MEDIUM) ? 2 : 3;
                    }
                }
            }
        }
        current = current->next;
    }
    return 0;
}