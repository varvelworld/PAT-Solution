#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> largest_factors;
int sum_of_largest_factors = 0;

void fun(int n, int k, int p, vector<int> factors, vector<int> items, int sum_of_items) {
	if (factors.size() == k) {
		// 递归出口
		if (sum_of_items == n) {
			int sum_of_factors = 0;
			for (auto it = factors.begin(); it != factors.end(); ++it) {
				sum_of_factors += *it;
			}
			if (sum_of_factors >= sum_of_largest_factors) {
				sum_of_largest_factors = sum_of_factors;
				largest_factors = factors;
			}
		}
		return;
	}
	else {
		int factor = 1;
		int item = 1;
		int sum = sum_of_items + item;
		int cur = factors.size();
		while (sum + 1 * (k - cur - 1) <= n && (cur == 0 || factors[cur - 1] >= factor)) {
			int check_sum = sum_of_items + item * (k - cur);
			if(check_sum > n) // 关键在剪枝
			{
				vector<int> factors_next = factors;
				vector<int> items_next = items;
				factors_next.push_back(factor);
				items_next.push_back(item);
				fun(n, k, p, factors_next, items_next, sum);
			}
			else if(check_sum == n) {
				vector<int> factors_next = factors;
				vector<int> items_next = items;
				while (factors_next.size() < k) {
					factors_next.push_back(factor);
					items_next.push_back(item);
				}
				fun(n, k, p, factors_next, items_next, check_sum);
			}
			++factor;
			item = pow(factor, p);
			sum = sum_of_items + item;
		}
	}
}

int main() {
	int n, k, p;
	vector<int> factors;
	vector<int> items;
	cin >> n >> k >> p;
	fun(n, k, p, factors, items, 0);
	if (sum_of_largest_factors > 0) {
		cout << n << " = ";
		for (auto it = largest_factors.begin(); it!= largest_factors.end(); ++it) {
			if (it == largest_factors.begin()) {
				cout << *it << "^" << p;
			}
			else {
				cout << " + " << *it << "^" << p;
			}
		}
		cout << endl;
	}
	else {
		cout << "Impossible" << endl;
	}
	return 0;
}