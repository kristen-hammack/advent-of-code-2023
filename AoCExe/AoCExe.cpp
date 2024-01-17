// AoC2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"

int main()
{
	int day;
	cout << "Enter the puzzle to run: ";
	cin >> day;
	switch (day) {
	case 1:
		cout << endl << "Day 1: ";
		day1::run();
		break;
	case 2:
		cout << endl << "Day 2: ";
		day2::run();
		break;
	case 3:
		cout << endl << "Day 3: ";
		day3::run();
		break;
	case 4:
		cout << endl << "Day 4: ";
		day4::run();
		break;
	case 5:cout << endl << "Day 5: ";
		day5::run();
		break;
	default:
		cout << endl << "Current day: ";
		day6::run();
	}
		
	cout << endl;
}
