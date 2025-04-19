#ifndef GAMEUI_H
#define GAMEUI_H
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>

#define SCREEN_WIDTH 1168
#define SCREEN_HEIGHT 700
#define USER_SPEED 30
#define USER_BULLET_SPEED 10
#define ENEMY_BULLET_SPEED 5
#define SKY_BULLET_SPEED 5
#define MAX_BULLETS 10
#define MAX_SKY_BULLETS 5

static int ENEMY_SPEED = 5;

using namespace std;

// Just declare the variables as extern, don't initialize them here
extern int shipPosX;
extern int shipPosY;
extern int score;
extern int health;
extern int rewardCount;
extern int bullet_pos_x, bullet_pos_y;
extern int reward_pos_x, reward_pos_y;

struct Enemy {
    int x, y;
    int speedX, speedY;
    bool moveRight;
    bool active;
    bool moveHorizontally;
};

extern Enemy enemies[5]; // Make this extern too

extern int bullets_random[5][2]; // Make this extern too

struct Bullet_user {
    int x, y;
    bool active;
};

struct Bullet_enemy {
    int x, y;
    bool active;
};

extern Bullet_user bullets[MAX_BULLETS]; // Make this extern too
extern Bullet_enemy skyBullets[MAX_SKY_BULLETS]; // Make this extern too

extern int rewards[5][2]; // Increased to 5 rewards to match first code

// Function declarations
void draw_ui();
void drawShip(int posX, int posY);
void draw_enemy(Enemy &enemy, int color);
void move_enemy(Enemy &enemy);
void fireBullet();
void updateBullets();
void updateSkyBullets();
void drawBullets();
void drawSkyBullets();
void spawn_bullets();
void moveShip();
void draw_reward();
void checkCollisions();
void initBullets();
void spawn_enemies();

#endif