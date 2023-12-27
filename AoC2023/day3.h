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