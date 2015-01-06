#include <stdio.h>
#include <string.h>

#define MAX_NUMBER_OF_NODES 1000

int graph[MAX_NUMBER_OF_NODES + 1][MAX_NUMBER_OF_NODES + 1]; //注：在函数体外定义的内置数组，其元素均初始化为0 《C++ primer 中文版第4版》P.97
int component_set[MAX_NUMBER_OF_NODES + 1];

/*
 * 前置：city！= enemy_city && root != enemy_city
 */
void dfs(int root, int enemy_city, int city, int number_of_nodes)
{
    for(int i = 1; i <= number_of_nodes; ++i)
    {
        if(i != enemy_city && !component_set[i] && graph[city][i] == 1)
        {
            component_set[i] = root;
            dfs(root, enemy_city, i, number_of_nodes);
        }
    }
}

int main()
{
    int number_of_nodes, number_of_highway, number_of_concern_city;
    scanf("%d%d%d", &number_of_nodes, &number_of_highway, &number_of_concern_city);
    for(int i = 0; i < number_of_highway; ++i)
    {
        int city1, city2;
        scanf("%d%d", &city1, &city2);
        graph[city1][city2] = graph[city2][city1] = 1;
    }
    for(int i = 0; i < number_of_concern_city; ++i)
    {
        int enemy_city;
        scanf("%d", &enemy_city);
        int count_component = 0;
        memset(component_set, 0, sizeof(int) * (number_of_nodes + 1));
        for(int j = 1; j <= number_of_nodes; ++j)
        {
            if(j != enemy_city && !component_set[j])
            {
                ++count_component;
                dfs(j, enemy_city, j, number_of_nodes);
            }
        }
        printf("%d\n", count_component - 1);
    }
    return 0;
}