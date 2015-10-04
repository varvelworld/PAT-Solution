#include <cstdio>
#include <cstdlib>
#include <cstring>

bool reverse(char number[], char reversed_number[])
{
    int length = strlen(number);
    for(int i = 0; i < length; ++i)
        reversed_number[i] = number[length - 1 - i];
    reversed_number[length] = '\0';
    return strcmp(number, reversed_number) == 0;
}

void add(char number[], char reversed_number[])
{
    int length = strlen(number);
    int d = 0;
    for(int i = length - 1; i >= 0; --i)
    {
        int c = number[i] - '0' + reversed_number[i] - '0' + d;
        number[i] = '0' + c % 10;
        d = c / 10;
    }
    if(d != 0)
    {
        memmove(number + 1, number, length + 1);
        number[0] = '0' + d;
    }
}

int main()
{
    char number[113], reversed_number[113], add_result_number[113];
    int max_step;
    scanf("%s%d", number, &max_step);
    int step = 0;
    while(!reverse(number, reversed_number) && step < max_step)
    {
        add(number, reversed_number);
        ++step;
    }
    printf("%s\n%d\n", number, step);
    return 0;
}