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

// Declare global variables as extern
extern int x, y;
extern struct User_name {
    char name[20];
} user;

// Function Declarations
void title();
void background_image();
void give_name();
void user_interference();
void component_click(int x, int y);
void give_coordinate();
void game_interference();
void history_interference();
void back_button();

#endif
