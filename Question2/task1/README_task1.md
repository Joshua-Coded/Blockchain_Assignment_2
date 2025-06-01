## 📄 README.md – Task 1: Blockchain Structure & SHA-256 Hashing

### 🎯 Objective

To implement a basic blockchain structure in C, including:

- A `Block` structure containing:
  - Index
  - Timestamp
  - List of transactions (simplified to strings)
  - Previous block hash
  - Nonce
- SHA-256 hashing functionality to compute and verify block integrity

---

### 🧱 Components Implemented

| Component        | Description |
|------------------|-------------|
| `Block` struct   | Stores all relevant block data including index, timestamp, transaction, previous hash, and nonce |
| SHA-256 hashing  | Used to generate a unique cryptographic hash for each block |
| Genesis block    | First block in the chain initialized with default values |
| `calculate_block_hash()` | Function to serialize and hash block contents |

---

### 🔧 Technologies Used

- **Language**: C
- **Hashing Algorithm**: SHA-256
- **Library Used**: [TinySHA2](https://github.com/cathal-purcell/tinySHA2) — lightweight, public domain SHA-256 implementation

---

### 📁 File Structure

```
task1/
├── task1.c        ← Main program (includes SHA-256 + Block logic)
├── README.md      ← This file
```

---

### 🛠️ Compilation Instructions

```bash
gcc -o task1 task1.c
./task1
```

---

### ✅ Output Example

```
Genesis Block Hash: 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08
```

---

### 📌 Code Highlights

#### Block Structure

```c
typedef struct {
    int index;
    time_t timestamp;
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE];
    char previous_hash[HASH_SIZE * 2 + 1]; // Hex encoded
    int nonce;
} Block;
```

#### SHA-256 Hashing

Uses TinySHA2 to compute a secure hash from block contents:

```c
void calculate_block_hash(const Block* block, char* output_hash)
```

#### Genesis Block Initialization

```c
void create_genesis_block(Block* block)
```

---

### 🧪 Testing

- The program successfully creates and hashes a genesis block.
- Future tasks will extend this structure to support mining, proof-of-work, and difficulty adjustment.
