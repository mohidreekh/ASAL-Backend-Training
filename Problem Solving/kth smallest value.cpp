#include <iostream>
#include<algorithm>
using namespace std;
struct Node {
	int item;
	Node* left;
	Node* right;
};

Node* insert(Node* root, int val) {

    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->item = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (val > root->item) {
        root->right = insert(root->right, val);
    }
    else {
        root->left = insert(root->left, val);
    }
    return root;
}

void kthSmallestValue(Node* root, int &k, int &result) {
    if (root == nullptr || k <= 0)
        return;

    kthSmallestValue(root->left, k, result);

    if (--k == 0)
        result = root->item;
    
    kthSmallestValue(root->right, k, result);
}

int main() {
	Node* root = nullptr;

    int arr[] = { 5,6,3,2,4,1 };
    int k = 3;

    int x;
	for (auto i : arr)
	{
		root = insert(root, i);
	}

    int result;
    kthSmallestValue(root, k, result);
    cout << "Result:" << result;
}