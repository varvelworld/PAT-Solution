#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <iostream>

void adjust(int datas[], int node, int len);

int main() 
{
    int datas[100];
    int s_datas[100];
    int len_of_datas;
    scanf("%d", &len_of_datas);
    for(int i = 0; i < len_of_datas; ++i) 
    {
        scanf("%d", datas + i);
    }
    for(int i = 0; i < len_of_datas; ++i) 
    {
        scanf("%d", s_datas + i);
    }

    // 找到mid,s_datas子数组(mid,len_of_datas),与datas中一样
    int mid;
    for(mid = len_of_datas - 1; s_datas[mid] == datas[mid] && mid >= 0; --mid);

    // 判断s_datas(0,mid]是否有序，有序就为插入排序，反之堆排序
    bool is_insertion = true;
    for(int i = 0; i < mid; ++i)
    {
        if(s_datas[i] > s_datas[i + 1])
        {
            is_insertion = false;
            break;
        }
    }

    if(is_insertion) // 如果为插入排序
    {
        int s = mid; // 待排序元素下标
        if(s >= len_of_datas) 
        {
            // 已经完全排序好了
            printf("already sorted\n");
            return 2;
        }
        int insert; // 插入位置（之前）
        do {
            ++s;
            if(s >= len_of_datas) {
                break;
            }
            for(insert = 0; insert < s && s_datas[insert] < s_datas[s]; ++insert) ;
        } while(insert == s);
        if(s < len_of_datas) {
            int s_value = s_datas[s];
            memmove(s_datas + insert + 1, s_datas + insert, (s - insert) * sizeof(int));
            s_datas[insert] = s_value;
        }
    }
    else { // 如果为堆排序
        // 查找已排序区域，(s,len_of_datas)
        int s;
        for(s = len_of_datas - 1; s >= 0 && s_datas[s] >= s_datas[0]; --s); // 循环不变式：且其所有元素大于等于堆顶元素（[s,len_of_datas)有序，必定满足）
        std::swap(s_datas[0], s_datas[s]);
        // 向下调整堆
        adjust(s_datas, 0, s);
    }

    // 输出结果
    if(is_insertion) 
    {
        printf("Insertion Sort\n");
    }
    else 
    {
        printf("Heap Sort\n");
    }
    printf("%d", s_datas[0]);
    for(int i = 1; i < len_of_datas; ++i) {
        printf(" %d", s_datas[i]);
    }
    printf("\n");
    return 0;
}

void adjust(int datas[], int node, int len) {
    int left = node * 2 + 1;
    int right = node * 2 + 2;
    if(left < len && datas[left] > datas[node] && (right >= len || datas[left] > datas[right])) {
        std::swap(datas[node], datas[left]);
        adjust(datas, left, len);
    }
    else if(right < len && datas[right] > datas[node] && (left >= len || datas[right] > datas[left])) {
        std::swap(datas[node], datas[right]);
        adjust(datas, right, len);
    }
    else {
        return ;
    }
}