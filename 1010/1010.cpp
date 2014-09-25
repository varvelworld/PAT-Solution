#include <iostream>
#include <string>

using namespace std;

int charToInt(char c)
{
    if('0' <= c && c <= '9')
    {
        return c - '0';
    }
    else
    {
        return c - 'a' + 10;
    }
}

long long calculate(string n, int radix)
{
    long long s = 0;
    long long r = 1;
    for(int i = n.size() - 1; i >= 0; i--)
    {
        s += charToInt(n[i]) * r;
        r *= radix;
    }
    return s;
}

int compare(string a, int radix, long long b)
{
    long long s = 0;
    long long r = 1;
    for(int i = a.size() - 1; i >= 0; i--)
    {
        s += charToInt(a[i]) * r;
        if(s > b) return 1;
        r *= radix;
    }
    if(s == b) return 0;
    else if(s > b) return 1;
    else return -1;
}

int maxDigit(string n)
{
    char max = '0';
    for(int i = 0; i < n.size(); i++)
    {
        if(n[i] > max)
        {
            max = n[i];
        }
    }
    return charToInt(max);
}

int main()
{
    string n[3];
    int tag;
    long long radix;
    long long s;//已知数的值
    string t;//未知数
    int c;//比较结果
    long long up, low;//二分法上下限
    long long mid;//二分法中项

    cin >> n[1] >> n[2] >> tag >> radix;

    s = calculate(n[tag], radix);
    t = tag == 1 ? n[2] : n[1];
    c = compare(t, radix, s);
    low = max(maxDigit(t) + 1, 2);
    if(c == 0)
    {
        if(t.size() == 1)
        {
            cout << max(2, maxDigit(t) + 1) << endl;
        }
        else
        {
            cout << radix << endl;
        }
        return 0;
    }
    
    if(c > 0)
    {
        up = radix;
    }
    else
    {
        up = max((long long) 2, s + 1);
    }
    
    do
    {
        mid = (up + low) / 2;
        c = compare(t, mid, s);
        if(c == 0)
        {
            if(mid > s)
            {
                cout << max((long long) 2, s + 1) << endl;
            }
            else
            {
                cout << mid << endl;
            }
            return 0;
        }
        else if(c < 0)
        {
            low = mid + 1;
        }
        else
        {
            up = mid - 1;
        }
    }while(up >= low);
    cout << "Impossible\n";
    return 0;
}

