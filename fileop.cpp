#include "fileop.h"
#include <cstdio>
#include <cstring>

HistoryUser all_users[100];
int total_users = 0;

User current_user;


void check_score(const User& current_user) {
    FILE* fp = fopen("history.txt", "r");
    total_users = 0;
    bool user_found = false;

    if (fp != NULL) {
        while (fscanf(fp, "%s %d", all_users[total_users].name, &all_users[total_users].score) != EOF) {
            total_users++;
        }
        fclose(fp);
    }

    for (int i = 0; i < total_users; i++) {
        if (strcmp(all_users[i].name, current_user.name) == 0) {
            user_found = true;
            if (current_user.score > all_users[i].score) {
                all_users[i].score = current_user.score;
            }
            break;
        }
    }

    if (!user_found && total_users < 100) {
        strcpy(all_users[total_users].name, current_user.name);
        all_users[total_users].score = current_user.score;
        total_users++;
    }

    fp = fopen("history.txt", "w");
    for (int i = 0; i < total_users; i++) {
        fprintf(fp, "%s %d\n", all_users[i].name, all_users[i].score);
    }
    fclose(fp);
}

void load_users_from_file() {
    FILE* fp = fopen("history.txt", "r");
    if (fp == NULL) {
        total_users = 0;
        return;
    }

    total_users = 0;
    while (fscanf(fp, "%s %d", all_users[total_users].name, &all_users[total_users].score) != EOF) {
        total_users++;
    }
    fclose(fp);
}

void sort_users_by_score() {
    for (int i = 0; i < total_users - 1; i++) {
        for (int j = i + 1; j < total_users; j++) {
            if (all_users[i].score < all_users[j].score) {
                HistoryUser temp = all_users[i];
                all_users[i] = all_users[j];
                all_users[j] = temp;
            }
        }
    }
}

void save_current_user() {
    FILE* fp = fopen("current_user.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%s %d %d\n", current_user.name, current_user.score, current_user.high_score);
        fclose(fp);
    }
}

void load_current_user(const char* username) {
    FILE* fp = fopen("current_user.txt", "r");
    if (fp != NULL) {
        if (fscanf(fp, "%s %d %d", current_user.name, &current_user.score, &current_user.high_score) != EOF) {
            fclose(fp);
            if (strcmp(current_user.name, username) == 0) return;
        } else {
            fclose(fp);
        }
    }

    load_users_from_file();
    for (int i = 0; i < total_users; i++) {
        if (strcmp(all_users[i].name, username) == 0) {
            strcpy(current_user.name, username);
            current_user.score = 0;
            current_user.high_score = all_users[i].score;
            return;
        }
    }

    strcpy(current_user.name, username);
    current_user.score = 0;
    current_user.high_score = 0;
}
