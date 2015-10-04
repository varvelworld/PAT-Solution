#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <limits>
#include <vector>
#include <cassert>

struct Highway
{
    int city1;
    int city2;
    int cost;
};

int graph_cost[501][501];
Highway destroyed_way[499 * 500];
int union_find_set[501];

/*
 * 前置：city！= enemy_city && root != enemy_city
 * 扁平树，只有一层
 */
void compute_union_find_set_by_dfs(int root, int enemy_city, int city, int number_of_city)
{
    for(int i = 1; i <= number_of_city; ++i)
    {
        if(i != enemy_city && !union_find_set[i] && graph_cost[city][i] > 0)
        {
            union_find_set[i] = root;
            compute_union_find_set_by_dfs(root, enemy_city, i, number_of_city);
        }
    }
}

int main()
{
    int number_of_city, number_of_highway;
    scanf("%d%d", &number_of_city, &number_of_highway);
    int number_of_destroyed_way = 0;
    for(int i = 0; i < number_of_highway; ++i)
    {
        int city1, city2, cost, status;
        scanf("%d%d%d%d",  &city1, &city2, &cost, &status);
        if(status)
        {
            graph_cost[city1][city2] = cost;
            graph_cost[city2][city1] = cost;
        }
        else
        {
            destroyed_way[number_of_destroyed_way].city1 = city1;
            destroyed_way[number_of_destroyed_way].city2 = city2;
            destroyed_way[number_of_destroyed_way].cost = cost;
            ++number_of_destroyed_way;
        }
    }
    std::sort(destroyed_way, destroyed_way + number_of_destroyed_way, [](const Highway &a, const Highway &b){ return a.cost < b.cost; });
    int max_total_cost = 0;
    std::vector<int> attention_citys; 
    for(int enemy_city = 1; enemy_city <= number_of_city; ++enemy_city)
    {
        int count_component = 0;
        memset(union_find_set, 0, sizeof(int) * (number_of_city + 1));
        for(int j = 1; j <= number_of_city; ++j)
        {
            if(j != enemy_city && !union_find_set[j])
            {
                ++count_component;
                union_find_set[j] = j;
                compute_union_find_set_by_dfs(j, enemy_city, j, number_of_city);
            }
        }
        int count_repair_way = count_component - 1;
        int total_cost = 0;
        for(int i = 0; i < number_of_destroyed_way && count_repair_way > 0; ++i)
        {
            int city1 = destroyed_way[i].city1;
            int city2 = destroyed_way[i].city2;
            if(city1 == enemy_city || city2 == enemy_city) continue;
            int city1_root = union_find_set[city1];
            int city2_root = union_find_set[city2];
            if(city1_root == city2_root) continue;
            //assert(city1_root != 0 && city2_root != 0 && city1_root != enemy_city && city2_root != enemy_city);
            // 修复
            for(int j = 1; j <= number_of_city; ++j)
            {
                if(union_find_set[j] == city2_root)
                    union_find_set[j] = city1_root;
            }
            int cost = destroyed_way[i].cost;
            total_cost += cost;
            --count_repair_way;
        }
        if(count_repair_way > 0) // 没有修复完成
            total_cost = std::numeric_limits<int>::max();
        if(total_cost > max_total_cost)
        {
            max_total_cost = total_cost;
            attention_citys.clear();
            attention_citys.push_back(enemy_city);
        }
        else if(total_cost > 0 && total_cost == max_total_cost)
            attention_citys.push_back(enemy_city);
    }
    if(attention_citys.empty())
        printf("0");
    else
    {
        auto iter = attention_citys.begin();
        printf("%d", *iter);
        ++iter;
        for(; iter != attention_citys.end(); ++iter)
            printf(" %d", *iter);
    }
    printf("\n");
    return 0;
}
