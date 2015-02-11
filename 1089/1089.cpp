#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>


int main()
{
	int length;
	scanf("%d", &length);
	int seq[100];
	int sorting_seq[100];
	for(int i = 0; i < length; ++i)
		scanf("%d", seq + i);
	for(int i = 0; i < length; ++i)
		scanf("%d", sorting_seq + i);
	int k = length - 1;
	while(k >= 0 && sorting_seq[k] == seq[k])
		--k;
	int i;
	for(i = 1; i <= length; ++i)
		if(sorting_seq[i] < sorting_seq[i - 1])
			break;
	if(i > k)
	{
		// 插入排序
		printf("Insertion Sort\n");
		std::sort(sorting_seq, sorting_seq + i + 1);
	}
	else
	{
		// 归并排序
		printf("Merge Sort\n");
		for(; i < length; ++i)
			if(sorting_seq[i] < sorting_seq[i - 1])
				break;
		int size_of_sub = pow(2, (int)(log((double)i) / log(2.0)));
		assert(size_of_sub > 1);
		for(int x = size_of_sub; x < length; x += size_of_sub)
		{
			int y;
			for(y = x + 1; y < x + size_of_sub && y < length; ++y)
			{
				if(sorting_seq[y] < sorting_seq[y - 1])
					break;
			}
			if(y < x + size_of_sub && y < length)
			{
				size_of_sub = pow(2, (int)(log(y - x) / log(2.0)));
				x = size_of_sub;
				break;
			}
		}
		// 归并进行下个迭代
		for(int x = 0; x < length; x += size_of_sub * 2)
		{
			int y = std::min(x + size_of_sub * 2, length);
			std::sort(sorting_seq + x, sorting_seq + y);
		}
	}

	if(length > 0)
		printf("%d", sorting_seq[0]);
	for(int i = 1; i < length; ++i)
		printf(" %d", sorting_seq[i]);
	printf("\n");
	return 0;
}