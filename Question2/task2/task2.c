#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

/* ================ CONSTANTS ================ */
#define HASH_SIZE 65                // Size of SHA-256 hash string (64 chars + null terminator)
#define MAX_TRANSACTIONS 10         // Maximum transactions per block
#define TRANSACTION_SIZE 100        // Maximum size of each transaction
#define DIFFICULTY 4                // Mining difficulty (number of leading zeros)

/* ================ COLOR SCHEME ================ */
#define COLOR_BRIGHT "\033[1m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[38;5;203m"
#define COLOR_GREEN "\033[38;5;84m"
#define COLOR_YELLOW "\033[38;5;227m"
#define COLOR_BLUE "\033[38;5;75m"
#define COLOR_PURPLE "\033[38;5;141m"
#define COLOR_CYAN "\033[38;5;87m"
#define COLOR_GRAY "\033[38;5;245m"

/* ================ DATA STRUCTURES ================ */
typedef struct {
    int index;                      // Block index in the chain
    time_t timestamp;               // Time when block was created
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE];  // Transaction data
    int transaction_count;          // Number of transactions in block
    char previous_hash[HASH_SIZE];  // Hash of previous block in chain
    int nonce;                      // Proof-of-work nonce
    char hash[HASH_SIZE];           // Current block's hash
} Block;

/* ================ FUNCTION PROTOTYPES ================ */
void calculate_sha256(const char* input, char output[HASH_SIZE]);
void calculate_block_hash(const Block* block, char* output_hash);
int validate_hash_difficulty(const char* hash, int difficulty);
void mine_block(Block* block, int difficulty);
void initialize_genesis_block(Block* block, int difficulty);
void display_block(const Block* block);
void show_menu(void);
void print_header(const char* text);
void print_success(const char* text);
void print_warning(const char* text);
void print_error(const char* text);

/* ================ UTILITY FUNCTIONS ================ */
void print_header(const char* text) {
    printf("\n" COLOR_BLUE COLOR_BRIGHT "▐▓▒▌ " COLOR_CYAN "%s " COLOR_BLUE "▐▓▒▌" COLOR_RESET "\n", text);
}

void print_success(const char* text) {
    printf(COLOR_GREEN "✓ %s" COLOR_RESET "\n", text);
}

void print_warning(const char* text) {
    printf(COLOR_YELLOW "⚠ %s" COLOR_RESET "\n", text);
}

void print_error(const char* text) {
    printf(COLOR_RED "✗ %s" COLOR_RESET "\n", text);
}

/* ================ CORE FUNCTIONS ================ */
void calculate_sha256(const char* input, char output[HASH_SIZE]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), hash);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_SIZE - 1] = '\0';
}

void calculate_block_hash(const Block* block, char* output_hash) {
    char block_data[2048] = {0};
    char temp_buffer[128];

    // Combine all block data into single string
    snprintf(temp_buffer, sizeof(temp_buffer), "%d", block->index);
    strncat(block_data, temp_buffer, sizeof(block_data) - strlen(block_data) - 1);
    
    snprintf(temp_buffer, sizeof(temp_buffer), "%ld", block->timestamp);
    strncat(block_data, temp_buffer, sizeof(block_data) - strlen(block_data) - 1);
    
    for (int i = 0; i < block->transaction_count; i++) {
        if (strlen(block->transactions[i]) > 0) {
            strncat(block_data, block->transactions[i], sizeof(block_data) - strlen(block_data) - 1);
        }
    }
    
    strncat(block_data, block->previous_hash, sizeof(block_data) - strlen(block_data) - 1);
    
    snprintf(temp_buffer, sizeof(temp_buffer), "%d", block->nonce);
    strncat(block_data, temp_buffer, sizeof(block_data) - strlen(block_data) - 1);

    calculate_sha256(block_data, output_hash);
}

int validate_hash_difficulty(const char* hash, int difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != '0') return 0;
    }
    return 1;
}

void mine_block(Block* block, int difficulty) {
    char current_hash[HASH_SIZE];
    block->nonce = 0;

    print_header("MINING PROCESS");
    printf(COLOR_PURPLE "⛏ Mining Block #%d" COLOR_RESET "\n", block->index);
    printf(COLOR_GRAY "Target Difficulty: %d leading zeros" COLOR_RESET "\n", difficulty);
    
    clock_t start = clock();
    do {
        calculate_block_hash(block, current_hash);
        block->nonce++;
    } while (!validate_hash_difficulty(current_hash, difficulty));
    clock_t end = clock();

    strcpy(block->hash, current_hash);
    
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf(COLOR_GREEN "✔ Successfully mined after %.2f seconds!" COLOR_RESET "\n", elapsed);
    printf(COLOR_CYAN "Nonce: %d" COLOR_RESET "\n", block->nonce - 1);
    printf(COLOR_YELLOW "Hash: %.12s...%s" COLOR_RESET "\n\n", block->hash, block->hash + 52);
}

void initialize_genesis_block(Block* block, int difficulty) {
    block->index = 0;
    block->timestamp = time(NULL);
    block->transaction_count = 1;
    strcpy(block->transactions[0], "Genesis Transaction");
    
    // Clear remaining transaction slots
    for (int i = 1; i < MAX_TRANSACTIONS; i++) {
        block->transactions[i][0] = '\0';
    }
    
    strcpy(block->previous_hash, "0000000000000000000000000000000000000000000000000000000000000000");
    block->nonce = 0;

    print_header("GENESIS BLOCK CREATION");
    mine_block(block, difficulty);
    print_success("Genesis block initialized successfully!");
}

void display_block(const Block* block) {
    print_header("BLOCK DETAILS");
    printf(COLOR_BLUE "┌───────────────────────────────┐" COLOR_RESET "\n");
    printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %15d " COLOR_BLUE "│" COLOR_RESET "\n", "Index:", block->index);
    printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %15s " COLOR_BLUE "│" COLOR_RESET "\n", "Timestamp:", ctime(&block->timestamp));
    printf(COLOR_BLUE "├───────────────────────────────┤" COLOR_RESET "\n");
    
    printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %15d " COLOR_BLUE "│" COLOR_RESET "\n", "Transactions:", block->transaction_count);
    for (int i = 0; i < block->transaction_count; i++) {
        printf(COLOR_BLUE "│ " COLOR_YELLOW "  %02d: %-20s " COLOR_BLUE "│" COLOR_RESET "\n", i+1, block->transactions[i]);
    }
    
    printf(COLOR_BLUE "├───────────────────────────────┤" COLOR_RESET "\n");
    printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %.12s... " COLOR_BLUE "│" COLOR_RESET "\n", "Previous Hash:", block->previous_hash);
    printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %15d " COLOR_BLUE "│" COLOR_RESET "\n", "Nonce:", block->nonce);
    printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %.12s... " COLOR_BLUE "│" COLOR_RESET "\n", "Hash:", block->hash);
    printf(COLOR_BLUE "└───────────────────────────────┘" COLOR_RESET "\n\n");
}

/* ================ USER INTERFACE ================ */
void show_menu(void) {
    Block genesis_block;
    int option;
    int genesis_created = 0;
    
    print_header("BLOCKCHAIN PROOF OF WORK DEMONSTRATION");
    printf(COLOR_GREEN "Mining difficulty: %d leading zeros" COLOR_RESET "\n\n", DIFFICULTY);
    
    do {
        printf(COLOR_BLUE "┌───────────────────────────────┐" COLOR_RESET "\n");
        printf(COLOR_BLUE "│ " COLOR_CYAN "MAIN MENU" COLOR_BLUE "                     │" COLOR_RESET "\n");
        printf(COLOR_BLUE "├───────────────────────────────┤" COLOR_RESET "\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "1. " COLOR_RESET "Create Genesis Block      " COLOR_BLUE "│" COLOR_RESET "\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "2. " COLOR_RESET "Display Genesis Block     " COLOR_BLUE "│" COLOR_RESET "\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "3. " COLOR_RESET "Exit                      " COLOR_BLUE "│" COLOR_RESET "\n");
        printf(COLOR_BLUE "└───────────────────────────────┘" COLOR_RESET "\n");
        printf(COLOR_PURPLE "Select option: " COLOR_RESET);
        scanf("%d", &option);
        getchar(); // Clear newline from input buffer

        switch (option) {
            case 1:
                if (!genesis_created) {
                    initialize_genesis_block(&genesis_block, DIFFICULTY);
                    genesis_created = 1;
                } else {
                    print_warning("Genesis block already exists!");
                }
                break;
                
            case 2:
                if (genesis_created) {
                    display_block(&genesis_block);
                } else {
                    print_error("Genesis block not created yet!");
                }
                break;
                
            case 3:
                print_success("Exiting program. Goodbye!");
                break;
                
            default:
                print_error("Invalid option. Please try again.");
        }
    } while (option != 3);
}

/* ================ MAIN FUNCTION ================ */
int main() {
    print_header("BLOCKCHAIN PROOF OF WORK SYSTEM");
    show_menu();
    return 0;
}
