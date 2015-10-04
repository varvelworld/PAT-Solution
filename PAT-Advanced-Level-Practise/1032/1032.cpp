#include <cstdio>
#include <cstdlib>

int mem_next[99999 + 1];
bool mark[99999 + 1];

int main()
{
    int head1, head2;
    int number_of_nodes;
    scanf("%d%d%d", &head1, &head2, &number_of_nodes);
    if(head1 == -1 || head2 == -1)
    {
        printf("-1\n");
    }
    else if(head1 == head2)
    {
        printf("%05d\n", head1);
    }
    else
    {
        for(int i = 0; i < number_of_nodes; ++i)
        {
            int address; char letter[2]; int next;
            scanf("%d%s%d", &address, letter, &next);
            mem_next[address] = next;
        }
        int p = head1;
        while(p != -1)
        {
            mark[p] = true;
            p = mem_next[p];
        }
        p = head2;
        while(p != -1)
        {
            if(mark[p])
            {
                printf("%05d", p);
                return 0;
            }
            p = mem_next[p];
        }
        printf("-1\n");
    }
    return 0;
}