#include <cstdio>
#include <algorithm>
#include <queue>

struct Node {
    int key;
    int index;
    int left_index;
    int right_index;
};

Node tree[100];
int number_of_nodes;
int numbers[100];
int index_inorder[100];


void inorder_tree(int root_index){
    static int k = 0;    
    if(root_index < 0) return ;
    inorder_tree(tree[root_index].left_index);
    tree[root_index].key = numbers[k++];
    inorder_tree(tree[root_index].right_index);
}

int main() {
    scanf("%d", &number_of_nodes);
    for(int i = 0; i < number_of_nodes; ++i) {
        tree[i].index = i;
        scanf("%d%d", &(tree[i].left_index), &(tree[i].right_index));
    }
    for(int i = 0; i < number_of_nodes; ++i) {
        scanf("%d", numbers + i);
    }
    std::sort(numbers, numbers + number_of_nodes);
    inorder_tree(0);
    std::queue<Node*> q;
    printf("%d", tree->key);
    if(tree->left_index > 0) q.push(tree + tree->left_index);
    if(tree->right_index > 0) q.push(tree + tree->right_index);
    while(!q.empty()) {
        Node *n =q.front();
        q.pop();
        printf(" %d", n->key);
        if(n->left_index > 0) q.push(tree + n->left_index);
        if(n->right_index > 0) q.push(tree + n->right_index);
    }
    return 0;
}