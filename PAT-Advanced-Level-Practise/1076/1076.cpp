#include <stdio.h>
#include <queue>
#include <limits>
// #include <cassert>

using namespace std;

struct Edge;
struct Vertex;

enum Color 
{
    black,  // 黑色表示已经被广度遍历
    gray,   // 灰色表示被发现，还没被遍历
    white   // 白色表示未发现
};

struct Vertex
{
    int id;
    Edge *edges;

    // 广度遍历信息
    int src_id;     // 广度遍历源节点id
    Color color;    // 广度遍历节点涂色
    int d;          // 到源节点的距离

    Vertex(): id(0), edges(nullptr), src_id(0), color(white), d(numeric_limits<int>::max()) {}
    Vertex(int id): id(id), edges(nullptr), src_id(0), color(white), d(numeric_limits<int>::max()) {}
};

struct Edge
{
    Vertex *dst;
    Edge *next;
    Edge(Vertex *dst): dst(dst), next(nullptr) {}
};

typedef Vertex* Graph; 

int main()
{
    int number_of_user, number_of_level;
    scanf("%d%d", &number_of_user, &number_of_level);
    Graph graph = new Vertex[number_of_user + 1];
    for(int i = 1; i <= number_of_user; ++i)
    {
        graph[i] = Vertex(i);
    }
    for(int i = 1; i <= number_of_user; ++i)
    {
        int number_of_followed;
        scanf("%d", &number_of_followed);
        for(int j = 1; j <= number_of_followed; ++j)
        {
            int followed_id;
            scanf("%d", &followed_id);
            Edge *edge = new Edge(&graph[i]);
            edge->next = graph[followed_id].edges;
            graph[followed_id].edges = edge;
        }
    }
    int number_of_query;
    scanf("%d", &number_of_query);
    for(int i = 0; i < number_of_query; ++i)
    {
        int query_id;
        scanf("%d", &query_id);
        Vertex* vertex = &(graph[query_id]);
        queue<Vertex*> queue;
        int black_count = 0;

        // 涂灰色
        vertex->src_id = query_id;
        vertex->color = gray;
        vertex->d = 0;

        queue.push(vertex);

        while(!queue.empty())
        {
            Vertex* queue_vertex = queue.front();
            queue.pop();
            //assert(queue_vertex->color != white);
            if(queue_vertex->color == gray)
            {
                // 涂黑色
                queue_vertex->src_id = query_id;
                queue_vertex->color = black;

                ++black_count;
                //assert(queue_vertex->d <= number_of_level);
                if(queue_vertex->d < number_of_level)
                {
                    Edge *edge = queue_vertex->edges;
                    while(edge)
                    {
                        Vertex* child_vertex = edge->dst;
                        if(child_vertex->src_id != 0 && child_vertex->src_id != query_id)
                        {
                            //assert(child_vertex->color == black || child_vertex->color == white);
                            // 重置之前计算的黑色和灰色节点，涂白色
                            child_vertex->src_id = 0;
                            child_vertex->color = white;
                            child_vertex->d = numeric_limits<int>::max();
                        }
                        if(child_vertex->color == white)
                        {
                            // 涂灰色
                            child_vertex->src_id = query_id;
                            child_vertex->color = gray;
                            child_vertex->d = queue_vertex->d + 1;

                            queue.push(child_vertex);
                        }
                        edge = edge->next;
                    }
                }
            }
        }
        printf("%d\n", black_count - 1);
    }
    return 0;
}