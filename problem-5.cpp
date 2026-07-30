#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main() 
{
	//vector<vector<int>> triangle = { {2} ,{3,4},{6,5,7},{4,1,8,3} };
	vector<vector<int>> triangle = { {-10} };

	int sum = 0;
	for (int i = 0; i < triangle.size(); i++)
	{
		int minValue = *min_element(triangle[i].begin(), triangle[i].end());
		sum += minValue;
	}
	cout << sum << endl;
}