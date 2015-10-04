#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

int compute_name_index(char name[5])
{
    return (name[0] - 'A') + (name[1] - 'A') * 26 + (name[2] - 'A') * 26 * 26 + (name[3] - '0') * 26 * 26 * 26;
}

set<int>* name_to_course[26 * 26 * 26 * 10];

int main()
{

    int number_of_students, number_of_courses;
    scanf("%d%d", &number_of_students, &number_of_courses);
    for(int i = 0; i < number_of_courses; ++i)
    {
        int course_index, number_of_registered_students;
        scanf("%d%d", &course_index, &number_of_registered_students);
        for(int j = 0; j < number_of_registered_students; ++j)
        {
            char stuend_name[5];
            scanf("%s", stuend_name);
            int name_index = compute_name_index(stuend_name);
            if(name_to_course[name_index] == nullptr)
                name_to_course[name_index] = new set<int>();
            name_to_course[name_index]->insert(course_index);
        }
    }
    for(int i = 0; i < number_of_students; ++i)
    {
        char stuend_name[5];
        scanf("%s", stuend_name);
        int name_index = compute_name_index(stuend_name);
        set<int>* course_set = name_to_course[name_index];
        if(course_set)
        {
            printf("%s %d", stuend_name, course_set->size());
            for(auto iter = course_set->begin(); iter != course_set->end(); ++iter)
                printf(" %d", *iter);
        }
        else
            printf("%s %d", stuend_name, 0);
        printf("\n");
    }
    return 0;
}