#include "Utils.h"
#include <iostream>
#include <string>
#include <cctype>
#include <climits>
#include <random>

using namespace std;

bool Utils::isValidNumber(const string& input)
{
    if (input.empty())
    {
        return false;
    }

    for (char c : input)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    return true;
}

double Utils::readNumber(string message, int min, int max)
{
    string input;

    while (true)
    {
        cout << message;
        cin >> input;

        if (!isValidNumber(input))
        {
            cout << "Invalid input! Enter numbers only.\n";
            continue;
        }

        int num = stod(input);

        if (num < min || num > max)
        {
            cout << "Number must be between "
                << min << " and " << max << endl;
            continue;
        }

        return num;
    }
}

string Utils::readAccountNumber(string message, int len)
{
    string input;

    while (true)
    {
        cout << message;
        cin >> input;

        if (input.length() != len)
        {
            cout << "Account number must be exactly "
                << len << " digits.\n";
            continue;
        }

        if (!isValidNumber(input))
        {
            cout << "Account number must contain numbers only.\n";
            continue;
        }

        return input;
    }
}

string Utils::generateRandomNumber(int length)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> firstDigit(1, 9);
    uniform_int_distribution<int> digit(0, 9);

    string result;

    // first number not 0
    result += to_string(firstDigit(gen));

    for (int i = 1; i < length; i++)
    {
        result += to_string(digit(gen));
    }

    return result;
}

string Utils::readString(string message)
{
    string input;

    cout << message;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    while (input.empty())
    {
        cout << "Input cannot be empty. Try again: ";
        getline(cin, input);
    }

    return input;
}