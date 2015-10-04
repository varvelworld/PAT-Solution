#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Account
{
    char username[11];
    char password[11];
};

int main()
{
    int number_of_accounts;
    cin >> number_of_accounts;
    vector<Account> modified_accouts;
    for(int i = 0; i < number_of_accounts; ++i){
        Account account;
        cin >> account.username >> account.password;
        bool modified = false;
        for(int j = 0; j < strlen(account.password); ++j)
        {
            if(account.password[j] == '1')
            {
                account.password[j] = '@';
                modified = true;
            }
            else if(account.password[j] == '0')
            {
                account.password[j] = '%';
                modified = true;
            }
            else if(account.password[j] == 'l')
            {
                account.password[j] = 'L';
                modified = true;
            }
            else if(account.password[j] == 'O')
            {
                account.password[j] = 'o';
                modified = true;
            }
        }
        if(modified) modified_accouts.push_back(account);
    }
    if(modified_accouts.empty())
    {
        if(number_of_accounts == 1)
            cout << "There is 1 account and no account is modified" << endl;
        else 
            cout << "There are " << number_of_accounts << " accounts and no account is modified" << endl;
    }
    else
    {
        cout << modified_accouts.size() << endl;
        for(auto iter = modified_accouts.begin(); iter != modified_accouts.end(); ++iter)
        {
            cout << iter->username << ' ' << iter->password << endl;
        }
    }
    return 0;
}