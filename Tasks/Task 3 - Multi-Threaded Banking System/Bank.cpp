#include "Bank.h"
#include <iostream>
#include <thread>

int Bank::getTotalTransfers() const
{
    return totalTransfers.load();
}

void Bank::addClient(std::unique_ptr<Account> client)
{
    std::lock_guard<std::mutex> lock(bankMutex);
    clients.push_back(std::move(client));
}

Account* Bank::findClientById(int id)
{
    std::lock_guard<std::mutex> lock(bankMutex);

    for (auto& client : clients)
    {
        if (client->getId() == id)
            return client.get();
    }

    return nullptr;
}

bool Bank::deposit(int amount, int clientId)
{
    if (amount <= 0)
        return false;

    Account* client = findClientById(clientId);

    if (!client)
        return false;

    if (client->deposit(amount))
    {
        totalDeposits++;
        return true;
    }
    return false;
}

bool Bank::withdraw(int amount, int clientId, std::chrono::milliseconds timeout)
{
    if (amount <= 0)
        return false;

    Account* client = findClientById(clientId);

    if (!client)
        return false;

    if (client->withdraw(amount, timeout))
    {
        totalWithdrawals++;
        return true;
    }
    return false;
}

bool Bank::transfer(int fromId, int toId, int amount)
{
    if (amount <= 0)
        return false;

    Account* from = findClientById(fromId);
    Account* to = findClientById(toId);

    if (!from || !to || from == to)
        return false;

    std::scoped_lock lock(
        from->getMutex(),
        to->getMutex()
    );

    if (from->getBalanceUnsafe() < amount)
        return false;

    from->removeBalanceUnsafe(amount);
    to->addBalanceUnsafe(amount);

    to->getConditionVariable().notify_one();

    totalTransfers++;
    return true;
}

void Bank::printBalance(int clientId)
{
    Account* client = findClientById(clientId);

    if (!client)
        return;

    std::cout << client->getName()
        << " Balance: "
        << client->getBalance()
        << std::endl;
}

std::string Bank::generateStatement(int clientId)
{
    Account* client = findClientById(clientId);

    if (!client)
        return "Client not found";

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::string statement;
    statement += "Client: " + client->getName() + "\n";
    statement += "Balance: " + std::to_string(client->getBalance()) + "\n";

    return statement;
}

std::future<std::string> Bank::generateStatementAsync(int clientId)
{
    return std::async(
        std::launch::async,
        &Bank::generateStatement,
        this,
        clientId
    );
}

void Bank::printBankStatistics()
{
    std::cout << "\n--- Bank Statistics ---\n";
    std::cout << "Total Deposits: " << totalDeposits.load() << std::endl;
    std::cout << "Total Withdrawals: " << totalWithdrawals.load() << std::endl;
    std::cout << "Total Transfers: " << totalTransfers.load() << std::endl;
}