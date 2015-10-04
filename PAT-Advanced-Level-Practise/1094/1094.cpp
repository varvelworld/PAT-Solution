#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

struct Member
{
	vector<int> children;
};

Member members[105];
int counts_members_by_level[105];
int max_level;

void dfs(int root, int level) {
	++counts_members_by_level[level];
	if (level > max_level) {
		max_level = level;
	}
	vector<int> children = members[root].children;
	for (auto iter = children.begin(); iter != children.end(); ++iter) {
		dfs(*iter, level + 1);
	}
}

int main() {
	int number_of_members;
	int number_of_parent;
	scanf("%d%d", &number_of_members, &number_of_parent);
	for (int i = 1; i <= number_of_parent; ++i) {
		int parent;
		int number_of_children;
		scanf("%d%d", &parent, &number_of_children);
		for (int j = 0; j < number_of_children; ++j) {
			int children;
			scanf("%d", &children);
			members[parent].children.push_back(children);
		}
	}
	dfs(1, 1);
	int largest_population_number = 0;
	int level_of_largest_population = 0;
	for (int i = 1; i <= max_level; ++i) {
		if (counts_members_by_level[i] > largest_population_number) {
			largest_population_number = counts_members_by_level[i];
			level_of_largest_population = i;
		}
	}
	printf("%d %d\n", largest_population_number, level_of_largest_population);
	return 0;
}