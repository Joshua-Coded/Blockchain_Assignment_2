# Blockchain Assignment 2

Assignment 2-[F:A] by Alana, due June 1, 2025. Implements blockchain transaction models (`Question1`) and mining tasks (`Question2`) in C.

## Directory Structure
- `Question1`
  - `task1`: UTXO simulation
  - `task2`: Account/Balance simulation
- `Question2`
  - `task1`: Blockchain setup
  - `task2`: Genesis block mining
  - `task3`: Block mining with transactions
  - `task4`: Difficulty adjustment

## Prerequisites
- GCC compiler
- OpenSSL (for `Question2`): `brew install openssl` (macOS)

## Question 1: Transaction Models

### Task 1: UTXO Simulation
**Simulates UTXO-based transactions (Bitcoin-like).**

```bash
cd Question1/task1
gcc utxo_simulation.c -o utxo_simulation
./utxo_simulation
Task 2: Account Model Simulation
Simulates Account/Balance transactions (Ethereum-like).
bash
cd Question1/task2
gcc account_model_simulation.c -o account_model_simulation
./account_model_simulation
Question 2: Blockchain Mining
Task 1: Blockchain Setup
Sets up a basic blockchain.
bash
cd Question2/task1
gcc task1.c -o task1 -lssl -lcrypto
./task1
Task 2: Genesis Block Mining
Mines a genesis block (4 leading zeros).
bash
cd Question2/task2
gcc task2.c -o task2 -lssl -lcrypto
./task2
Task 3: Block Mining with Transactions
Mines blocks with user transactions, verifies blockchain.
bash
cd Question2/task3
gcc task3.c -o task3 -lssl -lcrypto
./task3
Task 4: Difficulty Adjustment
Adjusts mining difficulty (2–4), simulates mining.
bash
cd Question2/task4
gcc task4.c -o task4 -lssl -lcrypto
./task4
Notes
Question1 uses users.txt for input data.
Question2/task3 and task4 fixed for verification errors (Invalid genesis block hash!).


