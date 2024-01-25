#include "day7.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

char get_sortable_char(const char c)
{
	switch (c)
	{
	case 'T':return 'I';
	case 'J':return 'J';
	case 'Q':return 'K';
	case 'K':return 'L';
	case 'A':return 'M';
	default:
		if (c > '1' && c <= '9')return 'H' - ('9' - c);
		return 0;
	}
}

class count_t
{
public:
	char c;
	int num;
};

int get_hand_type(const vector<char>& hand)
{
	char current = ';';
	map<char, int> counts;
	for (auto c : hand)
	{
		if (c == current)
		{
			++counts[c];
			continue;
		}
		counts[c] = 1;
		current = c;
	}

}

void day7::run()
{
	long long sum = 0;
	ifstream file("day7_input.txt");
	if (file.is_open())
	{
		string line;
	}
	file.close();

	cout << sum;
}