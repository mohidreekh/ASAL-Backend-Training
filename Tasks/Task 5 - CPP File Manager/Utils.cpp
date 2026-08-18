#include "Utils.h"

#include <iostream>
#include <limits>

std::string Utils::readString(const std::string& message)
{
    std::cout << message;

    std::string value;
    std::cin >> value;

    return value;
}

std::string Utils::readLine(const std::string& message)
{
    std::cout << message;

    std::string value;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::getline(std::cin, value);

    return value;
}

int Utils::readNumber(const std::string& message, int min, int max)
{
    int value;

    while (true)
    {
        std::cout << message;

        if (!(std::cin >> value))
        {
            std::cout << "Invalid input. Please enter a number.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        if (value < min || value > max)
        {
            std::cout << "Please enter a number between "
                << min << " and " << max << ".\n";
            continue;
        }

        return value;
    }
}
