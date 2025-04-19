#include "gameui.h"

Enemy enemies[5];
// Removed: int bullets_random[5][2];
int rewards[5][2];

int shipPosX = SCREEN_WIDTH / 2;
int shipPosY = SCREEN_HEIGHT - 100;
int score = 0;
int health = 3;
int rewardCount = 0;
int bullet_pos_x, bullet_pos_y;
int reward_pos_x, reward_pos_y;

Bullet_user bullets[MAX_BULLETS];
Bullet_enemy skyBullets[MAX_SKY_BULLETS];

void draw_ui() {
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 2);

    char score_text[20];
    sprintf(score_text, "Score: %d", score);
    outtextxy(SCREEN_WIDTH - 150, 20, score_text);

    char health_text[20];
    sprintf(health_text, "Health: %d", health);
    outtextxy(SCREEN_WIDTH - 150, 50, health_text);

    char reward_text[20];
    sprintf(reward_text, "Rewards: %d", rewardCount);
    outtextxy(SCREEN_WIDTH - 150, 80, reward_text);
}

void drawShip(int posX, int posY) {
    int bodyCoords[] = { posX, posY, posX - 12, posY + 50, posX + 13, posY + 50, posX, posY };
    int wingLeftCoords[] = { posX - 12, posY + 50, posX - 25, posY + 75, posX - 12, posY + 62 };
    int wingRightCoords[] = { posX + 13, posY + 50, posX + 25, posY + 75, posX + 13, posY + 62 };
    int thrusterCoords[] = { posX - 12, posY + 62, posX + 13, posY + 62, posX, posY + 75 };

    setfillstyle(SOLID_FILL, BLUE);
    fillpoly(4, bodyCoords);
    fillpoly(3, wingLeftCoords);
    fillpoly(3, wingRightCoords);
    fillpoly(3, thrusterCoords);
}

void draw_enemy(Enemy &enemy, int color) {
    if (!enemy.active) return;

    setcolor(LIGHTGRAY);

    int body[] = { enemy.x - 10, enemy.y - 35, enemy.x + 10, enemy.y - 35, enemy.x, enemy.y };
    int wingLeft[] = { enemy.x - 10, enemy.y - 35, enemy.x - 25, enemy.y - 25, enemy.x - 5, enemy.y - 15 };
    int wingRight[] = { enemy.x + 10, enemy.y - 35, enemy.x + 25, enemy.y - 25, enemy.x + 5, enemy.y - 15 };
    int thruster[] = { enemy.x - 5, enemy.y - 40, enemy.x + 5, enemy.y - 40, enemy.x, enemy.y - 50 };

    setfillstyle(SOLID_FILL, color);
    fillpoly(3, body);
    fillpoly(3, wingLeft);
    fillpoly(3, wingRight);
    setfillstyle(SOLID_FILL, BLUE);
    fillpoly(3, thruster);
}

void move_enemy(Enemy &enemy) {
    if (!enemy.active) return;

    if (enemy.moveHorizontally) {
        if (enemy.moveRight) enemy.x += enemy.speedX;
        else enemy.x -= enemy.speedX;
        if (enemy.x >= SCREEN_WIDTH - 100) enemy.moveRight = false;
        else if (enemy.x <= 50) enemy.moveRight = true;
    } else {
        enemy.y += enemy.speedY;
        if (enemy.y >= SCREEN_HEIGHT) {
            enemy.y = rand() % 200 + 50;
            enemy.x = rand() % (SCREEN_WIDTH - 100) + 50;
            health--;
        }
    }

    // Enemy bullet
    if (rand() % 20 == 0) {
        for (int i = 0; i < MAX_SKY_BULLETS; i++) {
            if (!skyBullets[i].active) {
                skyBullets[i].x = enemy.x;
                skyBullets[i].y = enemy.y;
                skyBullets[i].active = true;
                break;
            }
        }
    }
}

void fireBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].x = shipPosX;
            bullets[i].y = shipPosY;
            bullets[i].active = true;
            break;
        }
    }
}

void updateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= USER_BULLET_SPEED;
            if (bullets[i].y < 0) bullets[i].active = false;
        }
    }
}

void updateSkyBullets() {
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            skyBullets[i].y += SKY_BULLET_SPEED;
            if (skyBullets[i].y > SCREEN_HEIGHT) {
                skyBullets[i].x = rand() % SCREEN_WIDTH;
                skyBullets[i].y = 0;
                skyBullets[i].active = true;
            }
        }
    }
}

void drawBullets() {
    setfillstyle(SOLID_FILL, YELLOW);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            setcolor(YELLOW);
            circle(bullets[i].x, bullets[i].y, 3);
            floodfill(bullets[i].x, bullets[i].y, YELLOW);
        }
    }
}

void drawSkyBullets() {
    setfillstyle(SOLID_FILL, RED);
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            setcolor(WHITE);
            circle(skyBullets[i].x, skyBullets[i].y, 5);
            floodfill(skyBullets[i].x, skyBullets[i].y, WHITE);
        }
    }
}

// Removed spawn_bullets()

void moveShip() {
    static bool spaceReleased = true;

    if (GetAsyncKeyState(VK_LEFT) && shipPosX > 20) {
        shipPosX -= USER_SPEED;
    }
    if (GetAsyncKeyState(VK_RIGHT) && shipPosX < SCREEN_WIDTH - 20) {
        shipPosX += USER_SPEED;
    }

    if (GetAsyncKeyState(VK_SPACE)) {
        if (spaceReleased) {
            fireBullet();
            spaceReleased = false;
        }
    } else {
        spaceReleased = true;
    }

    updateBullets();
    updateSkyBullets();
    drawShip(shipPosX, shipPosY);
    drawBullets();
    drawSkyBullets();
}

void draw_reward() {
    for (int i = 0; i < 5; i++) {
        int x = rewards[i][0];
        int y = rewards[i][1];

        if (y > SCREEN_HEIGHT) {
            x = rand() % (SCREEN_WIDTH - 40) + 20;
            y = rand() % 200;
            rewards[i][0] = x;
            rewards[i][1] = y;
        }

        setcolor(COLOR(255, 215, 0));
        setfillstyle(SOLID_FILL, COLOR(255, 223, 0));
        fillellipse(x, y, 8, 8);
        setcolor(BLACK);
        outtextxy(x - 4, y - 4, "$");

        rewards[i][1] += 2;

        // Collision with ship
        if (y > shipPosY - 20 &&
            x > shipPosX - 20 &&
            x < shipPosX + 20) {
            rewardCount++;
            rewards[i][1] = SCREEN_HEIGHT + 1;
        }
    }
}

void checkCollisions() {
    // User bullets with enemies
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            for (int j = 0; j < 5; j++) {
                if (!enemies[j].active) continue;

                int dx = bullets[i].x - enemies[j].x;
                int dy = bullets[i].y - enemies[j].y;
                if (abs(dx) < 20 && abs(dy) < 20) {
                    score += 10;
                    enemies[j].x = rand() % (SCREEN_WIDTH - 100) + 50;
                    enemies[j].y = rand() % 200 + 50;
                    bullets[i].active = false;
                    break;
                }
            }
        }
    }

    // Sky bullets with ship
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            int dx = skyBullets[i].x - shipPosX;
            int dy = skyBullets[i].y - shipPosY;
            if (abs(dx) < 20 && abs(dy) < 20) {
                health--;
                skyBullets[i].active = false;
                skyBullets[i].y = 0;
                skyBullets[i].x = rand() % SCREEN_WIDTH;
            }
        }
    }

    // Removed: random bullets with ship

    // User bullets with rewards
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < MAX_BULLETS; j++) {
            if (bullets[j].active) {
                int dx = bullets[j].x - rewards[i][0];
                int dy = bullets[j].y - rewards[i][1];
                if (abs(dx) < 20 && abs(dy) < 20) {
                    rewardCount++;
                    rewards[i][0] = rand() % (SCREEN_WIDTH - 50);
                    rewards[i][1] = rand() % (SCREEN_HEIGHT - 100);
                    bullets[j].active = false;
                }
            }
        }
    }
}

void initBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }

    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        skyBullets[i].x = rand() % SCREEN_WIDTH;
        skyBullets[i].y = rand() % (SCREEN_HEIGHT / 2);
        skyBullets[i].active = true;
    }
}

void spawn_enemies() {
    for (int i = 0; i < 5; i++) {
        enemies[i].x = rand() % (SCREEN_WIDTH - 100) + 50;
        enemies[i].y = rand() % 200 + 50;
        enemies[i].active = true;
        enemies[i].moveHorizontally = (i < 3);
        enemies[i].speedX = (i < 3) ? ENEMY_SPEED : 0;
        enemies[i].speedY = (i >= 3) ? ENEMY_SPEED : 0;
        enemies[i].moveRight = (rand() % 2 == 0);
    }
}
