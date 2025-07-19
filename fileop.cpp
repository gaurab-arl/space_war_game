// Include necessary header files for file operations and string manipulation
#include "fileop.h"
#include <cstdio>
#include <cstring>

// Global arrays and variables for user management
HistoryUser all_users[100];  // Array to store all users from history file (max 100 users)
int total_users = 0;         // Counter for total number of users loaded from file


void check_score(const User& current_user) {
    // Open history file for reading to load existing user data
    FILE* fp = fopen("histo-ry.txt", "r");
    total_users = 0;           // Reset user counter
    bool user_found = false;   // Flag to track if current user exists in history
    


    // Load all existing users from file if it exists
    if (fp != NULL) {
        // Read each line containing username and score until end of file
        while (fscanf(fp, "%s %d", all_users[total_users].name, &all_users[total_users].score) != EOF) {
            total_users++;  // Increment counter for each user loaded
        }
        fclose(fp);  // Close file after reading
    }
    
    // Search through loaded users to find if current user already exists
    for (int i = 0; i < total_users; i++) {
        if (strcmp(all_users[i].name, current_user.name) == 0) {  // User found
            user_found = true;
            // Update score only if current score is higher (new high score)
            if (current_user.score > all_users[i].score) {
                all_users[i].score = current_user.score;
            }
            break;  // Exit loop once user is found and processed
        }
    }
    
    // If user doesn't exist in history, add them as new entry
    if (!user_found) {
        strcpy(all_users[total_users].name, current_user.name);  // Copy username
        all_users[total_users].score = current_user.score;       // Set score
        total_users++;  // Increment total user count
    }
    
    // Save the updated user list back to file
    fp = fopen("history.txt", "w");  // Open in write mode (overwrites existing file)
    for (int i = 0; i < total_users; i++) {
        fprintf(fp, "%s %d\n", all_users[i].name, all_users[i].score);  // Write each user
    }
    fclose(fp);  // Close file after writing
}

/**
 * Purpose: Save user information to the history file
 * This function is the main interface for saving user data
 */
void save_user_info(const User& current_user) {
    // First check and update the user's score in history
    // check_score(current_user);
    
    // Open history file in append mode
    FILE* fp = fopen("history.txt", "a");
    if (fp == NULL) {
        cout << "Error opening file!" << endl;  // Error handling for file opening failure
        return;
    }
    
    // Append user info to file (this may create duplicates due to check_score already saving)
    fprintf(fp, "%s %d\n", current_user.name, current_user.score);
    fclose(fp);  // Close file after writing
}

/**
 * Function: load_users_from_file()
 * Purpose: Load all user data from history.txt into memory
 * Populates the global all_users array with data from the history file
 * Used for displaying leaderboards and finding existing users
 */
void load_users_from_file() {
    // Open history file for reading
    FILE* fp = fopen("history.txt", "r");
    if (fp == NULL) {
        cout << "No history yet!" << endl;  // Message when no history file exists
        return;
    }
    
    total_users = 0;  // Reset user counter
    
    // Read all users from file into memory
    while (fscanf(fp, "%s %d", all_users[total_users].name, &all_users[total_users].score) != EOF) {
        total_users++;  // Increment counter for each user loaded
    }
    
    fclose(fp);  // Close file after reading
}

/**
 * Function: sort_users_by_score()
 * Purpose: Sort the loaded users by score in descending order (highest first)
 * Uses bubble sort algorithm to arrange users for leaderboard display
 * Should be called after load_users_from_file() to sort the data
 */
void sort_users_by_score() {
    // Bubble sort implementation - O(n²) time complexity
    for (int i = 0; i < total_users - 1; i++) {
        for (int j = i + 1; j < total_users; j++) {
            // Swap if current user has lower score than next user
            if (all_users[i].score < all_users[j].score) {
                HistoryUser temp = all_users[i];  // Temporary storage for swap
                all_users[i] = all_users[j];      // Move higher score to earlier position
                all_users[j] = temp;              // Complete the swap
            }
        }
    }
}

/**
 * Function: save_current_user()
 * Purpose: Save the current active user to a separate quick-access file
 * Creates a dedicated file for the currently playing user for faster loading
 * Stores name, current session score, and all-time high score
 */
void save_current_user() {
    // Open dedicated current user file for writing
    FILE* fp = fopen("current_user.txt", "w");
    if (fp == NULL) {
        return;  // Silent failure if file can't be opened
    }
    
    // Save current user's complete information
    fprintf(fp, "%s %d %d\n", current_user.name, current_user.score, current_user.high_score);
    fclose(fp);  // Close file after writing
}

/**
 * Function: load_current_user(const char* username)
 * Purpose: Load user data for a specific username, with fallback mechanisms
 * This function implements a multi-tier loading system:
 * 1. Try to load from quick-access current_user.txt
 * 2. Fall back to searching history.txt
 * 3. Create new user if not found anywhere
 * Parameters: username - name of the user to load
 */
void load_current_user(const char* username) {
    // TIER 1: Try to load from current_user.txt (fastest access)
    FILE* fp = fopen("current_user.txt", "r");
    if (fp != NULL) {
        // Read user data from current user file
        if (fscanf(fp, "%s %d %d", current_user.name, &current_user.score, &current_user.high_score) != EOF) {
            fclose(fp);
            // If the loaded user matches our target username, we're done
            if (strcmp(current_user.name, username) == 0) {
                return;  // Successfully loaded matching user
            }
        } else {
            fclose(fp);  // Close file if read failed
        }
    }
    
    // TIER 2: If current_user.txt doesn't exist or has different user,
    // search in the main history file
    load_users_from_file();  // Load all users from history
    
    for (int i = 0; i < total_users; i++) {
        if (strcmp(all_users[i].name, username) == 0) {  // User found in history
            strcpy(current_user.name, username);              // Set username
            current_user.score = 0;                           // Reset current session score
            current_user.high_score = all_users[i].score;     // Set high score from history
            return;  // Successfully loaded user from history
        }
    }
    
    // TIER 3: If user not found anywhere, create new user
    strcpy(current_user.name, username);  // Set the username
    current_user.score = 0;               // Initialize current score to 0
    current_user.high_score = 0;          // Initialize high score to 0
}