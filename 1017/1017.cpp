#include <iostream>
#include <queue>
#include <string>
#include <strstream>
#include <functional>
#include <iomanip>
#include <limits>

using namespace std;

struct Customer
{
    int arriving_time;
    int processing_time_interval;
    int process_begin_time;
    int process_end_time;
    Customer():arriving_time(0), processing_time_interval(0), process_begin_time(0), process_end_time(0) {}
    Customer(int arriving_time, int processing_time_interval):arriving_time(arriving_time), processing_time_interval(processing_time_interval), process_begin_time(0), process_end_time(0){}
};

int time_to_seconds(string time_str)
{
    int hour, minute, second;
    strstream ss;
    time_str[2] = ' ';
    time_str[5] = ' ';
    ss << time_str;
    ss >> hour >> minute >> second;
    return hour * 60 * 60 + minute * 60 + second;
}

istream& operator >> (istream& in, Customer &customer)
{
    string arriving_time_str;
    int processing_time_in_minutes;
    in >> arriving_time_str >> processing_time_in_minutes;
    if(in)
        customer = Customer(time_to_seconds(arriving_time_str), processing_time_in_minutes * 60);
    else
        customer = Customer();
    return in;
}

struct CustomerCmpInWindows
{
    bool operator() (const Customer &a,const Customer &b)
    {
        return a.process_end_time > b.process_end_time;
    }
};

struct CustomerCmpByTime
{
    bool operator() (const Customer &a,const Customer &b)
    {
        return a.arriving_time > b.arriving_time;
    }
};

int main()
{
    priority_queue<Customer, vector<Customer>, CustomerCmpInWindows> processing_coustomers;
    queue<Customer> waiting_coustomers;
    priority_queue<Customer, vector<Customer>, CustomerCmpByTime> coustomers;
    int number_of_customers, number_of_windows;
    cin >> number_of_customers >> number_of_windows;
    for(int i = 0; i < number_of_customers; ++i)
    {
        Customer customer = Customer();
        cin >> customer;
        coustomers.push(customer);
    }
    const int open_time = time_to_seconds("08:00:00");
    const int close_time = time_to_seconds("17:00:00");
    int now_time = open_time;
    int count_waiting_time = 0;
    int count_service_customer = 0;
    while(now_time <= close_time || !processing_coustomers.empty() || !waiting_coustomers.empty())
    {
        // 客户到达
        while(!coustomers.empty() && now_time >= coustomers.top().arriving_time && coustomers.top().arriving_time <= close_time)
        {
            waiting_coustomers.push(coustomers.top());
            coustomers.pop();
        }
        // 客户离开
        while(!processing_coustomers.empty() && now_time == processing_coustomers.top().process_end_time)
        {
            count_waiting_time += processing_coustomers.top().process_begin_time - processing_coustomers.top().arriving_time;
            ++count_service_customer;
            processing_coustomers.pop();
        }
        // 开始服务
        while(processing_coustomers.size() < number_of_windows && !waiting_coustomers.empty())
        {
            waiting_coustomers.front().process_begin_time = now_time;
            waiting_coustomers.front().process_end_time = now_time + waiting_coustomers.front().processing_time_interval;
            processing_coustomers.push(waiting_coustomers.front());
            waiting_coustomers.pop();
        }
        if(!processing_coustomers.empty() || !coustomers.empty())
            now_time = max(open_time, min(!processing_coustomers.empty() ? processing_coustomers.top().process_end_time : numeric_limits<int>::max(), !coustomers.empty() ? coustomers.top().arriving_time : numeric_limits<int>::max()));
        else
            now_time = close_time + 1;
    }
    cout << setiosflags(ios::fixed) << setprecision(1) << (double)count_waiting_time / count_service_customer / 60 << endl;
    return 0;
}