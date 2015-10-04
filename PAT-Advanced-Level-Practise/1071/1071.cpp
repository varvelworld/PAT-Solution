#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool is_alphanumerical(char c)
{
    return ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z');
}

int main()
{
    string text;
    getline(cin, text);
    map<string, int> words_count;
    string word;
    int max_word_count = 0;
    string max_word = "";
    for(int i = 0; i <= text.size(); ++i)
    {
        if(i < text.size() && is_alphanumerical(text[i]))
            word += text[i];
        else if(!word.empty())
        {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            auto iter_words_count = words_count.find(word);
            if(iter_words_count == words_count.end())
            {
                words_count.insert(make_pair(word, 1));
                if(1 > max_word_count)
                {
                    max_word = word;
                    max_word_count = 1;
                }
            }
            else
            {
                ++(iter_words_count->second);
                if(iter_words_count->second > max_word_count)
                {
                    max_word = word;
                    max_word_count = iter_words_count->second;
                }
            }
            word = "";
        }
    }
    cout << max_word << " " << max_word_count << endl;
    return 0;
}