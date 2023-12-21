#include "day2.h"

#include <fstream>
#include <iostream>
#include <map>
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
};

static bool is_possible(const game& game, const subset& actual)
{
	for(auto set : game.subsets)
	{
		for(const auto& color : actual.cubes)
		{
			auto key = color.first;
			const auto max = color.second;
			const auto game_num = set.cubes[key];
			if (game_num > max)return false;
		}
	}
	return true;
}



void day2::run()
{
	int sum = 0;
	vector<game> games;
	std::ifstream file("day2_input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			games.emplace_back(line);
		}
	}
	file.close();
	int i = 1;
	for(const auto& game : games)
	{
		if(is_possible(game, subset("12 red cubes, 13 green cubes, and 14 blue cubes")))
		{
			sum += i;
		}
		++i;
	}
	std::cout << sum;
}