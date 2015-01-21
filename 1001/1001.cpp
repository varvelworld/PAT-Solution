#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;
int main()
{
    int a, b, sum;
    cin >> a >> b;
    sum = a + b;
    stack<int> stk;

    if(sum == 0)
    {
        stk.push(0);
    }
    else if(sum < 0)
    {
        cout << "-";
        sum = -sum;
    }

    while(sum != 0)
    {
        stk.push(sum % 1000);
        sum /= 1000;
    }
    cout << stk.top();
    stk.pop();
    while(!stk.empty())
    {
        cout << ',' << setfill('0') << setw(3) << stk.top();
        stk.pop();
    }
    return 0;
}