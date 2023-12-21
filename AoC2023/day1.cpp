#include "day1.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class number
{
public:
	string name;
	int num;
	number(string name, const int num) :name(std::move(name)), num(num) {  }
};


static int get_line_value(const string& str)
{
	auto lnum = number("", 0);
	auto rnum = number("", 0);
	const vector<number> numbers = {
		number("one",1),
		number("two",2),
		number("three",3),
		number("four",4),
		number("five",5),
		number("six",6),
		number("seven",7),
		number("eight",8),
		number("nine",9)
	};
	auto min_index = str.length();
	size_t max_index = 0;
	for (const auto& num : numbers)
	{
		auto lindex = str.find(num.num + '0');
		if (lindex != string::npos && lindex < min_index)
		{
			min_index = lindex;
			lnum = num;
		}
		lindex = str.find(num.name);
		if (lindex != string::npos && lindex < min_index)
		{
			min_index = lindex;
			lnum = num;
		}
		auto rindex = str.rfind(num.num + '0');
		if (rindex != string::npos && rindex > max_index)
		{
			max_index = rindex;
			rnum = num;
		}
		rindex = str.rfind(num.name);
		if (rindex != string::npos && rindex > max_index)
		{
			max_index = rindex;
			rnum = num;
		}
	}
	if (rnum.num == 0)rnum.num = lnum.num;
	return lnum.num * 10 + rnum.num;
}

void day1::run()
{
	int sum = 0;
	std::ifstream file("day1_input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			sum += get_line_value(line);
		}
	}
	file.close();
	std::cout << sum;
}
