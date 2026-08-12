#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int value)
        : value(value), left(nullptr), right(nullptr) {
    }
};

//A node x is considered good if the path from the root of the tree to the node x 
//contains no nodes with a value greater than the value of node x
//Example 3 -> 2 -> 4
// 3 and 4 is good
void getNumberOfGoodNodes(Node* root, int& goodNum, int maxValueInPath) {

    if (root == nullptr) {
        return;
    }

    if (root->value >= maxValueInPath) {
        goodNum++;
        maxValueInPath = root->value;
    }

    getNumberOfGoodNodes(root->left, goodNum, maxValueInPath);
    getNumberOfGoodNodes(root->right, goodNum, maxValueInPath);
}

void deleteTree(Node* root)
{
    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main()
{
    Node* root = new Node(2);

    root->left = new Node(1);
    root->right = new Node(1);

    root->left->left = new Node(3);

    root->right->left = new Node(1);
    root->right->right = new Node(5);

    int numberOfGoodNodes = 0;

    getNumberOfGoodNodes(root, numberOfGoodNodes, root->value);

    cout << "Number of good nodes: " << numberOfGoodNodes << endl;

    deleteTree(root);
}