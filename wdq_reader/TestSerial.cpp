#include "Serial.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>



TEST(Serial, WDQ_FILE_INPUT) {
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input(path);
	ASSERT_TRUE(input.is_open());

	Serial::Word a = 0;
	input >> a;
	EXPECT_EQ(a, 0x24);
	int b = a & 0b11111;
	EXPECT_EQ(b, 4);
}