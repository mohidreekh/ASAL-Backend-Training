#include "BankDatabase.h"

#include <iostream>

//bool BankDatabase::accountExists(int accountNumber) const
//{
//    for (const Account& account : accounts)
//    {
//        if (account.accountNumber == accountNumber)
//        {
//            return true;
//        }
//    }
//
//    return false;
//}

bool BankDatabase::accountExists(int accountNumber) const
{
    return std::find_if(accounts.begin(),accounts.end(),
        [accountNumber](const Account& account)
        {
            return account.accountNumber == accountNumber;
        }) != accounts.end();
}

void BankDatabase::addAccount(const Account& account)
{
    if (accountExists(account.accountNumber))
    {
        std::cout << "Error: Account number already exists.\n";
        return;
    }

    accounts.push_back(account);

    std::cout << "Account created successfully.\n";
}

void BankDatabase::addSavingsAccount(const SavingsAccount& account)
{
    savingsAccounts.push_back(account);
}

void BankDatabase::addCheckingAccount(const CheckingAccount& account)
{
    checkingAccounts.push_back(account);
}

void BankDatabase::searchAccount(int accountNumber) const
{
    // Search in the main ACCOUNT table
    for (const Account& account : accounts)
    {
        if (account.accountNumber == accountNumber)
        {
            std::cout << "\nAccount Number: " << account.accountNumber << '\n';
            std::cout << "Holder Name: " << account.holderName << '\n';
            std::cout << "Balance: " << account.balance << '\n';
            std::cout << "Account Type: " << account.accountType << '\n';

            // If Savings, search in SAVINGS_ACCOUNT
            if (account.accountType == "Savings")
            {
                for (const SavingsAccount& savings : savingsAccounts)
                {
                    if (savings.accountNumber == accountNumber)
                    {
                        std::cout << "Interest Rate: " << savings.interestRate << "%\n";
                        return;
                    }
                }
            }

            // If Checking, search in CHECKING_ACCOUNT
            if (account.accountType == "Checking")
            {
                for (const CheckingAccount& checking : checkingAccounts)
                {
                    if (checking.accountNumber == accountNumber)
                    {
                        std::cout << "Overdraft Limit: " << checking.overdraftLimit << '\n';
                        return;
                    }
                }
            }

            return;
        }
    }

    std::cout << "Error: Account not found.\n";
}

void BankDatabase::displayAllAccounts() const
{
    std::cout << "\n===== ALL ACCOUNTS =====\n";

    for (const Account& account : accounts)
    {
        std::cout << "\nAccount Number: " << account.accountNumber << '\n';

        std::cout << "Holder Name: " << account.holderName << '\n';

        std::cout << "Balance: " << account.balance << '\n';

        std::cout << "Type: " << account.accountType << '\n';

        // Display Savings-specific information
        if (account.accountType == "Savings")
        {
            for (const SavingsAccount& savings : savingsAccounts)
            {
                if (savings.accountNumber == account.accountNumber)
                {
                    std::cout << "Interest Rate: " << savings.interestRate << "%\n";
                    break;
                }
            }
        }

        // Display Checking-specific information
        else if (account.accountType == "Checking")
        {
            for (const CheckingAccount& checking : checkingAccounts)
            {
                if (checking.accountNumber == account.accountNumber)
                {
                    std::cout << "Overdraft Limit: " << checking.overdraftLimit << '\n';
                    break;
                }
            }
        }
    }
}