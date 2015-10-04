#include <iostream>
#include <string>

using namespace std;

int main()
{
    int number_student;
    cin >> number_student;
    string first_student_id, last_student_id;
    string first_sign_in_time = "23:59:59", last_sign_out_time = "00:00:00";
    for(int i = 0; i < number_student; ++i)
    {
        string student_id;
        string sign_in_time, sign_out_time;
        cin >> student_id >> sign_in_time >> sign_out_time;
        if(sign_in_time < first_sign_in_time)
        {
            first_student_id = student_id;
            first_sign_in_time = sign_in_time;
        }
        if(sign_out_time > last_sign_out_time)
        {
            last_student_id = student_id;
            last_sign_out_time = sign_out_time;
        }
    }
    cout << first_student_id << ' ' << last_student_id << endl;
    cout << endl;
    return 0;
}