#include "userui.h"


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