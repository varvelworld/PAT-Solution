#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    char r[3] = {'W', 'T', 'L'};
    float a[3];
    float s = 1;
    for(int i = 0; i < 3; i++)
    {
        a[i] = 0;
        int max_j = 0;
        for(int j = 0; j < 3; j++)
        {
            float c;
            cin >> c;
            if(c > a[i]) 
            {
                max_j = j;
                a[i] = c;
            }
        }
        cout << r[max_j] << ' ';
        s *= a[i];
    }
    s = (s * 0.65f - 1.0f) * 2;
    printf("%.2f\n", s);
    return 0;
}
