#include <cstdio>
#include <cstdlib>
#include <algorithm>

int coupons[100000];
int products[100000];

int main()
{
    int number_of_coupon, number_of_product;
    scanf("%d", &number_of_coupon);
    for(int i = 0; i < number_of_coupon; ++i)
        scanf("%d", coupons + i);
    scanf("%d", &number_of_product);
    for(int i = 0; i < number_of_product; ++i)
        scanf("%d", products + i);
    std::sort(coupons, coupons + number_of_coupon);
    std::sort(products, products + number_of_product);
    int i = 0;
    int s = 0;
    int p;
    while(i < number_of_coupon && i < number_of_product && coupons[i] < 0 && (p = coupons[i] * products[i]) > 0)
    {
        s += p;
        ++i;
    }
    i = 0;
    while(i < number_of_coupon && i < number_of_product && coupons[number_of_coupon - 1 - i] > 0 && (p = coupons[number_of_coupon - 1 - i] * products[number_of_product - 1 - i]) > 0)
    {
        s += p;
        ++i;
    }
    printf("%d\n", s);
    return 0;
}