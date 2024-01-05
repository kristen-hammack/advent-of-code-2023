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
	int copies;
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
		copies = 1;
	}

	int winnings() const
	{
		int wins = 0;
		for (auto num : actual	)
		{
			if (find(begin(win), end(win), num) != end(win)) ++wins;
		}
		return wins;
	}
private:
	vector<int> win;
	vector<int> actual;
};

void copy_down(vector<card>::iterator first, const vector<card>::iterator& last, const int times,const int copies)
{
	int i = 0;
	while (first != last && i < times)
	{
		first->copies += copies;
		i++;
		++first;
	}
}

void day4::run()
{
	int sum = 0;

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
	for (auto it = begin(cards); it < end(cards); ++it)
	{
		sum += it->copies;
		copy_down(it + 1, end(cards), it->winnings(), it->copies);
	}

	cout << sum;
}
