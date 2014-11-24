#include <set>
#include <vector>
#include <algorithm>
#include <iterator>  
#include <iomanip>
#include <cstdio>

using namespace std;

int main()
{
    int number_of_set;
    vector<set<int>> sets;
    scanf("%d", &number_of_set);
    for(int i = 0; i < number_of_set; ++i)
    {
        int number_of_number;
        set<int> set;
        scanf("%d", &number_of_number);
        for(int j = 0; j < number_of_number; ++j)
        {
            int number;
            scanf("%d", &number);
            set.insert(number);
        }
        sets.push_back(set);
    }
    int number_of_query;
    scanf("%d", &number_of_query);
    for(int i = 0; i < number_of_query; ++i)
    {
        int number_set_a, number_set_b;
        scanf("%d%d", &number_set_a, &number_set_b);
        set<int> set_a, set_b;
        set_a = sets[number_set_a - 1];
        set_b = sets[number_set_b - 1];
        vector<int> set_a_intersection_set_b;
        set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), back_inserter(set_a_intersection_set_b));
        printf("%.1f%%\n", ((float)set_a_intersection_set_b.size() / (set_a.size() + set_b.size() - set_a_intersection_set_b.size())) * 100);
    }
    return 0;
}