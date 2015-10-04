#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int *a;
    int length;
    scanf("%d", &length);
    a = new int[length];
    for(int i = 0; i < length; ++i)
        scanf("%d", a + i);
    int count_swap = 0;
    int checked_index = 0;
    int tmp;
    while(true)
    {
        if(a[0] != 0)
        {
            int i = a[0];
            tmp = a[0];
            a[0] = a[i];
            a[i] = tmp;
            ++count_swap;
        }
        else
        {
            for(checked_index; checked_index < length; ++checked_index)
                if(a[checked_index] != checked_index)
                {
                    tmp = a[0];
                    a[0] = a[checked_index];
                    a[checked_index] = tmp;
                    ++count_swap;
                    break;
                }
                if(checked_index == length)
                    break;
        }
    }
    printf("%d\n", count_swap);
    return 0;
}