#include <cstdio>
#include <cstdlib>
#include <cstring>

char s[100005];

int main() {
	scanf("%s", s);
	int len = strlen(s);
	int count_p = 0;
	int count_pa = 0;
	int count_pat = 0;
	for (int i = 0; i < len; ++i) {
		char c = s[i];
		if (c == 'P') {
			++count_p;
		}
		else if (c == 'A') {
			count_pa += count_p;
			count_pa %= 1000000007;
		}
		else {
			count_pat += count_pa;
			count_pat %= 1000000007;
		}
	}
	printf("%d\n", count_pat);
	return 0;
}