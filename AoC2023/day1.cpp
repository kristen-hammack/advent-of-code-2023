#include "day1.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

static int get_line_number(const std::string& str)
{
	auto is_num = [](const char c) { return c - '0' >= 0 && c - '0' < 10; };

	const auto char1_ptr = std::find_if(begin(str), end(str), is_num);
	if (char1_ptr == end(str)) return 0;

	const auto char2_ptr = std::find_if(std::rbegin(str), std::rend(str), is_num);
	if (char2_ptr == rend(str)) return 0;

	return (*char1_ptr - '0') * 10 + *char2_ptr - '0';
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
			sum += get_line_number(line);
		}
	}
	file.close();
	std::cout << sum;
}
