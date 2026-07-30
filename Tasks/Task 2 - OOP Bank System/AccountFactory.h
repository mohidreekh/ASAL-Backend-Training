#pragma once

#include "Account.h"
#include <memory>

class AccountFactory
{
public:
    static std::unique_ptr<Account> createCheckingAccount(string accNum);

    static std::unique_ptr<Account> createSavingAccount(string accNum);
};