#include <cstdio>
#include <queue>

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node(int key): key(key), left(nullptr), right(nullptr) {}
};

Node* travel_to_tree(int postorder[], int inorder[], int number_of_nodes)
{
    int key = postorder[number_of_nodes - 1];
    Node *root = new Node(key);
    int i;
    for(i = 0; i < number_of_nodes; ++i)
        if(inorder[i] == key) break;
    int left_number_of_nodes = i;
    int right_number_of_nodes = number_of_nodes - i - 1;
    root->left = left_number_of_nodes == 0 ? nullptr : travel_to_tree(postorder, inorder, left_number_of_nodes);
    root->right = right_number_of_nodes == 0 ? nullptr : travel_to_tree(postorder + i, inorder + i + 1, right_number_of_nodes);
    return root;
}


int main()
{
    int postorder[30];
    int inorder[30];
    int number_of_nodes;
    scanf("%d", &number_of_nodes);
    for(int i = 0; i < number_of_nodes; ++i)
        scanf("%d", postorder + i);
    for(int i = 0; i < number_of_nodes; ++i)
        scanf("%d", inorder + i);
    Node *root = travel_to_tree(postorder, inorder, number_of_nodes);
    std::queue<Node*> q;
    q.push(root);
    if(!q.empty())
    {
        Node *node = q.front();
        q.pop();
        printf("%d", node->key);
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    while(!q.empty())
    {
        Node *node = q.front();
        q.pop();
        printf(" %d", node->key);
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    return 0;
}