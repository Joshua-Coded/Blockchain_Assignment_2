# 🏦 Account/Balance Transaction Simulator  

[![Blockchain Model](https://img.shields.io/badge/Model-Account%2FBalance-1e90ff?style=for-the-badge&logo=ethereum)](https://ethereum.org/en/developers/docs/accounts/)
[![Language](https://img.shields.io/badge/C-17%2B%20Years-00599C?style=for-the-badge&logo=c)](https://en.cppreference.com/w/c)
[![Platform](https://img.shields.io/badge/macOS%20%26%20Linux-Compatible-999999?style=for-the-badge&logo=apple)](https://www.apple.com/macos/)
[![Status](https://img.shields.io/badge/Status-Production%20Ready-brightgreen?style=for-the-badge)]()

[![Animated Header](https://readme-typing-svg.demolab.com?font=Fira+Code&weight=600&size=24&pause=1000&color=1E90FF&width=435&lines=Banking-style+Transactions;Ethereum-inspired+Model;Simple+but+Powerful)](https://git.io/typing-svg)

## 🌟 Key Features

| Feature | Description | Tech Spec |
|---------|-------------|-----------|
| **Named Accounts** | Human-readable names (Joshua, Favour) | `struct Account { char name[20]; float balance; }` |
| **Real-time Balances** | Instant balance updates after transactions | ANSI-colored output |
| **Secure Transfers** | Validation for overdrafts/invalid inputs | SHA-256 checksum |
| **User-Friendly CLI** | Interactive menu system | ✅ Color prompts<br>✅ Emoji feedback |

```c
// Core Transaction Logic
bool transferFunds(const char* sender, const char* receiver, float amount) {
    // Input validation
    if (amount <= 0) return false;
    
    // Balance check
    if (sender_balance < amount) return false;
    
    // Execute transfer
    sender_balance -= amount;
    receiver_balance += amount;
    return true;
}
```

## 🚀 Quick Start

### Prerequisites
```bash
# macOS
xcode-select --install

# Linux
sudo apt install build-essential
```

### Installation
1. Create `users.txt`:
   ```text
   Joshua,100.0
   Favour,50.0
   King,75.0
   ```
2. Compile & Run:
   ```bash
   gcc account_simulator.c -o bank_sim && ./bank_sim
   ```

## 📚 Usage Guide

### Step-by-Step Flow
1. **Launch Program**  
   ```text
   =====================================
      Account/Balance Transaction Simulator  
   =====================================
   ```

2. **View Balances** (Option 1)  
   ```text
   === Account Balances ===
   Name      | Balance
   ----------|---------
   Joshua    | 100.00
   Favour    | 50.00
   ```

3. **Transfer Funds** (Option 2)  
   ```text
   Enter sender's name: Joshua
   Enter receiver's name: Favour  
   Enter amount: 25.50
   ```

4. **Confirm Transaction**  
   ```text
   🎉 Success! Transferred 25.50 from Joshua to Favour
   Updated Balances:
   Joshua    | 74.50
   Favour    | 75.50
   ```

## 🧠 Learning Outcomes

### Core Concepts Demonstrated
| Concept | Implementation | Real-World Parallel |
|---------|----------------|---------------------|
| **State Management** | Global balance updates | Bank account ledgers |
| **Transaction Validation** | Amount/sender checks | Fraud prevention |
| **Account Model** | Named accounts | Traditional banking |

```diff
+ Key Differentiator from UTXO:
- UTXO: Tracks transaction outputs (like cash)
+ Account Model: Tracks balances (like bank accounts)
```

## ⚠️ Troubleshooting

| Issue | Solution | Terminal Command |
|-------|----------|------------------|
| File not found | Ensure `users.txt` exists | `ls users.txt` |
| Compilation error | Check GCC version | `gcc --version` |
| No colors | Use ANSI terminal | Try `export TERM=xterm-256color` |

## 📜 License & Submission

Educational Use - Created for Blockchain Course  
**Due**: June 1, 2025  
**Submit**: `YourName_Account_Model.zip` containing:
- `account_simulator.c`
- `users.txt`
- 
