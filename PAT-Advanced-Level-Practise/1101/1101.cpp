#include <iostream>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <cassert>

using namespace std;

int main() {
	int n;
	cin >> n;
	assert(n > 0);
	list<int> numbers;
	for (int i = 0; i < n; ++i) {
		int number;
		scanf("%d", &number);
		assert(number > 0);
		numbers.push_back(number);
	}
	int max = 0;
	for (auto it = numbers.begin(); it != numbers.end(); ) {
		if (*it > max) {
			max = *it; 
			++it;
		}
		else {
			list<int>::reverse_iterator r_it(it);
			while (r_it != numbers.rend() && *r_it > *it) {
				r_it = list<int>::reverse_iterator(numbers.erase((++r_it).base()));
			}
			it = numbers.erase(it);
		}
	}
	cout << numbers.size() << endl;
	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		if (it == numbers.begin()) {
			printf("%d", *it);
		}
		else {
			printf(" %d", *it);
		}
	}
	cout << endl;
	return 0;
}