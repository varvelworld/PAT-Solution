#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Mooncake
{
    double inventory;
    double price;
    double avg_price;
};

int main()
{
    int number_of_kind;
    int total_demand;
    cin >> number_of_kind >> total_demand;
    Mooncake* mooncakes = new Mooncake[number_of_kind];
    for(int i = 0; i < number_of_kind; ++i)
        cin >> mooncakes[i].inventory;
    for(int i = 0; i < number_of_kind; ++i)
    {
        cin >> mooncakes[i].price;
        mooncakes[i].avg_price = mooncakes[i].price / mooncakes[i].inventory;
    }
    sort(mooncakes, mooncakes + number_of_kind, [](const Mooncake &a, const Mooncake &b) {
        return a.avg_price > b.avg_price;
    });
    double profit = 0;
    for(int i = 0; i < number_of_kind && total_demand > 0; ++i)
    {
        if(total_demand <= mooncakes[i].inventory)
        {
            profit += mooncakes[i].avg_price * total_demand;
            total_demand = 0;
        }
        else
        {
            profit += mooncakes[i].avg_price * mooncakes[i].inventory;
            total_demand -= mooncakes[i].inventory;
        }
    }
    cout << setiosflags(ios::fixed) << setprecision(2) << profit;
    return 0;
}