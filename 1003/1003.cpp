#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

struct FlowEdge;
struct ResidualEdge; 

struct Vertex
{
    char name[4];
    FlowEdge *flow_edges;           // 流网络
    ResidualEdge *residual_edges;   // 残留网
    int dirty_flag;
    int bfs_color;
    ResidualEdge* bfs_in_edge;
    Vertex(char name[4]): flow_edges(nullptr), residual_edges(nullptr), dirty_flag(0), bfs_color(0), bfs_in_edge(nullptr)
    {
        strcpy(this->name, name);
    }
};

struct FlowEdge
{
    Vertex *src_vex;
    Vertex *dst_vex;
    int capacity;
    int flow;
    FlowEdge *next;
    FlowEdge(Vertex *src_vex, Vertex *dst_vex, int capacity):src_vex(src_vex), dst_vex(dst_vex), capacity(capacity), flow(0), next(nullptr) {}
};

struct ResidualEdge
{
    Vertex *src_vex;
    Vertex *dst_vex;
    FlowEdge *flow_edge;
    int residual;
    bool is_reverse;   //是否反向弧
    ResidualEdge *next;
    ResidualEdge *corresponding_edge;
    ResidualEdge(Vertex *src_vex, Vertex *dst_vex, FlowEdge *flow_edge, int residual, bool is_reverse):src_vex(src_vex), dst_vex(dst_vex), flow_edge(flow_edge), residual(residual), is_reverse(is_reverse), next(nullptr), corresponding_edge(nullptr) {}
};

inline int compute_key(char str[])
{
    int key = 0;
    key = key | str[0];
    key = key << 8 | str[1];
    key = key << 8 | str[2];
    return key;
}

int main()
{
    char src_planet[4], dst_planet[4];
    int number_of_edges;
    scanf("%s%s%d", src_planet, dst_planet, &number_of_edges);
    map<int, Vertex*> vex_set;// 顶点集
    Vertex *src_planet_vex = new Vertex(src_planet);
    Vertex *dst_planet_vex = new Vertex(dst_planet);
    vex_set.insert(make_pair(compute_key(src_planet), src_planet_vex));
    vex_set.insert(make_pair(compute_key(dst_planet), dst_planet_vex));
    for(int i = 0; i < number_of_edges; ++i)
    {
        char src[4], dst[4];
        int capacity;
        scanf("%s%s%d", src, dst, &capacity);
        int src_key = compute_key(src), dst_key = compute_key(dst);
        Vertex* src_vex, *dst_vex;
        auto src_vex_iter = vex_set.find(src_key);
        if(src_vex_iter != vex_set.end())
            src_vex = src_vex_iter->second;
        else
        {
            src_vex = new Vertex(src);
            vex_set.insert(make_pair(src_key, src_vex));
        }
        auto dst_vex_iter = vex_set.find(dst_key);
        if(dst_vex_iter != vex_set.end())
            dst_vex = dst_vex_iter->second;
        else
        {
            dst_vex = new Vertex(dst);
            vex_set.insert(make_pair(dst_key, dst_vex));
        }
        FlowEdge *flow_edge = new FlowEdge(src_vex, dst_vex, capacity);
        flow_edge->next = src_vex->flow_edges;
        src_vex->flow_edges = flow_edge;
        ResidualEdge *forward_residual_edge = new ResidualEdge(src_vex, dst_vex, flow_edge, capacity, false); // 正向弧
        forward_residual_edge->next = src_vex->residual_edges;
        src_vex->residual_edges = forward_residual_edge;
        ResidualEdge *reverse_residual_edge = new ResidualEdge(dst_vex, src_vex, flow_edge, 0, true);        // 反向弧
        reverse_residual_edge->next = dst_vex->residual_edges;
        dst_vex->residual_edges = reverse_residual_edge;
        forward_residual_edge->corresponding_edge = reverse_residual_edge;
        reverse_residual_edge->corresponding_edge = forward_residual_edge;
    }
    int i = 0;
    while(true)
    {
        // bfs搜索最短路径
        queue<Vertex*> bfs_queue;
        src_planet_vex->bfs_color = 1;  //涂灰
        src_planet_vex->bfs_in_edge = nullptr;
        src_planet_vex->dirty_flag = i;
        dst_planet_vex->bfs_color = 0;  //涂白
        dst_planet_vex->bfs_in_edge = nullptr;
        dst_planet_vex->dirty_flag = i;
        bfs_queue.push(src_planet_vex);
        while(!bfs_queue.empty())
        {
            Vertex* vex = bfs_queue.front();
            bfs_queue.pop();
            vex->bfs_color = 2; // 涂黑
            if(vex == dst_planet_vex)
                break;
            ResidualEdge* edge = vex->residual_edges;
            while(edge)
            {
                if(edge->residual > 0) 
                {
                    if(edge->dst_vex->dirty_flag < i)
                    {
                        edge->dst_vex->bfs_color = 0;
                        src_planet_vex->bfs_in_edge = nullptr;
                        edge->dst_vex->dirty_flag = i;
                    }
                    if(edge->dst_vex->bfs_color == 0)
                    {
                        bfs_queue.push(edge->dst_vex);
                        edge->dst_vex->bfs_in_edge = edge;
                        edge->dst_vex->bfs_color = 1; // 涂灰
                    }
                }
                edge = edge->next;
            }
        }
        ResidualEdge* edge = dst_planet_vex->bfs_in_edge;
        if(edge == nullptr)
            break;
        vector<ResidualEdge*> path;
        int min_residual = numeric_limits<int>::max();
        while(edge)
        {
            if(edge->residual < min_residual)
                min_residual = edge->residual;
            path.push_back(edge);
            edge = edge->src_vex->bfs_in_edge;
        }
        for(auto iter = path.begin(); iter != path.end(); ++iter)
        {
            (*iter)->residual -= min_residual;
            if((*iter)->is_reverse)
            {
                (*iter)->flow_edge->flow -= min_residual;
                (*iter)->corresponding_edge->residual += min_residual; // 正向残余弧
            }
            else 
            {
                (*iter)->flow_edge->flow += min_residual;
                (*iter)->corresponding_edge->residual -= min_residual; // 反向残余弧
            }
        }
        ++i;
    }
    FlowEdge* flow_edge = src_planet_vex->flow_edges;
    int total_flow = 0;
    while(flow_edge)
    {
        total_flow += flow_edge->flow;
        flow_edge = flow_edge->next;
    }
    printf("%d\n", total_flow);
    return 0;
}