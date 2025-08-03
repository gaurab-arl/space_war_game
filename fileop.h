#ifndef FILEOP_H
#define FILEOP_H

#include "userui.h"
#include "gameui.h"
#include "fileop.h"
#include "collision.h" // defines the User struct

#include <iostream>
using namespace std;

struct HistoryUser {
    char name[100];
    int score;
};

extern User current_user;

extern HistoryUser all_users[100];  // list of all past users
extern int total_users;


void save_current_user();
void load_current_user(const char* username);
void check_score(const User& current_user);
void load_users_from_file();
void sort_users_by_score();

#endif // FILEOP_H
