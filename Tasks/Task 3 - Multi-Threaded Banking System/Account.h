#pragma once
#include <string>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Account
{
private:
    int id;
    int balance;
    std::string name;

    mutable std::mutex mtx;
    std::condition_variable cv;

public:
    Account(int id, int balance, const std::string& name);

    int getId() const;
    std::string getName() const;
    int getBalance();
    int getBalanceUnsafe() const;

    bool deposit(int amount);
    bool withdraw(int amount, std::chrono::milliseconds timeout = std::chrono::milliseconds(100));

    void addBalanceUnsafe(int amount);
    void removeBalanceUnsafe(int amount);

    std::mutex& getMutex();
    std::condition_variable& getConditionVariable();
};
