#include "Account.h"

Account::Account(int id, int balance, const std::string& name)
    : id(id), balance(balance), name(name)
{
}

int Account::getId() const
{
    return id;
}

std::string Account::getName() const
{
    return name;
}

int Account::getBalance()
{
    std::lock_guard<std::mutex> lock(mtx);
    return balance;
}

int Account::getBalanceUnsafe() const
{
    return balance;
}

bool Account::deposit(int amount)
{
    if (amount <= 0)
        return false;

    {
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
    }

    cv.notify_all();
    return true;
}

bool Account::withdraw(int amount, std::chrono::milliseconds timeout)
{
    if (amount <= 0)
        return false;

    std::unique_lock<std::mutex> lock(mtx);

    bool success = cv.wait_for(lock, timeout, [&]()
        {
            return balance >= amount;
        });

    if (!success)
        return false;

    balance -= amount;
    return true;
}

void Account::addBalanceUnsafe(int amount)
{
    balance += amount;
}

void Account::removeBalanceUnsafe(int amount)
{
    balance -= amount;
}

std::mutex& Account::getMutex()
{
    return mtx;
}

std::condition_variable& Account::getConditionVariable()
{
    return cv;
}