#include <iostream>
#include <queue>
#include <limits>

using namespace std;

//Dijkstra算法
struct Edge;

struct Vertex 
{
    int key;        //城市编号
    int value;      //城市救援队数量
    Edge* edges;    //出边单链表
    bool s;         //集合S，已知最短路径结点集合
    int num;        //最短路径个数
    int d;          //最短路径长度
    int v;          //最短路径救援队数量
    Vertex() {}
    Vertex(int key, int value):key(key), value(value), edges(nullptr), s(false), num(0), d(numeric_limits<int>::max()), v(0){}
};

struct VertexQueueNode
{
    Vertex* vertex;
    int d;
    int v;
    VertexQueueNode():vertex(nullptr),d(0),v(0){}
    VertexQueueNode(Vertex* vertex):vertex(vertex),d(vertex->d),v(vertex->v){}
};

struct Edge 
{
    Vertex* dst;
    int weight;
    Edge* next;
};

struct VertexQueueNodeCmp
{
    bool operator() (const VertexQueueNode &a,const VertexQueueNode &b)
    {
        if(a.d == b.d) return a.v < b.v;
        return a.d > b.d;
    }
};

int main(){
    int n, m, c1, c2;
    cin >> n >> m >> c1 >> c2;
    Vertex* graph = new Vertex[n];
    priority_queue<VertexQueueNode, vector<VertexQueueNode>, VertexQueueNodeCmp> queue;//最小优先队列Q

    //初始化图
    for(int i = 0; i < n; ++i) 
    {
        int value;
        cin >> value;
        graph[i] = Vertex(i, value);
    }
    graph[c1].num = 1;
    graph[c1].d = 0;
    graph[c1].v = graph[c1].value;
    for(int i = 0; i < m; ++i)
    {
        int a, b, w;
        Edge* edge = new Edge;
        cin >> a >> b >> w;
        edge->weight = w;
        edge->dst = &graph[b];
        edge->next = graph[a].edges;
        graph[a].edges = edge;
        edge = new Edge;
        edge->weight = w;
        edge->dst = &graph[a];
        edge->next = graph[b].edges;
        graph[b].edges = edge;
    }

    //初始化最小优先队列
    queue.push(VertexQueueNode(&graph[c1]));

    while(!queue.empty())
    {
        Vertex* u = queue.top().vertex;
        queue.pop();
        if(u->s) continue;
        u->s = true;    //加入S集合
        Edge* e = u->edges;
        while(e != nullptr)
        {
            if(!e->dst->s)
            {
                int d = u->d + e->weight;
                int v = u->v + e->dst->value;
                if(d < e->dst->d)
                {
                    e->dst->d = d;
                    e->dst->v = v;
                    e->dst->num = u->num;
                    queue.push(VertexQueueNode(e->dst));
                }
                else if(d == e->dst->d)
                {
                    e->dst->num += u->num;
                    if(v > e->dst->v)
                    {
                        e->dst->d = d;
                        e->dst->v = v;
                        queue.push(VertexQueueNode(e->dst));
                    }
                }
            }
            e = e->next;
        }    
    }
    cout << graph[c2].num << ' ' << graph[c2].v << endl;
    return 0;
}