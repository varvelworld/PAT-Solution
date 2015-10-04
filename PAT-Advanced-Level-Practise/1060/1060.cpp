#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a, b;
    int n;
    string a_d, b_d;    //基数
    int a_e, b_e;       //阶数

    cin >> n >> a >> b;
    string::size_type i;
    for(i = 0; i != a.size(); ++i)
    {
        if(a[i] == '.')
        {
            a.erase(i, 1);
            break;
        }
    }
    a_e = i;
    for(i = 0; i != b.size(); ++i)
    {
        if(b[i] == '.')
        {
            b.erase(i, 1);
            break;
        }
    }
    b_e = i;

    for(i = 0; i < a.size(); ++i)
    {
        if(a[i] != '0') break;
    }
    if(i == a.size()){
        a_d = "0." + string(n, '0');
        a_e = 0;
    }
    else
    {
        a_d = "0." + a.substr(i, n);
        a_e -= i;
    }
    for(i = 0; i < b.size(); ++i)
    {
        if(b[i] != '0') break;
    }
    if(i == b.size()){
        b_d = "0." + string(n, '0');
        b_e = 0;
    }
    else
    {
        b_d = "0." + b.substr(i, n);
        b_e -= i;
    }
    
    if(a_e == b_e && a_d == b_d)
    {
        cout << "YES " << a_d << "*10^" << a_e << endl;
    }
    else
    {
        cout << "NO " << a_d << "*10^" << a_e << ' '<< b_d << "*10^" << b_e << endl;
    }
    return 0;
}