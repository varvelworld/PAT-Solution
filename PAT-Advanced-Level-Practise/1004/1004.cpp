#include <iostream>
#include <vector>

using namespace std;

struct Node 
{
    int level;
    int childCount;
    vector<int> children;
    Node(): level(0), childCount(0){}
};

void calculateLevel(Node tree[100], int id, int level)
{
    tree[id].level = level;
    for(vector<int>::iterator iter = tree[id].children.begin(); iter != tree[id].children.end(); ++iter)
    {
        calculateLevel(tree, *iter, level + 1);
    }
    return;
}

int main()
{
    int n, m;
    Node tree[100];                   //1至99
    int leafCountByLevel[100] = {0};  //各个层级叶子节点统计
    int maxLevel = 0;

    cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        int id, k;
        cin >> id >> k;
        tree[id].childCount = k;
        for(int j = 0; j < k; ++j)
        {
            int childId;
            cin >> childId;
            tree[id].children.push_back(childId);
        }
    }
    calculateLevel(tree, 1, 0);
    for(int i = 1; i <= n; ++i)
    {
        if(tree[i].childCount == 0)
        {
            int level = tree[i].level;
            ++(leafCountByLevel[level]); 
            if(level > maxLevel) maxLevel = level;
        }
    }
    for(int i = 0; i <= maxLevel; ++i)
    {
        cout << (i > 0 ? " " : "") << leafCountByLevel[i];
    }
    cout << endl;
    return 0;
}