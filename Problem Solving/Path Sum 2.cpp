#include <iostream>
#include<vector>
using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;

    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};


void dfs(Node* root, int targetSum, vector<vector<int>>& vPathes, vector<int>& path)
{
    if (!root) {
        return;
    }

    targetSum -= root->val;
    path.push_back(root->val);

    if (!root->left && !root->right && targetSum == 0) {
        vPathes.push_back(path);
    }

    dfs(root->left, targetSum, vPathes, path);
    dfs(root->right, targetSum, vPathes, path);

    path.pop_back();
}

vector<vector<int>> pathSum(Node* root, int targetSum)
{
    vector<vector<int>> vPathes;
    vector<int> path;

    dfs(root, targetSum, vPathes, path);

    return vPathes;
}


int main()
{
    Node* root = new Node(5);

    root->left = new Node(4);
    root->right = new Node(8);

    root->left->left = new Node(11);

    root->left->left->left = new Node(7);
    root->left->left->right = new Node(2);

    root->right->left = new Node(13);
    root->right->right = new Node(4);

    root->right->right->right = new Node(1);
    root->right->right->left = new Node(5);

    int targetSum = 22;

    vector<vector<int>> vPathes = pathSum(root, targetSum);
    for (int i = 0; i < vPathes.size(); i++)
    {
        cout << "[";
        for (int j = 0; j < vPathes[i].size(); j++)
        {
            cout << vPathes[i][j];
            if (j < vPathes[i].size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
        if (i < vPathes.size() - 1)
        {
            cout << ", ";
        }
    }
}