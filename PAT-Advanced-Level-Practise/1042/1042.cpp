#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string color[] = {"S", "H", "C", "D", "J"}; 
    string cards[2][54];
    int permutation[54];
    int current_cards_index = 0;
    int temp_cards_index = 1;
    int times;
    
    // init
    for(int i = 0; i < 54; ++i)
    {
        stringstream sstream;   // int转string
        sstream << (i % 13 + 1);
        cards[0][i] = color[i / 13] + sstream.str();
    }

    cin >> times;
    for(int i = 0; i < 54; ++i)
        cin >> permutation[i];

    for(int t = 0; t < times; ++t)
    {
        for(int i = 0; i < 54; ++i)
            cards[temp_cards_index][permutation[i] - 1] = cards[current_cards_index][i];
        current_cards_index = (current_cards_index + 1) % 2;
        temp_cards_index = (temp_cards_index + 1) % 2;
    }

    cout << cards[current_cards_index][0];
    for(int i = 1; i < 54; ++i)
        cout << " " << cards[current_cards_index][i];

    return 0;
}