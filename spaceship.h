#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship {
public:
    int x, y;
    int health;
    int score;

    Spaceship();
    void draw();
    void moveLeft();
    void moveRight();
};

#endif
