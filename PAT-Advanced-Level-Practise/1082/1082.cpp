#include <iostream>
#include <string>
#include <stack>

using namespace std;

string unit_zh[] = {"", " Shi", " Bai", " Qian"};
string wan_unit_zh[] = {""," Wan", " Yi"};
string num_zh[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};

string thousand_num_str_to_zh(string s)
{
    string result = "";
    int k = 0;  //位数
    stack<string> stack;
    for(auto iter = s.rbegin(); iter != s.rend(); ++iter, ++k)
    {
        int n = *iter - '0';
        if(n == 0 && (stack.empty() || stack.top() == num_zh[0])) 
            continue;
        else if(n == 0) 
            stack.push(num_zh[n]);
        else stack.push(num_zh[n] + unit_zh[k]);
    }
    if(!stack.empty())
    {
        result = stack.top();
        stack.pop();
    }
    while(!stack.empty())
    {
        result = result + " " + stack.top();
        stack.pop();
    }
    return result;
}

int main()
{
    string num_str;
    stack<string> result;
    bool isNegative = false;

    cin >> num_str;

    if(num_str[0] == '-')
    {
        isNegative = true;
        num_str.erase(0, 1);
    }
    while(num_str[0] == '0')
    {
        num_str.erase(0, 1);
    }
    int k = 0;  //位数
    string thousand_num_str = "";
    for(auto iter = num_str.rbegin(); iter != num_str.rend(); ++iter, ++k)
    {
        thousand_num_str = *iter + thousand_num_str;
        if(k % 4 == 3 || num_str.rend() == iter + 1)
        {
            string num = string(thousand_num_str);
            string s = thousand_num_str_to_zh(num);
            thousand_num_str = "";
            if(s != "") result.push(s + wan_unit_zh[k / 4]);
        }
    }
    if(result.empty()) result.push(num_zh[0]);
    if(isNegative) result.push("Fu");
    if(!result.empty())
    {
        cout << result.top();
        result.pop();
    }
    while(!result.empty())
    {
        cout << ' ' << result.top();
        result.pop();
    }
    return 0;
}