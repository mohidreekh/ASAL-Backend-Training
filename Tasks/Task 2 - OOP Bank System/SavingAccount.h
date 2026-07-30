#pragma once
#include <string>
#include "Account.h"


using namespace std;

class SavingAccount : public Account {
private:
    double _interestRate;

public:
    SavingAccount(string accountNumber,
        string accountHolderName,
        double balance,
        double interestRate);

    void setInterestRate(double interestRate);

    double getInterestRate() const;

    void addInterest();

    bool withdraw(double amount) override;

    void displayAccountInfo() const override;
};