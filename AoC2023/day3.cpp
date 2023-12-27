#include "day3.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std;
//count number of separate numbers found in the area
int scan(const string::const_iterator& first, const string::const_iterator& last)
{
	const regex r("\\d+");
	auto result_begin = sregex_iterator(first, last, r);
	auto result_end = sregex_iterator();
	return distance(result_begin, result_end);
}

string::const_iterator get_next_digit(const string::const_iterator& first, const string::const_iterator& last)
{
	auto search = [](const char c) {return c >= '0' && c <= '9'; };
	return find_if(first, last, search);
}
string::const_iterator get_next_non_digit(const string::const_iterator& first, const string::const_iterator& last)
{
	auto search = [](const char c) {return c < '0' || c > '9'; };
	return find_if(first, last, search);
}
string::const_iterator get_next_star(const string::const_iterator& first, const string::const_iterator& last)
{
	auto search = [](const char c) {return c == '*'; };
	return find_if(first, last, search);
}

tuple<int, string::const_iterator> get_int_next_to(const int index, const string& line)
{
	auto first = get_next_digit(begin(line), end(line));
	string::const_iterator last;
	auto found = false;
	//while !found
		//answer, start, length = get_next_int(begin(line)+start,end(line))
		//if(answer<0) break;
		//if(answer>0 && start >= index-1 && start + length <= index+1) ++found;
		//start += length;
	//return answer, begin(line)+start;
	auto end_int = false;
	while(first!=end(line) && !end_int)
	{
		int diff = distance(begin(line),end(line));
		if (diff >= index - 1 && diff <= index + 1)found = true;

	}
}

tuple<int,int,int> get_next_int(){}

int get_power(int index, string before, string line, string after)
{
	auto is_digit = [](const char c) {return c >= '0' && c <= '9'; };
	for (int i = 0; i < 2; ++i)
	{
		auto found = 0;
		auto first_b = begin(before);
		auto first_l = begin(line);
		auto first_a = begin(after);
		while(found<2)
		{
			//for each line
			//get the pointer to the next digit
			//until/unless we hit the end:
				//if this digit touches the given gear, count it as found
				//
			first_b = find_if(first_b, end(before), is_digit);
			while (first_b != end(before))
			{
				if (is_digit(*first_b))
				{
int diff = distance(begin(before), first_b);
				if (diff >= index - 1 && diff < +index + 1)++found;
					++first_b;
				}
				else { break; }
				
			}

			first_l = find_if(first_l, end(line), is_digit);
			while (first_l != end(line))
			{
				if (distance(first_l, first_l) == index)++found;
				if (is_digit(*first_l))++first_l;
			}

			first_a = find_if(first_a, end(after), is_digit);
			while (first_a != end(after))
			{
				if (distance(first_a, first_a) == index)++found;
				if (is_digit(*first_a))++first_a;
			}
		}
		
	}
}

string get_padded_string(const string& str)
{
	return "." + str + ".";
}

bool is_gear(const string::const_iterator& before, const string::const_iterator& star,
             const string::const_iterator& after)
{
	int i = 0;
	i += scan(before - 1, before + 1);
	i += scan(star - 1, star + 1);
	i += scan(after - 1, after + 1);
	return i==2;
}

int sum_line(const string& line_before, const string& str, const string& line_after)
{
	const auto p_string = get_padded_string(str);
	const auto p_before = get_padded_string(line_before);
	const auto p_after = get_padded_string(line_after);
	const auto start_p_before = begin(p_before);
	const auto start_p_after = begin(p_after);

	int sum = 0;
	auto star = get_next_star(begin(p_string), end(p_string));
	while (star != end(p_string))
	{
		const auto offset = distance(cbegin(p_string), star);
		auto before = start_p_before + offset;
		auto after = start_p_after + offset;
		if (is_gear(before, star, after))
		{
			sum += stoi(string(star, star));
		}
		star = get_next_star(star, end(p_string));
	}
	cout << endl << line_before << endl << str << endl << line_after << endl << "Sum: " << sum << endl;
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
