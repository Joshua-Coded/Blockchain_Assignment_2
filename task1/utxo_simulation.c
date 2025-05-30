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
#define MAX_ADDRESS_LEN 20
#define MAX_UTXOS 100
#define MAX_TXID_LEN 10
#define MAX_USERS 50
#define MAX_LINE_LEN 100

// UTXO structure
typedef struct {
    char txid[MAX_TXID_LEN]; // Transaction ID
    char address[MAX_ADDRESS_LEN]; // Receiver's address
    float amount; // Transaction amount
    bool spent; // Flag to mark if UTXO is spent
} UTXO;

// User structure
typedef struct {
    char name[MAX_ADDRESS_LEN];
} User;

// Global arrays and counts
UTXO utxo_list[MAX_UTXOS];
int utxo_count = 0;
User user_list[MAX_USERS];
int user_count = 0;

// Function to read users from file
bool read_users_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf(COLOR_RED "Error: Could not open %s\n" COLOR_RESET, filename);
        return false;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) && user_count < MAX_USERS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) > 0 && strlen(line) < MAX_ADDRESS_LEN) {
            strcpy(user_list[user_count].name, line);
            user_count++;
        }
    }
    fclose(file);
    if (user_count == 0) {
        printf(COLOR_RED "Error: No valid users found in %s\n" COLOR_RESET, filename);
        return false;
    }
    return true;
}

// Function to check if a user exists
bool is_valid_user(const char *name) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_list[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

// Function to display all users
void display_users() {
    printf(COLOR_CYAN "\n=== Available Users ===\n" COLOR_RESET);
    for (int i = 0; i < user_count; i++) {
        printf("%d. %s\n", i + 1, user_list[i].name);
    }
    printf("\n");
}

// Function to initialize sample UTXOs
void initialize_utxos() {
    if (user_count < 2) return; // Need at least 2 users
    // Initialize UTXOs for first two users
    snprintf(utxo_list[utxo_count].txid, MAX_TXID_LEN, "TX1");
    strcpy(utxo_list[utxo_count].address, user_list[0].name);
    utxo_list[utxo_count].amount = 50.0;
    utxo_list[utxo_count].spent = false;
    utxo_count++;

    snprintf(utxo_list[utxo_count].txid, MAX_TXID_LEN, "TX2");
    strcpy(utxo_list[utxo_count].address, user_list[0].name);
    utxo_list[utxo_count].amount = 30.0;
    utxo_list[utxo_count].spent = false;
    utxo_count++;

    snprintf(utxo_list[utxo_count].txid, MAX_TXID_LEN, "TX3");
    strcpy(utxo_list[utxo_count].address, user_list[1].name);
    utxo_list[utxo_count].amount = 20.0;
    utxo_list[utxo_count].spent = false;
    utxo_count++;
}

// Function to display all unspent UTXOs
void display_utxos() {
    printf(COLOR_CYAN "\n=== Available UTXOs ===\n" COLOR_RESET);
    printf("Index | TXID | Address | Amount | Spent\n");
    printf("-------------------------------------\n");
    bool has_utxos = false;
    for (int i = 0; i < utxo_count; i++) {
        if (!utxo_list[i].spent) {
            printf("%-5d | %-4s | %-7s | %.2f | %s\n", i, utxo_list[i].txid, utxo_list[i].address, 
                   utxo_list[i].amount, utxo_list[i].spent ? "Yes" : "No");
            has_utxos = true;
        }
    }
    if (!has_utxos) {
        printf(COLOR_RED "No unspent UTXOs available.\n" COLOR_RESET);
    }
    printf("\n");
}

// Function to generate a new unique TXID
void generate_txid(char *txid) {
    static int tx_counter = 4; // Start after initial TX1, TX2, TX3
    snprintf(txid, MAX_TXID_LEN, "TX%d", tx_counter++);
}

// Function to perform a transaction
bool perform_transaction() {
    char sender[MAX_ADDRESS_LEN], receiver[MAX_ADDRESS_LEN];
    float amount;
    int selected_utxos[MAX_UTXOS], selected_count = 0;
    float total_available = 0.0;

    // Display users for selection
    display_users();
    printf(COLOR_YELLOW "Enter sender's name: " COLOR_RESET);
    scanf("%s", sender);
    if (!is_valid_user(sender)) {
        printf(COLOR_RED "Error: Sender '%s' not found.\n" COLOR_RESET, sender);
        return false;
    }
    printf(COLOR_YELLOW "Enter receiver's name: " COLOR_RESET);
    scanf("%s", receiver);
    if (!is_valid_user(receiver)) {
        printf(COLOR_RED "Error: Receiver '%s' not found.\n" COLOR_RESET, receiver);
        return false;
    }
    printf(COLOR_YELLOW "Enter amount to transfer: " COLOR_RESET);
    scanf("%f", &amount);

    // Validate input
    if (amount <= 0) {
        printf(COLOR_RED "Error: Amount must be positive.\n" COLOR_RESET);
        return false;
    }
    if (strcmp(sender, receiver) == 0) {
        printf(COLOR_RED "Error: Sender and receiver cannot be the same.\n" COLOR_RESET);
        return false;
    }

    // Display sender's available UTXOs
    printf(COLOR_CYAN "\n%s's Available UTXOs:\n" COLOR_RESET, sender);
    printf("Index | TXID | Amount\n");
    printf("---------------------\n");
    bool has_utxos = false;
    for (int i = 0; i < utxo_count; i++) {
        if (!utxo_list[i].spent && strcmp(utxo_list[i].address, sender) == 0) {
            printf("%-5d | %-4s | %.2f\n", i, utxo_list[i].txid, utxo_list[i].amount);
            total_available += utxo_list[i].amount;
            has_utxos = true;
        }
    }
    if (!has_utxos) {
        printf(COLOR_RED "Error: No unspent UTXOs for %s.\n" COLOR_RESET, sender);
        return false;
    }
    if (total_available < amount) {
        printf(COLOR_RED "Error: Insufficient funds. Available: %.2f, Required: %.2f\n" COLOR_RESET, total_available, amount);
        return false;
    }

    // Select UTXOs to spend
    printf(COLOR_YELLOW "\nEnter indices of UTXOs to spend (enter -1 to finish):\n" COLOR_RESET);
    float selected_amount = 0.0;
    while (selected_amount < amount) {
        int index;
        printf(COLOR_YELLOW "Enter UTXO index: " COLOR_RESET);
        scanf("%d", &index);
        if (index == -1) break;
        if (index < 0 || index >= utxo_count || utxo_list[index].spent || 
            strcmp(utxo_list[index].address, sender) != 0) {
            printf(COLOR_RED "Error: Invalid or already spent UTXO index.\n" COLOR_RESET);
            continue;
        }
        selected_utxos[selected_count++] = index;
        selected_amount += utxo_list[index].amount;
    }
    if (selected_amount < amount) {
        printf(COLOR_RED "Error: Selected UTXOs (%.2f) do not cover the amount (%.2f).\n" COLOR_RESET, selected_amount, amount);
        return false;
    }

    // Mark selected UTXOs as spent
    for (int i = 0; i < selected_count; i++) {
        utxo_list[selected_utxos[i]].spent = true;
    }

    // Create new UTXO for receiver
    strcpy(utxo_list[utxo_count].address, receiver);
    utxo_list[utxo_count].amount = amount;
    utxo_list[utxo_count].spent = false;
    generate_txid(utxo_list[utxo_count].txid);
    utxo_count++;

    // Create change UTXO for sender if applicable
    float change = selected_amount - amount;
    if (change > 0) {
        strcpy(utxo_list[utxo_count].address, sender);
        utxo_list[utxo_count].amount = change;
        utxo_list[utxo_count].spent = false;
        generate_txid(utxo_list[utxo_count].txid);
        utxo_count++;
    }

    printf(COLOR_GREEN "\n🎉 Transaction successful! 🎉\n" COLOR_RESET);
    printf("Transferred %.2f from %s to %s\n", amount, sender, receiver);
    if (change > 0) {
        printf("Change of %.2f returned to %s\n", change, sender);
    }
    return true;
}

// Main function with interactive menu
int main() {
    printf(COLOR_GREEN "=====================================\n" COLOR_RESET);
    printf(COLOR_GREEN "   UTXO-Based Transaction Simulator  \n" COLOR_RESET);
    printf(COLOR_GREEN "=====================================\n" COLOR_RESET);

    // Load users from file
    if (!read_users_from_file("users.txt")) {
        printf(COLOR_RED "Failed to load users. Exiting.\n" COLOR_RESET);
        return 1;
    }

    initialize_utxos();
    if (utxo_count == 0) {
        printf(COLOR_RED "No initial UTXOs created. Ensure at least 2 users in users.txt.\n" COLOR_RESET);
        return 1;
    }

    int choice;
    while (true) {
        printf(COLOR_CYAN "\n=== Menu ===\n" COLOR_RESET);
        printf("1. View all unspent UTXOs\n");
        printf("2. View all users\n");
        printf("3. Perform a transaction\n");
        printf("4. Exit\n");
        printf(COLOR_YELLOW "Enter choice (1-4): " COLOR_RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_utxos();
                break;
            case 2:
                display_users();
                break;
            case 3:
                perform_transaction();
                display_utxos();
                break;
            case 4:
                printf(COLOR_GREEN "Thank you for using the simulator! Goodbye.\n" COLOR_RESET);
                return 0;
            default:
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    }
    return 0;
}
