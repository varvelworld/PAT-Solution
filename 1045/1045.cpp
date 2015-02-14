#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

struct Color
{
	int color;
	int width;
};

int favorite_color_order[200 + 1]; // favorite_color_order[color]表示最喜爱颜色的排序, color从1到N, order从1到N
Color color_stripe[10000];
int memo_longest_favorite_color_include_end[10000];

int longest_favorite_color_include_end(int end);

// 闭区间[0,end_index]的最长匹配的长度
int longest_favorite_color(int end) 
{
	if(end == 0) return color_stripe[0].width;
	return max(longest_favorite_color(end - 1), longest_favorite_color_include_end(end));
}

// 闭区间[0,end_index]中，包含end_index的最长匹配的长度
int longest_favorite_color_include_end(int end)
{
	if(memo_longest_favorite_color_include_end[end] != 0)
		return memo_longest_favorite_color_include_end[end];
	int max_length = 0;
	for(int i = 0; i < end; ++i)
	{
		if(favorite_color_order[color_stripe[i].color] > favorite_color_order[color_stripe[end].color])
			continue;
		int l = longest_favorite_color_include_end(i);
		if(l > max_length)
			max_length = l;
	}
	memo_longest_favorite_color_include_end[end] =  max_length + color_stripe[end].width;
	return memo_longest_favorite_color_include_end[end];
}

int main()
{
	int number_of_involved_colors;
	scanf("%d", &number_of_involved_colors);
	int number_of_favorite_colors;
	scanf("%d", &number_of_favorite_colors);
	for(int i = 1; i <= number_of_favorite_colors; ++i)
	{
		int color;
		scanf("%d", &color);
		favorite_color_order[color] = i;
	}
	int length_of_color_stripe;
	scanf("%d", &length_of_color_stripe);
	int k = -1;
	for(int i = 1; i <= length_of_color_stripe; i++)
	{
		int color;
		scanf("%d", &color);
		if(favorite_color_order[color] == 0) continue;
		if(i == 0 || color != color_stripe[k].color)
			color_stripe[++k].color = color;
		color_stripe[k].width++;
	}
	printf("%d", longest_favorite_color(k));
	return 0;
}