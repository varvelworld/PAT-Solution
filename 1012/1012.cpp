#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<pair<string, float>> cprogram;
    vector<pair<string, float>> mathematics;
    vector<pair<string, float>> english;
    vector<pair<string, float>> average;
    vector<pair<string, float>>* score[4];
    map<string, pair<int, int>> bestRank; // value中的pair first为rank,second为科目

    char word[4] = {'A', 'C', 'M', 'E'};
    score[0] = &average;
    score[1] = &cprogram;
    score[2] = &mathematics;
    score[3] = &english;

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        string s;
        float c, m, e, a;
        cin >> s >> c >> m >> e;
        a = (c + m + e) / 3.0f;
        cprogram.push_back(make_pair(s, c));
        mathematics.push_back(make_pair(s, m));
        english.push_back(make_pair(s, e));
        average.push_back(make_pair(s, a));
    }
    auto cmp = [](const pair<string, float> &a,const pair<string, float> &b){ return a.second > b.second;};
    for(int i = 0; i < 4; ++i)
    {
        sort(score[i]->begin(), score[i]->end(), cmp);
        int rank = 0;
        for(auto iter = score[i]->begin(); iter != score[i]->end(); ++iter)
        {
            if(rank == 0 || (*(iter - 1)).second > (*iter).second) 
                rank = iter - score[i]->begin() + 1;
            auto item = bestRank.find((*iter).first);
            if(item == bestRank.end() || (*item).second.first > rank) 
                bestRank[(*iter).first] = make_pair(rank, i);
        }
    }
    for(int i = 0; i < m; ++i)
    {
        string s;
        cin >> s;
        auto item = bestRank.find(s);
        if(item == bestRank.end())
        {
            cout << "N/A" << endl;
        }
        else
        {
            cout << (*item).second.first << ' ' << word[(*item).second.second] << endl;
        }
    }
    return 0;
}