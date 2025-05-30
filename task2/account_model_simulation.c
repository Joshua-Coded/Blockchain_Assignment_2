#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ANSI color codes for interactive UI
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_RESET "\033[0m"

// Define maximum lengths and constants
#define MAX_NAME_LEN 20
#define MAX_ACCOUNTS 50
#define MAX_LINE_LEN 100

// Account structure
typedef struct {
    char name[MAX_NAME_LEN]; // Account holder's name
    float balance;          // Current balance
} Account;

// Global account list and count
Account account_list[MAX_ACCOUNTS];
int account_count = 0;

// Function to read accounts from file
bool read_accounts_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf(COLOR_RED "Error: Could not open %s\n" COLOR_RESET, filename);
        return false;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) && account_count < MAX_ACCOUNTS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        // Parse name and balance (format: name,balance)
        char *name = strtok(line, ",");
        char *balance_str = strtok(NULL, ",");
        if (name && balance_str) {
            if (strlen(name) < MAX_NAME_LEN) {
                strcpy(account_list[account_count].name, name);
                account_list[account_count].balance = atof(balance_str);
                if (account_list[account_count].balance < 0) {
                    printf(COLOR_RED "Warning: Negative balance for %s ignored\n" COLOR_RESET, name);
                    continue;
                }
                account_count++;
            }
        }
    }
    fclose(file);
    if (account_count < 3) {
        printf(COLOR_RED "Error: At least 3 valid accounts required in %s\n" COLOR_RESET, filename);
        return false;
    }
    return true;
}

// Function to find account index by name
int find_account_index(const char *name) {
    for (int i = 0; i < account_count; i++) {
        if (strcmp(account_list[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to display all accounts
void display_accounts() {
    printf(COLOR_CYAN "\n=== Account Balances ===\n" COLOR_RESET);
    printf("Name            | Balance\n");
    printf("-------------------------\n");
    for (int i = 0; i < account_count; i++) {
        printf("%-15s | %.2f\n", account_list[i].name, account_list[i].balance);
    }
    printf("\n");
}

// Function to transfer funds between accounts
bool transferFunds(const char *sender, const char *receiver, float amount) {
    // Validate inputs
    if (amount <= 0) {
        printf(COLOR_RED "Error: Amount must be positive.\n" COLOR_RESET);
        return false;
    }
    if (strcmp(sender, receiver) == 0) {
        printf(COLOR_RED "Error: Sender and receiver cannot be the same.\n" COLOR_RESET);
        return false;
    }

    // Find sender and receiver indices
    int sender_idx = find_account_index(sender);
    int receiver_idx = find_account_index(receiver);
    if (sender_idx == -1) {
        printf(COLOR_RED "Error: Sender '%s' not found.\n" COLOR_RESET, sender);
        return false;
    }
    if (receiver_idx == -1) {
        printf(COLOR_RED "Error: Receiver '%s' not found.\n" COLOR_RESET, receiver);
        return false;
    }

    // Check sufficient balance
    if (account_list[sender_idx].balance < amount) {
        printf(COLOR_RED "Error: Insufficient balance. %s has %.2f, needs %.2f\n" COLOR_RESET,
               sender, account_list[sender_idx].balance, amount);
        return false;
    }

    // Perform transfer
    account_list[sender_idx].balance -= amount;
    account_list[receiver_idx].balance += amount;

    printf(COLOR_GREEN "\n🎉 Transaction successful! 🎉\n" COLOR_RESET);
    printf("Transferred %.2f from %s to %s\n", amount, sender, receiver);
    return true;
}

// Main function with interactive menu
int main() {
    printf(COLOR_GREEN "=====================================\n" COLOR_RESET);
    printf(COLOR_GREEN "   Account/Balance Transaction Simulator  \n" COLOR_RESET);
    printf(COLOR_GREEN "=====================================\n" COLOR_RESET);

    // Load accounts from file
    if (!read_accounts_from_file("users.txt")) {
        printf(COLOR_RED "Failed to load accounts. Exiting.\n" COLOR_RESET);
        return 1;
    }

    int choice;
    while (true) {
        printf(COLOR_CYAN "\n=== Menu ===\n" COLOR_RESET);
        printf("1. View all account balances\n");
        printf("2. Perform a transaction\n");
        printf("3. Exit\n");
        printf(COLOR_YELLOW "Enter choice (1-3): " COLOR_RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_accounts();
                break;
            case 2: {
                char sender[MAX_NAME_LEN], receiver[MAX_NAME_LEN];
                float amount;

                // Display accounts for selection
                display_accounts();
                printf(COLOR_YELLOW "Enter sender's name: " COLOR_RESET);
                scanf("%s", sender);
                printf(COLOR_YELLOW "Enter receiver's name: " COLOR_RESET);
                scanf("%s", receiver);
                printf(COLOR_YELLOW "Enter amount to transfer: " COLOR_RESET);
                scanf("%f", &amount);

                printf(COLOR_CYAN "\n=== Balances Before Transaction ===\n" COLOR_RESET);
                display_accounts();
                if (transferFunds(sender, receiver, amount)) {
                    printf(COLOR_CYAN "\n=== Balances After Transaction ===\n" COLOR_RESET);
                    display_accounts();
                }
                break;
            }
            case 3:
                printf(COLOR_GREEN "Thank you for using the simulator! Goodbye.\n" COLOR_RESET);
                return 0;
            default:
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    }
    return 0;
}
