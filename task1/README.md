
UTXO Transaction Simulator
C Platform Status
A C program simulating Bitcoin’s Unspent Transaction Output (UTXO) model. It reads user names from users.txt, generates unique addresses (e.g., ADDR1), and offers an interactive CLI to manage transactions, view UTXOs, and explore user-address mappings. Designed for Task 1 of a blockchain assignment, it emphasizes data integrity and immutability with a user-friendly interface.
📋 Overview
This program mimics Bitcoin’s UTXO-based transaction system, allowing users to:
View unspent and all UTXOs (spent/unspent).
List users and their generated addresses.
Perform transactions using addresses.
Exit with clear feedback.
Key features:
Automatic Address Generation: Assigns unique addresses (e.g., ADDR1 for Joshua).
Interactive CLI: Colorful prompts (green, red, yellow, cyan) and emojis (🎉).
Robust Validation: Ensures valid addresses, amounts, and UTXO selections.
Dynamic UTXO Management: Tracks spent/unspent outputs.
🛠️ How It Works
Data Structures
UTXO Struct:
txid: Transaction ID (e.g., TX1).
address: Receiver’s address (e.g., ADDR1).
amount: Transaction value (float, e.g., 50.0).
spent: Boolean flag for spent status.
User Struct:
name: User name (e.g., Joshua).
address: Generated address (e.g., ADDR1).
Global Arrays:
utxo_list: Up to 100 UTXOs.
user_list: Up to 50 users.
Core Functions
read_users_from_file(): Loads names from users.txt and assigns addresses.
generate_address(): Creates unique addresses (e.g., ADDR1, ADDR2).
is_valid_address(): Validates addresses against user list.
get_user_name_by_address(): Maps addresses to names for display.
display_users(): Shows user-address table.
initialize_utxos(): Sets initial UTXOs (e.g., ADDR1: 50.0, 30.0; ADDR2: 20.0).
display_utxos(): Lists unspent UTXOs.
display_all_utxos(): Lists all UTXOs, with spent ones in red.
generate_txid(): Produces unique TXIDs (e.g., TX4).
perform_transaction(): Manages transactions:
Prompts for sender/receiver addresses and amount.
Validates inputs and funds.
Selects UTXOs, marks them spent, and creates new UTXOs.
main(): Runs an interactive menu loop.
Interactivity
Colors: Green (success), red (errors/spent UTXOs), yellow (prompts), cyan (tables).
Emojis: 🎉 for successful transactions.
User Guidance: Displays user-address mappings before transactions.
Error Handling: Catches invalid addresses, negative amounts, and insufficient funds.
🚀 Running the Program
Prerequisites
C Compiler:
macOS: Install Xcode Command Line Tools:
bash
xcode-select --install
Linux: Install build essentials:
bash
sudo apt update && sudo apt install build-essential
Windows: Use MinGW or WSL with Ubuntu/GCC.
users.txt: A text file with user names (one per line).
Setup
Create users.txt:
Place in the same directory as utxo_simulation.c.
Example content:
text
Joshua
Favour
King
Aaron
Rules: Unique names, < 20 characters, no spaces or trailing newlines.
Compile:
In a terminal, navigate to the directory and run:
bash
gcc utxo_simulation.c -o utxo_simulation
Run:
Execute:
bash
./utxo_simulation
If users.txt is missing, the program exits with an error.
Interact:
Menu options (1-5):
View unspent UTXOs.
View all UTXOs.
View users and addresses.
Perform a transaction (use addresses like ADDR1).
Exit.
Troubleshooting
“Cannot open users.txt”: Ensure users.txt exists in the directory.
No colors: Use an ANSI-compatible terminal (e.g., macOS Terminal).
Invalid address: Enter addresses exactly as shown (e.g., ADDR1).
📄 Sample Input/Output
bash
$ gcc utxo_simulation.c -o utxo_simulation
$ ./utxo_simulation

=====================================
   UTXO-Based Transaction Simulator
=====================================

=== Menu ===
1. View unspent UTXOs
2. View all UTXOs (spent and unspent)
3. View all users and addresses
4. Perform a transaction
5. Exit
Enter choice (1-5): 3

=== Available Users and Addresses ===
Name            | Address
----------------|--------
Joshua          | ADDR1
Favour          | ADDR2
King            | ADDR3
Aaron           | ADDR4

=== Menu ===
Enter choice (1-5): 1

=== Unspent UTXOs ===
Index | TXID | User (Address)       | Amount | Spent
------|------|----------------------|--------|------
0     | TX1  | Joshua (ADDR1)       | 50.00  | No
1     | TX2  | Joshua (ADDR1)       | 30.00  | No
2     | TX3  | Favour (ADDR2)       | 20.00  | No

=== Menu ===
Enter choice (1-5): 4

=== Available Users and Addresses ===
Name            | Address
----------------|--------
Joshua          | ADDR1
Favour          | ADDR2
King            | ADDR3
Aaron           | ADDR4

Enter sender's address (e.g., ADDR1): ADDR1
Enter receiver's address (e.g., ADDR2): ADDR2
Enter amount to transfer: 60.00

Available UTXOs for Joshua (ADDR1):
Index | TXID | Amount
------|------|-------
0     | TX1  | 50.00
1     | TX2  | 30.00

Enter indices of UTXOs to spend (enter -1 to finish):
Enter UTXO index: 0
Enter UTXO index: 1
Enter UTXO index: -1

🎉 Transaction successful! 🎉
Transferred 60.00 from Joshua (ADDR1) to Favour (ADDR2)
Change of 20.00 returned to Joshua (ADDR1)

=== Unspent UTXOs ===
Index | TXID | User (Address)       | Amount | Spent
------|------|----------------------|--------|------
2     | TX3  | Favour (ADDR2)       | 20.00  | No
3     | TX4  | Favour (ADDR2)       | 60.00  | No
4     | TX5  | Joshua (ADDR1)       | 20.00  | No

=== Menu ===
Enter choice (1-5): 2

=== All UTXOs (Spent and Unspent) ===
Index | TXID | User (Address)       | Amount | Spent
------|------|----------------------|--------|------
0     | TX1  | Joshua (ADDR1)       | 50.00  | Yes
1     | TX2  | Joshua (ADDR1)       | 30.00  | Yes
2     | TX3  | Favour (ADDR2)       | 20.00  | No
3     | TX4  | Favour (ADDR2)       | 60.00  | No
4     | TX5  | Joshua (ADDR1)       | 20.00  | No

=== Menu ===
Enter choice (1-5): 5
Thank you for using the simulator! Goodbye.
🔧 Setup Instructions
Create users.txt with at least 2 names (see above).
Compile:
bash
gcc utxo_simulation.c -o utxo_simulation
Run:
bash
./utxo_simulation
Follow the menu prompts.
ℹ️ Notes
User Names: Must be unique, < 20 characters, no spaces in users.txt.
Addresses: Automatically generated (e.g., ADDR1).
Spent UTXOs: Highlighted in red for clarity.
ANSI Colors: May not work in some terminals (e.g., Windows CMD).
Limits: 100 UTXOs, 50 users.
TXIDs: Sequential (TX1, TX2, etc.).
Submission: Due June 5, 2025, 11:59 PM. Zip as YourFullName_UTXO_Blockchain.zip.
📚 Learning Outcomes
UTXO Model: Understands Bitcoin’s transaction system, with addresses mimicking public keys.
C Programming: Implements structs, arrays, file I/O, and error handling.
Blockchain Concepts: Demonstrates data integrity (spent flags) and immutability (fixed UTXOs).
