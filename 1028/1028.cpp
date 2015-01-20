#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Record
{
    char id[7];
    char name[9];
    int grade;

};

int main()
{
    int number_of_records, sort_column;
    scanf("%d%d", &number_of_records, &sort_column);
    vector<Record*> records;
    records.reserve(number_of_records);
    for(int i = 0; i < number_of_records; ++i)
    {
        Record *record = new Record();
        scanf("%s%s%d", record->id, record->name, &(record->grade));
        records.push_back(record);
    }
    switch(sort_column)
    {
    case 1:
        sort(records.begin(), records.end(), [](Record* a, Record* b){
            return strcmp(a->id, b->id) < 0;
        });
        break;
    case 2:
        sort(records.begin(), records.end(), [](Record* a, Record* b){
            int cmp = strcmp(a->name, b->name);
            if(cmp == 0)
                return strcmp(a->id, b->id) < 0;
            else
                return strcmp(a->name, b->name) < 0;
        });
        break;
    case 3:
        sort(records.begin(), records.end(), [](Record* a, Record* b){
            if(a->grade == b->grade)
                return strcmp(a->id, b->id) < 0;
            else
                return a->grade < b->grade;
        });
        break;
    }
    for(auto iter = records.begin(); iter != records.end(); ++iter)
    {
        printf("%s %s %d\n", (*iter)->id, (*iter)->name, (*iter)->grade);
    }
    return 0;
}