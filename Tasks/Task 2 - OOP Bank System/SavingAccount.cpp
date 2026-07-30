#include "SavingAccount.h"
#include <iostream>

using namespace std;

SavingAccount::SavingAccount(string accountNumber,
    string accountHolderName,
    double balance,
    double interestRate)
    : Account(accountNumber, accountHolderName, balance),
    _interestRate(interestRate)
{
}

void SavingAccount::setInterestRate(double interestRate)
{
    _interestRate = interestRate;
}

double SavingAccount::getInterestRate() const
{
    return _interestRate;
}

void SavingAccount::addInterest()
{
    double interest = getBalance() * (_interestRate / 100.0);
    setBalance(getBalance() + interest);
}

bool SavingAccount::withdraw(double amount)
{
    if (amount <= 0 || amount > getBalance())
        return false;

    setBalance(getBalance() - amount);
    return true;
}

void SavingAccount::displayAccountInfo() const
{
    cout << "\n**********************************************\n";
    cout << "Account Number: " << Account::getAccountNumber() << endl;
    cout << "Account Holder: " << Account::getAccountHolderName() << endl;
    cout << "Balance: " << Account::getBalance() << endl;
    cout << "Interest Rate  : " << _interestRate << "%\n";
    cout << "**********************************************\n";
}