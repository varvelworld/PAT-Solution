#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

struct GasStation
{
    double unit_price;
    int distance;
};

GasStation stations[501];

int main()
{
    int capacity_of_tank, total_distance, avg_distance;
    int number_of_stations;
    scanf("%d%d%d%d", &capacity_of_tank, &total_distance, &avg_distance, &number_of_stations);
    for(int i = 0; i < number_of_stations; ++i)
        scanf("%lf%d", &(stations[i].unit_price), &(stations[i].distance));
    stations[number_of_stations].distance = total_distance; // 哨兵
    stations[number_of_stations].unit_price = 0;
    assert(number_of_stations <= 500);
    sort(stations, stations + number_of_stations + 1, [](const GasStation &a, const GasStation &b){return a.distance < b.distance;});
    double current_tank = 0; // the tank is empty at the beginning
    double current_price = 0;
    double current_distance = 0;
    int full_tank_can_run = capacity_of_tank * avg_distance;
    if(stations[0].distance > 0)
    {
        printf("The maximum travel distance = %.2lf", 0);
        return 0;
    }
    for(int i = 0; i < number_of_stations;) // i当前加油站
    {
        assert(current_distance == stations[i].distance);
        if(stations[i + 1].distance > current_distance + full_tank_can_run) // 加满油也到不了
        {
            current_distance += full_tank_can_run;
            break;
        }
        double current_tank_can_run = current_tank * avg_distance;
        // 在当前油量下，找到最便宜的加油站
        int min_price_station = i;
        int j;
        for(j = i + 1; j <= number_of_stations && stations[j].distance <= current_distance + current_tank_can_run; ++j)
        {
            if(stations[j].unit_price < stations[min_price_station].unit_price)
                min_price_station = j;     
        }
        if(min_price_station > i)
        {
            current_tank -= (double)(stations[min_price_station].distance - stations[i].distance) / avg_distance;
            i = min_price_station;
            current_distance = stations[i].distance;
            continue;
        }
        // 假设满油，找到最近比现在便宜的加油站
        int less_price_station = i;
        for(j = i + 1; j <= number_of_stations && stations[j].distance <= current_distance + full_tank_can_run; ++j)
        {
            if(stations[j].unit_price < stations[i].unit_price)
            {
                less_price_station = j;  
                break;
            }
        }
        // 加油到刚好到less_price_station
        if(less_price_station > i)
        {
            current_price += ((double)(stations[less_price_station].distance - stations[i].distance) / avg_distance - current_tank) * stations[i].unit_price;
            current_tank = 0;
            i = less_price_station;
            current_distance = stations[i].distance;
            continue;
        }
        // 假设加满油，找到最便宜的加油站
        int min_price_station_except_i = i + 1;
        for(j = i + 1; j <= number_of_stations && stations[j].distance <= current_distance + full_tank_can_run; ++j)
        {
            if(stations[j].unit_price < stations[min_price_station_except_i].unit_price)
                min_price_station_except_i = j;     
        }
        // 加满油
        current_price += (capacity_of_tank - current_tank) * stations[i].unit_price;
        current_tank = capacity_of_tank;
        // 抵达min_price_station
        double d = stations[min_price_station_except_i].distance - stations[i].distance;
        current_tank -= d / avg_distance;
        //assert(current_tank >= 0);
        i = min_price_station_except_i;
        current_distance = stations[i].distance;
    }
    if(current_distance < total_distance)
        printf("The maximum travel distance = %.2lf", current_distance);
    else
        printf("%.2lf", current_price);
    return 0;
}


