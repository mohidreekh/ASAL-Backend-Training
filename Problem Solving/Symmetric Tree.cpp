#include <iostream>
#include<vector>
#include<string>
using namespace std;
struct Node {
    int item;
    Node* left;
    Node* right;

    Node(int n) : item(n), left(nullptr), right(nullptr) {}
};

bool isTreeSymmetric(Node* leftTree, Node* rigthTree) {

    if (leftTree == nullptr && rigthTree == nullptr)
        return true;

    if (leftTree == nullptr || rigthTree == nullptr)
        return false;

    if (leftTree->item != rigthTree->item)
        return false;

    return isTreeSymmetric(leftTree->left, rigthTree->right)
        && isTreeSymmetric(leftTree->right, rigthTree->left);
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(2);
    root->left->left = new Node(3);
    root->left->right = new Node(4);
    root->right->right = new Node(3);
    root->right->left = new Node(4);

    if (isTreeSymmetric(root, root))
    {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;

    }

}