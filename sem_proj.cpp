#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;

#define MAX_WIDTH 1080
#define MAX_HIGHT 700

struct user_name {
    char name[20] = ""; 
} user;

void give_coordinate();
void game_interference();
void history_interference();
void user_interference();
void give_name();
void component_click();

int main() {
    initwindow(MAX_WIDTH, MAX_HIGHT, "War Space Game");
    
    give_name();
    user_interference();

    component_click();  
    
    
    
    delay(1000); 
    getch();
    closegraph();
    return 0;
}


void give_name() {
    int i = 0;
    char ch;
    char display_name[21] = "";  

    readimagefile("C:\\Users\\user\\OneDrive\\Documents\\Graphic proj\\user_interference.bmp", 0, 0, MAX_WIDTH, MAX_HIGHT);
    setbkcolor(BLACK);

    setcolor(WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 6);           
    outtextxy(260, 64, " SPACE WAR GAME "); 

    for (int thickness = 0; thickness < 3; thickness++) {
        setcolor(DARKGRAY);
        rectangle(277 - thickness, 181 - thickness, 888 + thickness, 605 + thickness);
    }

    setcolor(WHITE);
    rectangle(277, 181, 888, 605);
    rectangle(293, 195, 873, 587);
    
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(336, 210, "Enter Your Name: ");

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(336, 256, 825, 305);
    setcolor(WHITE);
    rectangle(336, 256, 825, 305);

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

    while (1) {
        ch = getch();  

        if (ch == '\r') 
            break;
        else if (ch == '\b' && i > 0) {  
            i--;
            display_name[i] = '\0';  
            setfillstyle(SOLID_FILL, BLACK);
            bar(337, 257, 824, 304);  
            setcolor(WHITE);
            outtextxy(354, 264, display_name);  
        } 
        else if (i < 19 && ch >= 32 && ch <= 126) { 
            display_name[i] = ch;
            display_name[i + 1] = '\0';
            setfillstyle(SOLID_FILL, BLACK);
            bar(337, 257, 824, 304);
            setcolor(WHITE);
            outtextxy(354, 264, display_name);
            i++;
        }
    }

    strcpy(user.name, display_name);
    cleardevice();
}

void user_interference() {
    readimagefile("C:\\Users\\user\\OneDrive\\Documents\\Graphic proj\\user_interference.bmp", 0, 0, MAX_WIDTH, MAX_HIGHT);
    setbkcolor(BLACK);
      
    setfillstyle(SOLID_FILL, WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 7);           
    outtextxy(150, 60, " SPACE WAR GAME ");

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 6); 
    outtextxy(450, 230, user.name);
    outtextxy(480, 330, " Start ");
    outtextxy(480, 430, " History ");
    outtextxy(480, 530, " Exist ");
}

void component_click() {
    int x, y;

    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d \t %d \n ", x, y);

            // Start Button Click (480, 330) - Approximate Bounds
            if (x >= 480 && x <= 680 && y >= 330 && y <= 380) {
                setcolor(RED); // Click effect
                outtextxy(480, 330, " Start ");
                delay(100);
                setcolor(WHITE);
                outtextxy(480, 330, " Start ");
                cleardevice();
                game_interference();
                break;
            }

            // History Button Click (480, 430)
            if (x >= 480 && x <= 680 && y >= 430 && y <= 480) {
                setcolor(RED);
                outtextxy(480, 430, " History ");
                delay(100);
                setcolor(WHITE);
                outtextxy(480, 430, " History ");
                cleardevice();
                history_interference();
                break;
            }

            // Exit Button Click (480, 530)
            if (x >= 480 && x <= 680 && y >= 530 && y <= 580) {
                setcolor(RED);
                outtextxy(480, 530, " Exist ");
                delay(100);
                setcolor(WHITE);
                outtextxy(480, 530, " Exist ");
                closegraph();
                exit(0);
            }
        }
    }
}


void game_interference() {
return;

}

void history_interference()
{
	return;
}
