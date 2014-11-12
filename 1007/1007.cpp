#include <iostream>

using namespace std;

#define MAX_LENGTH_SEQUENCE 10000

int main()
{
    int sequence[MAX_LENGTH_SEQUENCE];
    int length_sequence;
    cin >> length_sequence;
    for(int i = 0; i < length_sequence; ++i)
    {
        cin >> sequence[i];
    }
    int sum = 0;
    int first_index = 0;
    int max_sum = sequence[0];
    int max_seq_first_index = 0, max_seq_last_index = 0;
    for(int i = 0; i < length_sequence; ++i)    //扫描法，线性时间
    {
        if(sum < 0)
        {
            sum = sequence[i];
            first_index = i;
        }
        else
            sum += sequence[i];
        if(max_sum < sum)
        {
            max_sum = sum;
            max_seq_first_index = first_index;
            max_seq_last_index = i;
        }
    }
    if(max_sum < 0)
        cout << 0 << ' ' << sequence[0] << ' ' << sequence[length_sequence - 1];
    else
        cout << max_sum << ' '<<  sequence[max_seq_first_index] << ' ' << sequence[max_seq_last_index]; 
    return 0;
}