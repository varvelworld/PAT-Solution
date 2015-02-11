#include <cstdio>
#include <cstring>
#include <map>
#include <queue>

using namespace std;

struct StudentNameCmp
{
	bool operator ()(char *a, char *b)
	{
		return strcmp(a, b) > 0;
	}
};

typedef priority_queue<char *, vector<char*>, StudentNameCmp> StudentQueue; // ¶ÑÅÅĞò

StudentQueue* course_index[2500 + 1];

int main()
{
	int number_of_students, number_of_courses;
	scanf("%d %d", &number_of_students, &number_of_courses);
	for(int i = 0; i < number_of_students; ++i)
	{
		char *student = new char[10];
		int number_of_courses_each;
		scanf("%s %d", student, &number_of_courses_each);
		for(int j = 0; j < number_of_courses_each; ++j)
		{
			int course;
			scanf("%d", &course);
			StudentQueue* students;
			if(course_index[course] == nullptr)
			{
				students = new StudentQueue();
				course_index[course] = students;
			}
			else
				students = course_index[course];
			students->push(student);
		}
	}
	for(int course = 1; course <= number_of_courses; ++course)
	{
		StudentQueue* students = course_index[course];
		if(students == nullptr)
			printf("%d 0\n", course);
		else
		{
			printf("%d %d\n", course, students->size());
			while(!students->empty())
			{
				printf("%s\n", students->top());
				students->pop();
			}
		}
	}
	return 0;
}