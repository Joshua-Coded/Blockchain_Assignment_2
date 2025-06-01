#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define HASH_SIZE 65 // 64 chars for hex SHA-256 + null terminator
#define MAX_TRANSACTIONS 10
#define TRANSACTION_SIZE 100
#define MAX_BLOCKS 100

// ANSI color codes for output
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_RESET "\033[0m"

// Define Block structure
typedef struct {
    int index;
    time_t timestamp;
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE];
    int transaction_count;
    char previous_hash[HASH_SIZE];
    int nonce;
    char hash[HASH_SIZE];
} Block;

// Define Blockchain structure
typedef struct {
    Block blocks[MAX_BLOCKS];
    int block_count;
} Blockchain;

// Calculate SHA-256 hash
void calculate_sha256(const char* input, char output[HASH_SIZE]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_SIZE - 1] = '\0';
}

// Calculate the hash of a block
void calculate_block_hash(const Block* block, char* output_hash) {
    char data[2048] = {0};
    char temp[128];

    snprintf(temp, sizeof(temp), "%d", block->index);
    strncat(data, temp, sizeof(data) - strlen(data) - 1);
    snprintf(temp, sizeof(temp), "%ld", block->timestamp);
    strncat(data, temp, sizeof(data) - strlen(data) - 1);
    for (int i = 0; i < block->transaction_count; i++) {
        if (strlen(block->transactions[i]) > 0) {
            strncat(data, block->transactions[i], sizeof(data) - strlen(data) - 1);
        }
    }
    strncat(data, block->previous_hash, sizeof(data) - strlen(data) - 1);
    snprintf(temp, sizeof(temp), "%d", block->nonce);
    strncat(data, temp, sizeof(data) - strlen(data) - 1);

    calculate_sha256(data, output_hash);
}

// Check if hash meets difficulty
int meets_difficulty(const char* hash, int difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != '0') return 0;
    }
    return 1;
}

// Mine a block and return nonce attempts
long mine_block(Block* block, int difficulty) {
    char hash[HASH_SIZE];
    block->nonce = 0;
    long attempts = 0;

    printf(COLOR_YELLOW "⛏️  Mining block %d with %d leading zeros...\n" COLOR_RESET, block->index, difficulty);
    clock_t start = clock();
    do {
        calculate_block_hash(block, hash);
        if (meets_difficulty(hash, difficulty)) {
            strcpy(block->hash, hash);
            break;
        }
        block->nonce++;
        attempts++;
    } while (1);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf(COLOR_GREEN "✅ Block mined! Nonce: %d, Hash: %.20s...\n" COLOR_RESET, block->nonce, block->hash);
    printf(COLOR_CYAN "🕒 Time: %.4f s, Attempts: %ld\n" COLOR_RESET, time_spent, attempts);
    return attempts;
}

// Create genesis block
void create_genesis_block(Blockchain* chain, int difficulty) {
    Block* block = &chain->blocks[0];
    block->index = 0;
    block->timestamp = time(NULL);
    block->transaction_count = 1;
    strcpy(block->transactions[0], "Genesis Transaction");
    for (int i = 1; i < MAX_TRANSACTIONS; i++) block->transactions[i][0] = '\0';
    strcpy(block->previous_hash, "0000000000000000000000000000000000000000000000000000000000000000");
    block->nonce = 0;

    printf(COLOR_YELLOW "🧱 Creating genesis block...\n" COLOR_RESET);
    mine_block(block, difficulty);
    chain->block_count = 1;
    printf(COLOR_GREEN "🌟 Genesis block created and mined!\n" COLOR_RESET);
}

// Add a new block
void add_block(Blockchain* chain, const char transactions[][TRANSACTION_SIZE], int transaction_count, const char* prev_hash, int difficulty) {
    if (chain->block_count >= MAX_BLOCKS) {
        printf(COLOR_RED "❌ Blockchain is full!\n" COLOR_RESET);
        return;
    }

    Block* block = &chain->blocks[chain->block_count];
    block->index = chain->block_count;
    block->timestamp = time(NULL);
    block->transaction_count = transaction_count < MAX_TRANSACTIONS ? transaction_count : MAX_TRANSACTIONS;

    for (int i = 0; i < block->transaction_count; i++) {
        strncpy(block->transactions[i], transactions[i], TRANSACTION_SIZE - 1);
        block->transactions[i][TRANSACTION_SIZE - 1] = '\0';
    }
    for (int i = block->transaction_count; i < MAX_TRANSACTIONS; i++) block->transactions[i][0] = '\0';

    strcpy(block->previous_hash, prev_hash);
    mine_block(block, difficulty);
    chain->block_count++;
    printf(COLOR_GREEN "🧱 Block %d added to the blockchain!\n" COLOR_RESET, block->index);
}

// Verify blockchain integrity
int verify_blockchain(const Blockchain* chain) {
    printf(COLOR_YELLOW "🔍 Verifying blockchain integrity...\n" COLOR_RESET);
    for (int i = 0; i < chain->block_count; i++) {
        const Block* block = &chain->blocks[i];
        char computed_hash[HASH_SIZE];

        calculate_block_hash(block, computed_hash);
        if (strcmp(block->hash, computed_hash) != 0) {
            printf(COLOR_RED "❌ Error: Block %d has invalid hash!\n" COLOR_RESET, block->index);
            return 0;
        }

        if (i > 0) {
            char prev_hash[HASH_SIZE];
            calculate_block_hash(&chain->blocks[i - 1], prev_hash);
            if (strcmp(block->previous_hash, prev_hash) != 0) {
                printf(COLOR_RED "❌ Error: Block %d has invalid previous hash!\n" COLOR_RESET, block->index);
                return 0;
            }
        }
    }
    printf(COLOR_GREEN "✅ Blockchain integrity verified!\n" COLOR_RESET);
    return 1;
}

// Simulate mining with different difficulties
void simulate_mining(Blockchain* chain, int start_difficulty, int end_difficulty) {
    int num_difficulties = end_difficulty - start_difficulty + 1;
    double times[10];
    long attempts[10];

    char transactions[2][TRANSACTION_SIZE] = {
        "Alice -> Bob: 10",
        "Bob -> Charlie: 5"
    };

    printf(COLOR_YELLOW "\n📊 Simulating mining with difficulties %d to %d...\n" COLOR_RESET, start_difficulty, end_difficulty);
    for (int i = 0; i < num_difficulties; i++) {
        int difficulty = start_difficulty + i;
        char prev_hash[HASH_SIZE];
        strcpy(prev_hash, chain->blocks[chain->block_count - 1].hash);

        times[i] = 0;
        attempts[i] = mine_block(&chain->blocks[chain->block_count], difficulty);
        add_block(chain, transactions, 2, prev_hash, difficulty);
        verify_blockchain(chain);
    }

    printf(COLOR_CYAN "\n📈 Mining Simulation Results:\n" COLOR_RESET);
    printf("----------------------------------------\n");
    printf("Difficulty | Time (seconds) | Nonce Attempts\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < num_difficulties; i++) {
        printf("%9d | %13.4f | %13ld\n", start_difficulty + i, times[i], attempts[i]);
    }
    printf("----------------------------------------\n");
}

// Print blockchain
void print_blockchain(const Blockchain* chain) {
    if (chain->block_count == 0) {
        printf(COLOR_RED "🚫 Blockchain is empty.\n" COLOR_RESET);
        return;
    }
    printf(COLOR_CYAN "\n🧬 ====== Blockchain ======\n" COLOR_RESET);
    for (int i = 0; i < chain->block_count; i++) {
        const Block* b = &chain->blocks[i];
        printf("\n🔗 Block %d\n", b->index);
        printf("-------------------\n");
        printf(COLOR_YELLOW "🕒 Timestamp: %s" COLOR_RESET, ctime(&b->timestamp));
        printf(COLOR_YELLOW "💸 Transactions:\n" COLOR_RESET);
        for (int j = 0; j < b->transaction_count; j++) {
            printf("  - %s\n", b->transactions[j]);
        }
        printf(COLOR_YELLOW "🔗 Previous Hash: %.20s...\n" COLOR_RESET, b->previous_hash);
        printf(COLOR_YELLOW "🔢 Nonce: %d\n" COLOR_RESET, b->nonce);
        printf(COLOR_YELLOW "🔐 Hash: %.20s...\n" COLOR_RESET, b->hash);
    }
    printf(COLOR_CYAN "=======================\n" COLOR_RESET);
}

// Interactive menu
void show_menu(Blockchain* chain) {
    int choice, start_diff = 2, end_diff = 4;
    do {
        printf(COLOR_CYAN "\n=============================\n" COLOR_RESET);
        printf(COLOR_CYAN "🌐 Task 4: Difficulty Adjustment\n" COLOR_RESET);
        printf(COLOR_CYAN "=============================\n" COLOR_RESET);
        printf("1️⃣  Create Genesis Block\n");
        printf("2️⃣  Simulate Mining\n");
        printf("3️⃣  Set Difficulty Range\n");
        printf("4️⃣  View Blockchain\n");
        printf("5️⃣  Verify Blockchain\n");
        printf("6️⃣  Exit\n");
        printf(COLOR_CYAN "=============================\n" COLOR_RESET);
        printf(COLOR_YELLOW "Select an option: " COLOR_RESET);
        if (scanf("%d", &choice) != 1) {
            printf(COLOR_RED "❌ Invalid input. Try again.\n" COLOR_RESET);
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear newline

        switch (choice) {
            case 1:
                chain->block_count = 0;
                create_genesis_block(chain, start_diff);
                verify_blockchain(chain);
                break;
            case 2:
                if (chain->block_count == 0) {
                    printf(COLOR_RED "❌ Create genesis block first!\n" COLOR_RESET);
                } else {
                    simulate_mining(chain, start_diff, end_diff);
                }
                break;
            case 3:
                printf(COLOR_YELLOW "⚙️ Enter start difficulty (1-6): " COLOR_RESET);
                if (scanf("%d", &start_diff) != 1) {
                    printf(COLOR_RED "❌ Invalid input. Using default (2).\n" COLOR_RESET);
                    start_diff = 2;
                }
                printf(COLOR_YELLOW "⚙️ Enter end difficulty (%d-6): " COLOR_RESET, start_diff);
                if (scanf("%d", &end_diff) != 1) {
                    printf(COLOR_RED "❌ Invalid input. Using default (4).\n" COLOR_RESET);
                    end_diff = 4;
                }
                while (getchar() != '\n'); // Clear newline
                if (start_diff < 1 || end_diff > 6 || start_diff > end_diff) {
                    printf(COLOR_RED "❌ Invalid range! Using default (2-4).\n" COLOR_RESET);
                    start_diff = 2;
                    end_diff = 4;
                } else {
                    printf(COLOR_GREEN "✅ Difficulty range set to %d-%d.\n" COLOR_RESET, start_diff, end_diff);
                }
                break;
            case 4:
                print_blockchain(chain);
                break;
            case 5:
                verify_blockchain(chain);
                break;
            case 6:
                printf(COLOR_GREEN "👋 Exiting Task 4. Goodbye!\n" COLOR_RESET);
                break;
            default:
                printf(COLOR_RED "❌ Invalid option. Try again.\n" COLOR_RESET);
        }
    } while (choice != 6);
}

int main() {
    printf(COLOR_CYAN "🚀 Welcome to Task 4: Difficulty Adjustment!\n" COLOR_RESET);
    Blockchain chain;
    chain.block_count = 0;
    show_menu(&chain);
    return 0;
}
