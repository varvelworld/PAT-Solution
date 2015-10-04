#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Customer
{
    int id;
    int processing_time_interval;
    int start_time;
    int finish_time;
    Customer(): id(0), processing_time_interval(0), start_time(0), finish_time(0) {}
    Customer(int id, int processing_time_interval): id(id), processing_time_interval(processing_time_interval), start_time(0), finish_time(0) {}
};

struct Window
{
    int id;
    queue<Customer*> line_queue;
    Window(): id(0) {}
    Window(int id): id(id) {}
};

struct WindowCmp
{
    // 前置：!a->line_queue.empty() && !b->line_queue.empty()
    bool operator() (Window* &a, Window* &b)
    {
        if(a->line_queue.front()->finish_time == b->line_queue.front()->finish_time)
            return a->id > b->id;
        return a->line_queue.front()->finish_time > b->line_queue.front()->finish_time;
    }
};

int main()
{
    int number_of_windows, the_capacity_yellow_line, number_of_customers, number_of_customer_queries;
    vector<Customer*> customers;
    vector<Window*> windows;
    queue<Customer*> waiting_queue;
    priority_queue<Window*, vector<Window*>, WindowCmp> finished_windows;
    cin >> number_of_windows >> the_capacity_yellow_line >> number_of_customers >> number_of_customer_queries;
    // 初始化客户列表，等候队列
    customers.push_back(nullptr);
    for(int i = 1; i <= number_of_customers; ++i)
    {
        int processing_time_interval;
        cin >> processing_time_interval;
        Customer *customer = new Customer(i, processing_time_interval);
        customers.push_back(customer);
        waiting_queue.push(customer);
    }
    // 初始化窗口列表
    windows.push_back(nullptr);
    for(int i = 1; i <= number_of_windows; ++i)
    {
        Window *window = new Window(i);
        windows.push_back(window);
    }
    int now_time = 0;
    // 等候队列入黄线
    for(int i = 1; i <= the_capacity_yellow_line; ++i)
    {
        if(waiting_queue.empty()) break;
        for(int j = 1; j <= number_of_windows; ++j)
        {
            if(waiting_queue.empty()) break;
            Customer *customer = waiting_queue.front();
            waiting_queue.pop();
            windows[j]->line_queue.push(customer);
        }
    }
    // 初始化结束时间优先队列
    for(int i = 1; i <= number_of_windows; ++i)
    {
        if(!windows[i]->line_queue.empty())
        {
            Customer *customer = windows[i]->line_queue.front();
            customer->start_time = now_time;
            customer->finish_time = now_time + customer->processing_time_interval;
            finished_windows.push(windows[i]);
        }
    }

    while(!finished_windows.empty())
    {
        Window *window = finished_windows.top();
        finished_windows.pop();
        now_time = window->line_queue.front()->finish_time;
        if(now_time >= (17 - 8) * 60) break;
        window->line_queue.pop();
        if(!waiting_queue.empty())
        {
            window->line_queue.push(waiting_queue.front());
            waiting_queue.pop();
        }
        if(!window->line_queue.empty())
        {
            Customer *customer = window->line_queue.front();
            customer->start_time = now_time;
            customer->finish_time = now_time + customer->processing_time_interval;
            finished_windows.push(window);
        }
    }
    for(int i = 1; i <= number_of_customer_queries; ++i)
    {
        int customer_query_id;
        cin >> customer_query_id;
        int finish_time = customers[customer_query_id]->finish_time;
        if(finish_time == 0) 
            cout << "Sorry" << endl;
        else
            cout << setfill('0') << setw(2) << finish_time / 60 + 8  << ":" << setfill('0') << setw(2) << finish_time % 60 << endl;
    }
    return 0;
}