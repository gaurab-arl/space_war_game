#include <iostream>
#include <graphics.h>
#include <stdio.h>   // for sprintf

using namespace std;

struct gameover {
	int score = 350;  // you can change this value to your real score
	int highest_score = 1000;
} user;

void game_over();

int main()
{
    initwindow(1000, 700, "Game Over Screen");
    game_over();
	getch();
	closegraph();
	return 0;
}

void game_over()
{ 
   char user_game_score[100];
   char user_game_highest[100];
   
   sprintf(user_game_score, "Your Score : %d", user.score);
   sprintf(user_game_highest, "Highest Score : %d", user.highest_score);

   //cleardevice();

   // Draw box
   setcolor(WHITE);
   rectangle(250 , 200 , 850 , 500);

   // Draw "GAME OVER"
   setcolor(YELLOW);
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);  // Big nice font
   outtextxy(300 , 250 , "GAME OVER");

   // Show user's score
   setcolor(RED);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);  // Smaller font for score
   outtextxy(320 , 350 , user_game_score);
   outtextxy(320 , 400 , user_game_highest);
}
