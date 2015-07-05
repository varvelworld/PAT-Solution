#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
#include <string>

using namespace std;

struct Node
{
    int address;
    int value;
    int next_address;
    Node* next;
};

int main() 
{
    map<int, Node*> address_map_to_node;
    int head_address;
    int number_of_nodes;
    
    scanf("%d %d", &head_address, &number_of_nodes);

    for(int i = 0; i < number_of_nodes; ++i) 
    {
        Node *node = new Node();
        scanf("%d %d %d", &(node->address), &(node->value), &(node->next_address));
        address_map_to_node.insert(make_pair(node->address, node));
    }

    Node *head = address_map_to_node.find(head_address)->second;

    Node *p = head;
    while(p != nullptr) 
    {
        if(p->next_address == -1) 
        {
            p->next = nullptr;
        }
        else 
        {
            p->next = address_map_to_node.find(p->next_address)->second;
        }
        p = p->next;
    }

    bool value_bitmap[10000] = {false};
    p = head;
    Node *removed_head = nullptr;
    Node *removed_tail = nullptr;

    value_bitmap[abs(p->value)] = true;

    while(p->next != nullptr)
    {
        if(value_bitmap[abs(p->next->value)])
        {
            Node *remvoed_node = p->next;
            p->next = p->next->next;
            if(p->next != nullptr) 
                p->next_address = p->next->address;
            else
                p->next_address = -1;

            remvoed_node->next = nullptr;
            remvoed_node->next_address = -1;

            if(removed_tail == nullptr) 
            {
                removed_head = removed_tail = remvoed_node;
            }
            else
            {
                removed_tail->next = remvoed_node;
                removed_tail->next_address = remvoed_node->address;
                removed_tail = remvoed_node;
            }
        }
        else 
        {
            value_bitmap[abs(p->next->value)] = true;
            p = p->next;
        }
    }

    p = head;
    while(p != nullptr) 
    {
        if(p->next_address != -1)
            printf("%05d %d %05d\n", p->address, p->value, p->next_address);
        else
            printf("%05d %d -1\n", p->address, p->value);
        p = p->next;
    }
    p = removed_head;
    while(p != nullptr) 
    {
        if(p->next_address != -1)
            printf("%05d %d %05d\n", p->address, p->value, p->next_address);
        else
            printf("%05d %d -1\n", p->address, p->value);
        p = p->next;
    }
    return 0;
}
