#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

struct Route;

struct City
{
    string name;
    int happiness;
    Route* routes;
    bool s;                             // S集合，已计算出最短路径
    int least_cost;                     // 最少花费
    int most_happiness;                 // 最多快乐
    double max_average_happiness;       // 平均快乐
    int least_cost_count;               // 最少花费路径个数
    City* pre_recommend_city;           // 推荐路线，前继城市
    int pre_recommend_city_count;       // 推荐路线，前继城市个数
    City(string name, int happiness): 
        name(name), happiness(happiness), routes(nullptr), 
        s(false), least_cost(numeric_limits<int>::max()), most_happiness(0), 
        max_average_happiness(0), least_cost_count(0), pre_recommend_city(nullptr), pre_recommend_city_count(0){}
};

struct Route
{
    City *city;
    int cost;
    Route *next;
    Route(City* city, int cost, Route* next): city(city), cost(cost), next(next) {}
};

struct QueueNode
{
    City* city;
    int least_cost;
    int most_happiness;
    int max_average_happiness;
    QueueNode(City* city): city(city), least_cost(city->least_cost), most_happiness(city->most_happiness), max_average_happiness(city->max_average_happiness) {}
    bool operator < (const QueueNode& n) const
    {
        return this->least_cost > n.least_cost || (this->least_cost == n.least_cost && this->most_happiness < n.most_happiness) || (this->least_cost == n.least_cost && this->most_happiness == n.most_happiness && this->max_average_happiness < n.max_average_happiness);
    }
};

int main()
{
    map<string, City*> city_map;
    int number_city, number_route;
    string start_city_name;
    cin >> number_city >> number_route >> start_city_name;
    {
        City* city = new City(start_city_name, 0);
        city_map.insert(make_pair(start_city_name, city));
    }
    for(int i = 1; i < number_city; ++i)
    {
        string name;
        int happiness;
        cin >> name >> happiness;
        City* city = new City(name, happiness);
        city_map.insert(make_pair(name, city));
    }
    for(int i = 0; i < number_route; ++i)
    {
        string city1_name, city2_name;
        int cost;
        cin >> city1_name >> city2_name >> cost;
        City* city1 = city_map[city1_name], *city2 = city_map[city2_name];
        city1->routes = new Route(city2, cost, city1->routes);
        city2->routes = new Route(city1, cost, city2->routes);
    }

    // 迪克斯拉算法
    priority_queue<QueueNode> queue = priority_queue<QueueNode>();
    City* start_city = city_map[start_city_name];
    start_city->least_cost = 0;
    start_city->least_cost_count = 1;
    start_city->most_happiness = start_city->happiness;
    queue.push(QueueNode(start_city));
    while(!queue.empty())
    {
        City* city = queue.top().city;
        queue.pop();
        if(city->s) continue;
        city->s = true;
        Route* route = city->routes;
        while(route != nullptr)
        {
            City* dst_city = route->city;
            if(!dst_city->s)
            {
                int cost = city->least_cost + route->cost;
                if(cost < dst_city->least_cost)
                {
                    int happiness = city->most_happiness + dst_city->happiness;
                    dst_city->least_cost_count = city->least_cost_count; 
                    dst_city->least_cost = cost;
                    dst_city->most_happiness = happiness;
                    dst_city->pre_recommend_city = city;
                    dst_city->pre_recommend_city_count = city->pre_recommend_city_count + 1;
                    dst_city->max_average_happiness = happiness / (dst_city->pre_recommend_city_count);
                    queue.push(QueueNode(dst_city));
                }
                else if(cost == dst_city->least_cost) 
                {
                    int happiness = city->most_happiness + dst_city->happiness;
                    dst_city->least_cost_count += city->least_cost_count;
                    if(happiness > dst_city->most_happiness)
                    {
                        dst_city->most_happiness = happiness;
                        dst_city->pre_recommend_city = city;
                        dst_city->pre_recommend_city_count = city->pre_recommend_city_count + 1;
                        dst_city->max_average_happiness = happiness / (dst_city->pre_recommend_city_count);
                        queue.push(QueueNode(dst_city));
                    }
                    else if(happiness == dst_city->most_happiness)
                    {
                        int max_average_happiness = happiness / (dst_city->pre_recommend_city_count);
                        if(max_average_happiness > dst_city->max_average_happiness)
                        {
                            dst_city->most_happiness = happiness;
                            dst_city->pre_recommend_city = city;
                            dst_city->pre_recommend_city_count = city->pre_recommend_city_count + 1;
                            dst_city->max_average_happiness = max_average_happiness;
                            queue.push(QueueNode(dst_city));
                        }
                    }
                }
            }
            route = route->next;
        }
    }

    City* rom_city = city_map["ROM"];
    stack<string> path;
    for(City* i = rom_city; i != nullptr; i = i->pre_recommend_city) path.push(i->name);
    cout << rom_city->least_cost_count << ' ' << rom_city->least_cost << ' ' << rom_city->most_happiness << ' ' << rom_city->max_average_happiness << endl;
    if(!path.empty())
    {
        cout << path.top();
        path.pop();
        while(!path.empty())
        {
            cout << "->" << path.top();
            path.pop();
        }
    }
    return 0;
}