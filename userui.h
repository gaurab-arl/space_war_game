#ifndef USERUI_H
#define USERUI_H

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>               
#include <iostream>

using namespace std;

#define MAX_WIDTH  1168  
#define MAX_HIGHT   700   

// Include the headers where Enemy, Bullet_user, Bullet_enemy are defined
#include "gameui.h"


// Declare global variables as extern
extern int x, y;

extern struct User_name {
    char name[20];
} user;

extern int shipPosX;
extern int shipPosY;
extern int score;
extern int health;
extern int rewardCount;
extern int bullet_pos_x;
extern int bullet_pos_y;
extern int reward_pos_x;
extern int reward_pos_y;

extern int bullets_random[5][2];
extern int rewards[5][2];

// Assuming these are full instances (not pointers), so full types are required
extern Enemy enemies[5];
extern Bullet_user bullets[10];
extern Bullet_enemy skyBullets[5];

// Function Declarations
void title();
void background_image();
void give_name();
void user_interference();
void component_click();
void give_coordinate();
void game_interference();
void history_interference();
void back_button();
void game_over();

#endif
