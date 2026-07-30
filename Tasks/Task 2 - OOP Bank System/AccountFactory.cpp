#include "AccountFactory.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

int ACCOUNT_NUMBER_LENGTH = 8;

unique_ptr<Account> AccountFactory::createCheckingAccount(string accountNumber = "23165487")
{
    string name;
    double initialBalance, limit;

    name = Utils::readString("Enter Account Holder Name: ");
    initialBalance = Utils::readNumber("Enter Initial Balance: $",50);
    limit = Utils::readNumber("Enter Overdraft Limit: $",0);

    return make_unique<CheckingAccount>(accountNumber, name, initialBalance, limit);
}

std::unique_ptr<Account> AccountFactory::createSavingAccount(string accountNumber = "11111111")
{
    string name;
    double initialBalance, rate;

    name = Utils::readString("Enter Account Holder Name: ");
    initialBalance = Utils::readNumber("Enter Initial Balance: $", 0);
    rate = Utils::readNumber("Enter Interest Rate: ", 0);

    return make_unique<SavingAccount>(accountNumber, name, initialBalance, rate);
}