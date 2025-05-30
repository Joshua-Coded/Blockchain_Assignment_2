
UTXO-Based Transaction Simulator
Overview
This C program simulates a simplified Unspent Transaction Output (UTXO) model, mimicking Bitcoin's transaction system. It reads user names from users.txt, automatically generates unique addresses for each user (e.g., ADDR1), and provides an interactive command-line interface (CLI) with colorful prompts and feedback. Users can:
View unspent UTXOs.
View all UTXOs (spent and unspent).
View user-address mappings.
Perform transactions using addresses.
Exit the program.
The program includes robust input validation and dynamic UTXO management, meeting the requirements of Task 1 while enhancing realism with address-based transactions.
How the Code Works
Data Structures
UTXO Struct:
Stores transaction ID (txid), address (e.g., ADDR1), amount, and spent flag.
User Struct:
Stores user name (e.g., Joshua) and generated address (e.g., ADDR1).
Global Arrays:
utxo_list: Maximum 100 UTXOs.
user_list: Maximum 50 users.
Key Functions
read_users_from_file():
Loads user names from users.txt and assigns unique addresses.
generate_address():
Creates addresses like ADDR1, ADDR2 for each user.
is_valid_address():
Checks if an address belongs to a user.
get_user_name_by_address():
Retrieves user name for an address for display purposes.
display_users():
Shows user names and their addresses in a table.
initialize_utxos():
Sets up initial UTXOs for the first two users' addresses (e.g., 50.0, 30.0 for ADDR1; 20.0 for ADDR2).
display_utxos():
Prints unspent UTXOs with user names and addresses.
display_all_utxos():
Prints all UTXOs, with spent UTXOs highlighted in red.
generate_txid():
Generates unique transaction IDs (e.g., TX4, TX5).
perform_transaction():
Prompts for sender/receiver addresses and amount.
Validates addresses and checks sufficient funds.
Allows selection of UTXOs by index, marks them as spent, and creates new UTXOs for the receiver and change.
Provides colorful feedback with user names and addresses.
main():
Interactive menu with options to view UTXOs, users, transact, or exit.
Interactivity
ANSI Color Codes: Green for success, red for errors/spent UTXOs, yellow for prompts, cyan for tables.
User-Address Mappings: Displayed before transactions to guide input.
Emoji Feedback: Uses 🎉 for successful transactions.
Error Handling: Validates addresses, amounts, and UTXO indices.
Running Guide
Install a C Compiler:
macOS: Install Xcode Command Line Tools with:
bash
xcode-select --install
Linux: Install build essentials:
bash
sudo apt update && sudo apt install build-essential
Windows: Install MinGW or use WSL with Ubuntu and GCC.
Prepare users.txt:
Create a file named users.txt in the same directory as utxo_simulation.c.
Add at least 2 user names (one per line), e.g.:
Joshua
Favour
King
Aaron
Ensure names are unique, < 20 characters, and have no spaces or trailing newlines.
Compile the Program:
Open a terminal in the directory with utxo_simulation.c and users.txt.
Run:
bash
gcc utxo_simulation.c -o utxo_simulation
This creates an executable (utxo_simulation).
Run the Program:
Execute:
bash
./utxo_simulation
If users.txt is missing or empty, the program exits with an error.
Interact with the CLI:
Choose from the menu (1-5) to view unspent UTXOs, all UTXOs, users/addresses, perform transactions, or exit.
For transactions, enter sender/receiver addresses (e.g., ADDR1, ADDR2) and amount.
Troubleshooting:
"Cannot open users.txt": Ensure users.txt exists in the same directory.
No colors: Use a terminal supporting ANSI codes (e.g., macOS Terminal, Linux terminal, Windows PowerShell).
Invalid address errors: Ensure addresses match those shown in the user list (e.g., ADDR1).
Sample Input/Output
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
------------------------- 
Joshua          | ADDR1
Favour          | ADDR2
King            | ADDR3
Aaron           | ADDR4

=== Menu ===
Enter choice (1-5): 1

=== Unspent UTXOs ===
Index | TXID | User (Address)       | Amount | Spent
----------------------------------------------- 
0     | TX1  | Joshua (ADDR1)       | 50.00 | No
1     | TX2  | Joshua (ADDR1)       | 30.00 | No
2     | TX3  | Favour (ADDR2)       | 20.00 | No

=== Menu ===
Enter choice (1-5): 4

=== Available Users and Addresses ===
Name            | Address
------------------------- 
Joshua          | ADDR1
Favour          | ADDR2
King            | ADDR3
Aaron           | ADDR4

Enter sender's address (e.g., ADDR1): ADDR1
Enter receiver's address (e.g., ADDR2): ADDR2
Enter amount to transfer: 60.00

Available UTXOs for Joshua (ADDR1):
Index | TXID | Amount
---------------------
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
----------------------------------------------- 
2     | TX3  | Favour (ADDR2)       | 20.00 | No
3     | TX4  | Favour (ADDR2)       | 60.00 | No
4     | TX5  | Joshua (ADDR1)       | 20.00 | No

=== Menu ===
Enter choice (1-5): 2

=== All UTXOs (Spent and Unspent) ===
Index | TXID | User (Address)       | Amount | Spent
----------------------------------------------- 
0     | TX1  | Joshua (ADDR1)       | 50.00 | Yes
1     | TX2  | Joshua (ADDR1)       | 30.00 | Yes
2     | TX3  | Favour (ADDR2)       | 20.00 | No
3     | TX4  | Favour (ADDR2)       | 60.00 | No
4     | TX5  | Joshua (ADDR1)       | 20.00 | No

=== Menu ===
Enter choice (1-5): 5
Thank you for using the simulator! Goodbye.
Setup Instructions
Ensure users.txt exists with at least 2 user names (one per line, as shown above).
Compile:
bash
gcc utxo_simulation.c -o utxo_simulation
Run:
bash
./utxo_simulation
Follow the menu prompts to interact.
