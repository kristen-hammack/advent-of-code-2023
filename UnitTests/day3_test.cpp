#include "pch.h"
#include "day3.h"

TEST(scan_should, return_number_of_ints_surrounding_gear) {
	string line = "7*77";
	const auto last = end(line) - 1;
	EXPECT_EQ(2, scan(begin(line), last));

	line = "77.7";
	EXPECT_EQ(2, scan(begin(line), last));

	line = "7777";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "77.7";
	EXPECT_EQ(2, scan(begin(line), last));

	line = "7.77";
	EXPECT_EQ(2, scan(begin(line), last));

	line = "..77";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "77..";
	EXPECT_EQ(1, scan(begin(line), last));

	line = ".77.";
	EXPECT_EQ(1, scan(begin(line), last));

	line = "....";
	EXPECT_EQ(0, scan(begin(line), last));
}

TEST(get_next_int_should, return_next_int)
{
	string line = "77.77..77...77";
	auto first = begin(line);
	const auto last = end(line);
	int i = 0;

	while(first!=last)
	{
		int answer, start, length;
		tie(answer, start, length) = get_next_int(first, last);
		EXPECT_EQ(answer, 77);
		first += start + length;
		++i;
	}
	EXPECT_EQ(i, 4);
}

TEST(get_next_star_should, return_index_of_star_in_line)
{
	const string line = "*1..**.11.*11";

	auto first = cbegin(line);
	auto star_index = get_next_star(first, cend(line));
	auto index = distance(first, star_index);
	EXPECT_EQ(index, 0);

	first = star_index + 1;
	star_index = get_next_star(first, cend(line));
	index = distance(cbegin(line), star_index);
	EXPECT_EQ(index, 4);

	first = star_index + 1;
	star_index = get_next_star(first, cend(line));
	index = distance(cbegin(line), star_index);
	EXPECT_EQ(index, 5);

	first = star_index + 1;
	star_index = get_next_star(first, cend(line));
	index = distance(cbegin(line), star_index);
	EXPECT_EQ(index, 10);
}

TEST(get_next_star_should, return_end_of_line_if_no_star_found)
{
	const string line = "*1.....";

	auto first = cbegin(line);
	auto star_index = get_next_star(first, cend(line));
	EXPECT_EQ(star_index, first);

	first = star_index + 1;
	star_index = get_next_star(first, cend(line));
	EXPECT_EQ(star_index, cend(line));
}

TEST(is_gear_should, return_true_if_2_ints_surround_a_star)
{
	const string line1 = ".*1..";
	const string line2 = ".1.*.";
	const string line3 = ".*1..";
	const string empty = ".....";

	auto star_index = get_next_star(cbegin(line1), cend(line1));
	auto relative_index = distance(cbegin(line1), star_index);
	auto before = cbegin(empty) + relative_index;
	auto after = cbegin(line2) + relative_index;
	auto isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, true);

	star_index = get_next_star(cbegin(line2), cend(line2));
	relative_index = distance(cbegin(line2), star_index);
	before = cbegin(line1) + relative_index;
	after = cbegin(line3) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, true);

	star_index = get_next_star(cbegin(line3), cend(line3));
	relative_index = distance(cbegin(line3), star_index);
	before = cbegin(line2) + relative_index;
	after = cbegin(empty) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, true);
}

TEST(is_gear_should, return_false_if_gt_2_ints_surround_a_star)
{
	const string line1 = "1*1.1";
	const string line2 = ".1.*1";
	const string line3 = "1*1.1";
	const string empty = ".....";

	auto star_index = get_next_star(cbegin(line1), cend(line1));
	auto relative_index = distance(cbegin(line1), star_index);
	auto before = cbegin(empty) + relative_index;
	auto after = cbegin(line2) + relative_index;
	auto isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, false);

	star_index = get_next_star(cbegin(line2), cend(line2));
	relative_index = distance(cbegin(line2), star_index);
	before = cbegin(line1) + relative_index;
	after = cbegin(line3) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, false);

	star_index = get_next_star(cbegin(line3), cend(line3));
	relative_index = distance(cbegin(line3), star_index);
	before = cbegin(line2) + relative_index;
	after = cbegin(empty) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, false);
}

TEST(is_gear_should, return_false_if_lt_2_ints_surround_a_star)
{
	const string line1 = "...*1.*.";
	const string line2 = "..*..1*.";
	const string line3 = ".*.1.*..";
	const string empty = "........";

	//2 stars on line1
	auto star_index = get_next_star(cbegin(line1), cend(line1));
	auto relative_index = distance(cbegin(line1), star_index);
	auto before = cbegin(empty) + relative_index;
	auto after = cbegin(line2) + relative_index;
	auto isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, false);

	star_index = get_next_star(star_index + 1, cend(line1));
	relative_index = distance(cbegin(line1), star_index);
	before = cbegin(empty) + relative_index;
	after = cbegin(line2) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_NE(star_index, cend(line1));
	EXPECT_EQ(isgear, false);

	//2 stars on line2
	star_index = get_next_star(cbegin(line2), cend(line2));
	relative_index = distance(cbegin(line2), star_index);
	before = cbegin(line1) + relative_index;
	after = cbegin(line3) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, false);

	star_index = get_next_star(star_index + 1, cend(line2));
	relative_index = distance(cbegin(line2), star_index);
	before = cbegin(line1) + relative_index;
	after = cbegin(line3) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_NE(star_index, cend(line2));
	EXPECT_EQ(isgear, false);

	//2 stars on line3
	star_index = get_next_star(cbegin(line3), cend(line3));
	relative_index = distance(cbegin(line3), star_index);
	before = cbegin(line2) + relative_index;
	after = cbegin(empty) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_EQ(isgear, false);

	star_index = get_next_star(star_index + 1, cend(line3));
	relative_index = distance(cbegin(line3), star_index);
	before = cbegin(line2) + relative_index;
	after = cbegin(empty) + relative_index;
	isgear = is_gear(before, star_index, after);
	EXPECT_NE(star_index, cend(line3));
	EXPECT_EQ(isgear, false);
}

TEST(get_gear_power_should, multiply_ints_surrounding_gear)
{
	const string line1 = ".*0..3..";
	const string line2 = ".10.*.4.";
	const string line3 = ".*20*5*.";
	const string empty = "........";

	//line1 gear: 0x10=0
	auto star = get_next_star(begin(line1), end(line1));
	auto star_index = distance(begin(line1), star);
	auto power = get_gear_power(empty, line1, line2, star_index);
	EXPECT_EQ(power, 0);

	//line2 gear: 20x3=60
	star = get_next_star(begin(line2), end(line2));
	star_index = distance(begin(line2), star);
	power = get_gear_power(line1, line2, line3, star_index);
	EXPECT_EQ(power, 60);

	//line3 gear1: 20x10=200
	star = get_next_star(begin(line3), end(line3));
	star_index = distance(begin(line3), star);
	power = get_gear_power(line2, line3, empty, star_index);
	EXPECT_EQ(power, 200);

	//line3 gear2: 20x5=100
	star = get_next_star(star + 1, end(line3));
	star_index = distance(begin(line3), star);
	power = get_gear_power(line2, line3, empty, star_index);
	EXPECT_EQ(power, 100);

	//line3 gear3: 5x4=20
	star = get_next_star(star + 1, end(line3));
	star_index = distance(begin(line3), star);
	power = get_gear_power(line2, line3, empty, star_index);
	EXPECT_EQ(power, 20);
}