#ifndef GAMEUI_H
#define GAMEUI_H

#include <graphics.h>

#include <time.h>
#include <windows.h>

#define SCREEN_WIDTH 1168
#define SCREEN_HEIGHT 700
#define MAX_BULLETS 10
#define MAX_SKY_BULLETS 5
#define MAX_ENEMY_BULLETS 5

// Game parameters
extern int ENEMY_SPEED;
extern int userSpeed;
extern int score;
extern int health;

// Renamed to avoid conflict with 'User' in userui.h
struct Player {
    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT - 100;
};

// Enemy structure
struct Enemy {
    int x, y;
    int speedX, speedY;
    bool moveRight;
};
extern Enemy enemies[5];

// Bullet structure
struct Bullet {
    int x, y;
    bool active;
};
extern Bullet bullets[MAX_BULLETS];
extern Bullet skyBullets[MAX_SKY_BULLETS];

// Ship position
extern int shipPosX;
extern int shipPosY;

// Function declarations
void initBullets();
void fireBullet();
void updateBullets();
void updateSkyBullets();
void drawBullets();
void drawSkyBullets();
void drawShip(int posX, int posY);
void moveShip();
void draw_ui();
void draw_enemy(Enemy &enemy, int color);
void move_enemy(Enemy &enemy);
void game_main();
void game_over();

#endif // GAMEUI_H
