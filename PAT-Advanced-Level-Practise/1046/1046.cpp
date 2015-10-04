#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int distances_of_start_i[100000 + 1 + 1];//起点到任意点的距离，从下标1开始，distances_of_start_i[number_of_exits + 1]为总长度
    int number_of_exits;
    int number_of_query;

    cin >> number_of_exits;
    distances_of_start_i[1] = 0;
    for(int i = 1;i <= number_of_exits; ++i)
    {
        cin >> distances_of_start_i[i + 1];
        distances_of_start_i[i + 1] += distances_of_start_i[i];
    }
    
    cin >> number_of_query;
    for(int i = 0; i < number_of_query; ++i)
    {
        int a, b;
        cin >> a >> b;
        int distance_of_a_b = abs(distances_of_start_i[a] - distances_of_start_i[b]);
        distance_of_a_b = min(distance_of_a_b, distances_of_start_i[number_of_exits + 1] - distance_of_a_b);
        cout << distance_of_a_b << endl;
    }
    
    return 0;
}