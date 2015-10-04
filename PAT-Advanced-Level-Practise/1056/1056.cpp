#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct Mice 
{
    int id;
    int weight;
    int init_order;
    int rank;
    Mice(int id, int weight): id(id), weight(weight), init_order(0), rank(0) {}
};

int main()
{
    int Np, Ng; // the number of programmers and the number of programmers every group 
    cin >> Np >> Ng;
    deque<Mice> mices;
    vector<Mice> mices_ranked;
    for(int i = 0; i < Np; ++i)
    {
        int weight;
        cin >> weight;
        mices.push_back(Mice(i, weight));
    }
    for(int i = 0; i < Np; ++i)
    {
        int init_order_id;
        cin >> init_order_id;
        mices[init_order_id].init_order = i;
    }
    sort(mices.begin(), mices.end(), [](const Mice& a, const Mice& b){return a.init_order < b.init_order;});
    int number_programmer = mices.size();
    while(number_programmer != 1)
    {
        int rank = ceil((float)number_programmer / Ng) + 1;
        for(int i = 0; i != number_programmer; )
        {
            if(i++ >= number_programmer) break; 
            Mice max_weight_in_group = mices.front();
            mices.pop_front();
            for(int j = 1; j != Ng; ++j)
            {
                if(i++ == number_programmer) break; 
                Mice mice = mices.front();
                mices.pop_front();
                if(max_weight_in_group.weight >= mice.weight)
                {
                    mice.rank = rank;
                    mices_ranked.push_back(mice);
                }
                else
                {
                    max_weight_in_group.rank = rank;
                    mices_ranked.push_back(max_weight_in_group);
                    max_weight_in_group = mice;
                }
            }
            mices.push_back(max_weight_in_group);
        }
        number_programmer = mices.size();
    }
    {
        Mice mice = mices.front();
        mice.rank = 1;
        mices_ranked.push_back(mice);
        mices.pop_front();
    }
    sort(mices_ranked.begin(), mices_ranked.end(), [](const Mice& a, const Mice& b){return a.id < b.id;});
    auto iter = mices_ranked.begin();
    if(iter != mices_ranked.end())
    {
        cout << iter->rank;
    }
    for(iter = ++iter; iter != mices_ranked.end(); ++iter)
    {
        cout << ' ' << iter->rank;
    }
    return 0;
}