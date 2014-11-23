#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

struct People
{
    char id[10];
    int virtue;
    int talent;
    People(char id[10], int virtue, int talent): virtue(virtue), talent(talent) {strcpy(this->id, id);}
};

bool operator > (const People &a, const People &b)
{
    int total_a = a.virtue + a.talent;
    int total_b = b.virtue + b.talent;
    return total_a > total_b 
        || total_a == total_b && (a.virtue > b.virtue || a.virtue == b.virtue && strcmp(a.id, b.id) < 0);
}

int main()
{
    int number_people, low_grade, hight_grade;
    cin >> number_people >> low_grade >> hight_grade;
    vector<People> sage, noblemen, fool_man, small_man;
    sage.reserve(number_people);
    noblemen.reserve(number_people);
    fool_man.reserve(number_people);
    small_man.reserve(number_people);
    for(int i = 0; i < number_people; ++i)
    {
        char id[10];
        int virtue, talent, fool_men;
        scanf("%s%d%d", id, &virtue, &talent);
        if(talent < low_grade || virtue < low_grade)
            continue;
        if(talent >= hight_grade && virtue >= hight_grade)
            sage.push_back(People(id, virtue, talent));
        else if(talent < hight_grade && virtue >= hight_grade)
            noblemen.push_back(People(id, virtue, talent));
        else if(talent < hight_grade && virtue < hight_grade && virtue >= talent)
            fool_man.push_back(People(id, virtue, talent));
        else 
            small_man.push_back(People(id, virtue, talent));
    }
    auto greater = [](const People &a, const People &b) {return a > b;};
    sort(sage.begin(), sage.end(), greater);
    sort(noblemen.begin(), noblemen.end(), greater);
    sort(fool_man.begin(), fool_man.end(), greater);
    sort(small_man.begin(), small_man.end(), greater);
    cout << (sage.size() + noblemen.size() + fool_man.size() + small_man.size()) << endl;
    for(auto iter = sage.begin(); iter != sage.end(); ++iter)
        printf("%s %d %d\n", iter->id, iter->virtue, iter->talent);
    for(auto iter = noblemen.begin(); iter != noblemen.end(); ++iter)
        printf("%s %d %d\n", iter->id, iter->virtue, iter->talent);
    for(auto iter = fool_man.begin(); iter != fool_man.end(); ++iter)
        printf("%s %d %d\n", iter->id, iter->virtue, iter->talent);
    for(auto iter = small_man.begin(); iter != small_man.end(); ++iter)
        printf("%s %d %d\n", iter->id, iter->virtue, iter->talent);
    return 0;
}