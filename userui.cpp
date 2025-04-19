#include "userui.h"
#include "gameui.h"
#include "fileop.h"

int x, y;  // Define the global variables here
User_name user; // Define user struct here



void background_image() {
    readimagefile("C:\\Users\\user\\OneDrive\\Documents\\SEMESTER Graphic proj\\deep_space_background.bmp", 0, 0, MAX_WIDTH, MAX_HIGHT);
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
void user_interference() {
    // Load background image - same as first screen
    background_image();
    title();
    
    // Create a similar box layout as in the first screen
    setcolor(WHITE);
    rectangle(327, 181, 838, 605);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(328, 182, 837, 604);
    
    rectangle(343, 195, 823, 587);
    setfillstyle(SOLID_FILL, BLACK);
    bar(344, 196, 822, 586);
    
    // Display username
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(500, 230, user.name);
    
    // Menu options with separators
    line(343, 290, 823, 290);
    
    // Start button
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(530, 330, "Start");
    
    line(343, 390, 823, 390);
    
    // History button
    outtextxy(520, 430, "History");
    
    line(343, 490, 823, 490);
    
    // Exit button
    outtextxy(540, 530, "Exit");
    
    // Wait for user interaction
    component_click();
}

void component_click() {
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            // Start button area
            if (x >= 530 && x <= 630 && y >= 330 && y <= 370) {
                cleardevice();
                game_interference();
                break;
            }
            // History button area
            if (x >= 520 && x <= 630 && y >= 430 && y <= 470) {
                cleardevice();
                history_interference();
                break;
            }
            // Exit button area
            if (x >= 540 && x <= 620 && y >= 530 && y <= 570) {
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
    srand(time(0));

    spawn_enemies();

    // Removed yellow bullets initialization

    for (int i = 0; i < 5; i++) {
        rewards[i][0] = rand() % (SCREEN_WIDTH - 40) + 20;
        rewards[i][1] = rand() % 200;
    }  

    initBullets();

    int activePage = 0, visualPage = 1;

   while (true && health > 0) {
    setactivepage(activePage);
    setvisualpage(visualPage);
    cleardevice();

    draw_ui();

    

    draw_reward();

    for (int i = 0; i < 5; i++) {
        draw_enemy(enemies[i], (i < 3) ? GREEN : RED);
        move_enemy(enemies[i]);
    }

    moveShip();
    checkCollisions();

    delay(50);
    std::swap(activePage, visualPage);
}

game_over();  // <- Call this instead of repeating the Game Over logic


    settextstyle(3, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, "Game Over!");

    delay(2000);  // Wait for 2 seconds
    cleardevice();
    user_interference();  // Go back to the main menu
}


void game_over() {
    settextstyle(3, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, "Game Over!");

    delay(2000);  // Pause so the user can see the message
    cleardevice();
    user_interference();  // Back to main menu
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
    

            component_click();
            
}

void title()
{
	setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(150, 60, 1020, 130);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 7);               // font direction size
    outtextxy(150, 60, " SPACE WAR GAME "); 
}