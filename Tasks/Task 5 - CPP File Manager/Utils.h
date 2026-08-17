#pragma once

#include <string>
#include<climits>

class Utils
{
public:
    static std::string readString(const std::string& message);
    static std::string readLine(const std::string& message);
    static int readNumber(const std::string& message, int min = INT_MIN, int max = INT_MAX);
};