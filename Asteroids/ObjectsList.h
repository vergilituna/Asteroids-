#ifndef OBJECTSLIST_H
#define OBJECTSLIST_H

// Hocanın projesinde yer alan temel sınıf ve yapıları dahil ediyoruz
#include "Shape.h"   
#include "Ship.h"    
#include "Bullet.h"  
#include "Asteroid.h"
#include "commonstuff.h"

// Listedeki her bir elemanı tutacak olan düğüm yapısı
struct Node {
    Shape* object;
    Node* next;
};

class ObjectsList {
private:
    int n;           // Listedeki toplam obje sayısı [cite: 152]
    Node* list_head; // Bağlı listenin başlangıç işaretçisi [cite: 152]

public:
    ObjectsList();   // Constructor [cite: 150]
    ~ObjectsList();  // Destructor [cite: 157]

    void move();     // Objeleri hareket ettiren fonksiyon [cite: 150]
    void draw();     // Objeleri ekrana çizen fonksiyon [cite: 150]

    void add(Shape* s);    // Listeye eleman ekleme [cite: 150]
    void remove(Shape* s); // Listeden eleman silme [cite: 150]

    Ship* getShip(); // Gemiye erişim sağlayan fonksiyon [cite: 150]

    int collisions(Bullet* bullet, Ship* ship); // Çarpışma kontrolü [cite: 150]
    void reposition(Ship* ship);               // Gemiyi yeniden konumlandırma [cite: 150]
};

#endif // OBJECTSLIST_H