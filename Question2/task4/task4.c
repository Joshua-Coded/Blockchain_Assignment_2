#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

/* ================ CONSTANTS ================ */
#define HASH_SIZE 65         // Size of SHA-256 hash string (64 chars + null terminator)
#define MAX_TRANSACTIONS 10  // Maximum transactions per block
#define TRANSACTION_SIZE 100 // Maximum size of each transaction
#define MAX_BLOCKS 100       // Maximum blocks in blockchain
#define DEFAULT_DIFFICULTY 4 // Default mining difficulty (number of leading zeros)

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
#define COLOR_ORANGE "\033[38;5;214m"

/* ================ DATA STRUCTURES ================ */
typedef struct
{
    int index;                                             // Block index in the chain
    time_t timestamp;                                      // Time when block was created
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE]; // Transaction data
    int transaction_count;                                 // Number of transactions in block
    char previous_hash[HASH_SIZE];                         // Hash of previous block in chain
    int nonce;                                             // Proof-of-work nonce
    char hash[HASH_SIZE];                                  // Current block's hash
} Block;

typedef struct
{
    Block blocks[MAX_BLOCKS]; // Array of blocks
    int block_count;          // Number of blocks in chain
} Blockchain;

/* ================ FUNCTION PROTOTYPES ================ */
void calculate_sha256(const char *input, char output[HASH_SIZE]);
void calculate_block_hash(const Block *block, char *output_hash);
int validate_hash_difficulty(const char *hash, int difficulty);
void mine_block(Block *block, int difficulty, double *time_taken, int *nonce_attempts);
void initialize_genesis_block(Blockchain *chain, int difficulty);
void add_block(Blockchain *chain, const char transactions[][TRANSACTION_SIZE],
               int transaction_count, const char *prev_hash, int difficulty);
int verify_blockchain(const Blockchain *chain);
void add_block_from_input(Blockchain *chain, int difficulty);
void display_blockchain(const Blockchain *chain);
void simulate_mining(Blockchain *chain, int start_difficulty, int end_difficulty);
void show_menu(Blockchain *chain);

/* ================ UTILITY FUNCTIONS ================ */
void print_header(const char *text)
{
    printf("\n" COLOR_BLUE COLOR_BRIGHT "▐▓▒▌ %s ▐▓▒▌" COLOR_RESET "\n", text);
}

void print_success(const char *text)
{
    printf(COLOR_GREEN "✓ %s" COLOR_RESET "\n", text);
}

void print_error(const char *text)
{
    printf(COLOR_RED "✗ %s" COLOR_RESET "\n", text);
}

/* ================ CORE FUNCTIONS ================ */
void calculate_sha256(const char *input, char output[HASH_SIZE])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_SIZE - 1] = '\0';
}

void calculate_block_hash(const Block *block, char *output_hash)
{
    char block_data[2048] = {0};
    char temp_buffer[128];

    snprintf(temp_buffer, sizeof(temp_buffer), "%d", block->index);
    strncat(block_data, temp_buffer, sizeof(block_data) - strlen(block_data) - 1);
    snprintf(temp_buffer, sizeof(temp_buffer), "%ld", block->timestamp);
    strncat(block_data, temp_buffer, sizeof(block_data) - strlen(block_data) - 1);
    for (int i = 0; i < block->transaction_count; i++)
    {
        if (strlen(block->transactions[i]) > 0)
        {
            strncat(block_data, block->transactions[i], sizeof(block_data) - strlen(block_data) - 1);
        }
    }
    strncat(block_data, block->previous_hash, sizeof(block_data) - strlen(block_data) - 1);
    snprintf(temp_buffer, sizeof(temp_buffer), "%d", block->nonce);
    strncat(block_data, temp_buffer, sizeof(block_data) - strlen(block_data) - 1);

    calculate_sha256(block_data, output_hash);
}

int validate_hash_difficulty(const char *hash, int difficulty)
{
    for (int i = 0; i < difficulty; i++)
    {
        if (hash[i] != '0')
            return 0;
    }
    return 1;
}

void mine_block(Block *block, int difficulty, double *time_taken, int *nonce_attempts)
{
    char current_hash[HASH_SIZE];
    block->nonce = 0;
    *nonce_attempts = 0;

    print_header("MINING PROCESS");
    printf(COLOR_PURPLE "⛏ Mining Block #%d" COLOR_RESET "\n", block->index);
    printf(COLOR_GRAY "Target Difficulty: %d leading zeros" COLOR_RESET "\n", difficulty);

    clock_t start = clock();
    do
    {
        calculate_block_hash(block, current_hash);
        (*nonce_attempts)++;
        if (validate_hash_difficulty(current_hash, difficulty))
        {
            strcpy(block->hash, current_hash);
            break;
        }
        block->nonce++;
    } while (1);

    clock_t end = clock();
    *time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf(COLOR_GREEN "✔ Successfully mined after %.2f seconds!" COLOR_RESET "\n", *time_taken);
    printf(COLOR_CYAN "Nonce: %d" COLOR_RESET "\n", block->nonce);
    printf(COLOR_YELLOW "Hash: %.12s...%s" COLOR_RESET "\n\n", block->hash, block->hash + 52);
}

void initialize_genesis_block(Blockchain *chain, int difficulty)
{
    if (chain->block_count > 0)
    {
        print_error("Genesis block already exists!");
        return;
    }

    Block *block = &chain->blocks[0];
    block->index = 0;
    block->timestamp = time(NULL);
    block->transaction_count = 1;
    strcpy(block->transactions[0], "Genesis Transaction");
    for (int i = 1; i < MAX_TRANSACTIONS; i++)
    {
        block->transactions[i][0] = '\0';
    }
    strcpy(block->previous_hash, "0000000000000000000000000000000000000000000000000000000000000000");
    block->nonce = 0;

    print_header("GENESIS BLOCK CREATION");
    double time_taken;
    int nonce_attempts;
    mine_block(block, difficulty, &time_taken, &nonce_attempts);
    chain->block_count = 1;
    print_success("Genesis block initialized successfully!");
}

void add_block(Blockchain *chain, const char transactions[][TRANSACTION_SIZE],
               int transaction_count, const char *prev_hash, int difficulty)
{
    if (chain->block_count >= MAX_BLOCKS)
    {
        print_error("Blockchain capacity reached!");
        return;
    }

    Block *block = &chain->blocks[chain->block_count];
    block->index = chain->block_count;
    block->timestamp = time(NULL);
    block->transaction_count = transaction_count < MAX_TRANSACTIONS ? transaction_count : MAX_TRANSACTIONS;

    for (int i = 0; i < block->transaction_count; i++)
    {
        strncpy(block->transactions[i], transactions[i], TRANSACTION_SIZE - 1);
        block->transactions[i][TRANSACTION_SIZE - 1] = '\0';
    }
    for (int i = block->transaction_count; i < MAX_TRANSACTIONS; i++)
    {
        block->transactions[i][0] = '\0';
    }

    strcpy(block->previous_hash, prev_hash);
    print_header("ADDING NEW BLOCK");
    double time_taken;
    int nonce_attempts;
    mine_block(block, difficulty, &time_taken, &nonce_attempts);
    chain->block_count++;
    print_success("New block added to the blockchain!");
}

int verify_blockchain(const Blockchain *chain)
{
    print_header("BLOCKCHAIN VERIFICATION");

    if (chain->block_count == 0)
    {
        print_error("Blockchain is empty!");
        return 0;
    }

    for (int i = 0; i < chain->block_count; i++)
    {
        const Block *block = &chain->blocks[i];
        char computed_hash[HASH_SIZE];

        calculate_block_hash(block, computed_hash);
        if (strcmp(block->hash, computed_hash) != 0)
        {
            printf(COLOR_BLUE "┌───────────────────────────────┐\n");
            printf(COLOR_BLUE "│ " COLOR_RED "Invalid hash in block %-2d      " COLOR_BLUE "│\n", block->index);
            printf(COLOR_BLUE "├───────────────────────────────┤\n");
            printf(COLOR_BLUE "│ " COLOR_CYAN "Expected: %.12s...%s " COLOR_BLUE "│\n", computed_hash, computed_hash + 52);
            printf(COLOR_BLUE "│ " COLOR_RED "Found:    %.12s...%s " COLOR_BLUE "│\n", block->hash, block->hash + 52);
            printf(COLOR_BLUE "└───────────────────────────────┘\n");
            return 0;
        }

        if (i > 0)
        {
            char prev_hash[HASH_SIZE];
            calculate_block_hash(&chain->blocks[i - 1], prev_hash);
            if (strcmp(block->previous_hash, prev_hash) != 0)
            {
                printf(COLOR_BLUE "┌───────────────────────────────┐\n");
                printf(COLOR_BLUE "│ " COLOR_RED "Invalid previous hash %-2d     " COLOR_BLUE "│\n", block->index);
                printf(COLOR_BLUE "├───────────────────────────────┤\n");
                printf(COLOR_BLUE "│ " COLOR_CYAN "Expected: %.12s...%s " COLOR_BLUE "│\n", prev_hash, prev_hash + 52);
                printf(COLOR_BLUE "│ " COLOR_RED "Found:    %.12s...%s " COLOR_BLUE "│\n", block->previous_hash, block->previous_hash + 52);
                printf(COLOR_BLUE "└───────────────────────────────┘\n");
                return 0;
            }
        }
    }

    printf(COLOR_BLUE "┌───────────────────────────────┐\n");
    printf(COLOR_BLUE "│ " COLOR_GREEN "Blockchain verification passed! " COLOR_BLUE "│\n");
    printf(COLOR_BLUE "│ " COLOR_GREEN "All %d blocks are valid.       " COLOR_BLUE "│\n", chain->block_count);
    printf(COLOR_BLUE "└───────────────────────────────┘\n");
    return 1;
}

void add_block_from_input(Blockchain *chain, int difficulty)
{
    if (chain->block_count == 0)
    {
        print_error("Create genesis block first!");
        return;
    }

    int txn_count;
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE];

    printf(COLOR_CYAN "\nEnter number of transactions (1-%d): " COLOR_RESET, MAX_TRANSACTIONS);
    if (scanf("%d", &txn_count) != 1 || txn_count <= 0 || txn_count > MAX_TRANSACTIONS)
    {
        print_error("Invalid number of transactions");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    printf(COLOR_CYAN "Enter %d transactions (format: sender->receiver:amount):\n" COLOR_RESET, txn_count);
    for (int i = 0; i < txn_count; i++)
    {
        printf(COLOR_YELLOW "  Transaction %d: " COLOR_RESET, i + 1);
        if (!fgets(transactions[i], TRANSACTION_SIZE, stdin))
        {
            print_error("Error reading transaction");
            return;
        }
        transactions[i][strcspn(transactions[i], "\n")] = '\0';
        if (strlen(transactions[i]) == 0)
        {
            print_error("Transaction cannot be empty");
            return;
        }
    }

    add_block(chain, transactions, txn_count, chain->blocks[chain->block_count - 1].hash, difficulty);
    verify_blockchain(chain);
}

void display_blockchain(const Blockchain *chain)
{
    print_header("BLOCKCHAIN CONTENTS");

    if (chain->block_count == 0)
    {
        print_error("Blockchain is empty");
        return;
    }

    printf(COLOR_BLUE "┌──────────────────────────────────────────────────────┐\n");
    printf(COLOR_BLUE "│ " COLOR_CYAN "BLOCKCHAIN (Length: %d)" COLOR_BLUE "                         │\n", chain->block_count);
    printf(COLOR_BLUE "├──────────────────────────────────────────────────────┤\n");

    for (int i = 0; i < chain->block_count; i++)
    {
        const Block *block = &chain->blocks[i];
        char time_str[26];
        ctime_r(&block->timestamp, time_str);
        time_str[24] = '\0'; // Remove newline

        printf(COLOR_BLUE "│ " COLOR_ORANGE "Block #%-3d" COLOR_BLUE "                                      │\n", block->index);
        printf(COLOR_BLUE "├──────────────────────────────────────────────────────┤\n");
        printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %-40s │\n", "Timestamp:", time_str);
        printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %-40d │\n", "Transactions:", block->transaction_count);
        for (int j = 0; j < block->transaction_count; j++)
        {
            printf(COLOR_BLUE "│   " COLOR_YELLOW "%-12d" COLOR_BLUE " %-37s │\n", j + 1, block->transactions[j]);
        }
        printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %.12s...%s │\n", "Prev Hash:", block->previous_hash, block->previous_hash + 52);
        printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %-40d │\n", "Nonce:", block->nonce);
        printf(COLOR_BLUE "│ " COLOR_CYAN "%-15s" COLOR_BLUE " %.12s...%s │\n", "Hash:", block->hash, block->hash + 52);
        if (i < chain->block_count - 1)
        {
            printf(COLOR_BLUE "├──────────────────────────────────────────────────────┤\n");
        }
    }
    printf(COLOR_BLUE "└──────────────────────────────────────────────────────┘\n");
}

void simulate_mining(Blockchain *chain, int start_difficulty, int end_difficulty)
{
    if (chain->block_count == 0)
    {
        print_error("Create genesis block first!");
        return;
    }

    if (start_difficulty < 1 || end_difficulty < start_difficulty || end_difficulty > 6)
    {
        print_error("Invalid difficulty range (must be 1-6)");
        return;
    }

    print_header("MINING SIMULATION");
    printf(COLOR_CYAN "Simulating mining with difficulties %d to %d...\n" COLOR_RESET, start_difficulty, end_difficulty);

    double times[6];
    int nonces[6];
    int blocks_added = 0;

    printf(COLOR_BLUE "┌──────────────────────────────────────────────────────┐\n");
    printf(COLOR_BLUE "│ " COLOR_CYAN "MINING SIMULATION RESULTS" COLOR_BLUE "                     │\n");
    printf(COLOR_BLUE "├────────────────────────┬──────────────┬──────────────┤\n");
    printf(COLOR_BLUE "│ " COLOR_YELLOW "%-22s" COLOR_BLUE " │ " COLOR_YELLOW "%-12s" COLOR_BLUE " │ " COLOR_YELLOW "%-12s" COLOR_BLUE " │\n", "Difficulty", "Time (s)", "Nonce Attempts");
    printf(COLOR_BLUE "├────────────────────────┼──────────────┼──────────────┤\n");

    for (int difficulty = start_difficulty; difficulty <= end_difficulty; difficulty++)
    {
        char transactions[1][TRANSACTION_SIZE] = {"Simulation Transaction"};
        add_block(chain, transactions, 1, chain->blocks[chain->block_count - 1].hash, difficulty);

        // Get time and nonce from the last block
        Block *last_block = &chain->blocks[chain->block_count - 1];
        double time_taken;
        int nonce_attempts;
        mine_block(last_block, difficulty, &time_taken, &nonce_attempts); // Re-mine to get metrics
        times[difficulty - start_difficulty] = time_taken;
        nonces[difficulty - start_difficulty] = nonce_attempts;

        printf(COLOR_BLUE "│ " COLOR_CYAN "%-22d" COLOR_BLUE " │ " COLOR_CYAN "%-12.4f" COLOR_BLUE " │ " COLOR_CYAN "%-12d" COLOR_BLUE " │\n",
               difficulty, time_taken, nonce_attempts);
        blocks_added++;
    }

    printf(COLOR_BLUE "└────────────────────────┴──────────────┴──────────────┘\n");
    print_success("Simulation completed!");
}

void show_menu(Blockchain *chain)
{
    int option;
    int start_difficulty = 2, end_difficulty = 4;

    print_header("BLOCKCHAIN DEMONSTRATION");
    printf(COLOR_GREEN "Default mining difficulty: %d leading zeros\n" COLOR_RESET, DEFAULT_DIFFICULTY);

    do
    {
        printf(COLOR_BLUE "\n┌───────────────────────────────┐\n");
        printf(COLOR_BLUE "│ " COLOR_CYAN "MAIN MENU" COLOR_BLUE "                     │\n");
        printf(COLOR_BLUE "├───────────────────────────────┤\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "1. " COLOR_RESET "Create Genesis Block      " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "2. " COLOR_RESET "Add New Block            " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "3. " COLOR_RESET "View Blockchain          " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "4. " COLOR_RESET "Verify Blockchain        " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "5. " COLOR_RESET "Set Difficulty Range     " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "6. " COLOR_RESET "Simulate Mining          " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "│ " COLOR_YELLOW "7. " COLOR_RESET "Exit                     " COLOR_BLUE "│\n");
        printf(COLOR_BLUE "└───────────────────────────────┘\n");
        printf(COLOR_PURPLE "Select option: " COLOR_RESET);

        if (scanf("%d", &option) != 1)
        {
            print_error("Invalid input");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (option)
        {
        case 1:
            chain->block_count = 0;
            initialize_genesis_block(chain, DEFAULT_DIFFICULTY);
            verify_blockchain(chain);
            break;
        case 2:
            add_block_from_input(chain, DEFAULT_DIFFICULTY);
            break;
        case 3:
            display_blockchain(chain);
            break;
        case 4:
            verify_blockchain(chain);
            break;
        case 5:
            printf(COLOR_CYAN "Enter start difficulty (1-6): " COLOR_RESET);
            if (scanf("%d", &start_difficulty) != 1 || start_difficulty < 1 || start_difficulty > 6)
            {
                print_error("Invalid start difficulty");
                while (getchar() != '\n');
                break;
            }
            printf(COLOR_CYAN "Enter end difficulty (%d-6): " COLOR_RESET, start_difficulty);
            if (scanf("%d", &end_difficulty) != 1 || end_difficulty < start_difficulty || end_difficulty > 6)
            {
                print_error("Invalid end difficulty");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');
            print_success("Difficulty range updated!");
            break;
        case 6:
            simulate_mining(chain, start_difficulty, end_difficulty);
            break;
        case 7:
            print_success("Exiting program. Goodbye!");
            break;
        default:
            print_error("Invalid option");
        }
    } while (option != 7);
}

int main()
{
    Blockchain chain;
    chain.block_count = 0;
    print_header("BLOCKCHAIN PROOF OF WORK SYSTEM");
    show_menu(&chain);
    return 0;
}
