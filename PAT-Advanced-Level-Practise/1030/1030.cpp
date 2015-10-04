#include <cstdlib>
#include <cstdio>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

struct Edge;

struct Vertex
{
    int id;
    Edge *edges;

    Vertex *pre_vex; // 最短路径前继节点
    bool s; // S集合
    int d;
    int c;
};

struct Edge
{
    Vertex *dst_vex;
    int distance;
    int cost;
    Edge *next;
};

struct QueueNode
{
    Vertex *vex;
    int d;
    int c;
    QueueNode(Vertex *vex):vex(vex), d(vex->d), c(vex->c) {}
};

struct QueueNodeCmp
{
    bool operator ()(const QueueNode &a, const QueueNode &b)
    {
        if(a.d == b.d)
            return a.c > b.c;
        else
            return a.d > b.d;
    }
};

int main()
{
    int number_of_cities, number_of_high_ways, src_city, dst_city;
    scanf("%d%d%d%d", &number_of_cities, &number_of_high_ways, &src_city, &dst_city);
    Vertex *vexs = new Vertex[number_of_cities];
    for(int i = 0; i < number_of_cities; ++i)
    {
        vexs[i].id = i;
        vexs[i].edges = nullptr;
        vexs[i].pre_vex = nullptr;
        vexs[i].s = false;
        vexs[i].d = numeric_limits<int>::max();
        vexs[i].c = numeric_limits<int>::max();
    }
    for(int i = 0; i < number_of_high_ways; ++i)
    {
        int city1, city2;
        int distance, cost;
        scanf("%d%d%d%d", &city1, &city2, &distance, &cost);
        {
            Edge *edge = new Edge();
            Vertex *vex = vexs + city1;
            edge->dst_vex = vexs + city2;
            edge->distance = distance;
            edge->cost = cost;
            edge->next = vex->edges;
            vex->edges = edge;
        }
        {
            Edge *edge = new Edge();
            Vertex *vex = vexs + city2;
            edge->dst_vex = vexs + city1;
            edge->distance = distance;
            edge->cost = cost;
            edge->next = vex->edges;
            vex->edges = edge;
        }
    }
    Vertex *src_city_vex = vexs + src_city;
    Vertex *dst_city_vex = vexs + dst_city;
    priority_queue<QueueNode, vector<QueueNode>, QueueNodeCmp> q; // Q最小优先队列
    src_city_vex->d = 0;
    src_city_vex->c = 0;
    q.push(QueueNode(src_city_vex));
    while(!q.empty())
    {
        Vertex *vex = q.top().vex;
        q.pop();
        if(vex->s) continue;
        vex->s = true;
        if(vex == dst_city_vex)
            break;
        Edge *edge = vex->edges;
        while(edge != nullptr)
        {
            if(!(edge->dst_vex->s))
            {
                int d = vex->d + edge->distance;
                int c = vex->c + edge->cost;
                if(d < edge->dst_vex->d || (d == edge->dst_vex->d && c < edge->dst_vex->c))
                {
                    edge->dst_vex->d = d;
                    edge->dst_vex->c = c;
                    edge->dst_vex->pre_vex = vex;
                    q.push(QueueNode(edge->dst_vex));
                }
            }
            edge = edge->next;
        }
    }
    stack<int> path;
    Vertex *vex = dst_city_vex;
    while(vex != nullptr)
    {
        path.push(vex->id);
        vex = vex->pre_vex;
    }
    while(!path.empty())
    {
        printf("%d ", path.top());
        path.pop();
    }
    printf("%d %d\n", dst_city_vex->d, dst_city_vex->c);
    return 0;
}