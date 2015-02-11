#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

/**
 * 计算m位9的“one”个数
**/
int count_ones(int m)
{
	if(m == 1)
		return 1;
	else
		return count_ones(m - 1) * 10 + pow(10, m - 1);
}

/**
  *计算number_str“one”的个数
**/
int count_ones(char *number_str, int m)
{
	if(m == 1)
		return number_str[0] >= '1' ? 1 : 0;
	if(number_str[0] == '0')
		return count_ones(number_str + 1, m - 1);
	else if(number_str[0] == '1')
		return atoi(number_str + 1) + 1 + count_ones(m - 1) + count_ones(number_str + 1, m - 1);
	else
		return (number_str[0] - '0') * count_ones(m - 1) + pow(10, m - 1) + count_ones(number_str + 1, m - 1);
}

int main()
{
	char number_str[15];
	scanf("%s", number_str);
	printf("%d", count_ones(number_str, strlen(number_str)));
	return 0;
}