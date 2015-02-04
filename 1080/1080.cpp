#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct School
{
    int quota;
    int current_rank;
    vector<int> admits;
};

struct Applicant
{
    int id;
    int ge, gi;
    float find_grade;
    int *choices;
};

School schools[100];

int main()
{
    int number_of_applicants, number_of_schools, number_of_choices;
    scanf("%d%d%d", &number_of_applicants, &number_of_schools, &number_of_choices);
    for(int i = 0; i < number_of_schools; ++i)
    {
        scanf("%d", &(schools[i].quota));
        schools[i].current_rank = 0;
    }
    Applicant *applicants = new Applicant[number_of_applicants];
    for(int i = 0; i < number_of_applicants; ++i)
    {
        applicants[i].id = i;
        scanf("%d%d", &(applicants[i].ge), &(applicants[i].gi));
        applicants[i].find_grade = (float)(applicants[i].ge + applicants[i].gi) / 2;
        applicants[i].choices = new int[number_of_choices];
        for(int j = 0; j < number_of_choices; ++j)
            scanf("%d", &(applicants[i].choices[j]));
    }
    Applicant *sorted_applicants = new Applicant[number_of_applicants];
    memcpy(sorted_applicants, applicants, number_of_applicants * sizeof(Applicant));
    sort(sorted_applicants, sorted_applicants + number_of_applicants + 1, [](const Applicant &a, const Applicant &b)
    {
        if(a.find_grade == b.find_grade)
            return  a.ge > b.ge;
        return a.find_grade > b.find_grade;
    });
    for(int i = 0; i < number_of_applicants; ++i)
    {
        Applicant *applicant = &(sorted_applicants[i]);
        int *choices = applicant->choices;
        for(int j = 0;  j < number_of_choices; ++j)
        {
            int choice = choices[j];
            School *choice_school = &(schools[choice]);
            if(choice_school->current_rank < choice_school->quota)
            {
                ++(choice_school->current_rank);
                choice_school->admits.push_back(applicant->id);
                break;
            }
            else if(choice_school->current_rank == choice_school->quota)
            {
                Applicant *last_applicant = &(applicants[choice_school->admits.back()]);
                if(last_applicant->find_grade == applicant->find_grade && last_applicant->ge == applicant->ge)
                {
                    choice_school->admits.push_back(applicant->id);
                    break;
                }
                else
                    ++(choice_school->current_rank);
            }
        }
    }
    for(int i = 0; i < number_of_schools; ++i)
    {
        sort(schools[i].admits.begin(), schools[i].admits.end());
        auto iter = schools[i].admits.begin();
        if(iter != schools[i].admits.end())
        {
            printf("%d", *iter);
            ++iter;
        }
        for( ; iter != schools[i].admits.end(); ++iter)
            printf(" %d", *iter);
        printf("\n");
    }
    return 0;
}