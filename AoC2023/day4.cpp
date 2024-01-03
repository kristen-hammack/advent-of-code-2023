#include "day4.h"
#include "day3.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <tuple>
using namespace std;


class card
{
public:
	explicit card(const string& str)
	{
		win = {};
		actual = {};
		auto first = begin(str);
		auto last = find(first, end(str), '|');
		int result, start, length;
		tie(result, start, length) = get_next_int(first, last);
		first += start + length + 2;
		while (first < last)
		{
			tie(result, start, length) = get_next_int(first, last);
			if (result < 0)break;
			win.emplace_back(result);
			first += start + length;
		}
		last = end(str);
		while (first < last)
		{
			tie(result, start, length) = get_next_int(first, last);
			if (result < 0)break;
			actual.emplace_back(result);
			first += start + length;
		}
	}

	double winnings() const
	{
		int wins = 0;
		for (auto num : actual	)
		{
			if (find(begin(win), end(win), num) != end(win)) ++wins;
		}
		if (wins == 0)return 0;
		return pow(2, wins - 1);
	}
private:
	vector<int> win;
	vector<int> actual;
};

void day4::run()
{
	double sum = 0;

	ifstream file("day4_input.txt");
	vector<card> cards;
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			cards.emplace_back(line);
		}
	}
	file.close();
	for(const auto& card : cards)
	{
		sum += card.winnings();
	}

	cout << sum;
}
