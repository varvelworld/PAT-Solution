#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main()
{
    int max_capacity;
    int sequence_length;
    int number_of_sequence;
    cin >> max_capacity >> sequence_length >> number_of_sequence;
    for(int i = 0; i < number_of_sequence; ++i)
    {
        queue<int> queue;
        for(int j = 1; j <= sequence_length; ++j)
            queue.push(j);
        stack<int> stack;
        bool possible_pop = true;
        for(int j = 0; j < sequence_length; ++j)
        {
            int num;
            cin >> num;
            if(!possible_pop) continue;
            while(stack.size() <= max_capacity && !queue.empty() &&(stack.empty() || stack.top() != num))
            {
                stack.push(queue.front());
                queue.pop();
            }
            if(stack.size() > max_capacity)
                possible_pop = false;
            else if(!stack.empty() && stack.top() == num)
                stack.pop();
            else
                possible_pop = false;
        }
        cout << (possible_pop ? "YES" : "NO") << endl;
    }
    return 0;
}