#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <vector>
#include <stack>
#include <string>
#include <strstream>

using namespace std;

struct Edge;
struct Vertex;

struct Vertex
{
    int id;
    int number_of_bike;
    Edge* edges;

    int d;
    bool s;
    vector<Vertex*> pre_vertexs;
    Vertex(): id(0), number_of_bike(0), edges(nullptr), d(numeric_limits<int>::max()), s(false){}
};

struct Edge
{
    Vertex* adjvex;
    int weight;
    Edge* next;
    Edge(Vertex* adjvex, int weight): adjvex(adjvex), weight(weight), next(nullptr) {}
};

struct QueueNode
{
    Vertex* vertex;
    int d;
    QueueNode(Vertex* vertex, int d): vertex(vertex), d(d) {};
};

struct QueueNodeCmp
{
    bool operator() (const QueueNode& a, const QueueNode& b)
    {
        return a.d > b.d;
    }
};

void dfs(Vertex* vertex, stack<int>* path, vector<stack<int>*>* paths)
{
    if(vertex->id == 0)
        paths->push_back(new stack<int>(*path));
    else
    {
        path->push(vertex->id);
        for(auto iter = vertex->pre_vertexs.begin(); iter != vertex->pre_vertexs.end(); ++iter)
            dfs(*iter, path, paths);
        path->pop();
    }
}

int main()
{
    int capacity_of_station;
    int number_of_stations;
    int problem_station_index;
    int number_of_roads;
    cin >> capacity_of_station >> number_of_stations >> problem_station_index >> number_of_roads;
    Vertex *graph = new Vertex[number_of_stations + 1];
    for(int i = 1; i <= number_of_stations; ++i)
    {
        graph[i].id = i;
        cin >> graph[i].number_of_bike;
    }
    for(int i = 1; i <= number_of_roads; ++i)
    {
        int city1, city2, time;
        cin >> city1 >> city2 >> time;
        Vertex *vex1 = graph + city1;
        Vertex *vex2 = graph + city2;
        {
            Edge *edge = new Edge(vex2, time);
            edge->next = vex1->edges;
            vex1->edges = edge;
        }
        {
            Edge *edge = new Edge(vex1, time);
            edge->next = vex2->edges;
            vex2->edges = edge;
        }
    }
    priority_queue<QueueNode, vector<QueueNode>, QueueNodeCmp> q;
    q.push(QueueNode(graph, 0));
    graph->d = 0;
    while(!q.empty())
    {
        Vertex* v = q.top().vertex;
        q.pop();
        if(v->s) continue;
        v->s = true;
        Edge* e = v->edges;
        while(e)
        {
            Vertex* adjvex = e->adjvex;
            if(!adjvex->s)
            {
                int d = v->d + e->weight;
                if(d < adjvex->d)
                {
                    adjvex->pre_vertexs.clear();
                    adjvex->pre_vertexs.push_back(v);
                    adjvex->d = d;
                    q.push(QueueNode(adjvex, d));
                }
                else if(d == adjvex->d)
                {
                    adjvex->pre_vertexs.push_back(v);
                    q.push(QueueNode(adjvex, d));
                }
            }
            e = e->next;
        }
    }
    // dfs遍历得到所有最短路径
    stack<int>* path = new stack<int>();
    vector<stack<int>*>* paths = new vector<stack<int>*>();
    dfs(graph + problem_station_index, path, paths);

    // 从最短路径中比较出最优解
    int min_send_bike = numeric_limits<int>::max();
    int min_back_bike = numeric_limits<int>::max();
    string optimal_path_str;
    for(auto iter = paths->begin(); iter != paths->end(); ++iter)
    {
        int send_bike = 0;
        int back_bike = 0;
        string path_str = "0";
        stack<int>* path = *iter;
        while(!path->empty())
        {
            int index = path->top();
            path->pop();
            strstream ss;
            string index_str; ss << index; ss >> index_str; // int 转 string
            path_str += "->" + index_str;
            int need_bike = capacity_of_station / 2 - graph[index].number_of_bike;
            if(need_bike > 0)
            {
                send_bike += max(need_bike - back_bike, 0);
                back_bike = max(back_bike - need_bike, 0);
            }
            else if(need_bike < 0)
                back_bike -= need_bike;
        }
        if(send_bike < min_send_bike || (send_bike == min_send_bike && back_bike < min_back_bike))
        {
            min_send_bike = send_bike;
            min_back_bike = back_bike;
            optimal_path_str = path_str;
        }
    }
    cout << min_send_bike << " " << optimal_path_str << " " << min_back_bike << endl;
    return 0;
}