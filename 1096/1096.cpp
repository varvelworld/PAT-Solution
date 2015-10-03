#include <cstdio>
#include <cstdlib>
#include <list>
#include <cmath>
#include <cassert>

using namespace std;

int main() {
	long n;
	long sqrt_n;
	scanf("%ld", &n);
	sqrt_n = sqrt(n);
	list<long> longest_factors;
	for (long i = 2; i <= sqrt_n; ++i) {
		if (n % i == 0) {
			list<long> factors;
			factors.push_back(i);
			long product = i;
			for (long j = i + 1; (product * j) <= n; ++j) {
				if (n % (product * j) == 0) {
					factors.push_back(j);
					product *= j;
				}
				else {
					break;
				}
			}
			if (factors.size() > longest_factors.size()) {
				longest_factors = factors;
			}
		}
	}
	if (longest_factors.empty() && n != 1) {
		longest_factors.push_back(n);
	}
	printf("%d\n", longest_factors.size());
	long assert_p = 1;
	for (auto it = longest_factors.begin(); it != longest_factors.end(); ++it) {
		if (it == longest_factors.begin()) {
			printf("%d", *it);
		}
		else {
			printf("*%d", *it);
		}
		assert_p *= *it;
	}
	return 0;
}