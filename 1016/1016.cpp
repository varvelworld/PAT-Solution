#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Record
{
    string customer_name;
    string time;
    string word;
    Record(string customer_name, string time, string word): customer_name(customer_name), time(time), word(word) {}
};

struct Call
{
    string on_line_time;
    string off_line_time;
    int charge;
    int call_minutes;
    Call(string on_line_time, string off_line_time, int charge, int call_minutes): on_line_time(on_line_time), off_line_time(off_line_time), charge(charge), call_minutes(call_minutes) {}
};

struct Customer
{
    string name;
    string month;
    string last_on_line_time;
    vector<Call> calls;
    int total_charge;
    Customer(string name, string month):name(name), month(month), total_charge(0) {}
};

inline int compute_minutes(string time)
{
    int day = atoi(time.substr(0, 2).c_str());
    int hour = atoi(time.substr(3, 5).c_str());
    int minute = atoi(time.substr(6, 8).c_str());
    return (day * 24 + hour) * 60 + minute;
}

inline void compute_charge(string on_line_time, string off_line_time, int toll[24], int& charge, int& call_minutes)
{
    int on_line_day = atoi(on_line_time.substr(0, 2).c_str());
    int on_line_hour = atoi(on_line_time.substr(3, 5).c_str());
    int on_line_minute = atoi(on_line_time.substr(6, 8).c_str());
    int off_line_day = atoi(off_line_time.substr(0, 2).c_str());
    int off_line_hour = atoi(off_line_time.substr(3, 5).c_str());
    int off_line_minute = atoi(off_line_time.substr(6, 8).c_str());
    int day, hour;
    charge = 0;
    call_minutes = 0;
    for(day = on_line_day, hour = on_line_hour; day < off_line_day || (day == off_line_day && hour < off_line_hour); (hour = (hour + 1) % 24) ? NULL : ++day)
    {
        charge += toll[hour] * 60;
        call_minutes += 60;
    }
    charge -= toll[on_line_hour] * on_line_minute;
    call_minutes -= on_line_minute;
    charge += toll[off_line_hour] * off_line_minute;
    call_minutes += off_line_minute;
}

struct CustomerCmp
{
    bool operator()(const string &a, const string &b)
    {
        return a < b;
    }
};

int main()
{
    int toll[24];
    for(int i = 0; i < 24; ++i)
        cin >> toll[i];
    int number_of_records;
    cin >> number_of_records;
    map<string, Customer*, CustomerCmp> customers;
    vector<Record> records;
    for(int i = 0; i < number_of_records; ++i)
    {
         string customer_name;
         string time;
         string word;
         cin >> customer_name >> time >> word;
         records.push_back(Record(customer_name, time, word));
    }
    sort(records.begin(), records.end(), [](const Record &a, const Record &b){return a.time < b.time;});
    for(int i = 0; i < number_of_records; ++i)
    {
         string customer_name = records[i].customer_name;
         string time = records[i].time;
         string word = records[i].word;
         auto customer_iter = customers.find(customer_name);
         Customer *customer;
         if(customer_iter == customers.end())
         {
             customer = new Customer(customer_name, time.substr(0, 2));
             customers.insert(make_pair(customer_name, customer));
         }
         else
             customer = customer_iter->second;
         if(word == "on-line")
             customer->last_on_line_time = time.substr(3, 11);
         else if(word == "off-line" && !customer->last_on_line_time.empty())
         {
             string on_line_time = customer->last_on_line_time;
             string off_line_time = time.substr(3, 11);
             customer->last_on_line_time = "";
             int charge = 0;
             int call_minutes = 0;
             compute_charge(on_line_time, off_line_time, toll, charge, call_minutes);
             customer->calls.push_back(Call(on_line_time, off_line_time, charge, call_minutes));
             customer->total_charge += charge;
         }
    }
    for(auto iter = customers.begin(); iter != customers.end(); ++iter)
    {
        Customer *customer = iter->second;
        if(customer->calls.empty()) continue;
        cout << customer->name << " " << customer->month << endl;
        for(auto iter = customer->calls.begin(); iter < customer->calls.end(); ++iter)
            cout << iter->on_line_time << " " << iter->off_line_time << " " << iter->call_minutes << " " << "$" << setiosflags(ios::fixed) << setprecision(2) << (double)iter->charge / 100 << endl;
        cout << "Total amount: $" << setiosflags(ios::fixed) << setprecision(2) << (double)customer->total_charge / 100<< endl;
    }
    return 0;
}