#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> getThreeSum(vector<int> vNums) {
    sort(vNums.begin(), vNums.end());

    vector<vector<int>> vResult;

    for (int i = 0; i < vNums.size(); i++)
    {
        // Skip duplicate i
        if (i > 0 && vNums[i] == vNums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = vNums.size() - 1;
        while (left < right)
        {
            int sum = vNums[i] + vNums[left] + vNums[right];
            if (sum == 0)
            {
                vResult.push_back({
                    vNums[i],
                    vNums[left],
                    vNums[right]
                    });

                left++;
                right--;

                // Skip duplicate left
                while (left < right && vNums[left] == vNums[left - 1]) {
                    left++;
                }

                // Skip duplicate right
                while (left < right && vNums[right] == vNums[right + 1]) {
                    right--;
                }
            }
            else if (sum > 0)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
    return vResult;
}

int main()
{
    vector<int> vNums = { -1, 0, 1, 2, -1, -4 };
    vector<vector<int>> vResult = getThreeSum(vNums);

    cout << "Result: [";
    for (int i = 0; i < vResult.size(); i++)
    {
        cout << "[";
        for (int j = 0; j < vResult[i].size(); j++)
        {
            cout << vResult[i][j];

            if (j != vResult[i].size() - 1) {
                cout << ",";
            }
        }
        cout << "]";

        if (i != vResult.size() - 1) {
            cout << ",";
        }
    }
    cout << "]\n";
}