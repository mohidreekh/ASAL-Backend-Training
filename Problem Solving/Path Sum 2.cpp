#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;

    Node(int value)
        : val(value), left(nullptr), right(nullptr) {}
};

Node* buildTree()
{
    Node* root = new Node(5);

    root->left = new Node(4);
    root->right = new Node(8);

    root->left->left = new Node(11);

    root->left->left->left = new Node(7);
    root->left->left->right = new Node(2);

    root->right->left = new Node(13);
    root->right->right = new Node(4);

    root->right->right->left = new Node(5);
    root->right->right->right = new Node(1);

    return root;
}

void dfs(Node* root, int targetSum, vector<vector<int>>& paths, vector<int>& currentPath)
{
    if (!root)
    {
        return;
    }

    targetSum -= root->val;
    currentPath.push_back(root->val);

    if (!root->left && !root->right && targetSum == 0)
    {
        paths.push_back(currentPath);
    }

    dfs(root->left, targetSum, paths, currentPath);
    dfs(root->right, targetSum, paths, currentPath);

    currentPath.pop_back();
}

vector<vector<int>> pathSum(Node* root, int targetSum)
{
    vector<vector<int>> paths;
    vector<int> currentPath;

    dfs(root, targetSum, paths, currentPath);

    return paths;
}

void printPaths(const vector<vector<int>>& paths)
{
    cout << "[";

    for (size_t i = 0; i < paths.size(); i++)
    {
        cout << "[";

        for (size_t j = 0; j < paths[i].size(); j++)
        {
            cout << paths[i][j];

            if (j + 1 < paths[i].size())
            {
                cout << ", ";
            }
        }

        cout << "]";

        if (i + 1 < paths.size())
        {
            cout << ", ";
        }
    }

    cout << "]\n";
}

int main()
{
    Node* root = buildTree();

    const int targetSum = 22;

    vector<vector<int>> paths = pathSum(root, targetSum);

    printPaths(paths);

    return 0;
}