#include <cstdlib>
#include <cstdio>
#include <algorithm>

struct Node
{
    int key;
    Node *left;
    Node *right;
    int h; // 树高
    int a; // 平衡因子
    Node(int key):key(key), left(nullptr), right(nullptr), h(1), a(0) {}
};


void ll(Node* &node)
{
    Node *a = node, *b = a->left, *c = b->left;
    Node *w = c->left, *x = c->right, *y = b->right, *z = a->right;
    int h = w ? w->h : 0;
    b->left = c;
    b->right = a;
    c->left = w;
    c->right = x;
    a->left = y;
    a->right = z;
    a->a = b->a = c->a = 0;
    b->h = h + 2;
    a->h = c->h = h + 1;
    node = b;
}

void lr(Node *&node)
{
    Node *a = node, *b = a->left, *c = b->right;
    Node *w = b->left, *x = c->left, *y = c->right, *z = a->right;
    int h = w ? w->h : 0;
    c->left = b;
    c->right = a;
    b->left = w;
    b->right = x;
    a->left = y;
    a->right = z;
    a->a = b->a = c->a = 0;
    c->h = h + 2;
    a->h = b->h = h + 1;
    node = c;
}

void rr(Node* &node)
{
    Node *a = node, *b = a->right, *c = b->right;
    Node *w = a->left, *x = b->left, *y = c->left, *z = c->right;
    int h = w ? w->h : 0;
    b->left = a;
    b->right = c;
    a->left = w;
    a->right = x;
    c->left = y;
    c->right = z;
    a->a = b->a = c->a = 0;
    b->h = h + 2;
    a->h = c->h = h + 1;
    node = b;
}

void rl(Node* &node)
{
    Node *a = node, *b = a->right, *c = b->left;
    Node *w = a->left, *x = c->left, *y = c->right, *z = b->right;
    int h = w ? w->h : 0;
    c->left = a;
    c->right = b;
    a->left = w;
    a->right = x;
    b->left = y;
    b->right = z;
    a->a = b->a = c->a = 0;
    c->h = h + 2;
    a->h = b->h = h + 1;
    node = c;
}

void insert(Node* &root, int key)
{
    if(root == nullptr)
    {
        root = new Node(key);
        return;
    }
    if(key < root->key)
    {
        insert(root->left, key);
        if(root->right == nullptr)
        {
            root->h = root->left->h + 1;
            root->a = root->left->h;
        }
        else
        {
            root->h = std::max(root->left->h, root->right->h) + 1;
            root->a = root->left->h - root->right->h;
        }
    }
    else
    {
        insert(root->right, key);
        if(root->left == nullptr)
        {
            root->h = root->right->h + 1;
            root->a = -root->right->h;
        }
        else
        {
            root->h = std::max(root->left->h, root->right->h) + 1;
            root->a = root->left->h - root->right->h;
        }
    }
    if(root->a == 2)
    {
        if(root->left->a == 1)
            ll(root);
        else
            lr(root);
    }
    else if(root->a == -2)
    {
        if(root->right->a == -1)
            rr(root);
        else
            rl(root);
    }
}

int main()
{
    Node *root = nullptr;
    int number_of_keys;
    scanf("%d", &number_of_keys);
    for(int i = 0; i < number_of_keys; ++i)
    {
        int key;
        scanf("%d", &key);
        insert(root, key);
    }
    printf("%d\n", root->key);
    return 0;
}