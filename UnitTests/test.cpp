#include "pch.h"
#include "day3.h"

TEST(scan_should, return_number_of_ints_surrounding_gear) {
	string line = "7*7";
	const auto last = end(line) - 1;
	EXPECT_EQ(2, scan(begin(line), last));

	line = "7.7";
	EXPECT_EQ(2, scan(begin(line), last));

	line = "777";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "77.";
	EXPECT_EQ(1, scan(begin(line), last));

	line = ".77";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "..7";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "7..";
	EXPECT_EQ(1, scan(begin(line), last));

	line = ".7.";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "...";
	EXPECT_EQ(0, scan(begin(line), last));
}