# Blockchain Assignment 2 - Mining Simulator 🌐

![C](https://img.shields.io/badge/Language-C-blue) 
![OpenSSL](https://img.shields.io/badge/Requires-OpenSSL-green)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)

**Assignment 2-[F:A]** by Alana  
**Due:** June 1, 2025  
Implements blockchain mining tasks (`Question2`) in C with Proof-of-Work (PoW) and difficulty adjustment.

## 📂 Directory Structure

```
Question2/
├── task1/          # Basic blockchain setup
├── task2/          # Genesis block mining (4 leading zeros)
├── task3/          # Block mining with transactions (fixed)
└── task4/          # Dynamic difficulty adjustment (2-4 zeros)
```

## 🛠 Prerequisites

- **GCC compiler**
- **OpenSSL**:
  ```bash
  # macOS
  brew install openssl
  
  # Ubuntu/Debian
  sudo apt-get install libssl-dev
  ```

## 🚀 Tasks Overview

| Task | Objective | Key Features | Compilation Command |
|------|-----------|--------------|----------------------|
| 1 | Blockchain setup | Block structure, basic hashing | `gcc task1.c -o task1 -lssl -lcrypto` |
| 2 | Genesis block | PoW with 4 leading zeros | `gcc task2.c -o task2 -lssl -lcrypto` |
| 3 | Transaction mining | Multi-block verification | `gcc task3.c -o task3 -lssl -lcrypto` |
| 4 | Difficulty adjustment | Interactive menu, timing analysis | `gcc task4.c -o task4 -lssl -lcrypto` |

## 💻 Running the Tasks

### Task 1: Blockchain Setup
```bash
cd Question2/task1
gcc task1.c -o task1 -lssl -lcrypto
./task1
```

### Task 2: Genesis Block Mining
```bash
cd Question2/task2
gcc task2.c -o task2 -lssl -lcrypto
./task2
```

### Task 3: Transaction Mining (Fixed)
```bash
cd Question2/task3
gcc task3.c -o task3 -lssl -lcrypto
./task3
```

### Task 4: Difficulty Adjustment
```bash
cd Question2/task4
gcc task4.c -o task4 -lssl -lcrypto
./task4
```

## 📊 Difficulty Analysis

| Difficulty | Leading Zeros | Avg. Mining Time | Effort Level |
|------------|---------------|------------------|--------------|
| 2 | 2 | ~0.05s | Moderate |
| 3 | 3 | ~0.12s | Noticeable |
| 4 | 4 | ~0.50s | Significant |

## 🛠️ Fixed Issues

- Resolved "Invalid genesis block hash!" error in Task 3
- Improved nonce handling during verification
- Enhanced hash comparison logic
- Added detailed verification output:
  - Expected vs actual hash values
  - Block-by-block validation status

## ✨ Features

- **Color-coded output** (Green=success, Yellow=warning, Red=error)
- **Interactive menus** in Task 4
- **Real-time mining feedback**
- **Comprehensive verification**
- **Portable** (macOS/Linux/Windows with WSL)

## 📝 Notes

1. All tasks share the same core blockchain structure
2. Each task builds upon the previous one
3. Uses standard OpenSSL for SHA-256 hashing
4. Includes emoji indicators for better UX (🎉, ✅, ⚠️)

