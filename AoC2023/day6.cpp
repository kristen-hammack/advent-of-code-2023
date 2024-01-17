#include "day6.h"
#include "day3.h"

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;


vector<long long> get_llongs(const string& line)
{
	vector<long long>result;
	auto first = begin(line);
	const auto last = end(line);
	long long i;
	int start, length;
	while (first < last)
	{
		tie(i, start, length) = get_next_llong(first, last);
		if (i < 0)break;
		result.emplace_back(i);
		first += start + length;
	}
	return result;
}


int get_better_options(const long long time, const long long distance)
{
	int answer = 0;
	for(long long t=0;t<time;t++)
	{
		if (t * (time - t) > distance)++answer;
	}
	return answer;
}

void day6::run()
{
	long long sum = 1;
	vector<long long> times;
	vector<long long> distances;
	ifstream file("day6_input.txt");
	if (file.is_open())
	{
		string line;
		if (getline(file, line)) times = get_llongs(line);
		if (getline(file, line)) distances = get_llongs(line);
	}
	file.close();
	for (size_t i=0;i<times.size();i++)
	{
		sum *= get_better_options(times[i], distances[i]);
	}

	cout << sum;
}
