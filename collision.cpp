#include "fileop.h"
#include "collision.h"
#include "gameui.h"
#include "userui.h"
#include <windows.h>

extern int health;
extern int score;
extern bool isGameOver;
extern int shipPosX, shipPosY;
extern Bullet skyBullets[];
extern int ENEMY_SPEED;

void user_bullets_fire(Bullet bullets[], Enemy enemies[], User &current_user) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j < 5; j++) {
            if (enemies[j].speedX == 0 && enemies[j].speedY == 0) continue;

            bool hit = (bullets[i].y >= enemies[j].y - 35 && bullets[i].y <= enemies[j].y) &&
                       (bullets[i].x >= enemies[j].x - (35 - (bullets[i].y - (enemies[j].y - 35)))) &&
                       (bullets[i].x <= enemies[j].x + (35 - (bullets[i].y - (enemies[j].y - 35))));

            if (hit) {
                Beep(850, 200);  // Hit sound
                bullets[i].active = false;

                // Reset enemy position
                enemies[j].x = rand() % (SCREEN_WIDTH - 100) + 50;
                enemies[j].y = 0;

                // Update scores
                current_user.score += 10;
                score = current_user.score;
            }
        }
    }
}

void check_sky_bullets(Bullet &bullet) {
    if (bullet.x >= shipPosX - 20 && bullet.x <= shipPosX + 20 &&
        bullet.y >= shipPosY - 20 && bullet.y <= shipPosY + 20) {
        Beep(600, 200);
        health--;
        health_dead();
    }
}

void health_dead() {
    if (health <= 0) {
        isGameOver = true;
        game_over();
    }
}

void check_collision_ship(Enemy &enemy) {
    // Enemy reached bottom of screen
    if (enemy.y >= 690) {
        Beep(2000, 200);
        isGameOver = true;
        game_over();
        return;
    }

    // Check collision with ship
    if (abs(enemy.x - shipPosX) < 25 && abs(enemy.y - shipPosY) < 25) {
        Beep(2000, 200);
        health--;
        health_dead();

        // Reset enemy after hit
        enemy.y = 50;
        enemy.x = rand() % (SCREEN_WIDTH - 100) + 50;
    }
}

void score_increase(User &current_user) {
    static int lastSpeedIncreaseScore = 0;

    if (current_user.score >= lastSpeedIncreaseScore + 100) {
        ENEMY_SPEED += 2;
        lastSpeedIncreaseScore = current_user.score;

        char msg[100];
        sprintf(msg, "Level up! Speed increased!");


        // Optional: Draw box behind message
        setfillstyle(SOLID_FILL, BLACK);
        bar(SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2 - 20, SCREEN_WIDTH / 2 + 160, SCREEN_HEIGHT / 2 + 30);

        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
        setcolor(YELLOW);
        outtextxy(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, msg);

        delay(1000); // <-- This line makes the message visible!
    }
}

