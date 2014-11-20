#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int total = 0, current_floor = 0;
    for(int i = 0; i < n; ++i)
    {
        int floor;
        cin >> floor;
        int diff = floor - current_floor;
        total += diff * (diff > 0 ? 6 : -4) + 5;
        current_floor = floor;
    }
    cout << total << endl;
    return 0;
}