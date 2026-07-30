#include<iostream>
#include<algorithm>
#include<unordered_map>

using namespace std;


int main() {

	//vector<int> nums = { 2,7,11,15 };
	//vector<int> nums = { 3,2,4 };
	vector <int> nums = { 3,3 };
	int target = 6;

	unordered_map<int, int> mNums;

	for (int i = 0; i < nums.size(); i++)
	{
		mNums[nums[i]] = i;

	}

    for(int i = 0; i < nums.size(); i++)
    {
        int tryNum = target - nums[0];
        
        if(mNums.find(tryNum) != mNums.end() && i != mNums[tryNum]){
            cout << "[ " << i << " , " << mNums[tryNum] << " ]";
			break;
        }

    }

}