#include<iostream>

using namespace std;

bool isPalindrom(string s) 
{
	for (int i = 0, j =s.size() - 1; i <= j; i++, j--)
	{
		if (s[i] != s[j])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	string s = "babad";
	string longesPalindrom = "";
	int max = 0;

	for (int i = 0; i < s.size(); i++)
	{
		string word = "";
		for (int j = 0; j < s.size(); j++)
		{
			word += s[j];
			if (isPalindrom(word) && word.size() > max)
			{
				longesPalindrom = word;
			}
		}
	}

	cout << "Longest Palindromic Substring : " << longesPalindrom << endl;
}