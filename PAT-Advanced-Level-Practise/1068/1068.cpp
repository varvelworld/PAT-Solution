#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int coins[10000];
int number_of_coins, pay_money;

struct Result
{
	int sum;
	vector<int> pay_conins;
	Result(): sum(-1) {}
	Result(int sum): sum(0) {}
};

Result memo[10000][101];

Result fun(int i, int pay)
{
	if(memo[i][pay].sum != -1)
		return memo[i][pay];
	if(pay < coins[i])
	{
		Result r = Result(0);
		memo[i][pay] = r;
		return r;
	}
	if(i == number_of_coins - 1)
	{
		Result r = Result(0);
		r.pay_conins.push_back(coins[i]);
		r.sum += coins[i];
		memo[i][pay] = r;
		return r;
	}
	Result r1 = fun(i + 1, pay - coins[i]);
	Result r2 = fun(i + 1, pay);
	if(r1.sum + coins[i] >= r2.sum)
	{
		r1.sum += coins[i];
		r1.pay_conins.push_back(coins[i]);
		memo[i][pay] = r1;
		return r1;
	}
	else
	{
		memo[i][pay] = r2;
		return r2;
	}
}

int main()
{
	scanf("%d%d", &number_of_coins, &pay_money);
	for(int i = 0; i < number_of_coins; ++i)
		scanf("%d", coins + i);
	std::sort(coins, coins + number_of_coins);
	Result r = fun(0, pay_money);
	if(r.sum == pay_money)
	{
		auto iter = r.pay_conins.rbegin();
		if(iter != r.pay_conins.rend())
		{
			printf("%d", *iter);
			++iter;
		}
		for(; iter != r.pay_conins.rend(); ++iter)
			printf(" %d", *iter);
	}
	else
		printf("No Solution");
	printf("\n");
	return 0;
}