#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;

struct Project
{
    int profit;
    int lasting;
    int deadline;

    double arg_profit;
};

Project prjects[50];
int number_of_projects;

map<long, int> memo;

int compute_profit(int project, int deadline)
{
    long key = deadline;
    key = key << 6;
    key = key | ((long)project);
    auto iter = memo.find(key);
    if(iter != memo.end()) return iter->second;
    if(project == number_of_projects) return 0;// 出口

    int begin = min(deadline, prjects[project].deadline) - prjects[project].lasting;
    int profit_do_this = 0;
    if(begin >= 0)
        profit_do_this = compute_profit(project + 1, begin) + prjects[project].profit;

    int profit_not_do_this = compute_profit(project + 1, deadline);
    int profit = max(profit_do_this, profit_not_do_this);
    memo.insert(make_pair(key, profit));
    return profit;
}

int main()
{
    scanf("%d", &number_of_projects);
    for(int i = 0; i < number_of_projects; ++i)
    {
        scanf("%d%d%d", &(prjects[i].profit), &(prjects[i].lasting), &(prjects[i].deadline));
        prjects[i].arg_profit = (double) prjects[i].profit / prjects[i].lasting;
    }
    sort(prjects, prjects + number_of_projects, [](const Project& a, const Project& b){
        return a.deadline > b.deadline;
    });
    printf("%d\n", compute_profit(0, prjects[0].deadline));
    return 0;
}