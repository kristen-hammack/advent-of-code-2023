#include "day3.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std;
//adjacent if scan(row-1,row+1,begin(num)-1,end(num)+1) has anything not a digit and not a .
bool scan(const string::const_iterator& first, const string::const_iterator& last)
{
	const regex r("[^\\d\\.]");
	return regex_search(first, last, r);
}

string::const_iterator get_next_digit(const string::const_iterator& first, const string::const_iterator& last)
{
	auto is_digit = [](const char c) {return c >= '0' && c <= '9'; };
	return find_if(first, last, is_digit);
}
string::const_iterator get_next_non_digit(const string::const_iterator& first, const string::const_iterator& last)
{
	auto is_digit = [](const char c) {return c < '0' || c > '9'; };
	return find_if(first, last, is_digit);
}

string get_padded_string(const string& str)
{
	return "." + str + ".";
}

int sum_line(const string& before, const string& str, const string& after)
{
	auto p_string = get_padded_string(str);
	const auto p_before = get_padded_string(before);
	const auto p_after = get_padded_string(after);
	const auto start_p_before = begin(p_before);
	const auto start_p_after = begin(p_after);

	int sum = 0;
	auto first = get_next_digit(begin(p_string), end(p_string));
	while (first != end(p_string))
	{
		auto last = get_next_non_digit(first, end(p_string));
		const auto offset = distance(cbegin(p_string), first);
		const auto len = distance(first, last);
		if (scan(start_p_before + offset-1, start_p_before + offset + len + 1)
			|| scan(first - 1, last + 1)
			|| scan(start_p_after + offset-1, start_p_after + offset + len + 1))
		{
			sum += stoi(string(first, last));
		}
		first = get_next_digit(last, end(p_string));
	}
	//cout << endl << before << endl << str << endl << after << endl << "Sum: " << sum << endl;
	return sum;
}

int do_work(ifstream& file)
{
	int sum = 0;
	string line1;
	string line2;
	string line3;
	if (!getline(file, line1)) { return sum; }
	sum = sum_line(line1, line1, line1);

	if (!getline(file, line2)) { return sum; }
	sum += sum_line(line1, line1, line2);

	while (true)
	{
		if (!getline(file, line3)) { return sum + sum_line(line1, line2, line2); }
		sum += sum_line(line1, line2, line3);
		line1 = line2;
		line2 = line3;
	}
}

void day3::run()
{
	int sum = 0;

	//string line1 = ".1....58.."; //58
	//string line2 = ".....+755."; //813
	//string line3 = "...$.*...."; //813
	//string line4 = ".664.598.."; //2075
	//auto b = scan(begin(line1), end(line1));
	//cout << "Line 1 Expected: false; actual: " << (b ? "true" : "false") << endl;
	//b = scan(begin(line2), end(line2));
	//cout << "Line 2 Expected: false; actual: " << (b ? "true" : "false") << endl;
	//b = scan(begin(line3), end(line3));
	//cout << "Line 3 Expected: true; actual: " << (b ? "true" : "false") << endl;
	//b = scan(begin(line4), end(line4));
	//cout << "Line 4 Expected: true; actual: " << (b ? "true" : "false") << endl;

	//auto digit_begin = get_next_digit(begin(line2), end(line2));
	//auto digit_end = get_next_non_digit(digit_begin, end(line2));
	//string s(digit_begin, digit_end);
	//cout << "Line 2 number Expected: 234; actual: " << s << endl;

	//digit_begin = get_next_digit(begin(line4), end(line4));
	//digit_end = get_next_non_digit(digit_begin, end(line4));
	//s = string(digit_begin, digit_end);
	//cout << "Line 4 number Expected: 1; actual: " << s << endl;

	//sum += sum_line(line1, line1, line1);
	//cout << line1 << endl << line1 << endl << line1 << endl << "Sum: " << sum << endl << endl;

	//sum += sum_line(line1, line1, line2);
	//cout << line1 << endl << line1 << endl << line2 << endl << "Sum: " << sum << endl << endl;

	//sum += sum_line(line1, line2, line3);
	//cout << line1 << endl << line2 << endl << line3 << endl << "Sum: " << sum << endl << endl;

	//sum += sum_line(line2, line3, line4);
	//cout << line2 << endl << line3 << endl << line4 << endl << "Sum: " << sum << endl << endl;

	//sum += sum_line(line3, line4, line4);
	//cout << line3 << endl << line4 << endl << line4 << endl << "Sum: " << sum << endl << endl;

	ifstream file("day3_input.txt");
	if (file.is_open())
	{
		sum = do_work(file);
	}
	file.close();
	
	cout << sum;
}
