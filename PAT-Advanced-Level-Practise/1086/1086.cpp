#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

struct Node 
{
  int id;
  Node* left;
  Node* right;
  Node(int id):id(id), left(nullptr), right(nullptr) {}
};

Node* build_tree(vector<int> pre_order, vector<int> in_order, int pre_order_begin, int in_order_begin, int node_count) 
{
    if(node_count <= 0) return nullptr;
    int root_id = pre_order[pre_order_begin];
    Node* root = new Node(root_id);
    for(int i = in_order_begin; i < in_order_begin + node_count; ++i) 
    {
        if(root_id == in_order[i]) 
        {
            int left_node_count =  i - in_order_begin;
            root->left = build_tree(pre_order, in_order, pre_order_begin + 1, in_order_begin, left_node_count);
            root->right = build_tree(pre_order, in_order, pre_order_begin + left_node_count + 1, i + 1, node_count - left_node_count - 1);
        }
    }
    return root;
}



void post_order_traversal(Node* root) 
{
    static bool firest_has_output = false;
    if(root == nullptr) 
        return;
    post_order_traversal(root->left);
    post_order_traversal(root->right);
    if(firest_has_output) 
    {
        cout << ' ';
    }
    firest_has_output = true;
    cout << root->id;
}

int main()
{
    int n;
    stack<int> stack;
    vector<int> pre_order;  // 先序
    vector<int> in_order;   // 中序

    cin >> n;
    int i = 0;
    string op;
    int id;
    while(i < n) 
    {
        cin >> op;
        if(op == "Push")
        {
            cin >> id;
            pre_order.push_back(id);
            stack.push(id);
        }
        else // op == "Pop"
        {
            in_order.push_back(stack.top());
            stack.pop();
            ++i;
        }
    }
    Node* root = build_tree(pre_order, in_order, 0, 0, n);
    post_order_traversal(root);
    return 0;
}