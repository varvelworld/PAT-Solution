#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//线性搜索
int lSearch(int seq[], int begin_index, int end_index, long long up_limit)
{
    int i = end_index - 1;
    for(; i != begin_index - 1; --i)
    {
        if(seq[i] <= up_limit)
            return i;
    }
    return i;
}

//二分搜索
int bSearch(int seq[], int begin_index, int end_index, long long up_limit)
{
    int up = end_index, low = begin_index;
    int mid;
    while(up > low + 4)
    {
        mid = (up + low) / 2;
        if(seq[mid] <= up_limit && (mid + 1 == end_index || seq[mid + 1] > up_limit))
            return mid;
        else if(seq[mid] <= up_limit)
            low = mid + 1;
        else
            up = mid;
    }
    return lSearch(seq, low, up, up_limit);
}

int main()
{
    int n, p;
    int sequence[100000]; 
    cin >> n >> p;
    for(int i = 0; i != n; ++i)
    {
        int num;
        cin >> num;
        sequence[i] = num;
    }
    sort(sequence, sequence + n);
    int max_count = 0;
    for(int i = 0; i < n - max_count; ++i)//目前已知最大数量大于可能最大数量，剪枝
    {
        long long up_limit = (long)sequence[i] * p;
        int max_index = bSearch(sequence, i + max_count, n, up_limit);// 剪枝
        max_count = max(max_count, max_index - i + 1);
    }
    cout << max_count << endl;
    return 0;
}