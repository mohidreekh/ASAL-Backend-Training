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

bool hasPathSum(Node* root, int targetSum, int currentSum)
{
    if (root == nullptr)
        return false;

    currentSum += root->val;

    if (root->left == nullptr && root->right == nullptr)
    {
        return currentSum == targetSum;
    }

    return hasPathSum(root->left, targetSum, currentSum) ||
        hasPathSum(root->right, targetSum, currentSum);
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

    if (hasPathSum(root, targetSum, 0))
        cout << "Path exists" << endl;
    else
        cout << "Path does not exist" << endl;
}