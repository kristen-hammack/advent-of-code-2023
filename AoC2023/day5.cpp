#include "day5.h"
#include "day3.h"

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;


class map_line
{
public:
	long long source_start;
	long long destination_start;
	long long range;
	explicit map_line(string line)
	{
		int int_start, length;
		auto first = begin(line);
		const auto last = end(line);
		tie(destination_start, int_start, length) = get_next_llong(first, last);
		first += int_start + length;
		tie(source_start, int_start, length) = get_next_llong(first,last);
		first += int_start + length;
		tie(range, int_start, length) = get_next_llong(first,last);
	}

	long long map_to_second(const long long first) const
	{
		if (first >= source_start && source_start + range > first)
		{
			const auto result = destination_start + first - source_start;
			return result;
		}
		return -1;
	}
};

class map
{
public:
	vector<map_line> lines;

	long long map_to_second(const long long first) const
	{
		for (auto line : lines)
		{
			const auto result = line.map_to_second(first);
			if(result<0) continue;
			return result;
		}
		return first;
	}
};



void day5::run()
{
	long long lowest = -1;

	ifstream file("day5_input.txt");
	if (file.is_open())
	{
		vector<long long> seeds;
		vector<map> maps;
		string line;
		if (getline(file, line))
		{
			auto first = cbegin(line);
			const auto last = cend(line);
			while(first<last)
			{
				long long result; int start, length;
				tie(result, start, length) = get_next_llong(first, last);
				if (result < 0)break;
				seeds.emplace_back(result);
				first += start + length;
			}
		}
		map m;
		getline(file, line); //throw away blank line
		getline(file, line); //throw away header line
		while (getline(file, line))
		{
			if (line.empty())
			{
				maps.emplace_back(m);
				m = map();
				getline(file, line); //throw away header line
			}
			m.lines.emplace_back(line);
		}
		for (const auto seed : seeds)
		{
			auto answer = seed;
			for (const auto& map : maps)
			{
				answer = map.map_to_second(answer);
			}
			if (lowest == -1)lowest = answer;
			else lowest = min(lowest, answer);
		}
	}
	file.close();

	cout << lowest;
}
