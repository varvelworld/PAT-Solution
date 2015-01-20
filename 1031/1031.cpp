#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    char str[81];
    int n1, n2, n3;
    scanf("%s", str);
    int length = strlen(str);
    n2 = (length + 2) / 3 + (length + 2) % 3;
    n1 = n3 = (length + 2 - n2) / 2;
    for(int i = 0; i < n1 - 1; ++i)
    {
        printf("%c", str[i]);
        for(int j = 0; j < n2 - 2; ++j)
            printf(" ");
        printf("%c\n", str[length - 1 - i]);
    }
    for(int i = 0; i < n2; ++i)
        printf("%c", str[n1 - 1 + i]);
    printf("\n");
    return 0;
}