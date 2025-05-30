Account/Balance Transaction Simulator
====================================

Overview
--------
This C program simulates a basic Account/Balance model, similar to Ethereum's transaction system. It reads user accounts (names and initial balances) from `users.txt` and provides an interactive CLI with colorful prompts and feedback. Users can view account balances, perform fund transfers, and exit, with robust input validation and balance updates.

How the Code Works
-----------------
- **Data Structures**:
  - `Account` struct: Stores account holder's name and balance (float).
  - Global array: `account_list` (max 50 accounts).
- **Key Functions**:
  - `read_accounts_from_file()`: Loads accounts from `users.txt` (format: name,balance).
  - `find_account_index()`: Returns the index of an account by name, or -1 if not found.
  - `display_accounts()`: Prints all accounts and their balances in a table format.
  - `transferFunds(sender, receiver, amount)`: Validates and performs a fund transfer:
    - Checks for positive amount, distinct sender/receiver, valid users, and sufficient balance.
    - Updates sender's and receiver's balances.
    - Returns true on success, false on failure.
  - `main()`: Interactive menu to view balances, transfer funds, or exit.
- **Interactivity**:
  - ANSI color codes enhance readability (green for success, red for errors, yellow for prompts, cyan for tables).
  - Displays all accounts before transactions to guide input.
  - Emoji feedback (e.g., 🎉) for successful transactions.
  - Shows balances before and after each transaction.
  - Robust error handling for invalid names, amounts, or insufficient funds.
- **Logic**:
  - Accounts are loaded from `users.txt` at startup.
  - Transfers only proceed if the sender has enough balance and both users exist.
  - Balances are updated atomically to maintain consistency.

Running Guide
-------------
1. **Install a C Compiler**:
   - Linux: `sudo apt update && sudo apt install build-essential`
   - macOS: `xcode-select --install`
   - Windows: Install MinGW or use WSL with Ubuntu and GCC.
2. **Prepare `users.txt`**:
   - Create a file named `users.txt` in the same directory as `account_model_simulation.c`.
   - Add at least 3 accounts (name,balance per line, e.g.):
     ```
     Joshua,50.0
     Favour,20.0
     King,30.0
     Aaron,10.0
     ```
   - Ensure names are unique, < 20 characters, no spaces, and balances are non-negative.
3. **Compile the Program**:
   - Open a terminal in the directory with `account_model_simulation.c` and `users.txt`.
   - Run: `gcc account_model_simulation.c -o account_model_simulation`
   - This creates an executable (`account_model_simulation` or `account_model_simulation.exe` on Windows).
4. **Run the Program**:
   - Execute: `./account_model_simulation` (or `account_model_simulation.exe` on Windows).
   - If `users.txt` is missing or has fewer than 3 accounts, the program exits with an error.
5. **Interact with the CLI**:
   - Choose from the menu (1-3) to view balances, transfer funds, or exit.
   - For transactions, enter sender/receiver names (e.g., Joshua, Favour) and amount.
   - Balances are shown before and after each transaction.
6. **Troubleshooting**:
   - **"Cannot open users.txt"**: Ensure `users.txt` exists in the same directory.
   - **No colors**: Use a terminal supporting ANSI codes (e.g., Linux/macOS Terminal, Windows PowerShell).
   - **Invalid input errors**: Ensure names match `users.txt` exactly and amounts are positive.

Expected Behavior
-----------------
- The program loads accounts from `users.txt` and requires at least 3 valid accounts.
- Users can view all account balances or transfer funds between accounts.
- Transfers are only successful if:
  - Sender and receiver are valid users from `users.txt`.
  - Sender has sufficient balance.
  - Amount is positive, and sender/receiver are different.
- Balances are updated immediately, and results are displayed with clear feedback.

Sample Input/Output
------------------
$ gcc account_model_simulation.c -o account_model_simulation
$ ./account_model_simulation

=====================================
   Account/Balance Transaction Simulator
=====================================

=== Menu ===
1. View all account balances
2. Perform a transaction
3. Exit
Enter choice (1-3): 1

=== Account Balances ===
Name            | Balance
-------------------------
Joshua          | 50.00
Favour          | 20.00
King            | 30.00
Aaron           | 10.00

=== Menu ===
Enter choice (1-3): 2

=== Account Balances ===
Name            | Balance
-------------------------
Joshua          | 50.00
Favour          | 20.00
King            | 30.00
Aaron           | 10.00

Enter sender's name: Joshua
Enter receiver's name: Favour
Enter amount to transfer: 25.00

=== Balances Before Transaction ===
Name            | Balance
-------------------------
Joshua          | 50.00
Favour          | 20.00
King            | 30.00
Aaron           | 10.00

🎉 Transaction successful! 🎉
Transferred 25.00 from Joshua to Favour

=== Balances After Transaction ===
Name            | Balance
-------------------------
Joshua          | 25.00
Favour          | 45.00
King            | 30.00
Aaron           | 10.00

=== Menu ===
Enter choice (1-3): 2

=== Account Balances ===
Name            | Balance
-------------------------
Joshua          | 25.00
Favour          | 45.00
King            | 30.00
Aaron           | 10.00

Enter sender's name: Joshua
Enter receiver's name: King
Enter amount to transfer: 30.00

=== Balances Before Transaction ===
Name            | Balance
-------------------------
Joshua          | 25.00
Favour          | 45.00
King            | 30.00
Aaron           | 10.00

Error: Insufficient balance. Joshua has 25.00, needs 30.00

=== Menu ===
Enter choice (1-3): 3
Thank you for using the simulator! Goodbye.

Notes
-----
- User names in `users.txt` must be unique, < 20 characters, and without spaces.
- Balances in `users.txt` must be non-negative floats (e.g., 50.0).
- The program requires `users.txt` to exist with at least 3 valid accounts.
- ANSI color codes may not work in some terminals (e.g., Windows CMD without ANSI support).
- Maximum limit: 50 accounts.
