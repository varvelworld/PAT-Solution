#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

static string week[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int main()
{
    string ciphertext[4];
    for(int i = 0; i < 4; ++i)
        cin >> ciphertext[i];
    int i;
    for(i = 0; i < min(ciphertext[0].length(), ciphertext[1].length()); ++i)
    {
        char c = ciphertext[0][i];
        if('A' <= c && c <= 'G' && c == ciphertext[1][i])
        {
            cout << week[c - 'A'];
            break;
        }
    }
    cout << " ";
    for(++i; i < min(ciphertext[0].length(), ciphertext[1].length()); ++i)
    {
        char c = ciphertext[0][i];
        if('0' <= c && c <= '9' && c == ciphertext[1][i])
        {
            cout << setfill('0') << setw(2) << c - '0';
            break;
        }
        else if('A' <= c && c <= 'N' && c == ciphertext[1][i])
        {
            cout << setfill('0') << setw(2) << c - 'A' + 10;
            break;
        }
    }
    cout << ":";
    for(int i = 0; i < min(ciphertext[2].length(), ciphertext[3].length()); ++i)
    {
        char c = ciphertext[2][i];
        if(('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z') && c == ciphertext[3][i])
        {
            cout << setfill('0') << setw(2) << i;
            break;
        }
    }
    return 0;
}