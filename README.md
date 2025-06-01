# Blockchain Assignment 2

**Assignment 2-[F:A]** by Alana  
**Due:** June 1, 2025  
Implements blockchain transaction models (`Question1`) and mining tasks (`Question2`) in C.

## 📂 Directory Structure

```
.
├── Question1/
│   ├── task1/          # UTXO simulation (Bitcoin-like)
│   └── task2/          # Account/Balance simulation (Ethereum-like)
└── Question2/
    ├── task1/          # Basic blockchain setup
    ├── task2/          # Genesis block mining
    ├── task3/          # Block mining with transactions (fixed)
    └── task4/          # Difficulty adjustment
```

## 🛠 Prerequisites

- GCC compiler
- OpenSSL (for `Question2`):
  ```bash
  # macOS
  brew install openssl
  
  # Ubuntu/Debian
  sudo apt-get install libssl-dev
  ```

## Question 1: Transaction Models

### Task 1: UTXO Simulation
**Simulates UTXO-based transactions (Bitcoin-like model)**

```bash
cd Question1/task1
gcc utxo_simulation.c -o utxo_simulation
./utxo_simulation
```

### Task 2: Account Model Simulation  
**Simulates Account/Balance transactions (Ethereum-like model)**

```bash
cd Question1/task2
gcc account_model_simulation.c -o account_model_simulation
./account_model_simulation
```

## Question 2: Blockchain Mining

### Task 1: Blockchain Setup
**Basic blockchain structure implementation**

```bash
cd Question2/task1
gcc task1.c -o task1 -lssl -lcrypto
./task1
```

### Task 2: Genesis Block Mining  
**Mines genesis block with 4 leading zeros difficulty**

```bash
cd Question2/task2
gcc task2.c -o task2 -lssl -lcrypto
./task2
```

### Task 3: Block Mining with Transactions (Fixed)  
**Now properly verifies blockchain integrity**

```bash
cd Question2/task3
gcc task3.c -o task3 -lssl -lcrypto
./task3
```

### Task 4: Difficulty Adjustment  
**Dynamic difficulty adjustment (2-4 leading zeros)**

```bash
cd Question2/task4
gcc task4.c -o task4 -lssl -lcrypto
./task4
```

## 📝 Notes

1. **Input Data**:
   - `Question1` uses `users.txt` for input data
   - Format: `username,balance`

2. **Fixed Issues**:
   - Resolved "Invalid genesis block hash!" error in `task3`
   - Improved verification logic for all blocks
   - Added proper nonce handling during verification

3. **Color Coding**:
   - All programs use colored terminal output for better readability
   - Green = success, Yellow = warning, Red = error

4. **Verification**:
   - Blockchain verification now shows:
     - Expected vs actual hash values
     - Block-by-block validation status
     - Detailed error messages
```

