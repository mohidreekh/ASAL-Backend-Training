#pragma once
#include<string>
#include<climits>

using namespace std;

class Utils {
public:
	static bool isValidNumber(const std::string& input);

	static double readNumber(string message, int min = INT_MIN, int max = INT_MAX);

	static string readAccountNumber(string message, int len = 8);

	static string generateRandomNumber(int length = 8);

	static string readString(std::string message);

};