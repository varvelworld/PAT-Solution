#include <iostream>
#include <string>
#include <stack>

using namespace std;

string word[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    string s;
    long sum = 0;
    cin >> s;
    for(int i = 0; i < s.length(); ++i)
    {
        sum += s[i] - '0';
    }
    stack<string> spell;
    while(sum != 0)
    {
        spell.push(word[sum % 10]);
        sum /= 10;
    }
    if(!spell.empty())
    {
        cout << spell.top();
        spell.pop();
    }
    else
    {
        cout << word[0];
    }
    while(!spell.empty())
    {
        cout << " " << spell.top();
        spell.pop();
    }
    return 0;
}