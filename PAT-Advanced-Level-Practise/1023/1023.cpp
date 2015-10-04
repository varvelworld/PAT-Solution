#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    char number[21], _double_number[22];
    char *double_number = _double_number + 1;
    scanf("%s", &number);
    _double_number[0] = '0';
    strcpy(double_number, number);
    bool check = false;
    int d = 0; //进位
    for(int i = strlen(double_number) - 1; i >= 0; --i)
    {
        int c = (double_number[i] - '0') * 2 + d;
        double_number[i] = '0' + (c % 10);
        d = c / 10;
    }
    _double_number[0] = '0' + d;
    if(_double_number[0] != '0')
    {
        printf("No\n");
        printf("%s\n", _double_number);
    }
    else
    {
        char output_double_number[22];
        strcpy(output_double_number, double_number);
        sort(number, number + strlen(number));
        sort(double_number, double_number + strlen(double_number));
        printf("%s\n", strcmp(number, double_number) == 0 ? "Yes" : "No");
        printf("%s\n", output_double_number);
    }
    return 0;
}