#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int number, base;
    cin >> number >> base;
    vector<int> number_in_base;
    while(number != 0)
    {
        number_in_base.push_back(number % base);
        number /= base;
    }
    // 检查
    int length_of_number_in_base = number_in_base.size();
    int i = 0, j = length_of_number_in_base - 1;
    while(i < j)
    {
        if(number_in_base[i] != number_in_base[j]) break;
        ++i; --j;
    }
    if(i >= j)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    if(length_of_number_in_base == 0)  
        number_in_base.push_back(0);
    cout << number_in_base[length_of_number_in_base - 1];
    for(i = length_of_number_in_base - 2; i >= 0 ; --i)
        cout << " " << number_in_base[i];
    return 0;
}