#include <cstdlib>
#include <cstdio>
#include <climits>

int main()
{
	int number_of_cases;
	scanf("%d", &number_of_cases);
	for(int i = 1; i <= number_of_cases; ++i)
	{
		printf("Case #%d: ", i);
		long long a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		if(a > 0 && b > 0 && a > LLONG_MAX - b)
			printf("true");
		else if(a < 0 && b < 0 && a < LLONG_MIN - b)
			printf("false");
		else
			printf(a + b > c ? "true" : "false");
		printf("\n");
	}
	return 0;
}