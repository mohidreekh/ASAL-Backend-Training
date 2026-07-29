#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include<future>

using namespace std;

class Client
{
private:

    int id;
    int balance;
    string name;

    mutex mtx;
    condition_variable cv;

    atomic<int> totalDeposits{ 0 };
    atomic<int> totalWithdrawals{ 0 };
    atomic<int> totalTransfers{ 0 };


public:

    Client(int id, int balance, const string& name)
        : id(id), balance(balance), name(name)
    {
    }

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getBalance()
    {
        lock_guard<mutex> lock(mtx);
        return balance;
    }

    int getBalanceUnsafe() const
    {
        return balance;
    }

    int getTotalDeposits() const
    {
        return totalDeposits.load();
    }

    int getTotalWithdrawals() const
    {
        return totalWithdrawals.load();
    }

    int getTotalTransfers() {
        return totalTransfers.load();
    }

    bool deposit(int amount)
    {
        if (amount <= 0)
            return false;

        {
            lock_guard<mutex> lock(mtx);

            balance += amount;
            totalDeposits++;
        }

        cv.notify_all();

        return true;
    }

    bool withdraw(int amount)
    {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [&]()
            {
                return balance >= amount;
            });

        balance -= amount;
        totalWithdrawals++;

        return true;
    }

    void addBalanceUnsafe(int amount)
    {
        balance += amount;
    }

    void removeBalanceUnsafe(int amount)
    {
        balance -= amount;
    }

    mutex& getMutex()
    {
        return mtx;
    }

    condition_variable& getConditionVariable()
    {
        return cv;
    }

    void increaseTotalTransfers() {
        totalTransfers++;
    }
};

class Bank
{
private:

    vector<unique_ptr<Client>> clients;

    mutex bankMutex;

    atomic<int> totalTransfers{ 0 };

public:

    int getTotalTransfers() const
    {
        return totalTransfers.load();
    }

    void addClient(unique_ptr<Client> client)
    {
        lock_guard<mutex> lock(bankMutex);

        clients.push_back(move(client));
    }

    Client* findClientById(int id)
    {
        lock_guard<mutex> lock(bankMutex);

        for (auto& client : clients)
        {
            if (client->getId() == id)
                return client.get();
        }

        return nullptr;
    }

    bool deposit(int amount, int clientId)
    {
        Client* client = findClientById(clientId);

        if (!client)
            return false;

        return client->deposit(amount);
    }

    bool withdraw(int amount, int clientId)
    {
        Client* client = findClientById(clientId);

        if (!client)
            return false;

        return client->withdraw(amount);
    }

    bool transfer(int fromId, int toId, int amount)
    {
        Client* from = findClientById(fromId);
        Client* to = findClientById(toId);

        if (!from || !to || from == to)
            return false;

        scoped_lock lock(
            from->getMutex(),
            to->getMutex()
        );

        if (from->getBalanceUnsafe() < amount)
            return false;

        from->removeBalanceUnsafe(amount);
        to->addBalanceUnsafe(amount);

        to->getConditionVariable().notify_one();

        totalTransfers++;
        from->increaseTotalTransfers();

        return true;
    }

    void printBalance(int clientId)
    {
        Client* client = findClientById(clientId);

        if (!client)
            return;

        cout << client->getName()
            << " Balance: "
            << client->getBalance()
            << endl;
    }

    string generateStatement(int clientId)
    {
        Client* client = findClientById(clientId);

        if (!client)
            return "Client not found";

        this_thread::sleep_for(chrono::seconds(2));

        string statement;

        statement += "Client: " + client->getName() + "\n";
        statement += "Balance: " + to_string(client->getBalance()) + "\n";
        statement += "Deposits: " + to_string(client->getTotalDeposits()) + "\n";
        statement += "Withdrawals: " + to_string(client->getTotalWithdrawals()) + "\n";
        statement += "Transfers: " + to_string(client->getTotalTransfers()) + "\n";

        return statement;
    }

    future<string> generateStatementAsync(int clientId)
    {
        return async(
            launch::async,
            &Bank::generateStatement,
            this,
            clientId
        );
    }
};

int main()
{
    Bank bank;

    bank.addClient(make_unique<Client>(1, 4000, "Mohammad"));
    bank.addClient(make_unique<Client>(2, 3000, "Ahmad"));
    bank.addClient(make_unique<Client>(3, 5000, "Ali"));

    {
        jthread atm1([&]()
            {
                for (int i = 0; i < 100; i++)
                {
                    bank.deposit(100, 1);
                }
            });

        jthread atm2([&]()
            {
                for (int i = 0; i < 100; i++)
                {
                    bank.withdraw(50, 1);
                }
            });

        jthread atm3([&]()
            {
                for (int i = 0; i < 100; i++)
                {
                    bank.transfer(1, 2, 25);
                }
            });

        jthread atm4([&]()
            {
                for (int i = 0; i < 100; i++)
                {
                    bank.deposit(150, 2);
                }
            });

        jthread atm5([&]()
            {
                for (int i = 0; i < 100; i++)
                {
                    bank.withdraw(100, 2);
                }
            });

        jthread atm6([&]()
            {
                for (int i = 0; i < 100; i++)
                {
                    bank.transfer(2, 3, 40);
                }
            });

        jthread atm7([&]()
            {
                for (int i = 0; i < 20; i++)
                {
                    bank.printBalance(1);
                }
            });

        jthread atm8([&]()
            {
                for (int i = 0; i < 20; i++)
                {
                    bank.printBalance(2);
                }
            });
    }

    auto report1 = bank.generateStatementAsync(1);
    auto report2 = bank.generateStatementAsync(2);
    auto report3 = bank.generateStatementAsync(3);

    cout << "\nFinal Results\n\n";
    cout << report1.get() <<endl;
    cout << report2.get() << endl;
    cout << report3.get() << endl;

    cout << "Total Transfers In Bank: "
        << bank.getTotalTransfers()
        << endl;

    return 0;
}