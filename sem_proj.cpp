#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>               
#include <iostream>                      // For fast input and output , using file 

using namespace std;

#define MAX_WIDTH  1080                 // Screen width 
#define MAX_HIGHT   700                 // Screen height 

// 🎯 Mouse click coordinates
int x, y;

// 🎮 Structure to store user name
struct user_name {
    char name[20] = ""; 
} user;

// Function Declarations
void background_image();                  // easy use for background image
void give_name();                        // Get user name at start
void user_interference();                // Main UI screen
void component_click(int x, int y);      // Handles click events
void give_coordinate();                  // Debugging: Get mouse coordinates

void game_interference();                // Game screen
void history_interference();             // History screen

void back_button();                      // Draw Back button

int main() {
    initwindow(MAX_WIDTH, MAX_HIGHT, "War Space Game");  // Initialize graphics window
    
    give_name();                          // Get user name
    user_interference();                  // Load UI screen

    component_click(x , y);               // Handle button clicks
    
    delay(1000);
    getch();                              // pause screen 
    closegraph();
    return 0;
}

void background_image()
{
    readimagefile("C:\\Users\\user\\OneDrive\\Documents\\Graphic proj\\user_interference.bmp", 0, 0, MAX_WIDTH, MAX_HIGHT);
}

// 📌 Function to get mouse coordinates for debugging
void give_coordinate() { 
    while (!kbhit()) {                                        // until key is hit it runs

        if (ismouseclick(WM_LBUTTONDOWN)) { 
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d \t %d \n ", x, y);                     // Print coordinates
        }
    } 
}

// 📌 Function to get user name at start
void give_name() {
    int i = 0;
    char ch;
    char display_name[21] = "";  

    // Load background image
    background_image();
 ////    setbkcolor(BLACK);                                                                                                        

    setcolor(WHITE);
    rectangle(260, 64, 961, 124);                           // first rectangle to include every item
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(261, 65, 960, 123);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 6);               // font direction size
    outtextxy(260, 64, " SPACE WAR GAME "); 

    // Name Input Box
    setcolor(WHITE);
    rectangle(277, 181, 888, 605);                           // first rectangle to include every item
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(278, 182, 887, 604);
    
    rectangle(293, 195, 873, 587);
    setfillstyle(SOLID_FILL, BLACK);
    bar(294, 196, 872, 586);

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(336, 210, "Enter Your Name: ");

    setfillstyle(SOLID_FILL, LIGHTGRAY);                         // input baar appers lightgray
    bar(336, 256, 825, 305);                                     // Name input bar
    setcolor(WHITE);
    rectangle(336, 256, 825, 305);

    // Instructions
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(305, 340, "  Name should be at least 6 to 8 letters ");
    
    setcolor(LIGHTCYAN);
    outtextxy(305, 380, "  -> Control your spaceship and fight enemies.");
    outtextxy(305, 420, "  -> Use arrow keys to move, and spacebar to shoot.");
    outtextxy(305, 460, "  -> Available arrow keys: UP, DOWN, RIGHT, LEFT.");
    outtextxy(305, 500, "  -> Defeat enemies and survive as long as possible.");
    
    setcolor(YELLOW);
    outtextxy(305, 545, "Press Enter after typing your name to continue.");

    // Input handling
    while (1) {
        ch = getch();                                        // Get character
  
        if (ch == '\r')                                     // Enter key -> Stop input
            break;
        else if (ch == '\b' && i > 0) {                    // Backspace handling
            i--;
            display_name[i] = '\0';                         // 
            setfillstyle(SOLID_FILL, BLACK);                 // balck box appers when started writing
            bar(337, 257, 824, 304);
            setcolor(WHITE);                                 // name display in white
            outtextxy(354, 264, display_name);
        } 
        else if (i < 19 && ch >= 32 && ch <= 126) { // Valid character input
            display_name[i] = ch;
            display_name[i + 1] = '\0';
            setfillstyle(SOLID_FILL, BLACK);
            bar(337, 257, 824, 304);
            setcolor(WHITE);
            outtextxy(354, 264, display_name);
            i++;
        }
    }

    strcpy(user.name, display_name);                             // store final name in structure
    cleardevice();
}

// Main UI Screen
void user_interference() {
    background_image();
    setbkcolor(BLACK);
      
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 7);           
    outtextxy(150, 60, " SPACE WAR GAME ");

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 6); 
    outtextxy(450, 230, user.name);
    outtextxy(480, 330, " Start ");
    outtextxy(480, 430, " History ");
    outtextxy(480, 530, " Exit ");

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            component_click(x, y);
        }
    }
}

// 📌 Handles clicks for UI components
void component_click(int x, int y) {
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d \t %d \n ", x, y); // Debugging  

            if (x >= 480 && x <= 680 && y >= 330 && y <= 380) { // Start Button
                cleardevice();
                game_interference();
                break;
            }
            if (x >= 480 && x <= 680 && y >= 430 && y <= 480) { // History Button
                cleardevice();
                history_interference();
                break;
            }
            if (x >= 480 && x <= 680 && y >= 530 && y <= 580) { // Exit Button
                closegraph();
                exit(0);
            }
            if (x >= 40 && x <= 140 && y >= 30 && y <= 70) { // Back Button
                cleardevice();
                clearmouseclick(WM_LBUTTONDOWN);
                user_interference();
                break;
            }
        }
    }
}

// 📌 Draws Back button
void back_button() {
    setcolor(WHITE);
    rectangle(40, 30, 140, 70);
    setfillstyle(SOLID_FILL, BLACK);
    bar(41, 31, 139, 69);
    setcolor(WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(60, 40, "Back");
}

// 📌 Game Screen
void game_interference() {
    cleardevice();
    back_button();
    
    while (true) {
        clearmouseclick(WM_LBUTTONDOWN);
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            component_click(x, y);
            break;
        }
    }
}

// 📌 History Screen
void history_interference() {
    cleardevice();
    back_button();
    
    while (true) {
        clearmouseclick(WM_LBUTTONDOWN);
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            component_click(x, y);
            break;
        }
    }
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/
 /* NOTE 
  
-   setcolor(WHITE);
    rectangle(40, 30, 140, 70);
    setfillstyle(SOLID_FILL, BLACK);
    bar(41, 31, 139, 69);
      when using baar first x , y coordinatae should be higher coordinate 

  */
/* --------------------------------------------------------------------------------------------------------------------------------------------*/
// main game function program to operate

