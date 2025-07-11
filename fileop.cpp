#include "fileop.h"
#include <cstdio>
#include <cstring>

HistoryUser all_users[100];
int total_users = 0;

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

    // Check if user already exists and update score if better
    for (int i = 0; i < total_users; i++) {
        if (strcmp(all_users[i].name, current_user.name) == 0) {
            user_found = true;
            if (current_user.score > all_users[i].score) {
                all_users[i].score = current_user.score;
            }
            break;
        }
    }

    // If new user, add to list
    if (!user_found) {
        strcpy(all_users[total_users].name, current_user.name);
        all_users[total_users].score = current_user.score;
        total_users++;
    }

    // Save updated list
    fp = fopen("history.txt", "w");
    for (int i = 0; i < total_users; i++) {
        fprintf(fp, "%s %d\n", all_users[i].name, all_users[i].score);
    }
    fclose(fp);
}

void save_user_info(const User& current_user) {
	 check_score(current_user);
    FILE* fp = fopen("history.txt", "a");
    if (fp == NULL) {
        cout << "Error opening file!" << endl;
        return;
    }
    fprintf(fp, "%s %d\n", current_user.name, current_user.score);
    fclose(fp);
}

void load_users_from_file() {
    FILE* fp = fopen("history.txt", "r");
    if (fp == NULL) {
        cout << "No history yet!" << endl;
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
    // Save the current user to a separate file for quick access
    FILE* fp = fopen("current_user.txt", "w");
    if (fp == NULL) {
        return;
    }
    
    fprintf(fp, "%s %d %d\n", current_user.name, current_user.score, current_user.high_score);
    fclose(fp);
}

void load_current_user(const char* username) {
    // First try to load from current_user.txt
    FILE* fp = fopen("current_user.txt", "r");
    if (fp != NULL) {
        if (fscanf(fp, "%s %d %d", current_user.name, &current_user.score, &current_user.high_score) != EOF) {
            fclose(fp);
            // If the loaded user matches our username, we're done
            if (strcmp(current_user.name, username) == 0) {
                return;
            }
        }
        fclose(fp);
    }
    
    // If we reach here, either the file doesn't exist or it's a different user
    // Try to find user in history.txt
    load_users_from_file();
    for (int i = 0; i < total_users; i++) {
        if (strcmp(all_users[i].name, username) == 0) {
            strcpy(current_user.name, username);
            current_user.score = 0; // Reset current score
            current_user.high_score = all_users[i].score;
            return;
        }
    }
    
    // If user not found in history either, it's a new user
    strcpy(current_user.name, username);
    current_user.score = 0;
    current_user.high_score = 0;
}

