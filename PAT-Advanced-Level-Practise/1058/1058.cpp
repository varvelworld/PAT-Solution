#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Money
{
    int Galleon;
    int Sickle;
    int Knut;
    Money(): Galleon(0), Sickle(0), Knut(0) {};
    Money(int Galleon, int Sickle, int Knut): Galleon(Galleon), Sickle(Sickle), Knut(Knut) {};
};

inline Money operator+(const Money &a, const Money &b)
{
    int Knut = a.Knut + b.Knut;
    int Sickle = a.Sickle + b.Sickle + Knut / 29;
    int Galleon = a.Galleon + b.Galleon + Sickle / 17;
    Knut %= 29;
    Sickle %= 17;
    return Money(Galleon, Sickle, Knut);
}

ostream& operator<<(ostream& out, const Money &money)
{
    out << money.Galleon << "." << money.Sickle << "." << money.Knut;
    return out;
}

void split(const string &str, const char &separator, vector<string> &result)
{
    size_t begin = 0, end;
    while(begin < str.length() && (end = str.find_first_of(separator, begin)) < str.length())
    {
        result.push_back(str.substr(begin, end - begin));
        begin = end + 1;
    }
    result.push_back(str.substr(begin, str.length() - begin));
}

istream& operator>>(istream& in, Money &money)
{
    string str;
    in >> str;
    if(!in) money = Money();
    vector<string> strs;
    split(str, '.', strs);
    money.Galleon   = atoi(strs[0].c_str());
    money.Sickle    = atoi(strs[1].c_str());
    money.Knut      = atoi(strs[2].c_str());
    return in;
}

int main()
{
    Money a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}