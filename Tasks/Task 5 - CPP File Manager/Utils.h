#pragma once
#include <iostream>
#include <string>
#include<climits>

using namespace std;

class Utils
{
public:

    static string readString(const string& message)
    {
        cout << message;

        string value;
        cin >> value;

        return value;
    }

    static string readLine(const string& message)
    {
        cout << message;

        string value;
        cin.ignore();
        getline(cin, value);

        return value;
    }

    static int readNumber(string message, int min = INT_MIN, int max = INT_MAX)
    {
        int value;

        while (true)
        {
            cout << message;

            if (!(cin >> value))
            {
                cout << "Invalid input. Please enter a number.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                continue;
            }

            if (value < min || value > max)
            {
                cout << "Please enter a number between "
                    << min << " and " << max << ".\n";
                continue;
            }

            return value;
        }
    }
};
