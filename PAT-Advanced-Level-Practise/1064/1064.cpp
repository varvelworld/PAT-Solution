#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#define EMPTY -1    //空元素

using namespace std;

int main()
{
    int k, in;
    int full_num;           //满二叉树元素数
    int insert_empty_num;   //转成完全树需要插入的空元素数
    vector<int> a;
    vector<int> t;          //临时列表

    cin >> k;
    for(int i = 0; i < k; ++i)
    {
        cin >> in;
        a.push_back(in);
    }
    sort(a.begin(), a.end());
    full_num = pow(2, ceil(log(a.size() + 1) / log(2))) - 1;
    insert_empty_num = full_num - a.size();
    if(insert_empty_num > 0)
    {
        copy(a.begin() + (a.size() - insert_empty_num), a.end(), back_inserter(t));
        a.erase(a.begin() + (a.size() - insert_empty_num), a.end());
        vector<int>::iterator iter_t = t.begin();
        while(iter_t != t.end())
        {
            a.push_back(*(iter_t++));
            a.push_back(EMPTY);
        }
    }
    //层遍历
    int first = a.size();
    int setp = (a.size() + 1) * 2;
    int flag = 0;
    do
    {
        first /= 2;
        setp /= 2;
        for(int i = first; i < a.size(); i += setp)
        {
            if(a[i] != EMPTY)
            {
                cout << (flag == 0 ? "" : " ") << a[i];
                flag = 1;
            }
        }
    } while(first > 0);
    cout << '\n';
    return 0;
}