UTXO-Based Transaction Simulator
===============================

Overview
--------
This C program simulates a simplified UTXO (Unspent Transaction Output) model, mimicking Bitcoin's transaction system. It reads user names from `users.txt` and provides an interactive CLI with colorful prompts and feedback. Users can view UTXOs, list available users, perform transactions, and exit, with robust input validation and dynamic UTXO management.

How the Code Works
-----------------
- **Data Structures**:
  - `UTXO` struct: Stores transaction ID (`txid`), address, amount, and `spent` flag.
  - `User` struct: Stores user names loaded from `users.txt`.
  - Global arrays: `utxo_list` (max 100 UTXOs) and `user_list` (max 50 users).
- **Key Functions**:
  - `read_users_from_file()`: Loads user names from `users.txt` into `user_list`.
  - `is_valid_user()`: Checks if a given name is in the user list.
  - `display_users()`: Shows all available users.
  - `initialize_utxos()`: Sets up initial UTXOs for the first two users (e.g., 50.0, 30.0 for user1; 20.0 for user2).
  - `display_utxos()`: Prints unspent UTXOs in a table format.
  - `generate_txid()`: Generates unique transaction IDs (e.g., TX4, TX5).
  - `perform_transaction()`: Handles transaction logic:
    - Lists users and prompts for sender, receiver, and amount.
    - Validates sender/receiver against `users.txt` and checks sufficient funds.
    - Allows selection of UTXOs by index, marks them as spent, creates new UTXOs for receiver and change.
    - Provides colorful feedback on success or errors.
  - `main()`: Interactive menu with options to view UTXOs, users, transact, or exit.
- **Interactivity**:
  - ANSI color codes enhance readability (green for success, red for errors, yellow for prompts, cyan for tables).
  - Displays users before transactions to guide input.
  - Emoji feedback (e.g., 🎉) and clear prompts improve user experience.
  - Robust error handling for invalid users, amounts, or UTXO indices.

Running Guide
-------------
1. **Install a C Compiler**:
   - Linux: Install GCC with `sudo apt update && sudo apt install build-essential`.
   - macOS: Install Xcode Command Line Tools with `xcode-select --install`.
   - Windows: Install MinGW or use WSL with Ubuntu and GCC.
2. **Prepare `users.txt`**:
   - Create a file named `users.txt` in the same directory as `utxo_simulation.c`.
   - Add user names (one per line, e.g.):
     ```
     Joshua
     Favour
     King
     Aaron
     ```
   - Ensure names are unique, < 20 characters, and have no spaces or trailing newlines.
3. **Compile the Program**:
   - Open a terminal in the directory containing `utxo_simulation.c` and `users.txt`.
   - Run: `gcc utxo_simulation.c -o utxo_simulation`
   - This creates an executable (`utxo_simulation` or `utxo_simulation.exe` on Windows).
4. **Run the Program**:
   - Execute: `./utxo_simulation` (or `utxo_simulation.exe` on Windows).
   - If `users.txt` is missing or empty, the program will exit with an error.
5. **Interact with the CLI**:
   - Choose from the menu (1-4) to view UTXOs, users, perform transactions, or exit.
   - For transactions, select sender/receiver from the listed users, enter an amount, and choose UTXOs by index.
6. **Troubleshooting**:
   - **"Cannot open users.txt"**: Ensure `users.txt` exists in the same directory.
   - **No colors**: Use a terminal supporting ANSI codes (e.g., Linux/macOS terminal, Windows PowerShell).
   - **Invalid input errors**: Ensure user names match `users.txt` exactly and UTXO indices are valid.

Sample Input/Output
------------------
$ gcc utxo_simulation.c -o utxo_simulation
$ ./utxo_simulation

=====================================
   UTXO-Based Transaction Simulator
=====================================

=== Menu ===
1. View all unspent UTXOs
2. View all users
3. Perform a transaction
4. Exit
Enter choice (1-4): 2

=== Available Users ===
1. Joshua
2. Favour
3. King
4. Aaron

=== Menu ===
Enter choice (1-4): 1

=== Available UTXOs ===
Index | TXID | Address | Amount | Spent
-------------------------------------
0     | TX1  | Joshua  | 50.00 | No
1     | TX2  | Joshua  | 30.00 | No
2     | TX3  | Favour  | 20.00 | No

=== Menu ===
Enter choice (1-4): 3

=== Available Users ===
1. Joshua
2. Favour
3. King
4. Aaron

Enter sender's name: Joshua
Enter receiver's name: Favour
Enter amount to transfer: 60.00

Joshua's Available UTXOs:
Index | TXID | Amount
---------------------
0     | TX1  | 50.00
1     | TX2  | 30.00

Enter indices of UTXOs to spend (enter -1 to finish):
Enter UTXO index: 0
Enter UTXO index: 1
Enter UTXO index: -1

🎉 Transaction successful! 🎉
Transferred 60.00 from Joshua to Favour
Change of 20.00 returned to Joshua

=== Available UTXOs ===
Index | TXID | Address | Amount | Spent
-------------------------------------
2     | TX3  | Favour  | 20.00 | No
3     | TX4  | Favour  | 60.00 | No
4     | TX5  | Joshua  | 20.00 | No

=== Menu ===
Enter choice (1-4): 4
Thank you for using the simulator! Goodbye.

Setup Instructions
------------------
1. Ensure `users.txt` exists in the same directory with at least 2 user names (one per line, as shown above).
2. Compile: `gcc utxo_simulation.c -o utxo_simulation`
3. Run: `./utxo_simulation`
4. Follow the menu prompts to interact.

Notes
-----
- User names in `users.txt` must be unique, < 20 characters, and without spaces.
- The program requires `users.txt` to exist and contain valid names.
- ANSI color codes may not work in some terminals (e.g., Windows CMD without ANSI support).
- Maximum limits: 100 UTXOs, 50 users.
- Transaction IDs are sequential (TX1, TX2, etc.).
