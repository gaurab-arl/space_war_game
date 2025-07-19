#include "fileop.h"
#include "collision.h"
#include "gameui.h"
#include "userui.h"
#include <windows.h>

extern int health;
extern int score;
extern bool isGameOver; 

void user_bullets_fire(Bullet bullets[], Enemy enemies[], User &current_user)
{
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) 
            continue;

        for (int j = 0; j < 5; j++) {
            // Skip inactive enemies
            if (enemies[j].speedX == 0 && enemies[j].speedY == 0) 
                continue;

            // Check collision
            if (bullets[i].y >= enemies[j].y - 35 && bullets[i].y <= enemies[j].y &&
    bullets[i].x >= enemies[j].x - (35 - (bullets[i].y - (enemies[j].y - 35))) &&
    bullets[i].x <= enemies[j].x + (35 - (bullets[i].y - (enemies[j].y - 35))))
{
                  ////sound during collision
                Beep(850, 200);
                bullets[i].active = false;

                //Corrected: Reset the specific enemy that was hit
                enemies[j].x = rand() % (SCREEN_WIDTH - 100) + 50;
                enemies[j].y = 0;

                // Increase score
                current_user.score += 10;

                // Update global score
                extern int score;
                score = current_user.score;
            }
        }
    }
}

void check_sky_bullets(Bullet &bullet)
{
    extern int shipPosX, shipPosY;

    if (bullet.x >= shipPosX - 20 && bullet.x <= shipPosX + 20 &&
        bullet.y >= shipPosY - 20 && bullet.y <= shipPosY + 20)
    {
        Beep(600, 200);
        health--;
        health_dead();
        
    }
}

void health_dead()
{
    if (health <= 0)
    {
        isGameOver = true; // ✅ Also set game over here
        game_over();
    }
}


void check_collision_ship(Enemy &enemy)
{
    // Check if enemy reached bottom of screen
    if (enemy.y >= 690)
    {
        Beep(2000, 200);
        isGameOver = true; // Set game over
        game_over();
        return;
    }
    
    // Check actual collision with player ship
    extern int shipPosX, shipPosY;
    
    // Use hitbox collision - enemies usually have larger hitboxes than bullets
    if (abs(enemy.x - shipPosX) < 25 && 
        abs(enemy.y - shipPosY) < 25)
    {
        Beep(2000, 200);
        health--;
        health_dead();
        
        // Reset enemy position after collision
        enemy.y = 50;
        enemy.x = rand() % (SCREEN_WIDTH - 100) + 50;
    }
}


/* 3. UPDATE TO score_increase() IN collision.cpp */

void score_increase(User &current_user)
{
    extern int ENEMY_SPEED;
    static int lastSpeedIncreaseScore = 0;
    
    // Increase speed every 100 points (100, 200, 300, etc.)
    if (current_user.score >= lastSpeedIncreaseScore + 100)
    {
        ENEMY_SPEED += 2;
        lastSpeedIncreaseScore = current_user.score;
        
        // Also increase the speed of sky bullets
        extern Bullet skyBullets[];
        
        // Notify player of increased difficulty
        char msg[100];
        sprintf(msg, "Level up! Speed increased!");
        setcolor(YELLOW);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
        outtextxy(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2, msg);
    }
}


