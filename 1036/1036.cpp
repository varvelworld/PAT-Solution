#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    int number_of_students;
    scanf("%d", &number_of_students);

    char highest_girl_name[11]; 
    char highest_girl_id[11]; 
    int highest_girl_grade; 
    memset(highest_girl_name, 0, 11);
    memset(highest_girl_id, 0, 11);
    highest_girl_grade = -1;

    char lowest_boy_name[11]; 
    char lowest_boy_id[11]; 
    int lowest_boy_grade; 
    memset(lowest_boy_name, 0, 11);
    memset(lowest_boy_id, 0, 11);
    lowest_boy_grade = 101;

    for(int i = 1; i <= number_of_students; ++i)
    {
        char name[11]; 
        char gender[2];
        char id[11]; 
        int grade;
        scanf("%s %s %s %d", name, gender, id, &grade);
        if(gender[0] == 'F')
        {
            if(grade > highest_girl_grade)
            {
                strcpy(highest_girl_name, name);
                strcpy(highest_girl_id, id);
                highest_girl_grade = grade;
            }
        }
        else
        {
            if(grade < lowest_boy_grade)
            {
                strcpy(lowest_boy_name, name);
                strcpy(lowest_boy_id, id);
                lowest_boy_grade = grade;
            }
        }
    }

    if(highest_girl_grade == -1)
        printf("Absent\n");
    else
        printf("%s %s\n", highest_girl_name, highest_girl_id);
    if(lowest_boy_grade == 101)
        printf("Absent\n");
    else
        printf("%s %s\n", lowest_boy_name, lowest_boy_id);
    if(highest_girl_grade == -1 || lowest_boy_grade == 101)
        printf("NA");
    else
        printf("%d\n", highest_girl_grade - lowest_boy_grade);

    return 0;
}