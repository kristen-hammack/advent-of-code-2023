// AoC2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"

int main()
{
	std::cout << "Day 1: ";
	day1::run();
	std::cout << std::endl << "Day 2: ";
	day2::run();
	std::cout<< std::endl << "Day 3: ";
	day3::run();
	std::cout<< std::endl << "Day 4: ";
	day4::run();
	std::cout << std::endl;
}