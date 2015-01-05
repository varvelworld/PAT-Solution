#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node
{
    string address;
    int key;
    string next;
    Node(): key(0) {}
};

bool operator < (const Node& a, const Node& b)
{
    return a.key < b.key;
}

int main()
{
    int number_of_nodes;
    string head_address;
    cin >> number_of_nodes >> head_address;
    unordered_map<string, Node> address_to_node;
    for(int i = 0; i < number_of_nodes; ++i)
    {
        Node node;
        cin >> node.address >> node.key >> node.next;
        address_to_node.insert(make_pair(node.address, node));
    }
    vector<Node> list;
    string p = head_address;
    while(p != "-1")
    {
        Node node = address_to_node.find(p)->second;
        list.push_back(node);
        p = node.next;
    }
    sort(list.begin(), list.end());
    head_address = list.begin() != list.end() ? list.begin()->address : "-1";
    cout << list.size() << " " << head_address << endl;
    for(auto iter = list.begin(); iter != list.end(); ++iter)
    {
        if(iter + 1 != list.end())
            iter->next = (iter + 1)->address;
        else
            iter->next = "-1";
        cout << iter->address << " " << iter->key << " " << iter->next << endl;
    }
    return 0;
}