# UTXO Transaction Simulator (C Implementation)

![Screenshot](./Screen%20Shot%202025-05-31%20at%2012.59.20%20AM.png) 
*Visual representation of UTXO transactions*

A C program simulating Bitcoin's Unspent Transaction Output (UTXO) model with an interactive CLI interface, designed for educational purposes in blockchain technology.

## 🌟 Key Features

- 🏷️ Automatic address generation (ADDR1, ADDR2,...)
- 💰 UTXO management with spent/unspent tracking
- 🔄 Transaction validation and processing
- 🎨 Colorful CLI interface with ANSI colors
- 📊 Comprehensive user and UTXO displays
- 🛡️ Robust input validation

## 📦 Prerequisites

- C compiler (GCC recommended)
- ANSI-compatible terminal
- Basic understanding of UTXO model

## 🛠️ Installation

1. Create `users.txt` in the project directory:
   ```bash
   echo -e "Joshua\nFavour\nKing\nAaron" > users.txt
   ```

2. Compile the program:
   ```bash
   gcc utxo_simulation.c -o utxo_simulation
   ```

3. Run the executable:
   ```bash
   ./utxo_simulation
   ```

## 🖥️ Usage

### Main Menu Options

| Option | Description                          |
|--------|--------------------------------------|
| 1      | View unspent UTXOs                   |
| 2      | View all UTXOs (spent + unspent)     |
| 3      | View users and addresses             |
| 4      | Perform a transaction                |
| 5      | Exit program                         |

### Sample Transaction Flow

```text
=== Menu ===
Enter choice (1-5): 4

Available Users:
Name    | Address
--------|--------
Joshua  | ADDR1
Favour  | ADDR2

Enter sender's address: ADDR1
Enter receiver's address: ADDR2  
Enter amount: 60.00

Available UTXOs:
Index | Amount
------|-------
0     | 50.00
1     | 30.00

Select UTXOs (enter -1 to finish):
> 0
> 1
> -1

🎉 Success! Transferred 60.00 to ADDR2
```

## 📚 Technical Documentation

### Data Structures

```c
// UTXO representation
struct UTXO {
    char txid[10];    // Transaction ID
    char address[10]; // Owner address  
    float amount;     // BTC amount
    int spent;        // 0=unspent, 1=spent
};

// User information
struct User {
    char name[20];    // User name
    char address[10]; // Generated address
};
```

### Core Functions

| Function                     | Description                          |
|------------------------------|--------------------------------------|
| `read_users_from_file()`     | Loads users from users.txt           |
| `generate_address()`         | Creates unique addresses             |
| `validate_transaction()`     | Checks transaction validity          |
| `display_utxos()`            | Shows UTXO table                     |
| `perform_transaction()`      | Handles transaction logic            |

## 🚨 Limitations

- Maximum 100 UTXOs
- Maximum 50 users
- No persistent storage (RAM only)
- Basic sequential TXID generation

## 📜 License

Educational use only - Created for Blockchain Course Assignment

## 📅 Due Date

**Submission Deadline**: June 1, 2025 @ 11:59 PM

## 🙋 Support

For issues, please contact:
- [j.alana@alustudent.com]
- [African Leadership University]
