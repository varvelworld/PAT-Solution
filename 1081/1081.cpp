#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

long compute_gcd(long a, long b)
{
    if(a > b)
        swap(a, b);
    long c = b % a;
    while(c != 0)
    {
        b = a;
        a = c;
        c = b % a;
    }
    return a;
}

int main()
{
    int number_of_rational;
    scanf("%ld", &number_of_rational);
    long sum_numerator = 0;
    long sum_denominator = 0;
    for(int i = 0; i < number_of_rational; ++i)
    {
        string str_rational;
        cin >> str_rational;
        auto k = str_rational.find("/");
        stringstream ss;
        ss << str_rational.substr(0, k) << " " << str_rational.substr(k + 1, str_rational.size());
        long numerator;
        long denominator;
        ss >> numerator >> denominator;
        if(numerator == 0)
            continue;
        else if(sum_numerator == 0)
        {
            sum_numerator = numerator;
            sum_denominator = denominator;
        }
        else
        {
            long gcd_denominator = compute_gcd(sum_denominator, denominator);
            long lcm_denominator = sum_denominator * denominator / gcd_denominator;
            sum_numerator = lcm_denominator / sum_denominator * sum_numerator + lcm_denominator / denominator * numerator;
            sum_denominator = lcm_denominator;
        }
        // 约分
        if(sum_numerator == 0)
            sum_denominator = 0;
        else
        {
            long gcd = compute_gcd(abs(sum_numerator), sum_denominator);
            if(gcd > 1)
            {
                sum_numerator /= gcd;
                sum_denominator /= gcd;
            }
        }
    }
    int sum_integer;
    if(sum_numerator == 0)
        sum_integer = 0;
    else
    {
        sum_integer = sum_numerator / sum_denominator;
        sum_numerator %= sum_denominator;
    }
    if(sum_integer == 0)
    {
        if(sum_numerator == 0)
            printf("0\n");
        else
            printf("%ld/%ld\n", sum_numerator, sum_denominator);
    }
    else
    {
        if(sum_numerator == 0)
            printf("%ld\n", sum_integer);
        else
            printf("%ld %ld/%ld\n", sum_integer, sum_numerator, sum_denominator);
    }
    return 0;
}