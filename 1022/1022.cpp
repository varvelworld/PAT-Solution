#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    multimap<string, string> title_map;
    multimap<string, string> author_map;
    multimap<string, string> key_word_map;
    multimap<string, string> publisher_map;
    multimap<string, string> published_year_map;

    int number_of_books;
    cin >> number_of_books; getchar();
    for(int i = 1; i <= number_of_books; ++i)
    {
        string id;
        string title, author;
        string publisher;
        string published_year;
        cin >> id; getchar();
        getline(cin, title);
        title_map.insert(make_pair(title, id));
        getline(cin, author);
        author_map.insert(make_pair(author, id));
        string key_words_str;
        getline(cin, key_words_str);
        size_t begin_index = 0;
        while(begin_index < key_words_str.size())
        {
            size_t end_index = key_words_str.find(' ', begin_index);
            if(end_index == string::npos)
                end_index = key_words_str.size();
            key_word_map.insert(make_pair(key_words_str.substr(begin_index, end_index - begin_index), id));
            begin_index = end_index + 1;
        }
        getline(cin, publisher);
        publisher_map.insert(make_pair(publisher, id));
        getline(cin, published_year);
        published_year_map.insert(make_pair(published_year, id));
    }
    int number_of_queries;
    cin >> number_of_queries;
    getchar();
    for(int i = 1; i <= number_of_queries; ++i)
    {
        string condition;
        getline(cin, condition);
        string context = condition.substr(3, condition.length());
        pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range;
        switch(condition[0])
        {
        case '1':
            range = title_map.equal_range(context);
            break;
        case '2':
            range = author_map.equal_range(context);
            break;
        case '3':
            range = key_word_map.equal_range(context);
            break;
        case '4':
            range = publisher_map.equal_range(context);
            break;
        case '5':
            range = published_year_map.equal_range(context);
            break;
        }
        cout << condition << endl;
        if(range.first == range.second)
        {
            cout << "Not Found" << endl;
        }
        vector<string> book_ids;
        while(range.first != range.second)
        {
            book_ids.push_back(range.first->second);
            ++range.first;
        }
        sort(book_ids.begin(), book_ids.end());
        for(auto iter = book_ids.begin(); iter != book_ids.end(); ++iter)
            cout << *iter << endl;
    }
    return 0;
}