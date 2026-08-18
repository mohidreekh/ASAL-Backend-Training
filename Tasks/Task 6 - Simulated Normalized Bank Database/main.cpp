#include <iostream>

#include "BankDatabase.h"

int main()
{
    BankDatabase database;

    // =========================
    // Add Accounts
    // =========================
    database.addAccount({
        1001,
        "Ahmed Ali",
        5000,
        "Savings"
        });

    database.addAccount({
        1002,
        "Sara Omar",
        3000,
        "Checking"
        });

    database.addAccount({
        1003,
        "Omar Hassan",
        7000,
        "Savings"
        });

    // =========================
    // Add Savings Accounts
    // =========================
    database.addSavingsAccount({
        1001,
        5
        });

    database.addSavingsAccount({
        1003,
        4
        });

    // =========================
    // Add Checking Account
    // =========================
    database.addCheckingAccount({
        1002,
        1000
        });

    // =========================
    // Search Account
    // =========================
    std::cout << "\n===== SEARCH ACCOUNT =====\n";
    std::cout << "Enter Account Number: ";
    int accountNumber;
    std::cin >> accountNumber;
    database.searchAccount(accountNumber);

    // =========================
    // Display All Accounts
    // =========================
    database.displayAllAccounts();

    // =========================
    // Test Duplicate Account
    // =========================
    std::cout << "\n===== TEST DUPLICATE =====\n";

    database.addAccount({
        1001,
        "Another Person",
        9000,
        "Savings"
        });

    return 0;
}