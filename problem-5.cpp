#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main()
{
	vector<vector<int>> triangle = { {2} ,{3,4},{6,5,7},{4,1,8,3} };
	//vector<vector<int>> triangle = { {-10} };

	int sum = triangle[0][0];
	vector<int> dp = triangle.back();

	for (int i = triangle.size() - 2; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
		}		
	}
	cout << dp[0] << endl;
}