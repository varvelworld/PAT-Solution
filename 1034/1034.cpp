#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge;

struct Vertex
{
    char name[4];
    int weight;
    Edge *edges;
    bool dfs_flag;

    Vertex(char name[4]): weight(0), edges(nullptr), dfs_flag(false)
    {
        strcpy(this->name, name);
    }
};

struct Edge
{
    Vertex *vex;
    Edge *next;
    Edge(Vertex *vex, Edge *next): vex(vex), next(next) {}
};

struct Gang
{
    char name[4];
    int count;
    Gang(char name[4], int count): count(count)
    {
        strcpy(this->name, name);
    }
};

map<int, Vertex*> graph;

void dfs(Vertex *vex, Vertex* &head, int &head_weight, int &count, int &double_total_weight)
{
    vex->dfs_flag = true;
    ++count;
    double_total_weight += vex->weight;
    if(vex->weight > head_weight)
    {
        head = vex;
        head_weight = vex->weight;
    }
    Edge *edge = vex->edges;
    while(edge)
    {
        if(!edge->vex->dfs_flag)
            dfs(edge->vex, head, head_weight, count, double_total_weight);
        edge = edge->next;
    }
}

int compute_key(char name[4])
{
    int key = 0;
    key = name[0] - 'A';
    key = key * 26 + (name[1] - 'A');
    key = key * 26 + (name[2] - 'A');
    return key;
}

int main()
{
    int number_of_calls, weight_threthold;
    scanf("%d%d", &number_of_calls, &weight_threthold);
    for(int i = 0; i < number_of_calls; ++i)
    {
        char name1[4], name2[4];
        int weight;
        scanf("%s%s%d", name1, name2, &weight);
        Vertex *vex1, *vex2;
        int key1 = compute_key(name1), key2 = compute_key(name2);
        auto iter_vex1 = graph.find(key1);
        if(iter_vex1 == graph.end())
        {
            vex1 = new Vertex(name1);
            graph.insert(make_pair(key1, vex1));
        }
        else
            vex1 = iter_vex1->second;
        auto iter_vex2 = graph.find(key2);
        if(iter_vex2 == graph.end())
        {
            vex2 = new Vertex(name2);
            graph.insert(make_pair(key2, vex2));
        }
        else
            vex2 = iter_vex2->second;
        vex1->edges = new Edge(vex2, vex1->edges);
        vex2->edges = new Edge(vex1, vex2->edges);
        vex1->weight += weight;
        vex2->weight += weight;
    }
    vector<Gang> gangs;
    for(auto iter = graph.begin(); iter != graph.end(); ++iter)
    {
        if(!iter->second->dfs_flag)
        {
            Vertex* head = nullptr;
            int head_weight = 0; 
            int count = 0;
            int double_total_weight = 0;
            dfs(iter->second, head, head_weight, count, double_total_weight);
            if(count > 2 && double_total_weight > weight_threthold * 2)
                gangs.push_back(Gang(head->name, count));
        }
    }
    sort(gangs.begin(), gangs.end(), [](const Gang &a, const Gang &b){return strcmp(a.name, b.name) < 0;});
    printf("%d\n", gangs.size());
    for(auto iter = gangs.begin(); iter != gangs.end(); ++iter)
    {
        printf("%s %d\n", iter->name, iter->count);
    }
    return 0;
}