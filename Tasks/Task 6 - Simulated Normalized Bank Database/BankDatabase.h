#pragma once

#include <vector>

#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

class BankDatabase
{
private:
    std::vector<Account> accounts;
    std::vector<SavingsAccount> savingsAccounts;
    std::vector<CheckingAccount> checkingAccounts;

    bool accountExists(int accountNumber) const;

public:
    void addAccount(const Account& account);
    void addSavingsAccount(const SavingsAccount& account);
    void addCheckingAccount(const CheckingAccount& account);

    void searchAccount(int accountNumber) const;
    void displayAllAccounts() const;
};