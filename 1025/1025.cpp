#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

struct Testee
{
    string registration_number;
    int score;
    int location_number;
    int local_rank;
    int final_rank;
    Testee():score(0), location_number(0), local_rank(0), final_rank(0) {}
    Testee(string registration_number, int score):registration_number(registration_number), score(score), location_number(location_number), local_rank(0), final_rank(0) {}
};

bool operator < (const Testee& a, const Testee& b)
{
    if(a.score == b.score)
        return a.registration_number > b.registration_number;
    else
        return a.score < b.score;
}

istream& operator >> (istream& in, Testee& testee)
{
    string registration_number;
    int score;
    cin >> registration_number >> score;
    if(in)
        testee = Testee(registration_number, score);
    else
        testee = Testee();
    return in;
}

ostream& operator << (ostream& out, Testee& testee)
{
    out << testee.registration_number << " " << testee.final_rank << " " << testee.location_number << " " << testee.local_rank << endl;
    return out;
}

int main()
{
    int number_of_locations;
    int count_testee = 0;
    vector<deque<Testee>> locations;
    cin >> number_of_locations;
    for(int i = 1; i <= number_of_locations; ++i)
    {
        deque<Testee> location;
        int number_of_testees;
        cin >> number_of_testees;
        for(int j = 1; j <= number_of_testees; ++j)
        {
            Testee testee;
            cin >> testee;
            ++count_testee;
            testee.location_number = i;
            location.push_back(testee);
        }
        sort(location.begin(), location.end());
        int rank = 1, seq = 1;
        for(auto iter = location.rbegin(); iter != location.rend(); ++iter)
        {
            iter->local_rank = rank;
             ++seq;
            if(iter + 1 != location.rend() && iter->score != (iter + 1)->score)
                rank = seq;
        }
        locations.push_back(location);
    }
    cout << count_testee << endl;
    priority_queue<Testee> queue;
    for(auto iter = locations.begin(); iter != locations.end(); ++iter)
    {
        queue.push(iter->back());
        iter->pop_back();
    }
    int rank = 0, seq = 0;
    int pre_score = -1;
    while(!queue.empty())
    {
        Testee testee = queue.top();
        queue.pop();
        deque<Testee> &location = locations[testee.location_number - 1];
        if(!location.empty())
        {
            queue.push(location.back());
            location.pop_back();
        }
        ++seq;
        if(pre_score != testee.score) rank = seq;
        pre_score = testee.score;
        testee.final_rank = rank;
        cout << testee;
    }
    return 0;
}