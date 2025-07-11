#ifndef USERUI_H
#define USERUI_H

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 1168
#define MAX_HEIGHT 700
#define MAX_USERS 100

struct User {
    char name[20];
    int score = 0;
    int high_score = 1000;
};

// Global variables
extern int x, y;
extern User current_user;

// Function declarations
void title();
void background_image();
void give_coordinate();
void give_name();
void back_button();
bool component_click(int x, int y);
void history_interference();
void user_interference();  
#endif