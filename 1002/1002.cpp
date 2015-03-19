#include <iostream>
#include <limits>
#include <stdio.h>
using namespace std;

struct Node
{
    float c;
    int e;
    Node* next;
};

int main()
{
    int k;
    Node* head = new Node(); // 表头
    int size = 0;
    head->e = numeric_limits<double>::max();
    head->next = head;
    int e;
    float c;

    Node* p = head;
    cin >> k;
    for(int i = 0; i < k; i++)
    {
        cin >> e >> c; 
        Node* np = new Node();
        np->e = e;
        np->c = c;
        np->next = p->next;
        p->next = np;
        ++size;
        p = np;
    }

    cin >> k;
    p = head;
    for(int i = 0; i < k; i++)
    {
        cin >> e >> c; 
        while(p->next != head && p->next->e >= e)
        {
            p = p->next;
        }
        if(p->e == e)
        {
            p->c += c;
        }
        else
        {
            Node* np = new Node();
            np->e = e;
            np->c = c;
            np->next = p->next;
            p->next = np;
            ++size;
            p = np;
        }
    }

    p = head;
    while(p->next != head)
    {
        if(p->next->c == 0)
        {
            Node* d = p->next;
            p->next = d->next;
            delete d;
            --size;
        }
        else
        {
            p = p->next;    
        }
    }

    cout << size;
    p = head->next;
    while(p != head)
    {
        printf(" %d %.1lf", p->e, p->c);
        p = p->next;
    }
    cout << endl;
    return 0;
}