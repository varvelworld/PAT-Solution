#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    unsigned long number;
    cin >> number;
    cout << number << "=";
    bool had_out_factor = false;
    for(int i = 2; i <= sqrt(number); ++i)
    {
        int count_i = 0;
        while(number % i == 0)
        {
            number /= i;
            ++count_i;
        }
        if(count_i != 0)
        {
            if(had_out_factor)
                cout << "*";
            else
                had_out_factor = true;
            if(count_i == 1)
                cout << i;
            else if(count_i > 1)
                cout << i << "^" << count_i;
        }
    }
    if(number != 1)
    {
        if(had_out_factor)
            cout << "*";
        else
            had_out_factor = true;
        cout << number << endl;
    }
    else if(number == 1 && !had_out_factor)
    {
        cout << number << endl;
    }
    return 0;
}