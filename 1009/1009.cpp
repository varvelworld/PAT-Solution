#include <iostream>
#include <map>
#include <functional>
#include <iomanip>

using namespace std;

void input_polynomial(map<int, float, greater<int>> &polynomial) 
{
    int length;
    cin >> length;
    for(int i = 0; i < length; ++i) 
    {
        int exp;
        float c;
        cin >> exp >> c;
        polynomial.insert(make_pair(exp, c));
    }
}

int main() 
{
    map<int, float, greater<int>> a, b;             // a,b 多项式, key为指数，value为系数，降序排序
    map<int, float, greater<int>> result;           // a,b 多项式乘积结果
    input_polynomial(a);
    input_polynomial(b);
    for(auto iter_a = a.begin(); iter_a != a.end(); ++iter_a)
    {
        for(auto iter_b = b.begin(); iter_b != b.end(); ++iter_b)
        {
            int exp = iter_a->first + iter_b->first;
            float c = iter_a->second * iter_b->second;
            auto iter = result.find(exp);
            if(iter == result.end()) 
            {
                result.insert(make_pair(exp, c));
            }
            else 
            {
                iter->second = iter->second + c;
            }
        }
    }
    for(auto iter_result = result.begin(); iter_result != result.end(); ++iter_result) 
    {
        if((int)(iter_result->second * 10) == 0) 
            iter_result = result.erase(iter_result);
    }
    cout << result.size();
    for(auto iter_result = result.begin(); iter_result != result.end(); ++iter_result) 
    {
        cout << ' ' << iter_result->first << ' ' << setiosflags(ios::fixed) << setprecision(1) << iter_result->second;
    }
    cout << endl;
    return 0;
}