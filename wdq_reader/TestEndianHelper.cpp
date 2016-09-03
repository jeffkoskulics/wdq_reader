#include "EndianHelper.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

TEST(EndianHelper, IntelIsLittleEndian) {
	EXPECT_TRUE(Serial::isLittleEndian());
}

TEST(EndianHelper, WDQ_FILE_INPUT) {
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	char unformatted[100];
	std::ifstream input(path);
	ASSERT_TRUE(input.is_open());
	input.get(unformatted, 90);
	std::cout << "Raw data looks like this: \n";
	std::cout.flags(std::ios::hex | std::ios::showbase);
	for (int i = 0; i < 10; ++i) std::cout << (0xff & unformatted[i]) << std::endl;
}