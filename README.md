# Blockchain Assignment 2 README

Assignment 2-[F:A] by Alana, due June 1, 2025. Implements blockchain transaction models (`Question1`) and mining tasks (`Question2`) in C.

## Directory Structure
- `Question1`: UTXO and Account model simulations (`task1`, `task2`).
- `Question2`: Blockchain mining tasks (`task1`, `task2`, `task3`, `task4`).

## Prerequisites
- GCC compiler
- OpenSSL (for `Question2`): `brew install openssl` (macOS)

## Question 1: Transaction Models

### Task 1: UTXO Simulation
- **Description**: Simulates UTXO-based transactions (Bitcoin-like).
- **Run**:
  ```bash
  cd Question1/task1
  gcc utxo_simulation.c -o utxo_simulation
  ./utxo_simulation
Task 2: Account Model Simulation
Description: Simulates Account/Balance transactions (Ethereum-like).
Run:
bash
cd Question1/task2
gcc account_model_simulation.c -o account_model_simulation
./account_model_simulation
Question 2: Blockchain Mining
Task 1: Blockchain Setup
Description: Sets up a basic blockchain.
Run:
bash
cd Question2/task1
gcc task1.c -o task1 -lssl -lcrypto
./task1
Task 2: Genesis Block Mining
Description: Mines a genesis block (4 leading zeros).
Run:
bash
cd Question2/task2
gcc task2.c -o task2 -lssl -lcrypto
./task2
Task 3: Block Mining with Transactions
Description: Mines blocks with user transactions, verifies blockchain.
Run:
bash
cd Question2/task3
gcc task3.c -o task3 -lssl -lcrypto
./task3
Task 4: Difficulty Adjustment
Description: Adjusts mining difficulty (2–4), simulates mining.
Run:
bash
cd Question2/task4
gcc task4.c -o task4 -lssl -lcrypto
./task4
Notes
Question1 uses users.txt for input data.
Question2/task3 and task4 fixed for verification errors.
