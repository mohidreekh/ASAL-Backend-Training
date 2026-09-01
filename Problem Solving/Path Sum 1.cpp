#include <iostream>

struct Node
{
    int val;
    Node* left;
    Node* right;

    Node(int value)
        : val(value), left(nullptr), right(nullptr) {}
};

bool hasPathSum(Node* root, int targetSum)
{
    if (root == nullptr)
    {
        return false;
    }

    targetSum -= root->val;

    if (root->left == nullptr && root->right == nullptr)
    {
        return targetSum == 0;
    }

    return hasPathSum(root->left, targetSum) ||
           hasPathSum(root->right, targetSum);
}

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

int main()
{
    Node* root = buildTree();

    const int targetSum = 22;

    if (hasPathSum(root, targetSum))
    {
        std::cout << "Path exists\n";
    }
    else
    {
        std::cout << "Path does not exist\n";
    }

    return 0;
}