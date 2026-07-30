#include "Account.h"
#include <iostream>

using namespace std;

Account::Account(string accountNumber,
    string accountHolderName,
    double balance)
{
    _accountNumber = accountNumber;
    _accountHolderName = accountHolderName;
    _balance = balance;
}

void Account::setAccountNumber(string accountNumber)
{
    _accountNumber = accountNumber;
}

void Account::setAccountHolderName(string accountHolderName)
{
    _accountHolderName = accountHolderName;
}

void Account::setBalance(double balance)
{
    _balance = balance;
}

string Account::getAccountNumber() const
{
    return _accountNumber;
}

string Account::getAccountHolderName() const
{
    return _accountHolderName;
}

double Account::getBalance() const
{
    return _balance;
}

bool Account::deposit(double amount)
{
    _balance += amount;
    return true;
}

void Account::displayAccountInfo() const
{
    cout << "\n**********************************************\n";
    cout << "Account Number: " << _accountNumber << endl;
    cout << "Account Holder: " << _accountHolderName << endl;
    cout << "Balance: " << _balance << endl;
    cout << "**********************************************\n";
}