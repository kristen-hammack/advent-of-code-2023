#pragma once
#include <fstream>
using namespace std;
class day3
{
public:
	static void run();
};

int scan(const string::const_iterator& first, const string::const_iterator& last);
string::const_iterator get_next_digit(const string::const_iterator& first, const string::const_iterator& last);
string::const_iterator get_next_non_digit(const string::const_iterator& first, const string::const_iterator& last);
string get_padded_string(const string& str);
int sum_line(const string& line_before, const string& str, const string& line_after);
tuple<int, int, int> get_next_int(const string::const_iterator& first, const string::const_iterator& last);
string::const_iterator get_next_star(const string::const_iterator& first, const string::const_iterator& last);
tuple<int, string::const_iterator> get_int_next_to(const int index, const string::const_iterator& first, const string::const_iterator& last);
bool is_gear(const string::const_iterator& before, const string::const_iterator& star, const string::const_iterator& after);
int get_gear_power(const string& before, const string& star_line, const string& after, const int star_index);