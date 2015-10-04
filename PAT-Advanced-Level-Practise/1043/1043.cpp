#include <cstdlib>
#include <cstdio>

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int key):key(key), left(nullptr), right(nullptr) {}
};

void postorder(Node *root, bool &is_first)
{
    if(root == nullptr) return;
    postorder(root->left, is_first);
    postorder(root->right, is_first);
    if(is_first)
    {
        printf("%d", root->key);
        is_first = false;
    }
    else
        printf(" %d", root->key);
}

int main()
{
    int number_of_nodes;
    scanf("%d", &number_of_nodes);
    Node *bst = nullptr, *bst_mirror = nullptr;
    bool is_bst = true, is_bst_mirror = true;
    for(int i = 0; i < number_of_nodes; ++i)
    {
        int key;
        scanf("%d", &key);
        Node *node = new Node(key);
        // insert to bst
        if(bst == nullptr) // bst == nullptr
            bst = node;
        else
        {

            Node *insert_node = bst;
            while(is_bst)
            {
                if(key < insert_node->key)
                {
                    if(insert_node->right != nullptr)
                    {
                        is_bst = false;
                        break;
                    }
                    if(insert_node->left != nullptr)
                    {
                        insert_node = insert_node->left;
                        continue;
                    }
                    else
                    {
                        insert_node->left = node;
                        break;
                    }
                }
                else // key > insert_node->key
                {
                    if(insert_node->right != nullptr)
                    {
                        insert_node = insert_node->right;
                        continue;
                    }
                    else
                    {
                        insert_node->right = node;
                        break;
                    }
                }
            }
        }
        node = new Node(key);
        // insert to bst_mirror
        if(bst_mirror == nullptr) // bst == nullptr
            bst_mirror = node;
        else
        {

            Node *insert_node = bst_mirror;
            while(is_bst_mirror)
            {
                if(key >= insert_node->key)
                {
                    if(insert_node->right != nullptr)
                    {
                        is_bst_mirror = false;
                        break;
                    }
                    if(insert_node->left != nullptr)
                    {
                        insert_node = insert_node->left;
                        continue;
                    }
                    else
                    {
                        insert_node->left = node;
                        break;
                    }
                }
                else // key < insert_node->key
                {
                    if(insert_node->right != nullptr)
                    {
                        insert_node = insert_node->right;
                        continue;
                    }
                    else
                    {
                        insert_node->right = node;
                        break;
                    }
                }
            }
        }
        if(!is_bst && !is_bst_mirror)
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    bool is_first = true;
    if(is_bst)
        postorder(bst, is_first);
    else
        postorder(bst_mirror, is_first);
    return 0;
}