# Simulated Normalized Bank Database in C++

## Description

This project simulates a simple normalized bank database using C++. Instead of relying on a database management system (such as MySQL or PostgreSQL), the project utilizes C++ `struct`s and `vector`s to represent normalized database tables in memory.

The primary goal of this project is to demonstrate the fundamental concepts of Database Normalization (**1NF**, **2NF**, and **3NF**) within an Object-Oriented C++ environment.

---

# Database Structure

The database consists of three main tables linked via relational primary/foreign key attributes.

## 1. ACCOUNT Table

| Account Number | Holder Name | Balance | Account Type |
| -------------- | ----------- | ------: | ------------ |
| **1001**       | Ahmed Ali   |    5000 | Savings      |
| **1002**       | Sara Omar   |    3000 | Checking     |
| **1003**       | Omar Hassan |    7000 | Savings      |

---

## 2. SAVINGS_ACCOUNT Table

| Account Number (FK) | Interest Rate |
| ------------------- | ------------: |
| **1001**            |            5% |
| **1003**            |            4% |

---

## 3. CHECKING_ACCOUNT Table

| Account Number (FK) | Overdraft Limit |
| ------------------- | --------------: |
| **1002**            |            1000 |

> **Note:** `AccountNumber` serves as the **Primary Key (PK)** in the `ACCOUNT` table and acts as a **Foreign Key (FK)** in both `SAVINGS_ACCOUNT` and `CHECKING_ACCOUNT` tables.

---

# C++ Data Representation

In C++, these database tables are represented using standard library vectors of custom structures:

```cpp
std::vector<Account> accounts;

std::vector<SavingsAccount> savingsAccounts;

std::vector<CheckingAccount> checkingAccounts;
```

---

# Features

## Add New Account

Create general accounts while checking for duplicate account numbers.

## Add Savings Information

Assign specific interest rates to savings accounts.

## Add Checking Information

Assign overdraft limits to checking accounts.

## Search Account

Search for any account by its unique `AccountNumber`.

## Display Accounts

View a complete list of all accounts along with their subtype-specific details.

---

# Normalization Principles

## First Normal Form (1NF)

Each field contains atomic (indivisible) values, and every record is unique.

### Example

* `AccountNumber = 1001`
* `HolderName = Ahmed Ali`
* `Balance = 5000`
* `AccountType = Savings`

---

## Second Normal Form (2NF)

Shared account properties are separated from type-specific properties to eliminate partial key dependencies.

* Common information is stored in the `ACCOUNT` table.
* Savings-specific information is stored in the `SAVINGS_ACCOUNT` table.
* Checking-specific information is stored in the `CHECKING_ACCOUNT` table.

---

## Third Normal Form (3NF)

Transitive dependencies are eliminated. Every non-key attribute depends strictly and directly on the Primary Key (`AccountNumber`).

```text
ACCOUNT:

AccountNumber → HolderName, Balance, AccountType


SAVINGS_ACCOUNT:

AccountNumber → InterestRate


CHECKING_ACCOUNT:

AccountNumber → OverdraftLimit
```

---

# Why Three Separate Structures?

Instead of using one large monolithic structure with optional fields, the database is split into three separate entities. This approach offers several advantages:

* Savings accounts require an `InterestRate` attribute.
* Checking accounts require an `OverdraftLimit` attribute.
* Prevents empty/null fields.
* Saves memory space.
* Produces a cleaner and more scalable OOP design.

---

# Project Structure

```text
BankDatabase/
│
├── include/
│   ├── Account.h
│   ├── SavingsAccount.h
│   ├── CheckingAccount.h
│   └── BankDatabase.h
│
├── src/
│   └── BankDatabase.cpp
│
└── main.cpp
```

---

# Example Output

```text
===== SEARCH ACCOUNT =====

Enter Account Number: 1001

Account Number: 1001
Holder Name: Ahmed Ali
Balance: 5000
Account Type: Savings
Interest Rate: 5%


===== ALL ACCOUNTS =====

Account Number: 1001
Holder Name: Ahmed Ali
Balance: 5000
Type: Savings
Interest Rate: 5%


Account Number: 1002
Holder Name: Sara Omar
Balance: 3000
Type: Checking
Overdraft Limit: 1000


Account Number: 1003
Holder Name: Omar Hassan
Balance: 7000
Type: Savings
Interest Rate: 4%
```

---
