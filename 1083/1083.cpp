#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
    string name;
    string id;
    int grade;
    Student(string name, string id, int grade): name(name), id(id), grade(grade) {};

};
int main()
{
    int n;
    vector<Student> students;
    cin >> n; 
    for(int i = 0; i < n; ++i)
    {
        string name, id;
        int grade;
        cin >> name >> id >> grade;
        students.push_back(Student(name, id, grade));
    }
    int min_garde, max_grade;
    cin >> min_garde >> max_grade;
    if(min_garde > max_grade) 
        swap(min_garde, max_grade);
    vector<Student> sort_students;
    for(auto iter = students.begin(); iter != students.end(); ++iter)
    {
        if(min_garde <= (*iter).grade && (*iter).grade <= max_grade)
        {
            sort_students.push_back(*iter);
        }
    }
    if(sort_students.empty())
    {
        cout << "NONE" << endl;
    }
    else
    {
        sort(sort_students.begin(), sort_students.end(), [](const Student& a, const Student& b){return a.grade > b.grade;});
        for(auto iter = sort_students.begin(); iter != sort_students.end(); ++iter)
        {
            cout << (*iter).name << ' ' << (*iter).id << endl; 
        }
    }
    return 0;
}