#pragma once
#include "Account.h"
#include <vector>
#include <memory>
#include <mutex>
#include <atomic>
#include <future>
#include <string>
#include <chrono>

class Bank
{
private:
    std::vector<std::unique_ptr<Account>> clients;

    mutable std::mutex bankMutex;

    std::atomic<int> totalDeposits{ 0 };
    std::atomic<int> totalWithdrawals{ 0 };
    std::atomic<int> totalTransfers{ 0 };

public:
    Bank() = default;

    int getTotalTransfers() const;

    void addClient(std::unique_ptr<Account> client);
    Account* findClientById(int id);

    bool deposit(int amount, int clientId);
    bool withdraw(int amount, int clientId, std::chrono::milliseconds timeout = std::chrono::milliseconds(100));
    bool transfer(int fromId, int toId, int amount);

    void printBalance(int clientId);
    std::string generateStatement(int clientId);
    std::future<std::string> generateStatementAsync(int clientId);

    void printBankStatistics();
};

