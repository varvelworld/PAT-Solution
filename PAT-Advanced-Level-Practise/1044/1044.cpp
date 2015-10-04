#include <cstdlib>
#include <cstdio>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    int number_of_diamonds, pay;
    int i, j;
    scanf("%d%d", &number_of_diamonds, &pay);
    int *diamonds = new int[number_of_diamonds];
    for(i = 0; i < number_of_diamonds; ++i)
        scanf("%d", diamonds + i);
    vector<pair<int, int>> results;
    int result_pay = numeric_limits<int>::max();
    i = 0, j = 0; // i,j分别表示区间的第一元素，和最后一个元素下标，下标从0开始
    int sum = 0;
    for( ; i < number_of_diamonds; ++i)
    {
        while(j < number_of_diamonds && sum <= pay)
        {
            sum += diamonds[j];
            if(result_pay == pay)
            {
                if(sum == pay)
                {
                    results.push_back(make_pair(i ,j));
                }
            }
            else
            {
                if(sum >= pay)
                {
                    if(sum < result_pay)
                    {
                        results.clear();
                        results.push_back(make_pair(i ,j));
                        result_pay = sum;
                    }
                    else if(sum == result_pay)
                    {
                        results.push_back(make_pair(i ,j));
                        result_pay = sum;
                    }
                }
            }
            
            ++j;
        }
        --j;
        sum -= diamonds[i] + diamonds[j];
    }
    for(auto iter = results.begin(); iter != results.end(); ++iter)
        printf("%d-%d\n", iter->first + 1, iter->second + 1);
    return 0;
}