#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
	double unit_price;
	vector<Node*> children;
	// ¡„ €…Ã Ù–‘
	int amount_of_product;
};

int main()
{
	int number_of_members;
	double root_unit_price;
	double percentage;
	scanf("%d%lf%lf", &number_of_members, &root_unit_price, &percentage);
	Node *tree = new Node[number_of_members];
	vector<Node*> retailers;
	for(int i = 0; i < number_of_members; ++i)
	{
		int number_of_receiver;
		scanf("%d", &number_of_receiver);
		if(number_of_receiver > 0)
		{
			for(int j = 0; j < number_of_receiver; ++j)
			{
				int receiver;
				scanf("%d", &receiver);
				tree[i].children.push_back(tree + receiver);
			}
		}
		else
		{
			scanf("%d", &(tree[i].amount_of_product));
			retailers.push_back(tree + i);
		}
	}
	queue<Node*> q;
	tree->unit_price = root_unit_price;
	q.push(tree);
	while(!q.empty())
	{
		Node* node = q.front();
		q.pop();
		for(auto iter = node->children.begin(); iter != node->children.end(); ++iter)
		{
			(*iter)->unit_price = node->unit_price * (percentage / 100 + 1);
			q.push(*iter);
		}
	}
	double total_sales = 0;
	for(auto iter = retailers.begin(); iter != retailers.end(); ++iter)
		total_sales += (*iter)->unit_price * (*iter)->amount_of_product;
	printf("%.1lf", total_sales);
	return 0;
}