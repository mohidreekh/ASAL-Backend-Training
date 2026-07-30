#pragma once
#include <string>
#include "Account.h"

using namespace std;

class CheckingAccount : public Account {
private:
    double _overdraftLimit;

public:
    CheckingAccount(string accountNumber,
        string accountHolderName,
        double balance,
        double overdraftLimit);

    void setOverdraftLimit(double overdraftLimit);

    double getOverdraftLimit() const;

    bool withdraw(double amount) override;

    void displayAccountInfo() const override;
};