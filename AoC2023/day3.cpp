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
	auto result_begin = sregex_iterator(first, last+1, r);
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

int get_gear_power(const string& before, const string& star_line, const string& after,	const size_t star_index, string::const_iterator& first)
{
	int gear_power = 0;
	int result;
	int nums_found = 0;
	for (auto line : { before,star_line,after })
	{
		first = begin(line);
		auto last = end(line);
		while (first != last)
		{
			tie(result, first) = get_int_next_to(star_index, first, last);
			if (result >= 0) {
				if (gear_power == 0)
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
			}
			else break;
		}
		if (nums_found > 1)break;
	}
	return gear_power;
}

void day3::run()
{
	int sum = 0;

	const string line1 = ".1....58.."; //0
	const string line2 = ".....+755."; //0
	const string line3 = "...$.*...."; //755*598, is_gear=true;
	const string line4 = ".664.59..."; //
	auto star = get_next_star(begin(line3), end(line3));
	auto star_index = distance(begin(line3), star);
	auto b = is_gear(begin(line2) + star_index, star, begin(line4) + star_index);
	cout << "Star 1 Expected: true; actual: " << (b ? "true" : "false") << endl;
	
	int result, start, length;
	tie(result, start, length) = get_next_int(begin(line4), end(line4));
	cout << "Line 4 first int Expected: 664, 1, 3; actual: " << result << ", " << start << ", " << length << endl;

	tie(result, start, length) = get_next_int(begin(line4) + start + length, end(line4));
	cout << "Line 4 second int Expected: 59, 5, 2; actual: " << result << ", " << start << ", " << length << endl;

	auto first = begin(line1);
	while(first!=end(line1))
	{
		tie(result, start, length) = get_next_int(first, end(line1));
		if (result >= 0) cout << "Found " << result << " at index " << start << " with length " << length << endl;
		else break;
		first += start + length;
		sum += result;
	}

	const int gear_power = get_gear_power(line2, line3, line4, star_index, first);
	cout << "Gear Power: " << gear_power << endl;

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

	//ifstream file("day3_input.txt");
	//if (file.is_open())
	//{
	//	sum = do_work(file);
	//}
	//file.close();
	
	cout << sum;
}
