#include "day2.h"

#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <vector>
using namespace std;

class subset
{
public:
	map<string,int> cubes;
	subset() = default;

	explicit subset (const string& line)
	{
		const regex r1(R"((\d+)\s+(\w+))");
		sregex_iterator rit(line.begin(), line.end(), r1);
		sregex_iterator rend{};
		while (rit != rend)
		{
			int num = stoi(rit->str(1));
			string key = rit->str(2);
			cubes.insert_or_assign(key, num);
			++rit;
		}
	}
	void add_if_larger(const string& key, int i)
	{
		cubes.try_emplace(key, i);
		if (cubes[key] < i) cubes[key] = i;
	}

};

class game
{
public:
	vector<subset> subsets;
	explicit game(const string& line)
	{
		const regex r1(R"((?:\d+\s+\w+,?\s?)+;?)");
		sregex_iterator rit(line.begin(), line.end(), r1);
		sregex_iterator rend{};
		while (rit != rend)
		{
			subsets.emplace_back(rit->str(0));
			++rit;
		}
	}

	subset min_set() const
	{
		subset min;
		for (const auto& set : subsets)
		{
			for (const auto& color : set.cubes)
			{
				auto key = color.first;
				const auto num = color.second;
				min.add_if_larger(key, num);
			}
		}
		return min;
	}

	int power() const
	{
		auto cubes = min_set().cubes;
		return accumulate(begin(cubes)
			, end(cubes)
			, 1
			, [] (const int value, const map<string, int>::value_type& p)
			{ return value * p.second; }
		);
	}
};




void day2::run()
{
	int sum = 0;
	vector<game> games;
	ifstream file("day2_input.txt");
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			games.emplace_back(line);
		}
	}
	file.close();
	for(const auto& game : games)
	{
		sum += game.power();
	}
	cout << sum;
}