#include <cstdio>

int main()
{
    int *seq_a, *seq_b;
    int length_a, length_b;

    // input
    scanf("%d", &length_a);
    seq_a = new int[length_a];
    for(int i = 0; i < length_a; ++i)
        scanf("%d", seq_a + i);
    scanf("%d", &length_b);
    seq_b = new int[length_b];
    for(int i = 0; i < length_b; ++i)
        scanf("%d", seq_b + i);

    int median_index =  (length_a + length_b + 1) / 2 - 1;

    if(seq_a[length_a - 1] <= seq_b[0]) 
    {
        printf("%d", (median_index < length_a) ? seq_a[median_index]  : seq_b[median_index - length_a]);
        return 0;
    }
    else if(seq_b[length_b - 1] <= seq_a[0]) 
    {
        printf("%d", (median_index < length_b) ? seq_b[median_index]  : seq_a[median_index - length_b]);
        return 0;
    }

    for(int i = 0, i_a = 0, i_b = 0; i_a < length_a || i_b < length_b; ++i)
    {
        if(!(i_b < length_b) || (i_a < length_a && seq_a[i_a] < seq_b[i_b]))
        {
            if(i == median_index)
            {
                printf("%d", seq_a[i_a]);
                break;
            }
            ++i_a;
        }
        else
        {
            if(i == median_index)
            {
                printf("%d", seq_b[i_b]);
                break;
            }
            ++i_b;
        }
    }

    return 0;
}