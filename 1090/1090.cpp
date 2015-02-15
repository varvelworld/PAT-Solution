#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
	double price;
	vector<Node*> children;
};

int main()
{
	int number_of_members;
	double root_price;
	double percentage;
	scanf("%d%lf%lf", &number_of_members, &root_price, &percentage);
	Node *tree = new Node[number_of_members];
	Node *root;
	for(int i = 0; i < number_of_members; ++i)
	{
		int parent;
		scanf("%d", &parent);
		if(parent == -1)
			root = tree + i;
		else
			tree[parent].children.push_back(tree + i);
	}
	queue<Node*> q;
	root->price = root_price;
	q.push(root);
	double highest_price = root_price;
	int count_highest_price = 1;
	while(!q.empty())
	{
		Node *node = q.front();
		q.pop();
		for(auto iter = node->children.begin(); iter != node->children.end(); ++iter)
		{
			(*iter)->price = node->price * (percentage / 100 + 1);
			if((*iter)->price > highest_price)
			{
				highest_price = (*iter)->price;
				count_highest_price = 1;
			}
			else if((*iter)->price == highest_price)
				++count_highest_price;
			q.push(*iter);
		}
	}
	printf("%.2lf %d\n", highest_price, count_highest_price);
	return 0;
}