#include <cstdio>
#include <cstdlib>

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int dominants_color = 0;
    for(int i = 0; i < m * n; ++i)
    {
        int color;
        scanf("%d", &color);
        if(dominants_color == 0) 
            dominants_color = color;
        else if(color != dominants_color)
            dominants_color = 0;
    }
    printf("%d\n", dominants_color);
    return 0;
}