#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int number_of_coins, pay;
	scanf("%d%d", &number_of_coins, &pay);
	vector<int> values;
	for(int i = 0; i < number_of_coins; ++i)
	{
		int value;
		scanf("%d", &value);
		values.push_back(value);
	}
	sort(values.begin(), values.end());
	int i = 0, j = values.size() - 1;
	while(i < j)
	{
		int add = values[i] + values[j];
		if(add > pay)
			--j;
		else if(add < pay)
			++i;
		else
			break;
	}
	if(i >= j)
		printf("No Solution\n");
	else
		printf("%d %d\n", values[i], values[j]);
	return 0;
}