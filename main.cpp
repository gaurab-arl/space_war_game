#include <graphics.h>
#include "userui.h"
#include "gameui.h"
#include "fileop.h"
#include "collision.h"


int main()
{
      initwindow(MAX_WIDTH, MAX_HEIGHT, "War Space Game");  // Initialize graphics window
    
    give_name();                          // Get user name
    user_interference();                  // Load UI screen

    component_click(x , y);               // Handle button clicks
    
    delay(1000);
    getch();                              // pause screen 
    closegraph();
    return 0; 
}
