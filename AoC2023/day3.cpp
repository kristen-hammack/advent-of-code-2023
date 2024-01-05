#include "day3.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <tuple>
using namespace std;
//count number of separate numbers found in the area
int scan(const string::const_iterator& first, const string::const_iterator& last)
{
	const regex r("\\d+");
	auto result_begin = sregex_iterator(first, last + 1, r);
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

/// \brief 
/// \param first 
/// \param last 
/// \return tuple(answer, start, length), where answer is the next int,
/// start is the start index of the int, and length is the length of the int in characters.
tuple<int,int,int> get_next_int(const string::const_iterator& first, const string::const_iterator& last)
{
	int answer = -1;
	int length = 0;
	auto is_digit = [](const char c) {return c >= '0' && c <= '9'; };
	auto it = get_next_digit(first, last);
	int start = distance(first, it);
	while(it!=last && is_digit(*it))
	{
		++length;
		++it;
	}
	if (length > 0)answer = stoi(string(first + start, it));

	return make_tuple(answer, start, length);
}

/// \brief 
/// \param first 
/// \param last 
/// \return tuple(answer, start, length), where answer is the next long,
/// start is the start index of the long, and length is the length of the long in characters.
tuple<long long,int,int> get_next_llong(const string::const_iterator& first, const string::const_iterator& last)
{
	long long answer = -1;
	int length = 0;
	auto is_digit = [](const char c) {return c >= '0' && c <= '9'; };
	auto it = get_next_digit(first, last);
	int start = distance(first, it);
	while(it < last && is_digit(*it))
	{
		++length;
		++it;
	}
	if (length > 0)answer = stoll(string(first + start, it));

	return make_tuple(answer, start, length);
}

/// \brief 
/// \param index 
/// \param first 
/// \param last 
/// \return (answer, iterator) where answer is the found int if it exists, or -1 if not; iterator points to the end of the returned int, or last if not found.
tuple<int, string::const_iterator> get_int_next_to(const int index, const string::const_iterator &first, const string::const_iterator &last)
{
	auto found = false;
	int answer = -1;
	int start_index = 0;
	int index_incrememtor = 0;
	int length = 0;
	while(!found)
	{
		tie(answer, index_incrememtor, length) = get_next_int(first + start_index, last);
		start_index += index_incrememtor;
		if (answer < 0)break; //didn't find an int in the specified search area
		if (start_index <= index + 1 && start_index + length > index - 1) found = true;
		start_index += length;
	}

	string::const_iterator it_return;
	if (answer < 0) it_return = last;
	else it_return = first + start_index;
	return make_tuple(answer, it_return);
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

int get_gear_power(const string& before, const string& star_line, const string& after, const int star_index)
{
	int gear_power = 0;
	int result;
	int nums_found = 0;
	for (const auto& line : { before,star_line,after })
	{
		int relative_index = star_index;
		auto first = cbegin(line);
		auto last = cend(line);
		while (first != last && relative_index > -2)
		{
			tie(result, first) = get_int_next_to(relative_index, first, last);
			if (result >= 0) {
				if (nums_found == 0)
				{
					gear_power = result;
					++nums_found;
				}
				else
				{
					gear_power *= result;
					++nums_found;
					break;
				}
				relative_index -= distance(cbegin(line), first);
			}
			else break;
		}
		if (nums_found > 1)break;
	}
	if (nums_found < 2)gear_power = 0;
	return gear_power;
}

int sum_line(const string& line_before, const string& str, const string& line_after)
{
	const auto p_string = get_padded_string(str);
	const auto p_before = get_padded_string(line_before);
	const auto p_after = get_padded_string(line_after);
	const auto start_p_before = begin(p_before);
	const auto start_p_after = begin(p_after);

	int sum = 0;// int gears = 0;
	auto star = get_next_star(begin(p_string), end(p_string));
	while (star != end(p_string))
	{
		const auto offset = distance(cbegin(p_string), star);
		auto before = start_p_before + offset;
		auto after = start_p_after + offset;
		if (is_gear(before, star, after))
		{
			//++gears;
			//cout << endl << line_before << endl << str << endl << line_after << endl << "Gear Power (Gear at " << offset - 1 << "): ";
			const int gear_power = get_gear_power(p_before, p_string, p_after, offset);
			//cout << gear_power << endl;
			sum += gear_power;
		}
		star = get_next_star(star + 1, end(p_string));
	}
	//cout << endl << line_before << endl << str << endl << line_after << endl << "Sum: " << sum << endl;
	//cout << "Gears on line (" << str << "): " << gears << endl;
	return sum;
}

int do_work(ifstream& file)
{
	int sum = 0;
	string line1;
	string line2;
	string line3;
	if (!getline(file, line1)) { return sum; }
	const auto n = line1.length();
	const auto fill = string(n, '.');

	sum = sum_line(fill, fill, line1);

	if (!getline(file, line2)) { return sum; }
	sum += sum_line(fill, line1, line2);

	while (true)
	{
		if (!getline(file, line3)) { return sum + sum_line(line1, line2, fill); }
		sum += sum_line(line1, line2, line3);
		line1 = line2;
		line2 = line3;
	}
}

void day3::run()
{
	int sum = 0;

	ifstream file("day3_input.txt");
	if (file.is_open())
	{
		sum = do_work(file);
	}
	file.close();
	
	cout << sum;
}
