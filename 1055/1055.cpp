#include <algorithm>
#include <iostream>
#include <iterator>  
#include <cstdlib>
#include <cstring>  
#include <cstdio>  

using namespace std;

#define MAX_AGE 200
#define MAX_OUTPUT_NUM 100
#define MAX_PEOPEL_NUM 100000

struct Richer
{
    char name[10];
    int age;
    int worth;
    bool operator < (const Richer& r) const{
        if((*this).worth < r.worth)
            return true;
        else if((*this).worth == r.worth)
        {
            if((*this).age > r.age)
                return true;
            else if((*this).age == r.age)
            {
                return strcmp((*this).name, r.name) > 0;
            }
        }
        return false;
    }
    bool operator > (const Richer& r) const{
        if((*this).worth > r.worth)
            return true;
        else if((*this).worth == r.worth)
        {
            if((*this).age < r.age)
                return true;
            else if((*this).age == r.age)
            {
                return strcmp((*this).name, r.name) < 0;
            }
        }
        return false;
    }
};

int ageCount[MAX_AGE + 1] = {0};

int richer[MAX_PEOPEL_NUM];

int main()
{
    Richer* people = new Richer[MAX_PEOPEL_NUM * 1000];
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; ++i)
    {
        scanf("%s%d%d", people[i].name, &people[i].age, &people[i].worth);  
    }
    sort(people, people + n, [](const Richer& a, const Richer& b){return a > b;});
    int r = 0;
    for(int i = 0; i < n; ++i)
    {
        if(++ageCount[people[i].age] <= MAX_OUTPUT_NUM)
        {
            richer[r++] = i;
        }
    }
    int richer_num = r;
    for(int i = 1; i <= k; ++i)
    {
        int max_output, min_age, max_age;
        scanf("%d%d%d", &max_output, &min_age, &max_age);  
        printf("Case #%d:\n",i);
        int j = 0;
        for(int i = 0; i < richer_num && j < max_output; ++i)
        {
            int age = people[richer[i]].age;
            if(min_age <= age && age <= max_age)
            {
                printf("%s %d %d\n", people[richer[i]].name, age, people[richer[i]].worth);
                ++j;
            }
        }
        if(j == 0)
        {
            printf("None\n");
        }
    }
    return 0;
}