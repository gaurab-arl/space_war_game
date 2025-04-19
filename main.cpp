#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameui.h"
#include "userui.h"
#include "fileop.h"

int main() {
    initwindow(MAX_WIDTH, MAX_HIGHT, "War Space Game");  // Initialize graphics window

    give_name();                          // Get user name
    user_interference();                  // Load UI screen

    component_click();               // Handle button clicks

    delay(1000);
    getch();                               // pause screen 
    closegraph();
    return 0; 
}
