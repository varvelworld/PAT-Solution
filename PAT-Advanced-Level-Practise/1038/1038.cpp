#include <iostream>
#include <vector>
#include <string>
#include <strstream>
#include <algorithm>

using namespace std;

int main()
{
    int number_of_numbers;
    cin >> number_of_numbers;
    vector<string> numbers;
    for(int i = 0; i < number_of_numbers; ++i)
    {
        string number;
        cin >> number;
        numbers.push_back(number);
    }
    sort(numbers.begin(), numbers.end(), [](const string &a, const string &b){
        return a + b < b + a;
    });
    strstream ss;
    for(auto iter = numbers.begin(); iter != numbers.end(); ++iter)
        ss << *(iter);
    string output;
    ss >> output;
    int i = 0;
    while(output[i] == '0' && i < output.length())
        ++i;
    if(i == output.length())
        cout << "0" << endl;
    else
        cout << output.substr(i, output.length());
    return 0;
}