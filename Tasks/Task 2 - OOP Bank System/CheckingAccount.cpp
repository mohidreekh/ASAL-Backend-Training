#include "CheckingAccount.h"
#include <iostream>

using namespace std;

CheckingAccount::CheckingAccount(string accountNumber,
    string accountHolderName,
    double balance,
    double overdraftLimit)
    : Account(accountNumber, accountHolderName, balance),
    _overdraftLimit(overdraftLimit)
{
}

void CheckingAccount::setOverdraftLimit(double overdraftLimit)
{
    _overdraftLimit = overdraftLimit;
}

double CheckingAccount::getOverdraftLimit() const
{
    return _overdraftLimit;
}

bool CheckingAccount::withdraw(double amount)
{
    if (amount <= 0)
        return false;

    if (amount > getBalance() + _overdraftLimit)
        return false;

    setBalance(getBalance() - amount);
    return true;
}

void CheckingAccount::displayAccountInfo() const
{
    cout << "\n**********************************************\n";
    cout << "Account Number: " << Account::getAccountNumber() << endl;
    cout << "Account Holder: " << Account::getAccountHolderName() << endl;
    cout << "Balance: " << Account::getBalance() << endl;
    cout << "Overdraft Limit : " << _overdraftLimit << endl;
    cout << "**********************************************\n";
}