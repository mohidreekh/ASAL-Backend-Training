#include <iostream>
#include <climits>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int value)
        : value(value), left(nullptr), right(nullptr) {
    }
};

//a node x is considered good if the path from the root of the tree to the node x 
//contains no nodes with a value greater than the value of node x
//Example 3 -> 2 -> 4
// 3 and 4 is good
void getNumberOfGoodNodes(Node* root, int &goodNum, int maxInPath) {

    if (root == nullptr)
        return;

    if (root->value >= maxInPath) {
        goodNum++;
        maxInPath = root->value;
    }

    getNumberOfGoodNodes(root->left, goodNum, maxInPath);
    getNumberOfGoodNodes(root->right, goodNum, maxInPath);
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
    int maxInPath = INT_MIN;
    getNumberOfGoodNodes(root, numberOfGoodNodes, maxInPath);

    cout << "Number of good node: " << numberOfGoodNodes << endl;
}