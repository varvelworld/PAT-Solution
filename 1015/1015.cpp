#include <stdio.h>
#include <string.h>
#include <math.h>

bool is_prime(int n)
{
    if(n == 1) return false;
    for(int i = 2; i <= sqrt((double)n); ++i)
        if(n % i == 0) return false;
    return true;
}

int reverse_number(int n, int radix)
{
    int result = 0;
    while(n)
    {
        result = result * radix + n % radix;
        n /= radix;
    }
    return result;
}

int main()
{
    while(true)
    {
        int number, radix;
        scanf("%d", &number);
        if(number < 0)
            break;
        scanf("%d", &radix);
        if(is_prime(number) && is_prime(reverse_number(number, radix))) 
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}