
# Account/Balance Transaction Simulator (C Implementation)

![Account Model](https://img.shields.io/badge/Model-Account/Balance-blue) 
![Language](https://img.shields.io/badge/Language-C-green)

A C program simulating Ethereum-style account-based transactions using named accounts (e.g., "Joshua") instead of cryptographic addresses.

## 🌟 Key Features
- 🏦 Traditional banking-style named accounts
- 💰 Real-time balance updates
- 🔄 Simple fund transfers between accounts
- 📊 Balance display before/after transactions
- 🛡️ Input validation and error handling

## 🚀 Quick Start
1. Create `users.txt`:
   ```text
   Joshua,50.0
   Favour,20.0
   King,30.0
   ```

2. Compile and run:
   ```bash
   gcc account_model_simulation.c -o account_sim
   ./account_sim
   ```

## 📋 Menu Options
1. **View Balances** - Shows all account balances
2. **Transfer Funds** - Transfer between named accounts
3. **Exit** - Quit the program

## 📝 Sample Transaction
```text
=== Account Balances ===
Joshua    | 50.00
Favour    | 20.00

Enter sender's name: Joshua
Enter receiver's name: Favour  
Enter amount: 30.00

🎉 Transferred 30.00 from Joshua to Favour

=== Updated Balances ===  
Joshua    | 20.00
Favour    | 50.00
```

## 📚 Learning Focus
- Account/Balance model vs UTXO
- State-based transactions
- Traditional banking parallels

## ⏰ Due Date: June 1, 2025
```
