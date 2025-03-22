#include "userui.h"

int x, y;  // Define the global variables here
User_name user; // Define user struct here

void background_image() {
   // readimagefile("C:\\Users\\user\\OneDrive\\Documents\\Graphic proj\\user_interference.bmp", 0, 0, MAX_WIDTH, MAX_HIGHT);
    readimagefile("C:\\Users\\user\\OneDrive\\Documents\\Graphic proj\\deep_space_background.bmp", 0, 0, MAX_WIDTH, MAX_HIGHT);
}


//  Function to get mouse coordinates for debugging
void give_coordinate() { 
    while (!kbhit()) {                                        // until key is hit it runs

        if (ismouseclick(WM_LBUTTONDOWN)) { 
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d \t %d \n ", x, y);                     // Print coordinates
        }
    } 
}
void give_name() {
    int i = 0;
    char ch;
    char display_name[21] = "";  
    bool is_valid_length = false;

    // Load background image
    background_image();
    title();
    
    // Name Input Box
    setcolor(WHITE);
    rectangle(277, 181, 888, 605);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(278, 182, 887, 604);
    
    rectangle(293, 195, 873, 587);
    setfillstyle(SOLID_FILL, BLACK);
    bar(294, 196, 872, 586);
    
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(336, 210, "Enter Your Name: ");

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(336, 256, 825, 305);
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
        ch = getch();
  
        if (ch == '\r') {
            // Only allow continuing if name is between 6-8 characters
            if (i >= 6 && i <= 8) {
                break;
            } else {
                // Display error message
                setcolor(RED);
                settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
                outtextxy(336, 330, "Name must be 6-8 characters!");
                delay(1500);
                // Clear the error message
                setfillstyle(SOLID_FILL, BLACK);
                bar(336, 330, 825, 355);
                // Restore original text
                settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
                setcolor(WHITE);
                outtextxy(305, 340, "  Name should be at least 6 to 8 letters ");
            }
        }
        else if (ch == '\b' && i > 0) {
            i--;
            display_name[i] = '\0';
            setfillstyle(SOLID_FILL, BLACK);
            bar(337, 257, 824, 304);
            setcolor(WHITE);
            outtextxy(354, 264, display_name);
        } 
        else if (i < 8 && ch >= 32 && ch <= 126) { // Changed max length to 8
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
// Main UI Screen
void user_interference() {
    // Load background image - same as first screen
    background_image();
    title();
    
    // Create a similar box layout as in the first screen
    setcolor(WHITE);
    rectangle(277, 181, 888, 605);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(278, 182, 887, 604);
    
    rectangle(293, 195, 873, 587);
    setfillstyle(SOLID_FILL, BLACK);
    bar(294, 196, 872, 586);
    
    // Display username
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(430, 230, user.name);
    
    // Create menu options with separating lines
    line(293, 290, 873, 290);
    
    // Start button
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(430, 330, "Start");
    
    line(293, 390, 873, 390);
    
    // History button
    outtextxy(430, 430, "History");
    
    line(293, 490, 873, 490);
    
    // Exit button
    outtextxy(430, 530, "Exit");
    
    // Handle clicks
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            
            // Start button area
            if (x >= 430 && x <= 580 && y >= 330 && y <= 370) {
                cleardevice();
                game_interference();
                break;
            }
            // History button area
            if (x >= 430 && x <= 580 && y >= 430 && y <= 470) {
                cleardevice();
                history_interference();
                break;
            }
            // Exit button area
            if (x >= 430 && x <= 580 && y >= 530 && y <= 570) {
                closegraph();
                exit(0);
            }
        }
    }
}
void component_click(int x, int y) {
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            
            // Start button
            if (x >= 430 && x <= 580 && y >= 330 && y <= 370) {
                cleardevice();
                
                game_interference();
                break;
            }
            // History button
            if (x >= 430 && x <= 580 && y >= 430 && y <= 470) {
                cleardevice();
               
                history_interference();
                break;
            }
            // Exit button
            if (x >= 430 && x <= 580 && y >= 530 && y <= 570) {
                closegraph();
                exit(0);
            }
            // Back button
            if (x >= 40 && x <= 140 && y >= 30 && y <= 70) {
    cleardevice();
    user_interference();
    break;
}
            }
        }
    }

// ?? Draws Back button
void back_button() {
    setcolor(WHITE);
    rectangle(40, 30, 140, 70);
    setfillstyle(SOLID_FILL, BLACK);
    bar(41, 31, 139, 69);
    setcolor(LIGHTGRAY);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(60, 40, "Back");
}

// ?? Game Screen
void game_interference() {
    cleardevice();
    background_image();
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

void history_interference() {
    // Use the same background as other screens instead of stars
    background_image();
       back_button();
    
    // Add your history content here
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    outtextxy(400, 150, "Game History");
    
    // Add some placeholder history content
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(300, 250, "No game records found yet.");
    
    while (true) {
    	
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            component_click(x, y);
            break;
        }
    }
}

void title()
{
	setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(150, 60, 1020, 130);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 7);               // font direction size
    outtextxy(150, 60, " SPACE WAR GAME "); 
}