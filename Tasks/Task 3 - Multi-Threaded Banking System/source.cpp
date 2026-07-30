#include "Bank.h"
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

int main()
{
    Bank bank;

    bank.addClient(make_unique<Account>(1, 4000, "Mohammad"));
    bank.addClient(make_unique<Account>(2, 3000, "Ahmad"));
    bank.addClient(make_unique<Account>(3, 5000, "Ali"));

    auto runRandomATM = [&](int atmId) {
        mt19937 rng(random_device{}() + atmId);
        uniform_int_distribution<int> opDist(0, 3);
        uniform_int_distribution<int> clientDist(1, 3);
        uniform_int_distribution<int> amountDist(10, 200);

        for (int i = 0; i < 50; ++i)
        {
            int op = opDist(rng);
            int client1 = clientDist(rng);

            if (op == 0)
            {
                bank.deposit(amountDist(rng), client1);
            }
            else if (op == 1)
            {
                bank.withdraw(amountDist(rng), client1);
            }
            else if (op == 2)
            {
                int client2 = clientDist(rng);
                while (client2 == client1) {
                    client2 = clientDist(rng);
                }
                bank.transfer(client1, client2, amountDist(rng));
            }
            else
            {
                bank.printBalance(client1);
            }

            this_thread::sleep_for(chrono::milliseconds(5));
        }
        };

    {
        vector<jthread> atms;
        for (int i = 1; i <= 6; ++i)
        {
            atms.emplace_back(runRandomATM, i);
        }
    }

    auto report1 = bank.generateStatementAsync(1);
    auto report2 = bank.generateStatementAsync(2);
    auto report3 = bank.generateStatementAsync(3);

    cout << "\nFinal Results\n\n";
    cout << report1.get() << endl;
    cout << report2.get() << endl;
    cout << report3.get() << endl;

    bank.printBankStatistics();

    return 0;
}