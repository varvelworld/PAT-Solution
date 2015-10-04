#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int weight;
    vector<int> children;
};

Node tree[100];

void dfs(int node, vector<int> path, int sum, int given_weight_number)
{
    sum += tree[node].weight;
    path.push_back(node);
    if(sum == given_weight_number && tree[node].children.empty())
    {
        auto iter = path.begin();
        if(iter != path.end())
            printf("%d", tree[*iter].weight);
        for(++iter; iter != path.end(); ++iter)
            printf(" %d", tree[*iter].weight);
        printf("\n");
    }
    else if(sum >= given_weight_number)
        return;
    else
    {
        for(auto iter = tree[node].children.begin(); iter != tree[node].children.end(); ++iter)
            dfs(*iter, path, sum, given_weight_number);
    }

}

int main()
{
    int number_of_nodes, number_of_non_leaf_nodes, given_weight_number;
    scanf("%d%d%d", &number_of_nodes, &number_of_non_leaf_nodes, &given_weight_number);
    for(int i = 0; i < number_of_nodes; ++i)
        scanf("%d", &(tree[i].weight));
    for(int i = 0; i < number_of_non_leaf_nodes; ++i)
    {
        int parent, number_of_children;
        scanf("%d%d", &parent, &number_of_children);
        for(int j = 0; j < number_of_children; ++j)
        {
            int child;
            scanf("%d", &child);
            tree[parent].children.push_back(child);
        }
        sort(tree[parent].children.begin(), tree[parent].children.end(), [](const int& a, const int& b){return tree[a].weight > tree[b].weight;});
    }
    dfs(0, vector<int>(), 0, given_weight_number);
    return 0;
}