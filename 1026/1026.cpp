#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <limits>

using namespace std;

struct Pair
{
    int arriving_time;
    int playing_time_interval;
    int vip_tage;

    int serving_time;
    int wating_time_interval;
};

struct PairCmp
{
    bool operator ()(Pair *a, Pair *b)
    {
        return a->arriving_time > b->arriving_time;
    }
};

struct Table
{
    int id;
    int number_of_players_served;
    bool is_vip;
    int over_time;
};

struct ServingTableCmp
{
    bool operator ()(Table *a, Table *b)
    {
        return a->over_time > b->over_time;
    }
};

struct FreeTableCmp
{
    bool operator ()(Table *a, Table *b)
    {
        return a->id > b->id;
    }
};

int str_to_time_in_seconds(char time_str[9])
{
    int time = time_str[7] - '0';
    time += (time_str[6] - '0') * 10;
    time += (time_str[4] - '0') * 60;
    time += (time_str[3] - '0') * 60 * 10;
    time += (time_str[1] - '0') * 60 * 60;
    time += (time_str[0] - '0') * 60 * 60 * 10;
    return time;
}

void time_in_seconds_to_str(int time_in_seconds, char time_str[9])
{
    int second = time_in_seconds % 60;
    time_in_seconds /= 60;
    int minute = time_in_seconds % 60;
    time_in_seconds /= 60;
    int hour = time_in_seconds;
    sprintf(time_str, "%02d:%02d:%02d", hour, minute, second);
}

Table tables[101];

int main()
{
    int number_of_pairs;    
    int number_of_tables, number_of_vip_tables;

    priority_queue<Pair*, vector<Pair*>, PairCmp> waiting_queue;    
    set<Table*, FreeTableCmp> free_vip_table_set;
    set<Pair*, PairCmp> waiting_vip_pair_set;
    priority_queue<Table*, vector<Table*>, ServingTableCmp> serving_table_queue;
    priority_queue<Table*, vector<Table*>, FreeTableCmp> free_table_queue;

    scanf("%d", &number_of_pairs);
    for(int i = 0; i < number_of_pairs; ++i)
    {
        char arriving_time_str[9];
        int playing_time_interval_in_minutes;
        Pair *pair = new Pair();
        scanf("%s%d%d", arriving_time_str, &playing_time_interval_in_minutes, &(pair->vip_tage));
        pair->arriving_time = str_to_time_in_seconds(arriving_time_str);
        pair->playing_time_interval = playing_time_interval_in_minutes * 60;
        waiting_queue.push(pair);
        if(pair->vip_tage)
            waiting_vip_pair_set.insert(pair);
    }

    scanf("%d%d", &number_of_tables, &number_of_vip_tables);
    for(int i = 1; i <= number_of_tables; ++i)
    {
        tables[i].id = i;
        tables[i].number_of_players_served = 0;
        tables[i].is_vip = false;
        tables[i].over_time = 0;
        free_table_queue.push(tables + i);
    }

    for(int i = 0; i < number_of_vip_tables; ++i)
    {
        int vip_id;
        scanf("%d", &vip_id);
        tables[vip_id].is_vip = true;
        free_vip_table_set.insert(tables + vip_id);
    }

    int now_time = str_to_time_in_seconds("08:00:00");
    int close_time = str_to_time_in_seconds("21:00:00");
    while(now_time < close_time && (!serving_table_queue.empty() || !waiting_queue.empty()))
    {
        {
            Table *serving_table;
            while(!serving_table_queue.empty() && (serving_table = serving_table_queue.top())->over_time == now_time)
            {
                serving_table_queue.pop();
                free_table_queue.push(serving_table);
                if(serving_table->is_vip)
                    free_vip_table_set.insert(serving_table);
            }
        }
        // vip优先
        {
            Pair *vip_pair;
            while(!free_vip_table_set.empty() && !waiting_vip_pair_set.empty() && now_time >= (vip_pair = *(waiting_vip_pair_set.rbegin()))->arriving_time)
            {
                Table *vip_table = *(free_vip_table_set.rbegin());
                free_vip_table_set.erase(--free_vip_table_set.end());  
                waiting_vip_pair_set.erase(--waiting_vip_pair_set.end());  
                ++(vip_table->number_of_players_served);
                vip_table->over_time = now_time + min(vip_pair->playing_time_interval, 60 * 60 * 2);
                vip_pair->serving_time = now_time;
                vip_pair->wating_time_interval = now_time - vip_pair->arriving_time;
                serving_table_queue.push(vip_table);
                // 输出
                char arriving_time_str[9], serving_time_str[9];
                time_in_seconds_to_str(vip_pair->arriving_time, arriving_time_str);
                time_in_seconds_to_str(vip_pair->serving_time, serving_time_str);
                printf("%s %s %d\n", arriving_time_str, serving_time_str, (int)((double)(vip_pair->wating_time_interval + 30) / 60));

            }
        }
        {
            Pair *pair;
            while(!free_table_queue.empty() && !waiting_queue.empty() && now_time >= (pair = waiting_queue.top())->arriving_time)
            {
                Table *table = free_table_queue.top();
                if(pair->vip_tage)
                {
                    auto iter_waiting_vip_pair = waiting_vip_pair_set.find(pair);
                    if(iter_waiting_vip_pair == waiting_vip_pair_set.end())
                    {
                        waiting_queue.pop();
                        continue;
                    }
                }
                if(table->is_vip)
                {
                    auto iter_free_vip_table = free_vip_table_set.find(table);
                    if(iter_free_vip_table == free_vip_table_set.end())
                    {
                        free_table_queue.pop();
                        continue;
                    }
                }
                if(pair->vip_tage)
                {
                    auto iter_waiting_vip_pair = waiting_vip_pair_set.find(pair);
                    if(iter_waiting_vip_pair != waiting_vip_pair_set.end())
                        waiting_vip_pair_set.erase(iter_waiting_vip_pair);
                }
                if(table->is_vip)
                {
                    auto iter_free_vip_table = free_vip_table_set.find(table);
                    if(iter_free_vip_table != free_vip_table_set.end())
                        free_vip_table_set.erase(iter_free_vip_table);
                }
                ++(table->number_of_players_served);
                table->over_time = now_time + min(pair->playing_time_interval, 60 * 60 * 2);;
                waiting_queue.pop();
                free_table_queue.pop();
                serving_table_queue.push(table);
                pair->serving_time = now_time;
                pair->wating_time_interval = now_time - pair->arriving_time;
                char arriving_time_str[9], serving_time_str[9];
                time_in_seconds_to_str(pair->arriving_time, arriving_time_str);
                time_in_seconds_to_str(pair->serving_time, serving_time_str);
                printf("%s %s %d\n", arriving_time_str, serving_time_str, (int)((double)(pair->wating_time_interval + 30) / 60));
            }
        }
        ++now_time;
    }
    int i = 1;
    if(i <= number_of_tables)
    {
        printf("%d", tables[i].number_of_players_served);
    }
    for(++i; i <= number_of_tables; ++i)
    {
        printf(" %d", tables[i].number_of_players_served);
    }
    printf("\n");
    return 0;
}