<div align="center">

# 🏦 Banking & Shopping System

### A console-based C++ application integrating a full Banking System with a Shopping Cart

[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![OOP](https://img.shields.io/badge/Paradigm-OOP-blueviolet?style=for-the-badge)](#-oop-concepts-demonstrated)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Unix-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://www.linux.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

</div>

---

## 📖 Overview

This mini-project simulates a real-world **Banking and Shopping experience** entirely in the terminal. A user opens a bank account, deposits/withdraws funds with password verification, and seamlessly transitions into a shopping cart — where the total purchase amount is securely deducted from the bank balance.

Built as part of an **Object-Oriented Programming with C++** course to demonstrate real OOP design patterns including inheritance, encapsulation, friend classes, namespaces, and structures.

---

## Features at a Glance

| Module | Feature | Details |
|--------|---------|---------|
| 🏦 **Bank** | Account Creation | Auto-generated 9-digit account number, custom password |
| 🏦 **Bank** | Deposit | Password-verified, updates balance instantly |
| 🏦 **Bank** | Withdraw | Password-verified, enforces ₹500 minimum balance |
| 🏦 **Bank** | Balance Display | Shows name, account no., type & current balance |
| 🏦 **Bank** | Address Management | Full address (house, city, state, PIN, email, mobile) |
| 🛒 **Shopping** | Add to Cart | Name, price, quantity — up to 4 items |
| 🛒 **Shopping** | View Cart | Formatted table with per-item and grand total |
| 🛒 **Shopping** | Delete Item | Remove by product name with auto recalculation |
| 🛒 **Shopping** | Clear Cart | Wipe cart for a fresh start |
| 🛒 **Shopping** | Billing | Password-verified deduction directly from bank account |

---

## Project Structure

```
Banking-Shopping-CPP/
│
├── Bank.h            # Declarations — A::Bank (base) & B::Bank (derived)
├── Bank.cpp          # Implementations of both Bank classes
│
├── Shopping.h        # Declaration — Shopping class
├── Shopping.cpp      # Implementation of Shopping class
│
├── BS_Appli.cpp      # Entry point — main() driver
│
└── README.md         # You are here
```

---

## OOP Concepts Demonstrated

```
┌─────────────────────────────────────────────────────────────────┐
│                      OOP Architecture                           │
│                                                                 │
│   namespace A                    namespace B                    │
│  ┌──────────────┐               ┌──────────────────────────┐   │
│  │   A::Bank    │◄──inherits────│        B::Bank           │   │
│  │   (Base)     │               │       (Derived)          │   │
│  │              │               │  + address struct        │   │
│  │ - Balance    │               │  + set_address()         │   │
│  │ - pswd       │               │  + processPayment()      │   │
│  │ - Name       │               │  + friend Shopping       │   │
│  │ + deposit()  │               └──────────┬───────────────┘   │
│  │ + withdraw() │                          │ friend            │
│  └──────────────┘               ┌──────────▼───────────────┐   │
│                                 │        Shopping          │   │
│                                 │  - Product[SZ]           │   │
│                                 │  - total_items (static)  │   │
│                                 │  + add_to_Cart()         │   │
│                                 │  + billing(B::Bank&)     │   │
│                                 └──────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

| Concept | Where It's Used |
|---|---|
| **Classes & Objects** | `A::Bank`, `B::Bank`, `Shopping` |
| **Inheritance** | `B::Bank` publicly inherits `A::Bank` |
| **Namespaces** | `namespace A` (base bank), `namespace B` (derived bank) |
| **Encapsulation** | `Balance_Left` & `pswd` are `private` — never exposed directly |
| **Access Specifiers** | `private`, `protected`, `public` across all classes |
| **Friend Class** | `Shopping` is `friend` of `B::Bank` for payment access |
| **Nested Structure** | `customer_address` struct inside `B::Bank` |
| **Static Members** | `Product[]`, `total_items`, `total_amount` in `Shopping` |
| **Constructors / Destructors** | All three classes define both |
| **`const` Member Functions** | `get_balance()`, `getAccountType()`, `getTotalAmount()` |

---

##  Security Design

```
Every sensitive operation is gated behind password verification:

  deposit()        ──► verify_pswd()     ──►  proceed  /   deny
  withdraw()       ──► verify_pswd()     ──►  proceed  /   deny
  processPayment() ──► verifyPassword()  ──►  proceed  /   deny

  + Minimum balance of ₹500 enforced on every withdrawal & payment
  + Password stored as private std::string — never accessible outside class
```

---

##  Getting Started

### Prerequisites
- GCC / G++ compiler
- Linux or macOS (uses `<unistd.h>` for `sleep()`)

### Compile & Run

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/Banking-Shopping-CPP.git
cd Banking-Shopping-CPP

# Compile (BS_Appli.cpp includes the other .cpp files directly)
g++ BS_Appli.cpp -o banking_app

# Run
./banking_app
```

> **Windows users:** Replace `sleep()` calls in `Bank.cpp` with `Sleep()` from `<windows.h>` and compile with MinGW.

---

##  Sample Output

```
==============================================
        BANKING AND SHOPPING APPLICATION
==============================================

You must deposit a minimum of 500 rupees to open a new account.
Press 1 for Yes, 0 for No: 1

Enter the Name: Arjun Sharma
Set your security/transaction password: ••••••
Account_No generated automatically: 748392015
Enter the Account_Type: Savings
Account created successfully with initial deposit of ₹ 500.00 /-

--- Bank Menu ---
1. Display Account Details
2. Deposit Amount
3. Proceed to Shopping
4. Withdraw Amount
5. Exit
Enter your choice: 3

A : Add to Cart        *
B : Billing            **
V : View Cart          *******
...

======== YOUR SHOPPING CART ========
Product              Price (₹)   Qty   Total Price (₹)
------------------------------------------------------------
Shampoo              200         2     400 /-
Soap                 50          5     250 /-
------------------------------------------------------------
Total Amount: ₹ 650 /-

Enter your pswd to authorize/approve payment: ••••••
pswd verified ✓
Payment processed: ₹ 650 /- deducted from your Savings account.
Remaining balance: ₹ 1350 /-
Cart cleared. You're all set for a fresh start!
```

---

##  Known Limitations

- Cart supports a maximum of **4 items** — change `#define SZ 4` in `Shopping.h` to increase
- `sleep()` is Linux/macOS only — use `Sleep()` from `<windows.h>` on Windows
- Account number uses `rand()` — not cryptographically unique across sessions
- Mobile number is randomly generated (simulation only)
- `BS_Appli.cpp` uses `#include ".cpp"` directly — functional but non-standard for large projects

---

##📋 Requirements Checklist

- [x] Bank class with account creation, deposit, withdraw, balance display
- [x] Password verification on all sensitive operations
- [x] Address structure with full customer details
- [x] Shopping cart — add, view, delete, clear
- [x] Billing deducts total from bank account with password auth
- [x] `Shopping` declared as `friend` of `B::Bank`
- [x] Minimum balance of ₹500 enforced
- [x] Updated bank balance displayed after successful billing

---

##  Author

**Ved Anand**
- GitHub: [@vedanand010102GitHub]((https://github.com/vedanand010102GitHub/Banking-Shopping-Application_CPP))

---

##  License

This project is licensed under the [MIT License](LICENSE).

---

<div align="center">

 If you found this helpful, consider giving it a star!

*Mini Project · C++ · Object-Oriented Programming*

</div>
