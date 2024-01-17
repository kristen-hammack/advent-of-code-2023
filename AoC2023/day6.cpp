#include "day6.h"
#include "day3.h"

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;


vector<int> get_ints(const string& line)
{
	vector<int>result;
	auto first = begin(line);
	const auto last = end(line);
	int i, start, length;
	while (first < last)
	{
		tie(i, start, length) = get_next_int(first, last);
		if (i < 0)break;
		result.emplace_back(i);
		first += start + length;
	}
	return result;
}


int get_better_options(const int time, const int distance)
{
	int answer = 0;
	for(int t=0;t<time;t++)
	{
		if (t * (time - t) > distance)++answer;
	}
	return answer;
}

void day6::run()
{
	int sum = 1;
	vector<int> times;
	vector<int> distances;
	ifstream file("day6_input.txt");
	if (file.is_open())
	{
		string line;
		if (getline(file, line)) times = get_ints(line);
		if (getline(file, line)) distances = get_ints(line);
	}
	file.close();
	for (size_t i=0;i<times.size();i++)
	{
		sum *= get_better_options(times[i], distances[i]);
	}

	cout << sum;
}
