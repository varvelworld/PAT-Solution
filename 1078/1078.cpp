#include <cstdio>
#include <cmath>
#include <cstring>

bool is_prime(int number)
{
    if(number == 1) return false;
    for(int i = 2; i <= sqrt(number); ++i)
        if(number % i == 0) return false;
    return true;
}

int main()
{
    int m_size, n;
    scanf("%d%d", &m_size, &n);
    int t_size = m_size;
    while(!is_prime(t_size)) ++t_size;
    int *hast_table = new int[t_size];
    memset(hast_table, 0, sizeof(int) * t_size);
    for(int i = 0; i < n; ++i)
    {
        int number;
        scanf("%d", &number);
        int hash = number % t_size;
        int offset = 0;
        int index;
        while(hast_table[index = (hash + offset * offset) % t_size] != 0 && offset < t_size) ++offset;
        if(i > 0) printf(" ");
        if(offset == t_size) printf("-");
        else
        {
            hast_table[index] = number;
            printf("%d", index);
        }
    }
    printf("\n");
    return 0;
}

