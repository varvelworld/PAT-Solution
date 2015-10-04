#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

char s[10001];
char t[10000 * 2 + 1 + 1];
int p[10000 * 2 + 1];
// Manacher’s Algorithm, 可以在线性时间内求解
int main()
{
    gets(s);
    int length_of_s = strlen(s);
    int length_of_t = length_of_s * 2 + 1 + 2;
    t[0] = '^';
    t[length_of_t - 1] = '$';
    for(int i = 0; i <= length_of_s; ++i)
    {
        t[i * 2 + 1] = '#';
        t[i * 2 + 1 + 1] = s[i];
    }
    int c = 0, r = 0;
    for(int i = 1; i < length_of_t - 1; ++i)
    {
        int i_mirror = 2 * c - i;
        p[i] = r > i ? std::min(r - i, p[i_mirror]) : 0;
        // 拓展i的回文
        while(t[i + p[i] + 1] == t[i - p[i] - 1])
            ++(p[i]);
        // 调整中心
        if(i + p[i] > r)
        { 
            c = i;
            r = i + p[i];
        }
    }
    // p中找出最大
    int max_len = 0;
    for(int i = 1; i < length_of_t - 1; ++i)
    {
        if(p[i] > max_len)
            max_len = p[i];
    }
    printf("%d", max_len);
    return 0;
}