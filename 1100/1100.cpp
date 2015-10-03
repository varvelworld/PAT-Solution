#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cassert>

using namespace std;

string mars[2][13] = {
	{"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"},
	{"tret", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"}
};

map<string, int> mars_map = { 
	{ "tret", 0 },
	{ "jan", 1 },{ "feb", 2 },{ "mar", 3 },{ "apr", 4 },{ "may", 5},{ "jun", 6 },{ "jly", 7 },{ "aug", 8 },{ "sep", 9 },{ "oct", 10 },{ "nov", 11 },{ "dec", 12 },
	{ "tam", 1 * 13 },{ "hel", 2 * 13 },{ "maa", 3 * 13 },{ "huh", 4 * 13 },{ "tou", 5 * 13 },{ "kes", 6 * 13 },{ "hei", 7 * 13 },{ "elo", 8 * 13 },{ "syy", 9 * 13 },{ "lok", 10 * 13 },{ "mer", 11 * 13 },{ "jou", 12 * 13 }
};

string earth_to_mars(int number) {
	if(number < 13){
		return mars[0][number % 13];
	}
	else if (number % 13 == 0) {
		return mars[1][number / 13];
	}
	else {
		return mars[1][number / 13] + " " + mars[0][number % 13];
	}
}

vector<string> split(string s) {
	stringstream ss;
	vector<string> subs;
	ss << s;
	while (!ss.eof()) {
		string sub;
		ss >> sub;
		subs.push_back(sub);
	}
	assert(subs.size() <= 2);
	return subs;
}

int mars_to_earth(string number) {
	int result = 0;
	for (string n : split(number)) {
		result += mars_map[n];
	}
	return result;
}

int main() {
	string str_n;
	getline(cin, str_n);
	int n;
	n = stoi(str_n);
	for (int i = 0; i < n; ++i) {
		string number;
		getline(cin, number);
		if ('0' <= number[0] && number[0] <= '9') {
			cout << earth_to_mars(stoi(number)) << endl;
		}
		else {
			cout << mars_to_earth(number) << endl;
		}
	}
	return 0;
}