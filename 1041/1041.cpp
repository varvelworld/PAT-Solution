#include <cstdio>
#include <cstdlib>

int c[10001];
int n[100000];

int main()
{
    int number_of_case;
    scanf("%d", &number_of_case);
    for(int i = 0; i < number_of_case; ++i)
    {
        int number;
        scanf("%d", &number);
        ++c[number];
        n[i] = number;
    }
    int i;
    for(i = 0; i < number_of_case; ++i)
    {
        if(c[n[i]] == 1)
        {
            printf("%d\n", n[i]);
            break;
        }
    }
    if(i == number_of_case) printf("None\n");
    return 0;
}