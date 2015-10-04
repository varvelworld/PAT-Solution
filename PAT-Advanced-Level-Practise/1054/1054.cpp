#include <cstdio>
#include <cstdlib>

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int dominants_color = 0;
    int count_dominants_color = 0;
    for(int i = 0; i < m * n; ++i)
    {
        int color;
        scanf("%d", &color);
        if(count_dominants_color == 0) 
        {
            dominants_color = color;
            ++count_dominants_color;
        }
        else if(color == dominants_color)
            ++count_dominants_color;
        else
            --count_dominants_color;
    }
    printf("%d\n", dominants_color);
    return 0;
}