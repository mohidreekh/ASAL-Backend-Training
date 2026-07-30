#include<iostream>
#include "Bank.h"
#include"Utils.h"

using namespace std;

int main() {

    Bank myBank;

    int choice = 0;

    do {
        cout << "\n========== BANK MANAGEMENT ==========\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Search Account\n";
        cout << "6. Display Account\n";
        cout << "7. Display All Accounts\n";
        cout << "8. Delete Account\n";
        cout << "9. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
        case 1: myBank.createSavingAccount(); break;
        case 2: myBank.createCheckingAccount(); break;
        case 3: myBank.deposit(); break;
        case 4: myBank.withdraw(); break;
        case 5: {
            string accNum = Utils::readAccountNumber("\nEnter Account Number to Search:");
            Account* acc = myBank.searchByAccountNumber(accNum);
            if (acc) {
                cout << "Success: Account found!\n";
            }
            else {
                cout << "Error: Account not found.\n";
            }
            break;
        }
        case 6: myBank.displayOneAccount(); break;
        case 7: myBank.displayAllAccounts(); break;
        case 8: myBank.deleteAccount(); break;
        case 9: cout << "Exiting Bank Management System. Goodbye!\n"; break;
        default: cout << "Invalid choice! Please select an option between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}