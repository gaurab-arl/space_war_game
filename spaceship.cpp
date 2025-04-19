#include <graphics.h>
#include "spaceship.h"

Spaceship::Spaceship() {
    x = 350;
    y = 500;
    health = 100;
    score = 0;
}

void Spaceship::draw() {
    setcolor(WHITE);
    rectangle(x, y, x + 40, y + 20);  // Basic spaceship shape
    floodfill(x + 20, y + 10, WHITE);
}

void Spaceship::moveLeft() {
    if (x > 0) x -= 10;
}

void Spaceship::moveRight() {
    if (x < 640) x += 10;
}
