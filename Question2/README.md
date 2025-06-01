# Blockchain Mining Simulator 🌐

![C](https://img.shields.io/badge/Language-C-blue) ![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey) ![Status](https://img.shields.io/badge/Status-Complete-green) 🚀

A C-based blockchain mining simulator developed for **Question 2** of a blockchain assignment, implementing Tasks 1–4 to demonstrate the mechanics of blockchain mining**, including **Proof-of-Work (PoW)** and **block difficulty adjustment**. The project simulates a simplified blockchain with transactions involving users Joshua, Alana, Favour, and Aaron, reinforcing concepts from UTXO (Task 1) and Account/Balance (Task 2) models.

## 📋 Project Overview

This project builds a blockchain mining simulator in C, progressing through four tasks to create a fully functional system. It features:

- **Task 1**: Defines a `Block` structure and a simplified SHA-256 hash function, creating a genesis block with transactions.
- **Task 2**: Implements Proof of Work (PoW) to mine the genesis block, requiring a hash with 2 leading zeros.
- **Task 3**: Simulates mining multiple blocks with previous hash references and verifies blockchain integrity.
- **Task 4**: Adds adjustable difficulty (1–4 leading zeros) and measures mining time, with an interactive CLI menu.

**Key Features**:
- **Blockchain Structure**: Blocks with `index`, `timestamp`, `transactions`, `prev_hash`, `nonce`, and `hash`.
- **Simplified Hashing**: Emulates SHA-256 for educational purposes, ensuring portability without external libraries.
- **Interactive CLI**: Uses ANSI colors (green for success, red for errors, yellow for prompts, cyan for output) and emojis (🎉, ✅) for mined blocks and verification.
- **Transaction Data**: Reads from `transactions.txt`, supporting users Joshua, Alana, Favour, King, and Aaron.
- **Verification**: Ensures blockchain immutability with hash link checks.
- **Difficulty Analysis**: Measures computational effort via mining time.

## 📁 Project Structure

The project is organized to separate each task’s implementation while sharing a common resources transaction file (`transactions.txt`):

plaintext
blockchain_mining_simulator/
├── task1/                  # Task 1: Blockchain environment setup
│   ├── blockchain_task1.c
│   ├── README_task1.md├── task2/                # Task 2: Proof of Work implementation
│   ├── blockchain_task2.c
│   ├── README_task2.md
├── task3/                # Task 3: Block mining simulation
│   ├── blockchain_task3.c
│   ├── README_task3.md├── task4/                # Task 4: Difficulty adjustment and analysis
│   ├── blockchain_task4.c
│   ├── README_task4.md
├── transactions.txt     # Shared transaction data
└── README.md             # Project overview (this file)
🚀 Getting Started
Prerequisites
C Compiler:
macOS: Install Xcode Command Line Tools:
bash
xcode-selectors --install
Linux: Install build essentials:
bash
 sudo apt-get update && sudo apt-get install build-essential
Windows: Use MinGW or WSL with Ubuntu/GCC.
transactions.txt: Contains transaction data, placed in the root directory.
Setup Instructions
Clone or Create the Project:
Create a GitHub repository (e.g., BlockchainMiningSimulator) or local directory:
bash
mkdir blockchain_mining_simulator
cd blockchain_mining_simulator
Initialize a Git repository (optional):
bash
git init
Create transactions.txt:
Place in blockchain_mining_simulator/ with the following content:
text
Joshua sends 10 to Favour
Favour sends 5 to Alana
Alana sends 3 to Aaron
Aaron sends 2 to Joshua
Format: One transaction per line, < 100 characters.
Compile and Run a Task:
For each task (replace X with 1–4):
bash
cd taskX
gcc blockchain_taskX.c -o blockchain_taskX
../blockchain_taskX
Ensure transactions.txt is in the root directory (blockchain_mining_simulator/).
Expected Behavior:
Task 1: Creates and displays a genesis block.
Task 2: Mines the genesis block with PoW (2 leading zeros).
Task 3: Mines two blocks and verifies the blockchain.
Task 4: Provides an interactive menu to mine blocks with adjustable difficulty and timing.
Troubleshooting
“Cannot open transactions.txt”: Verify transactions.txt is in blockchain_mining_simulator/.
No colors/emojis: Use an ANSI-compatible terminal (e.g., macOS Terminal).
Compilation errors: Ensure GCC is installed and up-to-date.
Nonce overflow: Occurs with high difficulty; Task 4 limits difficulty to 1–4.
📄 Tasks Overview
Task
Objective
Key Features
Task 1
Set up blockchain environment
Block struct, simplified SHA-256, genesis block creation
Task 2
Implement Proof of Work
PoW with 2 leading zeros, nonce iteration
Task 3
Simulate block mining
Mines multiple blocks, verifies hash links
Task 4
Adjust difficulty
User-specified difficulty (1–4), mining time analysis
Each task builds on the previous one, with code copied and enhanced as follows:
Task 2: Copies Task 1, adds is_valid_hash and proof_of_work.
Task 3: Copies Task 2, adds mine_block and verify_blockchain.
Task 4: Copies Task 3, adds timing and interactive menu.
📊 Difficulty Analysis (Task 4)
Task 4 measures the impact of difficulty (number of leading zeros in the hash) on mining time:
Difficulty
Leading Zeros
Approx. Time
Effort
1
1 zero
~0.01s
Minimal
2
2 zeros
~0.05s
Moderate
3
3 zeros
~0.12s
Noticeable
4
4 zeros
~0.50s
Significant
Observation: Higher difficulty increases nonce iterations, simulating real-world mining computational effort (e.g., Bitcoin’s dynamic difficulty).
Implication: Demonstrates how PoW secures the blockchain by requiring computational work.
🛑 Challenges and Solutions
SHA-256 Implementation:
Challenge: Setting up OpenSSL on macOS is complex for educational purposes.
Solution: Used a simplified hash function (ASCII sum modulo large number) to emulate SHA-256, formatted as a 64-character hex string.
Nonce Overflow:
Challenge: High difficulty could cause nonce wraparound.
Solution: Added overflow check in proof_of_work and limited difficulty to 1–4.
File Access:
Challenge: Accessing transactions.txt from task subdirectories.
Solution: Used relative path ../transactions.txt in code.
Interactivity:
Challenge: Ensuring user-friendly output.
Solution: Added ANSI colors (green, red, yellow, cyan) and emojis (🎉, ✅) for clarity and engagement.
📚 Learning Outcomes
Blockchain Mining: Understands the role of PoW in securing blockchains through computational puzzles.
Proof of Work: Grasps nonce iteration and difficulty’s impact on mining effort.
Blockchain Structure: Implements linked blocks with hashes, ensuring immutability.
C Programming: Applies structs, file I/O, dynamic memory, and timing functions.
