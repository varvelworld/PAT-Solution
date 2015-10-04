#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string scientific_notation;
	cin >> scientific_notation;
	char integer_sign = scientific_notation[0];
	string integer = scientific_notation.substr(1, 1);
	size_t e_pos = scientific_notation.find('E');
	string decimals = scientific_notation.substr(3, e_pos - 3);
	char exp_sign = scientific_notation[e_pos + 1];
	string exp = scientific_notation.substr(e_pos + 1, scientific_notation.size() - e_pos - 1);
	int int_exp = atoi(exp.c_str());
	if(int_exp > 0)
	{
		if(int_exp <= decimals.size())
		{
			integer = integer + decimals.substr(0, int_exp);
			decimals = decimals.substr(int_exp, decimals.size() - int_exp);
		}
		else
		{
			integer = integer + decimals + string(int_exp - decimals.size(), '0');
			decimals = "";
		}
	}
	else if(int_exp < 0)
	{
		decimals = string(-int_exp - 1, '0') + integer + decimals;
		integer = "0";
	}
	cout << (integer_sign == '-' ? "-" : "") << integer << (decimals == "" ? "" : "." + decimals) << endl;
	return 0;
}