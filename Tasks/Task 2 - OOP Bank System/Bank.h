#pragma once
#include <vector>
#include <memory>
#include"Account.h"

using namespace std;

class Bank
{
private:
    vector<unique_ptr<Account>> _accounts;

    bool isAccountNumberUnique(const string& accountNumber) const;

    string getUniqueNumber();

public:

    void createSavingAccount();

    void createCheckingAccount();

    void deposit();

    void withdraw();

    Account* searchByAccountNumber(const string& accountNumber) const;

    void displayOneAccount() const;

    void displayAllAccounts() const;

    void deleteAccount();
};