#include <cstdio>
#include <cstdlib>
#include <queue>
#include <limits>

using namespace std;

struct Edge;

struct Vertex
{
	int id; // 负数表示加油站
	Edge *edges;

	//gas station
	float min_dist;
	float avg_dist;

	// 迪克斯拉算法
	bool s;
	int d;
};

struct Edge
{
	Vertex *src;
	Vertex *dst;
	int dist;
	Edge *next;
};

struct QueueNode
{
	Vertex *vex;
	int d;
	QueueNode(Vertex *vex):vex(vex), d(vex->d) {}
};

struct QueueNodeCmp
{
	bool operator ()(const QueueNode& a, const QueueNode& b)
	{
		return a.d > b.d;
	}
};

int main()
{
	int number_of_houses, number_of_stations, number_of_roads, service_range;
	scanf("%d%d%d%d", &number_of_houses, &number_of_stations, &number_of_roads, &service_range);
	Vertex *houses = new Vertex[number_of_houses + 1];
	for(int i = 1; i <= number_of_houses; ++i)
	{
		houses[i].id = i;
		houses[i].edges = nullptr;
		houses[i].s = false;
		houses[i].d = numeric_limits<int>::max();
	}
	Vertex *stations = new Vertex[number_of_stations + 1];
	for(int i = 1; i <= number_of_stations; ++i)
	{
		stations[i].id = -i;
		stations[i].edges = nullptr;
		stations[i].s = false;
		stations[i].d = numeric_limits<int>::max();
	}
	for(int i = 1; i <= number_of_roads; ++i)
	{
		char vex1_str[5], vex2_str[5];
		Vertex *vex1, *vex2;
		int dist;
		scanf("%s%s%d", vex1_str, vex2_str, &dist);
		if(vex1_str[0] == 'G')
		{
			int station = atoi(vex1_str + 1);
			vex1 = stations + station;
		}
		else
		{
			int house = atoi(vex1_str);
			vex1 = houses + house;
		}
		if(vex2_str[0] == 'G')
		{
			int station = atoi(vex2_str + 1);
			vex2 = stations + station;
		}
		else
		{
			int house = atoi(vex2_str);
			vex2 = houses + house;
		}
		{
			Edge *edge = new Edge();
			edge->src = vex1;
			edge->dst = vex2;
			edge->dist = dist;
			edge->next = vex1->edges;
			vex1->edges = edge;
		}
		{
			Edge *edge = new Edge();
			edge->src = vex2;
			edge->dst = vex1;
			edge->dist = dist;
			edge->next = vex2->edges;
			vex2->edges = edge;
		}
	}
	for(int i = 1; i <= number_of_stations; ++i)
	{
		// 计算加油站到所有居民区最短路径
		Vertex *station = stations + i;
		priority_queue<QueueNode, vector<QueueNode>, QueueNodeCmp> q;
		station->d = 0;
		q.push(QueueNode(station));
		while(!q.empty())
		{
			Vertex *v = q.top().vex;
			q.pop();
			if(v->s) continue;
			v->s = true;
			Edge *e = v->edges;
			while(e)
			{
				if(!e->dst->s)
				{
					int d = v->d + e->dist;
					if(d < e->dst->d)
					{
						e->dst->d = d;
						q.push(QueueNode(e->dst));
					}
				}
				e = e->next;
			}
		}
		int sum_dist = 0;
		int min_dist = numeric_limits<int>::max();
		int j;
		for(j = 1; j <= number_of_houses; ++j)
		{
			sum_dist += houses[j].d;
			if(houses[j].d > service_range)
				break;
			if(houses[j].d < min_dist)
				min_dist = houses[j].d;
		}
		if(j <= number_of_houses)
		{
			station->min_dist = -1;
			station->avg_dist = -1;
		}
		else
		{
			station->min_dist = min_dist;
			station->avg_dist = (double)sum_dist / number_of_houses;
		}
		// 初始化迪克斯拉
		for(j = 1; j <= number_of_houses; ++j)
		{
			houses[j].d = numeric_limits<int>::max();
			houses[j].s = false;
		}
		for(j = 1; j <= number_of_stations; ++j)
		{
			stations[j].d = numeric_limits<int>::max();
			stations[j].s = false;
		}
	}
	int recommend_station = 1;
	for(int i = 2; i <= number_of_stations; ++i)
		if((stations[i].min_dist > stations[recommend_station].min_dist) || (stations[i].min_dist == stations[recommend_station].min_dist && stations[i].avg_dist < stations[recommend_station].avg_dist))
			recommend_station = i;
	if(stations[recommend_station].min_dist == -1)
	{
		printf("No Solution\n");
	}
	else
	{
		printf("G%d\n", recommend_station);
		printf("%.1f %.1f\n", stations[recommend_station].min_dist, stations[recommend_station].avg_dist);
	}
	return 0;
}
