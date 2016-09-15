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
	std::array<std::vector<float>,4> samples;
	auto numSamples = cr.GetNumSamples();
	for (int i = 0; i < 4; ++i) samples[i].reserve(numSamples);

	for (int i = 0; i < numSamples; ++i)
		for (int channel = 1; channel <= 4; ++channel)
			samples[channel - 1].push_back(cr.GetOutput(channel, i));

	EXPECT_EQ(73254, samples[0].size());

	std::array<float, 4> mins, maxes;

	for (int channel = 1; channel <= 4; ++channel)
	{
		auto result = std::minmax_element(samples[channel - 1].begin(), samples[channel - 1].end());
		mins[channel - 1] = *result.first;
		maxes[channel - 1] = *result.second;
	}

	EXPECT_LT(-1.0, mins[0]);
	EXPECT_LT(-2.0, mins[1]);
	EXPECT_LT(-750.0, mins[2]);
	EXPECT_LT(-2.0, mins[3]);

	EXPECT_GT(10.0, maxes[0]);
	EXPECT_GT(10.0, maxes[1]);
	EXPECT_GT(750.0, maxes[2]);
	EXPECT_GT(10.0, maxes[3]);
}

/*
TEST(read_over_network, large_file)
{
	std::cout << "Begining network tests...\n";

	const char* path = R"(\\NVMG-PC\Users\NVMG\Desktop\Guardian IGU Tests\GD13\GD13 Test 2  85C 10-Mar-2016.WDQ)";
	std::ifstream input{ path , std::ifstream::in | std::ifstream::binary };
	input.exceptions(std::ios::badbit | std::ios::eofbit);
	ASSERT_TRUE(input.is_open());

	CODAS_Reader cr{ input };

	const auto num_samples = cr.GetNumSamples();
	const auto num_channels = cr.GetNumChannels();
	std::vector<float> data; 
	const int num_samples_to_grab = 10000;
	data.reserve(10000);

	for (int i = 0; i < num_samples_to_grab; ++i)
	{
		int sample = num_samples / num_samples_to_grab;
		std::cout << "getting sample " << i * sample << "\n";
		data.push_back(cr.GetOutput(3, i * sample));
	}

	const char* output_path = R"(../../wdq_reader/wdq_reader/TestData/NetworkOutput.txt)";
	std::ofstream output{ output_path };

	for (auto x : data)
	{
		output << x << "\n";
	}
}*/