#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <list>
#include <set>

using namespace std;

struct Record {
	string plate_number;
	string time;
	string status;
};

list<Record> records;
map<string, list<Record>::iterator> cars_to_in_iter_map;
map<string, string> cars_to_in_time;
map<string, string> cars_to_parked_time;


int time_to_seconds(string time) {
	int hour = static_cast<int>(strtol(time.substr(0, 2).c_str(), nullptr, 10));
	int minute = static_cast<int>(strtol(time.substr(3, 5).c_str(), nullptr, 10));
	int second = static_cast<int>(strtol(time.substr(6, 8).c_str(), nullptr, 10));
	int seconds = hour * 60 * 60 + minute * 60 + second;
	return seconds;
}

string seconds_to_time(int seconds) {
	string time;
	int hour = seconds / (60 * 60);
	int minute = seconds % (60 * 60) / 60;
	int second = seconds % 60;
	stringstream ss;
	ss << setw(2) << setfill('0') << hour << ":"
		<< setw(2) << setfill('0') << minute << ":"
		<< setw(2) << setfill('0') << second;
	ss >> time;
	return time;
}

string diff_time(string a, string b) {
	int seconds_a = time_to_seconds(a);
	int seconds_b = time_to_seconds(b);
	int seconds_diff = seconds_a - seconds_b;
	return seconds_to_time(seconds_diff);
}

string add_time(string a, string b) {
	int seconds_a = time_to_seconds(a);
	int seconds_b = time_to_seconds(b);
	int seconds_diff = seconds_a + seconds_b;
	return seconds_to_time(seconds_diff);
}

int main() {
	int number_of_records;
	int number_of_queries;
	cin >> number_of_records >> number_of_queries;
	for (int i = 0; i < number_of_records; ++i) {
		Record record;
		cin >> record.plate_number
			>> record.time
			>> record.status;
		records.push_back(record);
	}
	records.sort([](Record a, Record b) {return a.time < b.time;});
	for (auto record_iter = records.begin(); record_iter != records.end(); ) {
		Record record = *record_iter;
		auto iter = cars_to_in_iter_map.find(record.plate_number);
		if ("in" == record.status) {
			if (iter == cars_to_in_iter_map.end()) {
				cars_to_in_iter_map.insert(make_pair(record.plate_number, record_iter));
				++record_iter;
			}
			else {
				records.erase(iter->second);
				iter->second = record_iter;
				++record_iter;
			}
		}
		else if ("out" == record.status) {
			if (iter != cars_to_in_iter_map.end()) {
				cars_to_in_iter_map.erase(iter);
				++record_iter;
			}
			else {
				record_iter = records.erase(record_iter);
			}
		}
	}
	for (pair<string, list<Record>::iterator> pair : cars_to_in_iter_map) {
		records.erase(pair.second);
	}
	cars_to_in_iter_map.clear();
	assert(!records.empty());
	auto record_iter = records.begin();
	set<string> plate_numbers_of_parked_longest;
	string time_of_parked_longest = "00:00:00";
	for (int i = 0; i < number_of_queries; ++i) {
		string query;
		cin >> query;
		while (record_iter != records.end() && record_iter->time <= query) {
			string plate_number = record_iter->plate_number;
			string time = record_iter->time;
			string status = record_iter->status;
			if ("in" == status) {
				cars_to_in_time.insert(make_pair(plate_number, time));
			}
			else if ("out" == status) {
				auto cars_to_time_iter = cars_to_in_time.find(plate_number);
				string diff = diff_time(time, cars_to_time_iter->second);
				auto cars_to_parked_time_iter = cars_to_parked_time.find(plate_number);
				string parked_time;
				if (cars_to_parked_time_iter != cars_to_parked_time.end()) {
					parked_time = add_time(diff, cars_to_parked_time_iter->second);
				}
				else {
					parked_time = diff;
				}
				if (parked_time > time_of_parked_longest) {
					plate_numbers_of_parked_longest.clear();
					plate_numbers_of_parked_longest.insert(plate_number);
					time_of_parked_longest = parked_time;
				}
				else if (parked_time == time_of_parked_longest) {
					plate_numbers_of_parked_longest.insert(plate_number);
				}
				cars_to_in_time.erase(cars_to_time_iter);
				cars_to_parked_time[plate_number] = parked_time;
			}
			++record_iter;
		}
		cout << cars_to_in_time.size() << endl;
	}
	// ----原谅我无比丑陋的复制粘贴，做题而已，就酱
	while (record_iter != records.end()) {
		string plate_number = record_iter->plate_number;
		string time = record_iter->time;
		string status = record_iter->status;
		if ("in" == status) {
			cars_to_in_time.insert(make_pair(plate_number, time));
		}
		else if ("out" == status) {
			auto cars_to_time_iter = cars_to_in_time.find(plate_number);
			string diff = diff_time(time, cars_to_time_iter->second);
			auto cars_to_parked_time_iter = cars_to_parked_time.find(plate_number);
			string parked_time;
			if (cars_to_parked_time_iter != cars_to_parked_time.end()) {
				parked_time = add_time(diff, cars_to_parked_time_iter->second);
			}
			else {
				parked_time = diff;
			}
			if (parked_time > time_of_parked_longest) {
				plate_numbers_of_parked_longest.clear();
				plate_numbers_of_parked_longest.insert(plate_number);
				time_of_parked_longest = parked_time;
			}
			else if (parked_time == time_of_parked_longest) {
				plate_numbers_of_parked_longest.insert(plate_number);
			}
			cars_to_in_time.erase(cars_to_time_iter);
			cars_to_parked_time[plate_number] = parked_time;
		}
		++record_iter;
	}
	// ----复制粘贴end
	assert(cars_to_in_time.empty());
	assert(!plate_numbers_of_parked_longest.empty());
	for (auto iter = plate_numbers_of_parked_longest.begin();
		iter != plate_numbers_of_parked_longest.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << time_of_parked_longest;
	return 0;
}