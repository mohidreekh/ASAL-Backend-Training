#pragma once
#include <string>
#include<memory>

using namespace std;

class Account {
private:
    string _accountNumber;
    string _accountHolderName;
    double _balance;

public:
    Account(string accountNumber,
        string accountHolderName,
        double balance);

    virtual ~Account() = default;

    void setAccountNumber(string accountNumber);
    
    void setAccountHolderName(string accountHolderName);
    
    void setBalance(double balance);

    string getAccountNumber() const;

    string getAccountHolderName() const;

    double getBalance() const;

    virtual bool deposit(double amount);

    virtual bool withdraw(double amount) = 0;

    virtual void displayAccountInfo() const;
};