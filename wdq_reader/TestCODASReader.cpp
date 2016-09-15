#include "CODAS_reader.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(construction, CODAS_Reader)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input{ path };
	ASSERT_TRUE(input.is_open());
	
	CODAS_Reader cr{ input };
}

TEST(num_samples, CODAS_Reader)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input{ path };
	ASSERT_TRUE(input.is_open());

	CODAS_Reader cr{ input };
	EXPECT_EQ(4, cr.GetNumChannels());
	EXPECT_EQ(73254, cr.GetNumSamples());
}

#include <vector>
TEST(get_some_samples, CODAS_Reader)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input{ path };
	ASSERT_TRUE(input.is_open());

	CODAS_Reader cr{ input };
	auto num_channels = cr.GetNumChannels();
	std::vector<int> samples;
	samples.reserve(cr.GetNumSamples());

	for (int i = 0; i < cr.GetNumSamples(); ++i)
		samples.push_back(cr.GetSample(2, i));

	EXPECT_EQ(73254, samples.size());
}

#include <algorithm>
TEST(get_all_samples, CODAS_Reader)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input{ path , std::ifstream::in | std::ifstream::binary };
	input.exceptions(std::ios::badbit | std::ios::eofbit);
	ASSERT_TRUE(input.is_open());

	CODAS_Reader cr{ input };
	auto num_channels = cr.GetNumChannels();
	std::vector<float> samples;
	samples.reserve(cr.GetNumSamples());

	for (int i = 0; i < cr.GetNumSamples(); ++i)
		samples.push_back(cr.GetOutput(3, i));

	EXPECT_EQ(73254, samples.size());
	auto result = std::minmax_element(samples.begin(), samples.end());
	EXPECT_EQ(-32767, *result.first);
	EXPECT_EQ(28502, *result.second);



	const char* output_path{ R"(../../wdq_reader/wdq_reader/TestData/output1.txt)"};
	std::ofstream output{ output_path, std::ofstream::out };
	ASSERT_TRUE(output.is_open());
	for (auto i : samples) output << i << "\n";
	output.close();
}

TEST(get_float_samples, CODAS_Reader)
{
	const char* path = R"(..\..\wdq_reader\wdq_reader\TestData\Eastman 7 Test 1  18-July-2016.WDQ)";
	std::ifstream input{ path };
	ASSERT_TRUE(input.is_open());

	CODAS_Reader cr{ input };
	auto sample = cr.GetSample(1, 0);

	auto result = cr.GetOutput(2, 0);
	EXPECT_NEAR(1.184, result, 0.001);
}