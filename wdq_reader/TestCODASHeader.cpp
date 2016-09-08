#include "CODAS_header.h"
#include "gtest/gtest.h"
#include <fstream>


TEST(CODAS_header, read_test_file)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input(path);
	ASSERT_TRUE(input.is_open());

	CODAS_header c(input);
	EXPECT_EQ(4, c.get_num_channels());
	EXPECT_EQ(73254, c.get_num_samples());
	EXPECT_NEAR(319.9659, c.get_sample_rate(),0.001);
}

TEST(WaveformChannelInfo, readChannelInfo)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input(path);
	ASSERT_TRUE(input.is_open());

	CODAS_header c(input);
	EXPECT_STREQ("Volt", c.getWaveformChannelInfo(1).getEngineeringUnits());
	EXPECT_STREQ("Volt", c.getWaveformChannelInfo(2).getEngineeringUnits());

}