#include <stdio.h>
#include <string.h>
#include <vector>

int char_to_index(char c)
{
    if(c == '_') return 36;
    return '0' <= c && c <= '9' ? c - '0' : c - 'A' + 10; 
}

void str_up(char s[])
{
    for(int i = 0; i < strlen(s); ++i)
    {
        if('a' <= s[i] && s[i] <= s[i]) s[i] += 'A' - 'a';
    }
}

int main()
{
    char supposed_type[81], actually_type[81];

    char all_char[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";                  
    bool is_supposed[37] = {false};               // 预期输入字符集合，字符all_char[i]是否预期键入
    bool is_type_out[37] = {false};               // 实际输入字符集合，字符all_char[i]是否实际打出
    std::vector<int> supposed_order_index;        // 字符all_char[supposed_order_index[i]]为预期键入字符,i以预期键入顺序排序
    supposed_order_index.reserve(37);             // 容量设为36;

    scanf("%s%s", supposed_type, actually_type);
    str_up(supposed_type);
    str_up(actually_type);
    for(int i = 0; i < strlen(supposed_type); ++i)
    {
        int index = char_to_index(supposed_type[i]);
        if(!is_supposed[index])
        {
            supposed_order_index.push_back(index);
            is_supposed[index] = true;
        }
    }
    for(int i = 0; i < strlen(actually_type); ++i)
    {
        is_type_out[char_to_index(actually_type[i])] = true;
    }
    for(auto iter = supposed_order_index.begin(); iter != supposed_order_index.end(); ++iter)
    {
        if(!is_type_out[*iter])
            printf("%c", all_char[*iter]);
    }
    return 0;
}


