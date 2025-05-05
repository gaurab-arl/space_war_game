#include "userui.h"
#include "gameui.h"
#include "fileop.h"
#include "collision.h"

int x = 0, y = 0;
User current_user;

void background_image() {
   readimagefile("deep_space_background.bmp", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void give_coordinate() {
    while (!kbhit()) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d \t %d \n", x, y);
        }
    }
}

void title() {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(150, 60, 1020, 130);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 7);
    outtextxy(150, 60, " SPACE WAR GAME ");
}

void give_name() {
    int i = 0;
    char ch;
    char display_name[21] = "";

    background_image();
    title();

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

    while (1) {
        ch = getch();
        if (ch == '\r') {
            if (i >= 6 && i <= 8) {
                break;
            } else {
                setcolor(RED);
                settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
                outtextxy(336, 330, "Name must be 6-8 characters!");
                delay(1500);
                setfillstyle(SOLID_FILL, BLACK);
                bar(336, 330, 825, 355);
                settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
                setcolor(WHITE);
                outtextxy(305, 340, "  Name should be at least 6 to 8 letters ");
            }
        } else if (ch == '\b' && i > 0) {
            i--;
            display_name[i] = '\0';
        } else if (i < 8 && ch >= 32 && ch <= 126) {
            display_name[i++] = ch;
            display_name[i] = '\0';
        }
        setfillstyle(SOLID_FILL, BLACK);
        bar(337, 257, 824, 304);
        setcolor(WHITE);
        outtextxy(354, 264, display_name);
    }

    strcpy(current_user.name, display_name);
    cleardevice();
}

void back_button() {
    setcolor(WHITE);
    rectangle(40, 30, 140, 70);
    setfillstyle(SOLID_FILL, BLACK);
    bar(41, 31, 139, 69);
    setcolor(LIGHTGRAY);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(60, 40, "Back");
}

bool component_click(int mx, int my) {
    // "Start" button at (530, 330)
    if (mx >= 520 && mx <= 610 && my >= 330 && my <= 370) {
        cleardevice();
        game_main();
        return true;
    }
    // "History" button at (520, 430)
    if (mx >= 510 && mx <= 630 && my >= 430 && my <= 470) {
        cleardevice();
        history_interference();
        return true;
    }
    // "Exit" button at (540, 530)
    if (mx >= 530 && mx <= 610 && my >= 530 && my <= 570) {
        closegraph();
        exit(0);
    }
    // Back button
    if (mx >= 40 && mx <= 140 && my >= 30 && my <= 70) {
        cleardevice();
        user_interference();
        return true;
    }
    return false;
}

void history_interference() {
    background_image();
    title();
    back_button();

    // Expanded outer panel
    setcolor(WHITE);
    rectangle(327, 151, 838, 645); // Increased height
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(328, 152, 837, 644);

    // Expanded inner panel
    rectangle(343, 165, 823, 627);
    setfillstyle(SOLID_FILL, BLACK);
    bar(344, 166, 822, 626);

    // Title
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    outtextxy(470, 180, "Game History");

    // Load and sort users
    load_users_from_file();
    sort_users_by_score();

    // Display top 8 users
    int start_y = 240;  // Start higher to fit all 8
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (int i = 0; i < total_users && i < 8; i++) {
        if (i == 0) setcolor(YELLOW);
        else if (i == 1) setcolor(LIGHTGRAY);
        else if (i == 2) setcolor(BROWN);
        else setcolor(WHITE);

        char display[200];
        sprintf(display, "%d. %s - %d", i + 1, all_users[i].name, all_users[i].score);
        outtextxy(370, start_y, display);
        start_y += 42;  // Slightly tighter spacing to fit 8 rows

        // Line separator
        setcolor(LIGHTGRAY);
        line(350, start_y - 10, 815, start_y - 10);
    }

    // Wait for click
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            clearmouseclick(WM_LBUTTONDOWN);
            if (component_click(x, y))
                break;
        }
        delay(100);
    }
}



void user_interference() {
    background_image();
    title();

    setcolor(WHITE);
    rectangle(327, 181, 838, 605);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(328, 182, 837, 604);

    rectangle(343, 195, 823, 587);
    setfillstyle(SOLID_FILL, BLACK);
    bar(344, 196, 822, 586);

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(500, 230, current_user.name);

    line(343, 290, 823, 290);
    outtextxy(530, 330, "Start");

    line(343, 390, 823, 390);
    outtextxy(520, 430, "History");

    line(343, 490, 823, 490);
    outtextxy(540, 530, "Exit");

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            clearmouseclick(WM_LBUTTONDOWN); // Clear extra clicks
            if (component_click(x, y))
                break;
        }
        delay(100);
    }
}

