#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vNums = { -1, 0, 1, 2, -1, -4 };
    vector<vector<int>> vResult;

    sort(vNums.begin(), vNums.end());

    for (int i = 0; i < vNums.size(); i++)
    {
        // Skip duplicate i
        if (i > 0 && vNums[i] == vNums[i - 1])
            continue;

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
                while (left < right && vNums[left] == vNums[left - 1])
                    left++;

                // Skip duplicate right
                while (left < right && vNums[right] == vNums[right + 1])
                    right--;
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

    cout << "Result: ";
    cout << "[";

    for (const auto& row : vResult)
    {
        cout << "[";

        for (int value : row)
        {
            cout << value << " ";
        }

        cout << "],";
    }

    cout << "]\n";
}