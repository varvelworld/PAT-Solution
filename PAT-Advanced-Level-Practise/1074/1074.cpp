#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>

struct Node
{
	int key;
	int pre;
	int next;
};

Node mem[100000];

int main()
{
	int head;
	int number_of_node, len_sublist;
	scanf("%d%d%d", &head, &number_of_node, &len_sublist);
	for(int i = 0; i < number_of_node; ++i)
	{
		int address;
		scanf("%d", &address);
		scanf("%d", &(mem[address].key));
		scanf("%d", &(mem[address].next));
	}
	int p = head;
	mem[p].pre = -1;
	int l = 1;
	while(p != -1)
	{
		int next = mem[p].next;
		if(next != -1)
			mem[next].pre = p;
		if(l % len_sublist == 0)
		{
			int q = p;
			int sub_head;
			int sub_end = p;
			for(int i = 0; i < len_sublist; ++i)
			{
				std::swap(mem[q].next, mem[q].pre);
				sub_head = q;
				q = mem[q].next;
			}
			std::swap(mem[sub_head].next, mem[sub_end].pre);
			if(q != -1) mem[q].next = sub_end;
			if(next != -1) mem[next].pre = sub_head;
			if(l == len_sublist)
				head = sub_end;
		}
		p = next;
		++l;
	}
	
	// Êä³ö
	p = head;
	int count = 0;
	while(p != -1)
	{
		if(mem[p].next != -1)
			printf("%05d %d %05d\n", p, mem[p].key, mem[p].next);
		else
			printf("%05d %d -1\n", p, mem[p].key);
		//assert(++count <= number_of_node);
		p = mem[p].next;
	}
  	return 0;
}