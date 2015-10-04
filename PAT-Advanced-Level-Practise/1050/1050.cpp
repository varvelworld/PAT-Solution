#include <cstdlib>
#include <cstdio>
#include <cstring>

char s1[10001];
char s2[10001];
char s[10001];
bool m[256];

int main()
{
	memset(m,0,sizeof(m));  
	gets(s1);
	gets(s2);
	size_t s1_len = strlen(s1);
	size_t s2_len = strlen(s2);
	if(s2_len == 0)
	{
		printf("%s\n", s1);
		return 0;
	}
	for(int i = 0; i < s2_len; ++i)
	{
		char c = s2[i];
		m[(unsigned char)c] = true;
	}
	int k = 0;
	for(int i = 0; i < s1_len; ++i)
	{
		char c = s1[i];
		if(!m[(unsigned char)c])
			s[k++] = c;
	}
	s[k] = '\0';
	printf("%s\n", s);
	return 0;
}