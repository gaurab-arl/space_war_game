// Include necessary header files for UI, file operations, and collision detection
#include "userui.h"
#include "gameui.h"
#include "fileop.h"
#include "collision.h"

// Global game configuration variables
int ENEMY_SPEED = 5;        // Speed at which enemies move
int userSpeed = 30;         // Speed at which player ship moves
int score = 0;              // Current game score
int health = 3;             // Player's remaining health points

// Game object arraysi
Enemy enemies[5];                    // Array to store 5 enemy objects
Bullet bullets[MAX_BULLETS];        // Array for player's bullets
Bullet skyBullets[MAX_SKY_BULLETS]; // Array for decorative sky bullets (background effect)

// Player ship position variables
int shipPosX = SCREEN_WIDTH / 2;    // Ship's X position (centered horizontally)
int shipPosY = SCREEN_HEIGHT - 100; // Ship's Y position (near bottom of screen)

// Game state flag
bool isGameOver = false;

/**
 * Function: game_over()
 * Purpose: Display game over screen with final score and high score
 * Shows a formatted game over message with player statistics
 */
void game_over()
{
    char user_game_score[100];   // Buffer for current score display
    char user_game_highest[100]; // Buffer for high score display

    // Format score strings for display
    sprintf(user_game_score, "Your Score : %d", current_user.score);
    sprintf(user_game_highest, "Highest Score : %d", current_user.high_score);

    // Draw game over dialog box
    setcolor(WHITE);
    rectangle(250, 200, 850, 500); // Draw rectangular border

    // Display "GAME OVER" title
    setcolor(YELLOW);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5); // Large, bold font
    outtextxy(300, 250,(char*)"GAME OVER");

    // Display score information
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); // Medium font size
    outtextxy(320, 350, user_game_score);     // Show current score
    outtextxy(320, 400, user_game_highest);   // Show high score
}

/**
 * Function: initBullets()
 * Purpose: Initialize bullet arrays at game start
 * - Deactivates all player bullets
 * - Creates random sky bullets for background effect
 */
void initBullets() {
    // Initialize all player bullets as inactive
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = false;
    
    // Initialize sky bullets with random positions for visual effect
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        skyBullets[i].x = rand() % SCREEN_WIDTH;        // Random X position
        skyBullets[i].y = rand() % (SCREEN_HEIGHT / 2); // Random Y in upper half
        skyBullets[i].active = true;                    // All sky bullets start active
    }
}

/**
 * Function: fireBullet()
 * Purpose: Create a new bullet when player fires
 * Finds first inactive bullet slot and activates it at ship position
 */
void fireBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {  // Find first available bullet slot
            bullets[i].x = shipPosX;      // Set bullet X to ship position
            bullets[i].y = shipPosY;      // Set bullet Y to ship position
            bullets[i].active = true;     // Activate the bullet
            Beep(1000, 200);             // Play shooting sound effect
            break;                        // Exit after firing one bullet
        }
    }
}

/**
 * Function: updateBullets()
 * Purpose: Update positions of all active player bullets
 * Moves bullets upward and deactivates them when they leave screen
 */
void updateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= 10;          // Move bullet upward
            if (bullets[i].y < 0)        // If bullet goes off top of screen
                bullets[i].active = false; // Deactivate bullet
        }
    }
}

/**
 * Function: updateSkyBullets()
 * Purpose: Update decorative sky bullets that fall from top
 * Creates continuous rain effect by recycling bullets
 */
void updateSkyBullets() {
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            skyBullets[i].y += 5;        // Move bullet downward (slower than player bullets)
            if (skyBullets[i].y > SCREEN_HEIGHT) { // If bullet goes off bottom
                skyBullets[i].x = rand() % SCREEN_WIDTH; // Reset to random X position
                skyBullets[i].y = 0;                     // Reset to top of screen
            }
        }
    }
}

/**
 * Function: drawBullets()
 * Purpose: Render all active player bullets on screen
 * Draws yellow filled circles for player projectiles
 */
void drawBullets() {
    setfillstyle(SOLID_FILL, YELLOW);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            setcolor(YELLOW);
            circle(bullets[i].x, bullets[i].y, 3);         // Draw bullet outline
            floodfill(bullets[i].x, bullets[i].y, YELLOW); // Fill with yellow color
        }
    }
}

/**
 * Function: drawSkyBullets()
 * Purpose: Render decorative sky bullets (background effect)
 * Draws light blue filled circles for atmospheric effect
 */
void drawSkyBullets() {
    setfillstyle(SOLID_FILL, COLOR(175, 150, 0)); // Set fill color
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            setcolor(LIGHTBLUE);
            circle(skyBullets[i].x, skyBullets[i].y, 4);          // Slightly larger than player bullets
            floodfill(skyBullets[i].x, skyBullets[i].y, LIGHTBLUE); // Fill with light blue
        }
    }
}

/**
 * Function: drawShip(int posX, int posY)
 * Purpose: Render player's spaceship at specified coordinates
 * Draws a multi-part ship with body, wings, and thruster
 * Parameters: posX - X coordinate, posY - Y coordinate
 */
void drawShip(int posX, int posY) {
    // Define ship body as triangular shape pointing upward
    int bodyCoords[] = { posX, posY, posX - 12, posY + 50, posX + 13, posY + 50, posX, posY };
    
    // Define left wing coordinates
    int wingLeftCoords[] = { posX - 12, posY + 50, posX - 25, posY + 75, posX - 12, posY + 62 };
    
    // Define right wing coordinates  
    int wingRightCoords[] = { posX + 13, posY + 50, posX + 25, posY + 75, posX + 13, posY + 62 };
    
    // Define thruster/engine coordinates
    int thrusterCoords[] = { posX - 12, posY + 62, posX + 13, posY + 62, posX, posY + 75 };

    // Set fill style and draw all ship components in blue
    setfillstyle(SOLID_FILL, BLUE);
    fillpoly(4, bodyCoords);      // Draw main body (4 points)
    fillpoly(3, wingLeftCoords);  // Draw left wing (3 points)
    fillpoly(3, wingRightCoords); // Draw right wing (3 points)
    fillpoly(3, thrusterCoords);  // Draw thruster (3 points)
}

/**
 * Function: moveShip()
 * Purpose: Handle player input and ship movement
 * Processes keyboard input for movement and shooting
 * Updates bullet positions
 */
void moveShip() {
    static bool spaceReleased = true; // Prevents continuous firing when space held down
    
    // Handle left/right movement with boundary checking
/*    if (GetAsyncKeyState(VK_LEFT) && shipPosX > 20) 
        shipPosX -= userSpeed;  // Move left if not at left boundary
    if (GetAsyncKeyState(VK_RIGHT) && shipPosX < SCREEN_WIDTH - 20) 
        shipPosX += userSpeed;  // Move right if not at right boundary
*/
    
    // Alternative movement controls (WASD)
    if (GetAsyncKeyState('Z') && shipPosX > 20) 
        shipPosX -= userSpeed;  // Move left with 'A' key
    if (GetAsyncKeyState('C') && shipPosX < SCREEN_WIDTH - 20) 
        shipPosX += userSpeed;  // Move right with 'D' key

    // Handle shooting with space bar or 'W' key
    if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState('X')) {
        if (spaceReleased) {     // Only fire if key was previously released
            fireBullet();        // Create new bullet
            spaceReleased = false; // Mark key as pressed
        }
    } else {
        spaceReleased = true;    // Mark key as released
    }

    // Update all bullet positions every frame
    updateBullets();
    updateSkyBullets();
}

/**
 * Function: draw_ui()
 * Purpose: Display game UI elements (score and health)
 * Shows current score and remaining health in top-right corner
 */
void draw_ui() {
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 2); // Set font style for UI text

    // Display current score
    char score_text[20];
    sprintf(score_text, "Score: %d", score);
    outtextxy(SCREEN_WIDTH - 150, 20, score_text);

    // Display current health
    char health_text[20];
    sprintf(health_text, "Health: %d", health);
    outtextxy(SCREEN_WIDTH - 150, 50, health_text);
}

/**
 * Function: draw_enemy(Enemy& enemy, int color)
 * Purpose: Render an enemy spaceship with specified color
 * Draws enemy ship pointing downward (opposite of player ship)
 * Parameters: enemy - reference to enemy object, color - fill color
 */
void draw_enemy(Enemy& enemy, int color) {
    setcolor(LIGHTGRAY);
    
    // Define enemy body (triangular, pointing down)
    int body[] = {
        enemy.x - 10, enemy.y - 35,
        enemy.x + 10, enemy.y - 35,
        enemy.x, enemy.y,
        enemy.x - 10, enemy.y - 35
    };
    
    // Define enemy left wing
    int wingLeft[] = {
        enemy.x - 10, enemy.y - 35,
        enemy.x - 25, enemy.y - 25,
        enemy.x - 5, enemy.y - 15
    };
    
    // Define enemy right wing
    int wingRight[] = {
        enemy.x + 10, enemy.y - 35,
        enemy.x + 25, enemy.y - 25,
        enemy.x + 5, enemy.y - 15
    };
    
    // Define enemy thruster (at top, since ship points down)
    int thruster[] = {
        enemy.x - 5, enemy.y - 40,
        enemy.x + 5, enemy.y - 40,
        enemy.x, enemy.y - 50
    };

    // Draw enemy ship components
    setfillstyle(SOLID_FILL, color);
    fillpoly(3, body);      // Main body with specified color
    fillpoly(3, wingLeft);  // Left wing with specified color
    fillpoly(3, wingRight); // Right wing with specified color
    setfillstyle(SOLID_FILL, BLUE);
    fillpoly(3, thruster);  // Thruster always blue
}

/**
 * Function: move_enemy(Enemy& enemy)
 * Purpose: Update enemy position based on movement pattern
 * Handles both horizontal oscillation and vertical descent
 * Parameters: enemy - reference to enemy object to move
 */
void move_enemy(Enemy& enemy) {
    // Handle horizontal movement (side-to-side)
    if (enemy.speedX != 0) {
        if (enemy.moveRight)
            enemy.x += enemy.speedX;  // Move right
        else
            enemy.x -= enemy.speedX;  // Move left

        // Reverse direction when hitting screen boundaries
        if (enemy.x >= SCREEN_WIDTH - 100)
            enemy.moveRight = false;  // Start moving left
        else if (enemy.x <= 50)
            enemy.moveRight = true;   // Start moving right
    }

    // Handle vertical movement (downward)
    if (enemy.speedY != 0) {
        enemy.y += enemy.speedY;     // Move down
        if (enemy.y >= SCREEN_HEIGHT) // If enemy goes off bottom
            enemy.y = 50;            // Reset to top

        // Check for collision with player ship
        check_collision_ship(enemy);
    }
}

/**
 * Function: game_main()
 * Purpose: Main game loop - handles all game logic and rendering
 * This is the core function that runs the entire game
 */
void game_main() {
    // Initialize game state variables
    bool game_running = true;
    isGameOver = false;
    health = 3;              // Reset player health
    score = 0;               // Reset score
    current_user.score = 0;  // Reset user score

    // Initialize graphics and game setup
    cleardevice();
    srand(time(0));          // Seed random number generator
    background_image();      // Draw background

    // Initialize enemy positions and movement patterns
    for (int i = 0; i < 5; i++) {
        enemies[i].x = rand() % (SCREEN_WIDTH - 100) + 50;  // Random X position
        enemies[i].y = rand() % 200 + 50;                   // Random Y position in upper area
        enemies[i].speedX = (i < 3) ? ENEMY_SPEED : 0;      // First 3 enemies move horizontally
        enemies[i].speedY = (i >= 3) ? ENEMY_SPEED : 0;     // Last 2 enemies move vertically
        enemies[i].moveRight = (rand() % 2 == 0);           // Random initial direction
    }

    initBullets();           // Initialize bullet arrays
    int page = 0;            // For double buffering (smooth animation)

    // Main game loop
    while (game_running) {
        // Double buffering setup for smooth animation
        setactivepage(page);        // Set page to draw on
        setvisualpage(1 - page);    // Set page to display
        cleardevice();              // Clear the drawing page

        if (!isGameOver) {
            // Draw game elements
            draw_ui();              // Display score and health
            drawSkyBullets();       // Draw background effect bullets

            // Process sky bullet collisions
            for (int i = 0; i < MAX_SKY_BULLETS; i++) {
                check_sky_bullets(skyBullets[i]);
            }

            // Handle player bullet collisions with enemies
            user_bullets_fire(bullets, enemies, current_user);
            
            score = current_user.score;  // Update local score variable
            
            // Increase score over time
            score_increase(current_user);

            // Draw and move all enemies
            for (int i = 0; i < 5; i++) {
                // Color coding: first 3 enemies green, last 2 red
                draw_enemy(enemies[i], (i < 3) ? GREEN : RED);
                move_enemy(enemies[i]);
            }

            // Handle player ship
            moveShip();                    // Process input and movement
            drawShip(shipPosX, shipPosY);  // Draw ship at current position
            drawBullets();                 // Draw player bullets

        } else {
            game_running = false;  // Exit loop if game over
        }
 
        delay(40);           // Control frame rate (25 FPS)
        page = 1 - page;     // Switch buffer pages
    }

    // Game cleanup and final score handling
    cleardevice();
    setvisualpage(page);
    
    // Update high score if needed and save user data
    if (current_user.score > current_user.high_score) {
        current_user.high_score = current_user.score;
        check_score(current_user);
  // Save with new high score
    } else {
       check_score(current_user);
 // Save current session data
    }
    
    // Display game over screen and cleanup
    game_over();             // Show final scores
    delay(1500);            // Wait 1.5 seconds
    cleardevice();          // Clear screen
    closegraph();           // Close current graphics window
    
    // Restart graphics system and return to main menu
    initwindow(MAX_WIDTH, MAX_HEIGHT, "War Space Game");
    user_interference();    // Return to main menu
}
