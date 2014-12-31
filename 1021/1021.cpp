#include <iostream>
#include <set>
#include <queue>
#include <limits>
#include <iterator> 
#include <algorithm>

using namespace std;

struct Node;
struct Edge 
{
    Node *node;
    Edge *next;
    Edge():node(nullptr), next(nullptr){};
};

struct Node 
{
    int id;
    Edge *edges;
    int start_id;
    int deepth;
    int traversal;
    Node():id(0), edges(nullptr), start_id(0), deepth(0), traversal(0) {}
    Node(int id, Edge *edges):id(id), edges(edges), start_id(0), deepth(0), traversal(0) {}
};

int main()
{
    int number_of_nodes;
    cin >> number_of_nodes;
    Node *graph = new Node[number_of_nodes + 1];
    set <Node*> nodes;

    // 计算连通分量数量 union-find
    int* union_set = new int[number_of_nodes + 1];

    // init graph
    for(int i = 1; i <= number_of_nodes; ++i)
    {
        graph[i].id = i;
        graph[i].edges = nullptr;
        nodes.insert(graph + i);
        union_set[i] = i;
    }

    for(int i = 1; i <= number_of_nodes - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        {
            Edge *edge_a = new Edge();
            edge_a->node = graph + b;
            edge_a->next = graph[a].edges;
            graph[a].edges = edge_a;
        }
        {
            Edge *edge_b = new Edge();
            edge_b->node = graph + a;
            edge_b->next = graph[b].edges;
            graph[b].edges = edge_b;
        }
        int a_root_id = a;
        int b_root_id = b;
        while(union_set[a_root_id] != a_root_id)
            a_root_id = union_set[a_root_id];
        while(union_set[b_root_id] != b_root_id)
            b_root_id = union_set[b_root_id];
        union_set[a_root_id] = b_root_id;
    }

    int components_count = 0;
    for(int i = 1; i <= number_of_nodes; ++i)
        if(union_set[i] == i) ++components_count;
    if(components_count > 1)
    {
        cout << "Error: " << components_count << " components" << endl;
        return 0;
    }

    // 两次BFS
    int max_deep = 0;
    set<Node*> max_deep_nodes[2];
    Node* node = graph + 1;
    for(int i = 0; i < 2; ++i)
    {
        queue<Node*> queue;
        node->deepth = 0;
        queue.push(node);
        while(!queue.empty())
        {
            node = queue.front();
            queue.pop();
            if(node->traversal >= i + 1) continue;
            node->traversal = i + 1;
            if(max_deep == node->deepth)
                max_deep_nodes[i].insert(node);
            else if(max_deep < node->deepth)
            {
                max_deep = node->deepth;
                max_deep_nodes[i].clear();
                max_deep_nodes[i].insert(node);
            }
            Edge *e = node->edges;
            while(e != nullptr)
            {
                if(e->node->traversal >= i + 1)
                {
                    e = e->next;
                    continue;
                }
                e->node->deepth = node->deepth + 1;
                queue.push(e->node);
                e = e->next;
            }
        }
        node = *(max_deep_nodes[i].begin());
    }
    set<Node*> max_deep_nodes_union;
    set_union(max_deep_nodes[0].begin(), max_deep_nodes[0].end(), max_deep_nodes[1].begin(), max_deep_nodes[1].end(), inserter(max_deep_nodes_union, max_deep_nodes_union.begin()));
    for(auto iter = max_deep_nodes_union.begin(); iter != max_deep_nodes_union.end(); ++iter)
    {
        cout << (*iter)->id << endl;
    }

    return 0;
}