#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Node {
	int key;
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
};

Node tree[10];
vector<int> level_order_keys;
vector<int> in_order_keys;

void level_order(Node* root) {
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node *node = q.front();
		q.pop();
		level_order_keys.push_back(node->key);
		if (node->left != nullptr) {
			q.push(node->left);
		}
		if (node->right != nullptr) {
			q.push(node->right);
		}
	}
}

void in_order(Node* node) {
	if (node == nullptr) {
		return;
	}
	else {
		in_order(node->left);
		in_order_keys.push_back(node->key);
		in_order(node->right);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		tree[i].key = i;
		string left_str, right_str;
		cin >> left_str >> right_str;
		if (right_str != "-") {
			tree[i].left = tree + stoi(right_str);
			tree[i].left->parent = tree[i].left;
		}
		if (left_str != "-") {
			tree[i].right = tree + stoi(left_str);
			tree[i].right->parent = tree[i].right;
		}
	}
	Node* root;
	for (int i = 0; i < n; ++i) {
		if (tree[i].parent == nullptr) {
			root = &(tree[i]);
		}
	}
	level_order(root);
	in_order(root);
	for (auto it = level_order_keys.begin(); it != level_order_keys.end(); ++it) {
		if (it == level_order_keys.begin()) {
			cout << *it;
		} 
		else {
			cout << " " << *it;
		}
	}
	cout << endl;
	for (auto it = in_order_keys.begin(); it != in_order_keys.end(); ++it) {
		if (it == in_order_keys.begin()) {
			cout << *it;
		}
		else {
			cout << " " << *it;
		}
	}
	cout << endl;
	return 0;
}