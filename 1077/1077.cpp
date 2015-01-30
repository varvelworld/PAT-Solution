#include <cstdlib>
#include <cstdio>
#include <cstring>

char* compute_common_suffix(char *a, char *b)
{
    int length_of_a = strlen(a);
    int length_of_b = strlen(b);
    char* p = a + length_of_a - 1;
    char* q = b + length_of_b - 1;
    while(p >= a && q >= b && *p == *q)
    {
        --p; --q;
    }
    return p + 1;
}

int main()
{
    int number_of_files;
    scanf("%d", &number_of_files);
    getchar();
    char file_1th[257], file[257];
    gets(file_1th);
    char *common_suffix = file_1th;
    for(int i = 2; i <= number_of_files; ++i)
    {
        gets(file);
        common_suffix = compute_common_suffix(common_suffix, file);
    }
    if(strlen(common_suffix) == 0)
        printf("nai\n");
    else
        printf("%s\n", common_suffix);
    return 0;
}