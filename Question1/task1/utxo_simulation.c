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
    char address[MAX_ADDRESS_LEN]; // Receiver's address (e.g., ADDR1)
    float amount; // Transaction amount
    bool spent; // Flag to mark if UTXO is spent
} UTXO;

// User structure
typedef struct {
    char name[MAX_ADDRESS_LEN]; // User's name (e.g., Joshua)
    char address[MAX_ADDRESS_LEN]; // Generated address (e.g., ADDR1)
} User;

// Global arrays and counts
UTXO utxo_list[MAX_UTXOS];
int utxo_count = 0;
User user_list[MAX_USERS];
int user_count = 0;

// Function to generate a unique address for a user
void generate_address(char *address, int index) {
    snprintf(address, MAX_ADDRESS_LEN, "ADDR%d", index + 1); // e.g., ADDR1, ADDR2
}

// Function to read users from file and assign addresses
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
            generate_address(user_list[user_count].address, user_count); // Assign address
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

// Function to check if an address is valid
bool is_valid_address(const char *address) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_list[i].address, address) == 0) {
            return true;
        }
    }
    return false;
}

// Function to get user name by address
const char* get_user_name_by_address(const char *address) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_list[i].address, address) == 0) {
            return user_list[i].name;
        }
    }
    return "Unknown";
}

// Function to display all users with their addresses
void display_users() {
    printf(COLOR_CYAN "\n=== Available Users and Addresses ===\n" COLOR_RESET);
    printf("Name            | Address\n");
    printf("-------------------------\n");
    for (int i = 0; i < user_count; i++) {
        printf("%-15s | %s\n", user_list[i].name, user_list[i].address);
    }
    printf("\n");
}

// Function to initialize sample UTXOs
void initialize_utxos() {
    if (user_count < 2) return; // Need at least 2 users
    // Initialize UTXOs for first two users using their addresses
    snprintf(utxo_list[utxo_count].txid, MAX_TXID_LEN, "TX1");
    strcpy(utxo_list[utxo_count].address, user_list[0].address); // e.g., ADDR1
    utxo_list[utxo_count].amount = 50.0;
    utxo_list[utxo_count].spent = false;
    utxo_count++;

    snprintf(utxo_list[utxo_count].txid, MAX_TXID_LEN, "TX2");
    strcpy(utxo_list[utxo_count].address, user_list[0].address); // e.g., ADDR1
    utxo_list[utxo_count].amount = 30.0;
    utxo_list[utxo_count].spent = false;
    utxo_count++;

    snprintf(utxo_list[utxo_count].txid, MAX_TXID_LEN, "TX3");
    strcpy(utxo_list[utxo_count].address, user_list[1].address); // e.g., ADDR2
    utxo_list[utxo_count].amount = 20.0;
    utxo_list[utxo_count].spent = false;
    utxo_count++;
}

// Function to display unspent UTXOs
void display_utxos() {
    printf(COLOR_CYAN "\n=== Unspent UTXOs ===\n" COLOR_RESET);
    printf("Index | TXID | User (Address)       | Amount | Spent\n");
    printf("-----------------------------------------------\n");
    bool has_utxos = false;
    for (int i = 0; i < utxo_count; i++) {
        if (!utxo_list[i].spent) {
            printf("%-5d | %-4s | %s (%s) | %.2f | %s\n", i, utxo_list[i].txid,
                   get_user_name_by_address(utxo_list[i].address), utxo_list[i].address,
                   utxo_list[i].amount, utxo_list[i].spent ? "Yes" : "No");
            has_utxos = true;
        }
    }
    if (!has_utxos) {
        printf(COLOR_RED "No unspent UTXOs available.\n" COLOR_RESET);
    }
    printf("\n");
}

// Function to display all UTXOs (spent and unspent)
void display_all_utxos() {
    printf(COLOR_CYAN "\n=== All UTXOs (Spent and Unspent) ===\n" COLOR_RESET);
    printf("Index | TXID | User (Address)       | Amount | Spent\n");
    printf("-----------------------------------------------\n");
    bool has_utxos = false;
    for (int i = 0; i < utxo_count; i++) {
        if (utxo_list[i].spent) {
            printf(COLOR_RED "%-5d | %-4s | %s (%s) | %.2f | %s\n" COLOR_RESET,
                   i, utxo_list[i].txid, get_user_name_by_address(utxo_list[i].address),
                   utxo_list[i].address, utxo_list[i].amount, "Yes");
        } else {
            printf("%-5d | %-4s | %s (%s) | %.2f | %s\n",
                   i, utxo_list[i].txid, get_user_name_by_address(utxo_list[i].address),
                   utxo_list[i].address, utxo_list[i].amount, "No");
        }
        has_utxos = true;
    }
    if (!has_utxos) {
        printf(COLOR_RED "No UTXOs available.\n" COLOR_RESET);
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
    char sender_addr[MAX_ADDRESS_LEN], receiver_addr[MAX_ADDRESS_LEN];
    float amount;
    int selected_utxos[MAX_UTXOS], selected_count = 0;
    float total_available = 0.0;

    // Display users for selection
    display_users();
    printf(COLOR_YELLOW "Enter sender's address (e.g., ADDR1): " COLOR_RESET);
    scanf("%s", sender_addr);
    if (!is_valid_address(sender_addr)) {
        printf(COLOR_RED "Error: Sender address '%s' not found.\n" COLOR_RESET, sender_addr);
        return false;
    }
    printf(COLOR_YELLOW "Enter receiver's address (e.g., ADDR2): " COLOR_RESET);
    scanf("%s", receiver_addr);
    if (!is_valid_address(receiver_addr)) {
        printf(COLOR_RED "Error: Receiver address '%s' not found.\n" COLOR_RESET, receiver_addr);
        return false;
    }
    printf(COLOR_YELLOW "Enter amount to transfer: " COLOR_RESET);
    scanf("%f", &amount);

    // Validate input
    if (amount <= 0) {
        printf(COLOR_RED "Error: Amount must be positive.\n" COLOR_RESET);
        return false;
    }
    if (strcmp(sender_addr, receiver_addr) == 0) {
        printf(COLOR_RED "Error: Sender and receiver addresses cannot be the same.\n" COLOR_RESET);
        return false;
    }

    // Display sender's available UTXOs
    printf(COLOR_CYAN "\nAvailable UTXOs for %s (%s):\n" COLOR_RESET,
           get_user_name_by_address(sender_addr), sender_addr);
    printf("Index | TXID | Amount\n");
    printf("---------------------\n");
    bool has_utxos = false;
    for (int i = 0; i < utxo_count; i++) {
        if (!utxo_list[i].spent && strcmp(utxo_list[i].address, sender_addr) == 0) {
            printf("%-5d | %-4s | %.2f\n", i, utxo_list[i].txid, utxo_list[i].amount);
            total_available += utxo_list[i].amount;
            has_utxos = true;
        }
    }
    if (!has_utxos) {
        printf(COLOR_RED "Error: No unspent UTXOs for address %s.\n" COLOR_RESET, sender_addr);
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
            strcmp(utxo_list[index].address, sender_addr) != 0) {
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
    strcpy(utxo_list[utxo_count].address, receiver_addr);
    utxo_list[utxo_count].amount = amount;
    utxo_list[utxo_count].spent = false;
    generate_txid(utxo_list[utxo_count].txid);
    utxo_count++;

    // Create change UTXO for sender if applicable
    float change = selected_amount - amount;
    if (change > 0) {
        strcpy(utxo_list[utxo_count].address, sender_addr);
        utxo_list[utxo_count].amount = change;
        utxo_list[utxo_count].spent = false;
        generate_txid(utxo_list[utxo_count].txid);
        utxo_count++;
    }

    printf(COLOR_GREEN "\n🎉 Transaction successful! 🎉\n" COLOR_RESET);
    printf("Transferred %.2f from %s (%s) to %s (%s)\n", amount,
           get_user_name_by_address(sender_addr), sender_addr,
           get_user_name_by_address(receiver_addr), receiver_addr);
    if (change > 0) {
        printf("Change of %.2f returned to %s (%s)\n", change,
               get_user_name_by_address(sender_addr), sender_addr);
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
        printf("1. View unspent UTXOs\n");
        printf("2. View all UTXOs (spent and unspent)\n");
        printf("3. View all users and addresses\n");
        printf("4. Perform a transaction\n");
        printf("5. Exit\n");
        printf(COLOR_YELLOW "Enter choice (1-5): " COLOR_RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_utxos();
                break;
            case 2:
                display_all_utxos();
                break;
            case 3:
                display_users();
                break;
            case 4:
                perform_transaction();
                display_utxos();
                break;
            case 5:
                printf(COLOR_GREEN "Thank you for using the simulator! Goodbye.\n" COLOR_RESET);
                return 0;
            default:
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    }
    return 0;
}
