#include <iostream>
#include <string.h>  
#include <stdio.h>  
#include <stack>
#include <set>

using namespace std;

struct MidBalanceTree   // 中位数平衡树
{
    multiset<int> small_number_set; // 小于等于中位数的集合，左子树
    int median;                     // 中位数
    multiset<int> big_number_set;   // 大于等于中位数的集合，右子树
    MidBalanceTree(): median(-1) {};
    int peek_median()
    {
        return median;
    }

    void insert(int num)
    {
        if(median == -1) median = num;
        else
        {
            if(num < median)
                small_number_set.insert(num);
            else
                big_number_set.insert(num);
            if(small_number_set.size() + 1 < big_number_set.size())
            {
                small_number_set.insert(median);
                auto median_iter = big_number_set.begin();
                median = *median_iter;
                big_number_set.erase(median_iter);
            }
            else if(small_number_set.size() > big_number_set.size())
            {
                big_number_set.insert(median);
                auto median_iter = prev(small_number_set.end());
                median = *median_iter;
                small_number_set.erase(median_iter);
            }
        }
    }

    void erase(int num)
    {
        // assert median != -1
        if(median == num)
        {
            // assert small_number_set.size() <= big_number_set.size()
            median = -1;
            if(small_number_set.size() < big_number_set.size())    
            {
                auto median_iter = big_number_set.begin();
                median = *median_iter;
                big_number_set.erase(median_iter);
            }
            else if(!small_number_set.empty())
            {
                auto median_iter = prev(small_number_set.end());
                median = *median_iter;
                small_number_set.erase(median_iter);
            }
        }
        else if(num < median)
        {
            small_number_set.erase(small_number_set.find(num));
            if(small_number_set.size() + 1 < big_number_set.size())
            {
                small_number_set.insert(median);
                auto median_iter = big_number_set.begin();
                median = *median_iter;
                big_number_set.erase(median_iter);
            }
        }
        else // assert num > median
        {
            big_number_set.erase(big_number_set.find(num));
            if(small_number_set.size() > big_number_set.size())
            {
                big_number_set.insert(median);
                auto median_iter = prev(small_number_set.end());
                median = *median_iter;
                small_number_set.erase(median_iter);
            }
        }
    }
};

int main()
{
    int number_command;
    scanf("%d", &number_command);
    stack<int> stack;
    MidBalanceTree number_tree;
    for(int i = 0; i < number_command; ++i)
    {
        char command[16];
        scanf("%s", command);
        if(strcmp(command, "Pop") == 0)
        {
            if(stack.empty())
                printf("Invalid\n");
            else
            {
                int top = stack.top();
                stack.pop();
                number_tree.erase(top);
                printf("%d\n", top);
            }
        }
        else if(strcmp(command, "PeekMedian") == 0)
        {
            if(stack.empty())
                printf("Invalid\n");
            else
                printf("%d\n", number_tree.peek_median());
        }
        else // command  == "Push"
        {
            int num;
            scanf("%d", &num);
            stack.push(num);
            number_tree.insert(num);
        }
    }
    return 0;
}