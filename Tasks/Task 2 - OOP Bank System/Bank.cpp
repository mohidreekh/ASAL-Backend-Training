#include "Bank.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include <iostream>
#include <algorithm>
#include "AccountFactory.h"
#include "Utils.h"

using namespace std;

string Bank::getUniqueNumber() {
    string accNum;
    do
    {
        accNum = Utils::generateRandomNumber(8);
    } while (!isAccountNumberUnique(accNum));

    return accNum;
}

bool Bank::isAccountNumberUnique(const string& accountNumber) const {
    for (const auto& acc : _accounts) {
        if (acc->getAccountNumber() == accountNumber) {
            return false;
        }
    }
    return true;
}

void Bank::createSavingAccount()
{
    cout << "\n========== Create Savings Account ==========\n";

    string randomAccountNumber = getUniqueNumber();

    auto account = AccountFactory::createSavingAccount(randomAccountNumber);

    if (account == nullptr)
    {
        cout << "Failed to create savings account.\n";
        return;
    }

    _accounts.push_back(std::move(account));

    cout << "Savings Account created successfully!\n";
    cout << "Account Number : " << randomAccountNumber << endl;
}

void Bank::createCheckingAccount() {
    cout << "\n========== Create Checking Account ==========\n";
    string randomAccountNumber = getUniqueNumber();

    auto account = AccountFactory::createSavingAccount(randomAccountNumber);
    if (account == nullptr) {
        cout << "Failed to create account.\n";
        return;
    }

    _accounts.push_back(move(account));
    cout << "Checking Account created successfully!\n";
    cout << "Account Number : " << randomAccountNumber << endl;
}


void Bank::deposit() {
    string accNum = Utils::readAccountNumber("\nEnter Account Number : ");
    double amount;

    Account* acc = searchByAccountNumber(accNum);
    if (acc != nullptr) {
        amount = Utils::readNumber("Enter Deposit Amount: $", 1);
        acc->deposit(amount);

        cout << "You added " + to_string(amount) + "$ " + "succesfully\n";
    }
    else {
        cout << "Error: Account not found.\n";
    }
}

void Bank::withdraw()
{
    string accNum = Utils::readAccountNumber("\nEnter Account Number: ");

    Account* acc = searchByAccountNumber(accNum);

    if (acc)
    {
        double amount = Utils::readNumber("Enter Withdrawal Amount: $", 1);

        acc->withdraw(amount);
        cout << "You withdrew " + to_string(amount) + "$ successfully\n";
    }
    else
    {
        cout << "Error: Account not found.\n";
    }
}


Account* Bank::searchByAccountNumber(const string& accountNumber) const {
    for (const auto& acc : _accounts) {
        if (acc->getAccountNumber() == accountNumber) {
            return acc.get(); //return pointer
        }
    }
    return nullptr;
}

void Bank::displayOneAccount() const {
    string accNum;
    cout << "\nEnter Account Number to Display: ";
    cin >> accNum;

    Account* acc = searchByAccountNumber(accNum);
    if (acc != nullptr) {
        acc->displayAccountInfo();
    }
    else {
        cout << "Error: Account not found.\n";
    }
}

void Bank::displayAllAccounts() const {
    if (_accounts.empty()) {
        cout << "\nNo accounts found in the bank database.\n";
        return;
    }
    cout << "\n================ ALL ACCOUNTS ================\n";
    for (const auto& acc : _accounts) {
        acc->displayAccountInfo();
    }
}

void Bank::deleteAccount() {
    string accNum = Utils::readAccountNumber("\nEnter Account Number to Delete: ");

    auto it = remove_if(_accounts.begin(), _accounts.end(),
        [&accNum](const unique_ptr<Account>& acc) {
            return acc->getAccountNumber() == accNum;
        });

    if (it != _accounts.end()) {
        _accounts.erase(it, _accounts.end());
        cout << "Account " << accNum << " deleted successfully.\n";
    }
    else {
        cout << "Error: Account not found.\n";
    }
}