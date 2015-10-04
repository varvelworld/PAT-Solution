#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

const int size_of_counts = 10 + 26 + 26;
int counts_shop[size_of_counts];
int counts_eva[size_of_counts];

size_t index_by_char(char c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	else if ('a' <= c && c <= 'z') {
		return 10 + c - 'a';
	}
	else if ('A' <= c && c <= 'Z') {
		return 10 + 26 + c - 'A';
	}
	else {
		assert(false);
		return -1;
	}
}

int main() {
	char shop[1005];
	char eva[1005];
	scanf("%s", shop);
	scanf("%s", eva);
	int len_of_shop = strlen(shop);
	int len_of_eva = strlen(eva);
	for (int i = 0; i < len_of_shop; ++i) {
		char c = shop[i];
		++counts_shop[index_by_char(c)];
	}
	int count_of_missing = 0;
	for (int i = 0; i < len_of_eva; ++i) {
		char c = eva[i];
		if ((--counts_shop[index_by_char(c)]) < 0) {
			++count_of_missing;
		}
	}
	if (count_of_missing > 0) {
		printf("No %d\n", count_of_missing);
	}
	else {
		printf("Yes %d\n", len_of_shop - len_of_eva);
	}
	return 0;
}