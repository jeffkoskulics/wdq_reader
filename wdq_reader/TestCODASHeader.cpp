#include "CODAS_header.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(CODAS_header, LastByteOfElement)
{
	ASSERT_EQ(-1, LastByteOfElement[0]);
	ASSERT_EQ(109, LastByteOfElement[33]);
	ASSERT_EQ(-1, LastByteOfElement[34]);
	ASSERT_EQ(-1, LastByteOfElement[35]);
}

TEST(CODAS_header, LastByteOfElement2)
{
	EXPECT_EQ(36, LastByteOfElement.size());
}

TEST(CODAS_header, read_test_file)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input(path);
	ASSERT_TRUE(input.is_open());

	CODAS_header c(input);
	EXPECT_EQ(4, c.get_num_channels());
	EXPECT_EQ(73254, c.get_num_samples());
	EXPECT_DOUBLE_EQ(319.9659, c.get_sample_rate());
}