#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

struct Pixel
{
	int volume;
	bool s;
};

int M, N, L;
Pixel slice[1286][128][60];

struct Coord
{
	int m, n, l;
	Coord(int m, int n, int l): m(m), n(n), l(l) {}
};

void dfs(int m, int n, int l, int &count)
{
	stack<Coord> stk;
	while(true)
	{
		slice[m][n][l].s = true;
		if(m > 0 && slice[m - 1][n][l].volume == 1 && !slice[m - 1][n][l].s) 
		{
			stk.push(Coord(m, n, l));
			++count;
			--m;
		}
		else if(n > 0 && slice[m][n - 1][l].volume == 1 && !slice[m][n - 1][l].s) 
		{
			stk.push(Coord(m, n, l));
			++count;
			--n;
		}
		else if(l > 0 && slice[m][n][l - 1].volume == 1 && !slice[m][n][l - 1].s) 
		{
			stk.push(Coord(m, n, l));
			++count;
			--l;
		}
		else if(m + 1 < M && slice[m + 1][n][l].volume == 1 && !slice[m + 1][n][l].s) 
		{
			stk.push(Coord(m, n, l));
			++count;
			++m;
		}
		else if(n + 1 < N && slice[m][n + 1][l].volume == 1 && !slice[m][n + 1][l].s) 
		{
			stk.push(Coord(m, n, l));
			++count;
			++n;
		}
		else if(l + 1 < L && slice[m][n][l + 1].volume == 1 && !slice[m][n][l + 1].s) 
		{
			stk.push(Coord(m, n, l));
			++count;
			++l;
		}
		else if(!stk.empty())
		{
			Coord coord = stk.top();
			stk.pop();
			m = coord.m;
			n = coord.n;
			l = coord.l;
		}
		else
			break;
	}
}

int main()
{
	scanf("%d%d%d", &M, &N, &L);
	int threshold;
	scanf("%d", &threshold);
	assert(M <= 1286);
	assert(N <= 128);
	assert(L <= 60);
	for(int l = 0; l < L; ++l)
	{
		for(int m = 0; m < M; ++m)
		{
			for(int n = 0; n < N; ++n)
			{
				int volume;
				scanf("%d", &volume);
				slice[m][n][l].volume = volume;
				slice[m][n][l].s = false;
			}
		}
	}
	int total_volume = 0;
	for(int l = 0; l < L; ++l)
	{
		for(int m = 0; m < M; ++m)
		{
			for(int n = 0; n < N; ++n)
			{
				if(slice[m][n][l].volume == 1 && !slice[m][n][l].s)
				{
					int count = 1;
					dfs(m, n, l, count);
					if(count >= threshold)
						total_volume += count;
				}
			}
		}
	}
	printf("%d\n", total_volume);
	return 0;
}