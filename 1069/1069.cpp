#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
    char number_str[5];
    int number;
    scanf("%d", &number);
    while(true)
    {
        sprintf(number_str, "%04d", number);
        sort(number_str, number_str + 4, [](const char &a, const char &b){return a > b;});
        int number_non_increasing = atoi(number_str);
        sort(number_str, number_str + 4, [](const char &a, const char &b){return a < b;});
        int number_non_decreasing = atoi(number_str);
        int new_number = number_non_increasing - number_non_decreasing;
        printf("%04d - %04d = %04d\n", number_non_increasing, number_non_decreasing, new_number);
        if(new_number == 0 || new_number == 6174) break;
        number = new_number;
    }
    return 0;
}