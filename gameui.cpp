#include "userui.h"
#include "gameui.h"
#include "fileop.h"
#include "collision.h"

int ENEMY_SPEED = 5;
int userSpeed = 30;
int score = 0;
int health = 3;

Enemy enemies[5];
Bullet bullets[MAX_BULLETS];
Bullet skyBullets[MAX_SKY_BULLETS];

int shipPosX = SCREEN_WIDTH / 2;
int shipPosY = SCREEN_HEIGHT - 100;

bool isGameOver = false;

void game_over()
{
    char user_game_score[100];
    char user_game_highest[100];

    sprintf(user_game_score, "Your Score : %d", current_user.score);
    sprintf(user_game_highest, "Highest Score : %d", current_user.high_score);

    setcolor(WHITE);
    rectangle(250, 200, 850, 500);

    setcolor(YELLOW);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(300, 250,(char*)"GAME OVER");

    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(320, 350, user_game_score);
    outtextxy(320, 400, user_game_highest);
}

void initBullets() {
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = false;
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        skyBullets[i].x = rand() % SCREEN_WIDTH;
        skyBullets[i].y = rand() % (SCREEN_HEIGHT / 2);
        skyBullets[i].active = true;
    }
}

void fireBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].x = shipPosX;
            bullets[i].y = shipPosY;
            bullets[i].active = true;
            Beep(1000, 200);
            break;
        }
    }
}

void updateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= 10;
            if (bullets[i].y < 0)
                bullets[i].active = false;
        }
    }
}

void updateSkyBullets() {
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            skyBullets[i].y += 5;
            if (skyBullets[i].y > SCREEN_HEIGHT) {
                skyBullets[i].x = rand() % SCREEN_WIDTH;
                skyBullets[i].y = 0;
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
    setfillstyle(SOLID_FILL, COLOR(175, 150, 0));
    for (int i = 0; i < MAX_SKY_BULLETS; i++) {
        if (skyBullets[i].active) {
            setcolor(LIGHTBLUE);
            circle(skyBullets[i].x, skyBullets[i].y, 4);
            floodfill(skyBullets[i].x, skyBullets[i].y, LIGHTBLUE);
        }
    }
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

void moveShip() {
    static bool spaceReleased = true;
    if (GetAsyncKeyState(VK_LEFT) && shipPosX > 20) shipPosX -= userSpeed;
    if (GetAsyncKeyState(VK_RIGHT) && shipPosX < SCREEN_WIDTH - 20) shipPosX += userSpeed;

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
}

void draw_ui() {
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 2);

    char score_text[20];
    sprintf(score_text, "Score: %d", score);
    outtextxy(SCREEN_WIDTH - 150, 20, score_text);

    char health_text[20];
    sprintf(health_text, "Health: %d", health);
    outtextxy(SCREEN_WIDTH - 150, 50, health_text);
}

void draw_enemy(Enemy& enemy, int color) {
    setcolor(LIGHTGRAY);
    int body[] = {
        enemy.x - 10, enemy.y - 35,
        enemy.x + 10, enemy.y - 35,
        enemy.x, enemy.y,
        enemy.x - 10, enemy.y - 35
    };
    int wingLeft[] = {
        enemy.x - 10, enemy.y - 35,
        enemy.x - 25, enemy.y - 25,
        enemy.x - 5, enemy.y - 15
    };
    int wingRight[] = {
        enemy.x + 10, enemy.y - 35,
        enemy.x + 25, enemy.y - 25,
        enemy.x + 5, enemy.y - 15
    };
    int thruster[] = {
        enemy.x - 5, enemy.y - 40,
        enemy.x + 5, enemy.y - 40,
        enemy.x, enemy.y - 50
    };

    setfillstyle(SOLID_FILL, color);
    fillpoly(3, body);
    fillpoly(3, wingLeft);
    fillpoly(3, wingRight);
    setfillstyle(SOLID_FILL, BLUE);
    fillpoly(3, thruster);
}

void move_enemy(Enemy& enemy) {
    if (enemy.speedX != 0) {
        if (enemy.moveRight)
            enemy.x += enemy.speedX;
        else
            enemy.x -= enemy.speedX;

        if (enemy.x >= SCREEN_WIDTH - 100)
            enemy.moveRight = false;
        else if (enemy.x <= 50)
            enemy.moveRight = true;
    }

    if (enemy.speedY != 0) {
        enemy.y += enemy.speedY;
        if (enemy.y >= SCREEN_HEIGHT) enemy.y = 50;

        check_collision_ship(enemy);
    }
}

void game_main() {
    bool game_running = true;
    isGameOver = false;
    health = 3;
    score = 0;
    current_user.score = 0;

    cleardevice();
    srand(time(0));
    background_image();

    for (int i = 0; i < 5; i++) {
        enemies[i].x = rand() % (SCREEN_WIDTH - 100) + 50;
        enemies[i].y = rand() % 200 + 50;
        enemies[i].speedX = (i < 3) ? ENEMY_SPEED : 0;
        enemies[i].speedY = (i >= 3) ? ENEMY_SPEED : 0;
        enemies[i].moveRight = (rand() % 2 == 0);
    }

    initBullets();
    int page = 0;

    while (game_running) {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        if (!isGameOver) {
            draw_ui();
            drawSkyBullets();

            for (int i = 0; i < MAX_SKY_BULLETS; i++) {
                check_sky_bullets(skyBullets[i]);
            }

            user_bullets_fire(bullets, enemies, current_user);
            
            score = current_user.score;
            
            score_increase(current_user);

            for (int i = 0; i < 5; i++) {
                draw_enemy(enemies[i], (i < 3) ? GREEN : RED);
                move_enemy(enemies[i]);
            }

            moveShip();
            drawShip(shipPosX, shipPosY);
            drawBullets();

        } else {
            game_running = false;
        }
 
        delay(40);
        page = 1 - page;
    }

    cleardevice();
    setvisualpage(page);
    
    if (current_user.score > current_user.high_score) {
        current_user.high_score = current_user.score;
        save_user_info(current_user);
    } else {
        save_user_info(current_user);
    }
    
    game_over();
    delay(1500);
    cleardevice();       
    closegraph();
    initwindow(MAX_WIDTH, MAX_HEIGHT, "War Space Game");
    user_interference();
}